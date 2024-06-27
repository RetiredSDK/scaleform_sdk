/**************************************************************************

PublicHeader:   Render
Filename    :   Render_DrawableImage.cpp
Content     :   DrawableImage is a software-accessible render-target image
                virtualization used to implement BitmapData
Created     :   September 2011
Authors     :   Michael Antonov

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "Render/Render_DrawableImage.h"
#include "Render/Render_DrawableImage_Queue.h"
#include "Render/Render_HAL.h"
#include "Kernel/SF_HeapNew.h"
#include "Render/Render_TreeShape.h"
#include "Render/Render_ShapeDataFloatMP.h"

namespace Scaleform { namespace Render {

//--------------------------------------------------------------------
// ***** DrawableImageContext

DrawableImageContext::DrawableImageContext(
    Context* controlContext,
    ThreadCommandQueue* commandQueue,
    const Interfaces& i)
: RContext(0),
  pControlContext(controlContext), pRTCommandQueue(commandQueue),
  IDefaults(i)
{
    RContext = new(RContextBacking) Context(Memory::GetHeapByAddress(getThis()));
    if ( pControlContext )
        pControlContext->AddCaptureNotify(this);
}
DrawableImageContext::~DrawableImageContext()
{
    if (RContext)
    {
        RContext->~Context();
        RContext = 0;
    }

    if ( pControlContext )
        pControlContext->RemoveCaptureNotify(this);
    processTreeRootKillList();
}

// ContextCaptureNotify Implementation
void DrawableImageContext::OnCapture()
{
    if (RContext)
        RContext->Capture();

    // DICommandQueue can potentially be removed from the list here.
    Ptr<DICommandQueue> queue = 0;
    if (!QueueList.IsEmpty())
    {
        for (queue = QueueList.GetFirst(); ;)
        {
            DICommandQueue* queueNext = QueueList.GetNext(queue);
            queue->OnCapture();
            if (QueueList.IsNull(queueNext))
                break;
            queue = queueNext;
        }
    }
    processTreeRootKillList();
}
void DrawableImageContext::OnNextCapture(ContextImpl::RenderNotify* notify)
{
    ExecuteNextCapture(notify);

    // DICommandQueue can potentially be removed from the list here.
    for (DICommandQueue* queue = QueueList.GetFirst(); !QueueList.IsNull(queue);)
    {
        DICommandQueue* queueNext = QueueList.GetNext(queue);
        queue->OnNextCapture(notify);
        queue = queueNext;
    }
}

void DrawableImageContext::OnShutdown(bool waitFlag)
{
    // Flush out all of our dependent queues, and remove them.
    while (!QueueList.IsEmpty())
    {
        Ptr<DICommandQueue> queue = QueueList.GetFirst();
        RemoveCaptureNotify(queue);

        if (waitFlag)
        {
            // If we are allowed to wait, let all the currently queued commands execute.
            queue->ExecuteCommandsAndWait();
        }
        else
        {
            // If not, discard all the commands in the queue.
            queue->DiscardCommands();
        }
    }

    pControlContext = 0;
    if (RContext)
    {
        processTreeRootKillList();
        if (waitFlag)
        {
            RContext->~Context();
            RContext = 0;
    }
        else
        {
            RContext->Shutdown(waitFlag);
        }
    }
}

void DrawableImageContext::ExecuteNextCapture(ContextImpl::RenderNotify* notify)
{
    if (RContext)
        RContext->NextCapture(notify);
}

void DrawableImageContext::AddCaptureNotify(DICommandQueue* notify)
{
    Lock::Locker scopeLock(getLock());
    //SF_ASSERT(notify->pDIContext == this);
    QueueList.PushBack(notify);
}

void DrawableImageContext::RemoveCaptureNotify(DICommandQueue* notify)
{
    Lock::Locker scopeLock(getLock());
    //SF_ASSERT(notify->pDIContext == this);
    if (notify->pNext != 0 )
    {
        notify->RemoveNode();
        notify->pNext = notify->pPrev = 0;
    }
}

void DrawableImageContext::processTreeRootKillList()
{
    if (!RContext)
        return;

    Lock::Locker lock(&TreeRootKillListLock);
    for ( UPInt i = 0; i < TreeRootKillList.GetSize(); ++i )
    {
        TreeRootKillList[i]->Release();
    }
    TreeRootKillList.Clear();
}

void DrawableImageContext::AddTreeRootToKillList( TreeRoot* proot )
{
    Lock::Locker lock(&TreeRootKillListLock);
    TreeRootKillList.PushBack(proot);
}

//--------------------------------------------------------------------
// ***** DrawableImage


// Init with regular image
//   - Passed image provides original data
//   - For faster operation, orignalData->GetImageFormatNoConv() should match
//     our format
DrawableImage::DrawableImage(bool transparent,
                             ImageBase* originalData, DrawableImageContext* dicontext) :
    DrawableImageState(0),
    Transparent(transparent),
    pQueue(0),
    pCPUModifiedNext(0),
    pGPUModifiedNext(0),
    pDelegateImage(originalData),
    pContext(dicontext),
    pRT(0),
    pFence(0)

{
    initialize(originalData->GetFormat(), originalData->GetSize(), dicontext);
}

// Flash only supports one format with alpha/not.
DrawableImage::DrawableImage(ImageFormat format, ImageSize size, bool transparent,
                             Color fillColor, DrawableImageContext* dicontext) :
    DrawableImageState(0),
    Transparent(transparent),
    pQueue(0),
    pCPUModifiedNext(0),
    pGPUModifiedNext(0)
{
    initialize(format, size, dicontext);

    // If we don't have an image format with transparency, set the alpha channel to full.
    // On platforms that always store an alpha channel, this will ensure consistent behavior.
    if ( !Transparent )
        fillColor.SetAlpha(0xFF);

    addCommand(DICommand_Clear(this, fillColor));
}

// This thread command is used when a DrawableImage is destroyed on the main thread, and must be unmapped.
class UnmapTextureThreadCommand : public ThreadCommand
{
public:
    UnmapTextureThreadCommand(Texture* ptex) :
        pTexture(ptex) { }

    virtual void Execute()
    {
        if (pTexture)
            pTexture->Unmap();
    }
private:
    Ptr<Texture> pTexture;
};

DrawableImage::~DrawableImage()
{
    // If the image is currently mapped, unmap it. This would cause the destructor for this
    // object to be called again, on another thread, once the unmap command has executed.
    // Instead, artificially increase and decrease refcount, so this doesn't happen. This should
    // be valid, as we know we are in the destructor, refcount should already be zero.
    if (isMapped())
    {
        Interfaces rifs;
        pContext->GetRenderInterfacesRT(&rifs);
        if ( rifs.RenderThreadID == GetCurrentThreadId() )
        {
            // If we are in the RT, we can unmap immediately. Because we are being destroyed,
            // we know that there should be no commands in our queue that reference us.
            unmapTextureRT();
        }
        else
        {
            // Need to push a thread command to unmap the texture. However, we can't flush the
            // DrawableImage queue now, because we may be in the process of destruction within a Context::Capture(),
            // while simultaneously trying to display the movie, and this would cause a deadlock.
            Ptr<UnmapTextureThreadCommand> pcmd = *SF_NEW UnmapTextureThreadCommand(pTexture);
            pContext->GetQueue()->PushThreadCommand(pcmd);
        }
    }

    {
        // Thread safety may be accomplished in a lighter method.
        Lock::Locker lock(&pQueue->QueueLock);
        RemoveNode(); // Remove from pQueue->ImageList
    }

    // If this DrawableImage has a fence associated with it, we must wait for it to complete. If we do not,
    // the memory for this image will be freed, but the GPU could subsequently write data into the freed memory,
    // thus corrupting some other (likely) texture data.
    if (pFence && pFence->IsPending(FenceType_Fragment))
        pFence->WaitFence(FenceType_Fragment);

    pQueue.Clear();
}

// param rtMap needs to be set properly, and can only be true if this is executing on the RT.
bool DrawableImage::MapImageSource(ImageData* data, ImageBase* i)
{
    // TODOBM: Will we support sub-images for source?

    if (!data || !i)
        return false;

    // Map first image
    if (i->GetImageType() == Image::Type_DrawableImage)
    {
        DrawableImage* pdi = (DrawableImage*)i;
        if (pdi->isMapped() || (pdi->mapTextureRT(true)))
        {
            *data = pdi->getMappedData();
            return true;
        }
        SF_DEBUG_WARNING(1, "DrawableImage::MapImageSource - map source failed");
    }
    else if (i->GetImageType() == Image::Type_RawImage)
    {
        RawImage* image = (RawImage*)i;
        if ((image->GetFormat() == Image_B8G8R8A8) ||
            (image->GetFormat() == Image_R8G8B8A8))
        {
            image->GetImageData(data);
            return true;
        }
        SF_DEBUG_WARNING(1, "DrawableImage::MapImageSource - bad source image format "
            "(can only use B8G8R8A8/R8G8B8A8 formats)");
    }
    return false;
}


// initialize() - shared constructor initalization logic
void DrawableImage::initialize(ImageFormat format, const ImageSize &size,
                               DrawableImageContext* dicontext)
{
    SF_AMP_CODE(ImageId = ImageBase::GetNextImageId();)

    SF_ASSERT(dicontext);
    pContext = dicontext;
    pRT = 0;

	Interfaces rifs;
	pContext->GetRenderInterfacesRT(&rifs);

    // Image_R8G8B8A8 is the preferred format
    SF_ASSERT(pDelegateImage || rifs.pTextureManager->IsDrawableImageFormat(format));

    Format = format;
    ISize = size;

    pCPUModifiedNext = 0;
    pGPUModifiedNext = 0;

    // Only create a new queue if one does not already exist. One could exist, if we had a delegate
    // image, but are being a 'real' DrawableImage. In this case, we want our queue to remain merged
    // with the delegate's.
    if (!pQueue)
    {
        pQueue = *SF_HEAP_AUTO_NEW(this) DICommandQueue(dicontext);
        pQueue->ImageList.PushBack(this);
    }

    // If the delegate image does not exist, create a new texture to hold the data.
    if (!pDelegateImage)
    {
        if (rifs.pTextureManager && rifs.pTextureManager->CanCreateTextureCurrentThread())
        {
            // DrawableImage can't work without a texture
            if (!createTextureFromManager(rifs.pHAL, rifs.pTextureManager))
                return;
        }
        else
        {
            addCommand(DICommand_CreateTexture(this));
        }
    }
    else if (pDelegateImage->GetImageType() == Image::Type_DrawableImage)
    {
        // If we have a delegate that is a DrawableImage, merge our queues together. Note: this should
        // never happen in the render thread.
        SF_DEBUG_ASSERT(GetCurrentThreadId() != rifs.RenderThreadID, "Cannot merge queues on the render thread.");
        mergeQueueWith(pDelegateImage->GetAsImage());
    }
}

void DrawableImage::addToCPUModifiedList()
{
    // Thread safety may be accomplished in a lighter method.
    Lock::Locker lock(&pQueue->QueueLock);

    if (pContext && pContext->GetControlContext())
        pContext->GetControlContext()->SetDIChangesRequired();

    if (!(DrawableImageState&DIState_CPUDirty))
    {
        SF_DEBUG_ASSERT((DrawableImageState&DIState_GPUDirty)==0, "DrawableImage is both CPU and GPU modified.");
        DrawableImageState |= DIState_CPUDirty;
        pCPUModifiedNext = pQueue->pCPUModifiedImageList;
        pQueue->pCPUModifiedImageList = this;
    }
}

void DrawableImage::addToGPUModifiedListRT()
{
    // Thread safety may be accomplished in a lighter method.
    Lock::Locker lock(&pQueue->QueueLock);

    if (pContext && pContext->GetControlContext())
        pContext->GetControlContext()->SetDIChangesRequired();

    if (!(DrawableImageState&DIState_GPUDirty))
    {
        SF_DEBUG_ASSERT((DrawableImageState&DIState_CPUDirty)==0, "DrawableImage is both CPU and GPU modified.");
        DrawableImageState |= DIState_GPUDirty;
        pGPUModifiedNext = pQueue->pGPUModifiedImageList;
        pQueue->pGPUModifiedImageList = this;
    }
}

static UInt32 UpperPowerOfTwo(UInt32 val)
{
	val--;
	val |= val >> 1;
	val |= val >> 2;
	val |= val >> 4;
	val |= val >> 8;
	val |= val >> 16;
	val++;
	return val;
}

bool DrawableImage::createTextureFromManager(HAL* phal, TextureManager* tmanager)
{
    // For image-source initialization, pDelegate image will be valid, so our Decode implementation will
    // be called to obtain the data. Otherwise, we pass the address of this image, as the texture may need
    // to perform operations on it during device reset.
    ImageSize texSize = ImageSize(Alg::Max<unsigned>(1u, ISize.Width), Alg::Max<unsigned>(1u, ISize.Height));

    bool forcePOT = !tmanager->IsNonPow2Supported(tmanager->GetDrawableImageFormat(), ImageUse_RenderTarget|ImageUse_MapRenderThread);
    
    // Drawable images on GLES have problems when rendering to NPOT textures, even if seemingly all requirements are met.
    // So, force DrawableImage targets to be power-of-two.
#if defined(SF_OS_IPHONE) || defined(SF_OS_ANDROID)
    forcePOT = true;
#endif
    
	if(forcePOT)
	{
		texSize.SetWidth(UpperPowerOfTwo(texSize.Width));
		texSize.SetHeight(UpperPowerOfTwo(texSize.Height));
	}

	Texture* texture =
        tmanager->CreateTexture(Format, 1, texSize,
                                ImageUse_RenderTarget|ImageUse_MapRenderThread,
                                pDelegateImage ? pDelegateImage.GetPtr() : this);
    if (!texture)
        return false;
    initTexture_NoAddRef(texture);

    // TODOBM: needs depth/stencil?
    pRT = *phal->CreateRenderTarget(texture, false);
    if (!pRT)
        return false;

    return true;
}

Texture* DrawableImage::GetTexture(TextureManager* pmanager)
{
    if (pDelegateImage &&
        (pDelegateImage->GetImageType() != Type_ImageBase &&
         pDelegateImage->GetImageType() != Type_Other))
    {
        // Upcast, but that should be fine, because we have checked GetImageType.
        // All our subclasses should be derived from Image.
        Image* pimage = (Image*)pDelegateImage.GetPtr();
        return pimage->GetTexture(pmanager);
    }
    return pTexture;
}

bool DrawableImage::Decode(ImageData* pdest, CopyScanlineFunc copyScanline, void* arg) const
{
    // Can be called either during initialization or after,
    // in which case it can work through mapping.

    SF_UNUSED3(pdest, copyScanline, arg);
    return false;
}

void DrawableImage::TextureLost(TextureLossReason reason)
{
    if ( reason == TLR_DeviceLost )
    {
        // Clear our render target.
        pRT = 0;
    }
}

bool DrawableImage::mapTextureRT(bool readOnly, bool forceRemap)
{
    // Thread safety may be accomplished in a lighter method.
    Lock::Locker lock(&pQueue->QueueLock);
    SF_ASSERT(!isMapped());

    // If image has a delegate, determine whether it could actually be mapped or not.
    // This only applies in the readOnly case; if it to be written to, it must be converted.
    if (readOnly && MapImageSource(&MappedData, pDelegateImage))
    {
        DrawableImageState |= DIState_MappedRead;
        return isMapped();
    }

    // If we've reached here, it means that we can't map pDeleteImage (if it even exist).
    // If it does exist, we need to convert it into a 'true' BitmapData w/RT.
    if (pDelegateImage)
    {
        if (!ensureRenderableRT())
            return false;
    }


    // Use the texture to map. This sets both mapped read/write, regardless of the readOnly parameter.
    if (pTexture)
    {
        if (pTexture->Map(&MappedData))
        {
            DrawableImageState |= (DIState_Mapped|DIState_MappedRead);
        }
    }

	if(forceRemap)
	{
		DrawableImageState |= DIState_ForceRemap;
	}

    return isMapped();
}

bool DrawableImage::ensureRenderableRT()
{
    // If we already have a render target, nothing to do.
    if (isRenderableRT())
        return true;

    Interfaces rifs;
    pContext->GetRenderInterfacesRT(&rifs);

    // Clear delegate image, initialize, and copy the contents of the delegate image.
    ImageSize imageSize = ISize;
    Ptr<ImageBase> poldDelegate = pDelegateImage;
    Texture* pdelegateTexture = 0;

    // Case 1: We already have a texture, which means we are recovering from a device reset. Simply recreate RT.
    if (pTexture)
    {
        // TODOBM: needs depth/stencil?
        pRT = *rifs.pHAL->CreateRenderTarget(pTexture, false);
        if (!pRT)
            return false;
    }
    // Case 2: We have a delegate image, and we are being converted into a real target (because the image couldn't
    // be mapped, or because it is now a drawing target).
    else if ( pDelegateImage )
    {
        imageSize = pDelegateImage->GetSize();
        pdelegateTexture = pDelegateImage->GetAsImage()->GetTexture(rifs.pTextureManager);
        pDelegateImage = 0;
        initialize(rifs.pTextureManager->GetDrawableImageFormat(), imageSize, pContext);
    }

    // If the RT wasn't created immediately, then we must fail.
    SF_DEBUG_WARNING(!pRT, "Could not create DrawableImage delegate copy.");
    if (!pRT)
        return false;

    // If we have a delegate texture, or image, do our best to copy the old contents to the new target.
    if ( pdelegateTexture )
    {
        bool beginFrame = (rifs.pHAL->GetHALState() & HAL::HS_InFrame) == 0;
        bool beginScene = (rifs.pHAL->GetHALState() & HAL::HS_InScene) == 0;
        if (beginFrame)
            rifs.pHAL->BeginFrame();
        if (!beginScene)
            rifs.pHAL->EndScene();
        rifs.pHAL->BeginScene();

        rifs.pHAL->PushRenderTarget(RectF(pRT->GetSize()), pRT, HAL::PRT_Resolve);
        Matrix2F mvp = Matrix2F::Scaling(2,-2) * Matrix2F::Translation(-0.5f, -0.5f);
        Matrix2F texgen;
        texgen.AppendScaling((Size<float>)(pRT->GetSize()) / pRT->GetBufferSize());

        // Note: we always overwriteAll (including alpha), even if the image is not transparent. If the
        // delegate was non-transparent, its alpha channel should return full alpha.
        rifs.pHAL->applyBlendMode(Blend_OverwriteAll, true, true);
        rifs.pHAL->DrawableCopyback(pdelegateTexture, mvp, texgen);
        rifs.pHAL->PopRenderTarget(HAL::PRT_Resolve);

        // After we render the delegate image to our new RT, we need to update the staging target as well.
        // Becase we are mapping it immediately, and it will not be updated by the updateCPUModifiedImages.
        updateStagingTargetRT();

        rifs.pHAL->EndScene();
        if (!beginScene)
            rifs.pHAL->BeginScene();
        if (beginFrame)
            rifs.pHAL->EndFrame();
    }
    else if ( poldDelegate )
    {
        if (mapTextureRT(false))
        {
            poldDelegate->Decode(&getMappedData());
            unmapTextureRT();
        }
    }
    return true;
}

void DrawableImage::unmapTextureRT()
{
    // Thread safety may be accomplished in a lighter method.
    Lock::Locker lock(&pQueue->QueueLock);

    if (isMapped() && pTexture)
    {
        pTexture->Unmap();
        DrawableImageState &= ~(DIState_Mapped|DIState_MappedRead);
    }
}

void DrawableImage::updateRenderTargetRT()
{
    if (pTexture)
    {
        unmapTextureRT();

        Interfaces rifs;
        pContext->GetRenderInterfacesRT(&rifs);
        pTexture->UpdateRenderTargetData((Render::RenderTargetData*)pRT->GetRenderTargetData(), rifs.pHAL);
    }
}

void DrawableImage::updateStagingTargetRT()
{
    if ( pTexture )
    {
        Interfaces rifs;
        pContext->GetRenderInterfacesRT(&rifs);

        unmapTextureRT();
        pTexture->UpdateStagingData((Render::RenderTargetData*)pRT->GetRenderTargetData());

        // If the system has a concept of fencing, insert a fence for this DrawableImage (after UpdateStagingData,
        // because on certain platforms, this may cause a resolve, which we need to wait for).
        if (rifs.pHAL->GetRenderSync())
            pFence = rifs.pHAL->GetRenderSync()->InsertFence();

		// Set if the texture needs immediate access after staging update
		if(DrawableImageState & DIState_ForceRemap)
		{
			DrawableImageState &= ~DIState_ForceRemap;
			mapTextureRT(false);
		}
    }
}

// Applies our queue to the 'other' image, which is typically
// a command source.
bool DrawableImage::mergeQueueWith(Image* other)
{
    DrawableImage* p = 0;

    // Lock scope
    {
        // Thread safety may be accomplished in a lighter method.
        Lock::Locker lock(&pQueue->QueueLock);

        if (other->GetImageType() != Image::Type_DrawableImage)
        {
            SF_DEBUG_WARNING(1,"Attempting to merge a DrawableImage with another Image type.");
            return true;
        }

        p = (DrawableImage*)other;
        if (p->pQueue == pQueue)
            return true;
        if (p->pContext != pContext)
        {
            // TBD: Do raw copy through mapping if context doesn't match.
            SF_DEBUG_ASSERT(0, "Merging DrawableImages between contexts is not supported.");
            return false;
        }
    }

    // Flush 'p'.
    // TBD: A more efficient alternative in the future may involve queuing
    // up p's internal queue as to-be-executed.
    p->pQueue->ExecuteCommandsAndWait();

    // Switch the image to use our queue to ensure synchronization
    p->RemoveNode(); // From p->pQueue.ImageList

    // Images should never be GPU modified at this point.
    SF_DEBUG_ASSERT((p->DrawableImageState&DIState_GPUDirty)==0, "Unexpected GPU modified DrawableImage.");

    // Remove the image from the old queue's CPU modified image list
    if (p->DrawableImageState&DIState_CPUDirty)
    {
        if (p == p->pQueue->pCPUModifiedImageList)
            p->pQueue->pCPUModifiedImageList = p->pCPUModifiedNext;
        else
        {
            DrawableImage* pnext = p->pQueue->pCPUModifiedImageList;
            while (p != pnext->pCPUModifiedNext)
                pnext = pnext->pCPUModifiedNext;
            pnext->pCPUModifiedNext = p->pCPUModifiedNext;
        }
    }

    // Lock scope
    {
        Lock::Locker lock(&pQueue->QueueLock);
        p->pQueue = pQueue;
        pQueue->ImageList.PushBack(p);

        // If the image is CPU modified, then add it to the new queue's list.
        if (p->DrawableImageState&DIState_CPUDirty)
        {
            p->DrawableImageState &= ~DIState_CPUDirty;
            p->addToCPUModifiedList();
        }
    }
    return true;
}



template<class C>
void DrawableImage::addCommand(const C& cmd)
{
    if (pContext && pContext->GetControlContext())
        pContext->GetControlContext()->SetDIChangesRequired();

    DISourceImages sources;
    if (cmd.GetSourceImages(&sources))
    {
        if (sources[0] && !mergeQueueWith(sources[0]))
            return;
        if (sources[1] && !mergeQueueWith(sources[1]))
            return;
    }

    pQueue->AddCommand(cmd);

    // If the command requires a return value, wait for it to complete.
    if (cmd.GetRenderCaps() & DICommand::RC_CPU_Return)
        pQueue->ExecuteCommandsAndWait();
}

ImageData& DrawableImage::getMappedData()
{
    SF_ASSERT(isMapped()); 

    // If we are obtaining the mapped data, it means we will be using this DrawableImage as an input
    // or output immediately. If it has a fence pending, we must wait for the GPU to be finished producing
    // these results. Otherwise, we may get intermediate results.
    if (pFence && pFence->IsPending(FenceType_Fragment))
        pFence->WaitFence(FenceType_Fragment);
    pFence = 0;
    return MappedData;
}


// Generates a filtered image from a source. Source can be a DrawableImage, furthermore
// they may refer to the same image, although that's more expensive due to a temp copy.
void DrawableImage::ApplyFilter(DrawableImage* source,
								const Rect<SInt32>& sourceRect, const Point<SInt32>& destPoint,
								Filter* filter)
{
    addCommand(DICommand_ApplyFilter(this, source, sourceRect, destPoint, filter));
}

// Determine what rectangle ApplyFilter would affect.
void DrawableImage::CalcFilterRect(RectF* result,
								   const Rect<SInt32>& sourceRect, Filter* filter)
{
    // NOTE: This does not use a command, because it does not actually access any image data.
    RectF bounds = sourceRect;
    TreeNode::NodeData::expandByFilterBounds(filter, &bounds);
    if ( result )
        *result = bounds;
}

// ColorTransform
void DrawableImage::ColorTransform(const Rect<SInt32>& rect, const Cxform& cxform)
{
    addCommand(DICommand_ColorTransform(this, rect, cxform));
}


void DrawableImage::Compare(DrawableImage* image0, DrawableImage* image1)
{
    addCommand(DICommand_Compare(this, image0, image1));
}



// TBD: Should bitmaps be used for dest ?
void DrawableImage::CopyChannel(DrawableImage* source,
		                        const Rect<SInt32>& sourceRect, const Point<SInt32>& destPoint,
                                ChannelBits sourceChannel, ChannelBits destChannel)
{
    addCommand(
        DICommand_CopyChannel(this, source, sourceRect, destPoint, sourceChannel, destChannel));
}

void DrawableImage::CopyPixels(DrawableImage* source,
                               const Rect<SInt32>& sourceRect, const Point<SInt32>& destPoint,
					           DrawableImage* alphaSource, const Point<SInt32>* alphaPoint,
                               bool mergeAlpha)
{

    // Flash observation:
    //  - Both sourceRect and destPoint can be out of bounds, including negative values.
    //  - Only the relevant part (properly computed) is copied.
    //  - Specifying the alphaSource causes blending
    //  - If alphaSource is specified, only the intersection of the two image bodies is copied
    //    (this is properly adjusted by the alphaPoint)
    addCommand(
        DICommand_CopyPixels(this, source, sourceRect, destPoint, alphaSource, alphaPoint, mergeAlpha));
}


// Draw the render tree
// Does deep tree copy inside for queuing purposes
void DrawableImage::Draw(TreeNode* subtree,
                         const Matrix2F& matrix, const Cxform& cform,
                         BlendMode blendMode, const Rect<SInt32>* clipRect)
{
    if (!pContext || !pContext->RContext)
        return;

    // Clone the tree and apply matrices
    Ptr<TreeRoot> root = *pContext->RContext->CreateEntry<TreeRoot>();
    if (!root)
        return;
    Ptr<TreeNode> childSubtree = *subtree->Clone(pContext->RContext);
    root->Add(childSubtree);

    Rect<SInt32> clip = clipRect ? *clipRect : Rect<SInt32>(GetSize());
    Viewport vp(GetSize(), clip, Viewport::View_IsRenderTexture);

    root->SetViewport(vp);
    root->SetMatrix(matrix);

    // "Subtree" need to be at the origin now, regardless of its position within its parent.
    childSubtree->SetMatrix(Matrix2F::Identity);
    // "Subtree" will become visible, even if it was not visible in the regular context.
    childSubtree->SetVisible(true);
    childSubtree->SetCxform(cform);
    childSubtree->SetBlendMode(blendMode);

    // Will Release during processTreeRootKillList.
    root->AddRef();

    if (pContext->GetControlContext())
        pContext->GetControlContext()->SetDIChangesRequired();
    pContext->OnCapture();

    addCommand(DICommand_Draw(this, root, clipRect));
}


void DrawableImage::Draw(Image* source,
                         const Matrix2F& matrix, const Cxform& cform,
                         BlendMode blendMode, const Rect<SInt32>* clipRect,
                         bool smoothing)
{
    if (!pContext || !pContext->RContext)
        return;

    // Create a tree, with only one shape node.
    Ptr<TreeRoot> root = *pContext->RContext->CreateEntry<TreeRoot>();
    if (!root)
        return;
    Ptr<TreeShape> childSubtree = *pContext->RContext->CreateEntry<TreeShape>();
    root->Add(childSubtree);

    // Create the fill definition for the source image.
    FillStyleType fill;
    fill.Color  = 0;
    fill.pFill  = *SF_NEW ComplexFill;
    fill.pFill->pImage = source;
    // TODOBM: smoothing?
    SF_UNUSED(smoothing);

    // Create a unit square rectangle, the size of the image.
    Ptr<ShapeDataFloatMP> rectData = *SF_NEW ShapeDataFloatMP();
    rectData->AddFillStyle(fill);
    rectData->StartLayer();
    rectData->StartPath(1, 0, 0);
    rectData->RectanglePath(0, 0, (float)source->GetSize().Width, (float)source->GetSize().Height);
    rectData->CountLayers();
    childSubtree->SetShape( rectData );

    Rect<SInt32> clip = clipRect ? *clipRect : Rect<SInt32>(GetSize());
    Viewport vp(GetSize(), clip);

    root->SetViewport(vp);
    root->SetMatrix(matrix);
    childSubtree->SetMatrix(Matrix2F::Identity);
    childSubtree->SetCxform(cform);
    childSubtree->SetBlendMode(blendMode);

    // Will Release during processTreeRootKillList.
    root->AddRef();

    if (pContext->GetControlContext())
        pContext->GetControlContext()->SetDIChangesRequired();
    pContext->OnCapture();

    addCommand(DICommand_Draw(this, root, clipRect));
}


void DrawableImage::FillRect(const Rect<SInt32>& rect, Color color)
{
    // Fail if user mapped
    addCommand(DICommand_FillRect(this, rect, color));
}

void DrawableImage::FloodFill(const Point<SInt32>& pt, Color color)
{
    addCommand(DICommand_FloodFill(this, pt, color));
}

Rect<SInt32> DrawableImage::GetColorBoundsRect(UInt32 mask, UInt32 color, bool findColor)
{
    Rect<SInt32> result;
    DICommand_GetColorBoundsRect cmd(this, mask, color, findColor, &result);
    addCommand(cmd);
    // Command will execute immediately in addCommand, because it specifies RC_CPU_Return.
    SF_DEBUG_ASSERT(cmd.GetCPUCaps() & DICommand::RC_CPU_Return, "Expected to wait for return value.");
    return result;
}

// Get pixel value without alpha. If out of bounds, returns 0.
Color DrawableImage::GetPixel(SInt32 x, SInt32 y)
{
    // Calls GetPixel32 internally, no need for addCommand.
    Color c = GetPixel32(x, y);
    c.SetAlpha(0);
    return c;
}

// Get pixel value with alpha.
Color DrawableImage::GetPixel32(SInt32 x, SInt32 y)
{
    if (((UInt32)x >= ISize.Width) || ((UInt32)y >= ISize.Height) || (x < 0) || (y < 0))
        return 0;

    Color result;
    DICommand_GetPixel32 cmd(this, x, y, &result);
    addCommand(cmd);
    return result;
}

// Returns false in case of bounds error.
bool DrawableImage::GetPixels(DIPixelProvider& provider, const Rect<SInt32>& sourceRect)
{
    // Do a quick-no overlapping test, and see if we can return immediately.
    if (!Rect<SInt32>(Size<SInt32>(ISize.Width, ISize.Height)).Contains(sourceRect))
        return false;

    bool result;
    DICommand_GetPixels cmd(this, sourceRect, provider, &result);
    addCommand(cmd);

    // Command will execute immediately in addCommand, because it specifies RC_CPU_Return.
    SF_DEBUG_ASSERT(cmd.GetCPUCaps() & DICommand::RC_CPU_Return, "Expected to wait for return value.");
    return result;
}

// Computes populations counts of each channels color values (RGBA).
// Receives four pointers of arrays of 256 values.
void DrawableImage::Histogram(Rect<SInt32>* rect, unsigned colors[4][256])
{
    for ( unsigned i = 0; i <4; ++i )
        memset(colors[i], 0, sizeof(colors[i]));

    Rect<SInt32> hrect;
    if ( rect )
        hrect = *rect;
    else
        hrect = Rect<SInt32>(GetSize());

    DICommand_Histogram cmd(this, hrect, (unsigned*)colors);
    addCommand(cmd);

    // Command will execute immediately in addCommand, because it specifies RC_CPU_Return.
    SF_DEBUG_ASSERT(cmd.GetCPUCaps() & DICommand::RC_CPU_Return, "Expected to wait for return value.");
}


bool DrawableImage::HitTest(const Point<SInt32>& firstPoint, Rect<SInt32>& secondImage,
                            unsigned alphaThreshold)
{
    bool result;
    DICommand_HitTest cmd(this, firstPoint, secondImage, alphaThreshold, &result);
    addCommand(cmd);

    // Command will execute immediately in addCommand, because it specifies RC_CPU_Return.
    SF_DEBUG_ASSERT(cmd.GetCPUCaps() & DICommand::RC_CPU_Return, "Expected to wait for return value.");
    return result;
}

bool DrawableImage::HitTest(ImageBase* secondImage,
                            const Point<SInt32>& firstPoint, const Point<SInt32>& secondPoint,
                            unsigned firstThreshold, unsigned secondThreshold)
{
    bool result;
    DICommand_HitTest cmd(this, secondImage, firstPoint, secondPoint, firstThreshold, secondThreshold, &result);
    addCommand(cmd);

    // Command will execute immediately in addCommand, because it specifies RC_CPU_Return.
    SF_DEBUG_ASSERT(cmd.GetCPUCaps() & DICommand::RC_CPU_Return, "Expected to wait for return value.");
    return result;
}

// Merge source image into destination image with per-channel blending.
void DrawableImage::Merge(DrawableImage* source,
                          const Rect<SInt32>& sourceRect, const Point<SInt32>& destPoint,
                          unsigned redMult, unsigned greenMult, unsigned blueMult, unsigned alphaMult)
{
    addCommand(DICommand_Merge(this, source, sourceRect, destPoint, redMult, greenMult, blueMult, alphaMult));
}


// Noise
void DrawableImage::Noise(unsigned randomSeed, unsigned low, unsigned high,
                          unsigned channelMask, bool grayscale)
{
    addCommand(DICommand_Noise(this, randomSeed, low, high, channelMask, grayscale));
}

// PaletteMap
void DrawableImage::PaletteMap(DrawableImage* source,
                               const Rect<SInt32>& sourceRect, const Point<SInt32>& destPoint,
                               UInt32** channels)
{
    addCommand(DICommand_PaletteMap(this, source, sourceRect, destPoint, channels ));
}

// PerlinNoise
void DrawableImage::PerlinNoise(float frequencyX, float frequencyY, unsigned numOctaves, unsigned randomSeed,
                                bool stitch, bool fractal, unsigned channelMask, bool grayScale,
                                float* offsets, unsigned offsetCount)
{
    addCommand(DICommand_PerlinNoise(this, frequencyX, frequencyY, numOctaves, randomSeed,
        stitch, fractal, channelMask, grayScale, offsets, offsetCount));
}

unsigned DrawableImage::PixelDissolve(DrawableImage* source,
                                      const Rect<SInt32>& sourceRect, const Point<SInt32>& destPoint,
                                      unsigned randomSeed, unsigned numPixels, Color fill)
{
    unsigned result;
    DICommand_PixelDissolve cmd(this, source, sourceRect, destPoint, randomSeed, numPixels, fill, &result);
    addCommand(cmd);

    // Command will execute immediately in addCommand, because it specifies RC_CPU_Return.
    SF_DEBUG_ASSERT(cmd.GetCPUCaps() & DICommand::RC_CPU_Return, "Expected to wait for return value.");
    return result;
}

void DrawableImage::Scroll(int x, int y)
{
    addCommand(DICommand_Scroll(this, x, y));
}

void DrawableImage::SetPixel(SInt32 x, SInt32 y, Color c)
{
    if (!Rect<SInt32>(Size<SInt32>(ISize.Width-1, ISize.Height-1)).Contains(x, y))
        return;
    addCommand(DICommand_SetPixel32(this, x, y, c, false));
}

void DrawableImage::SetPixel32(SInt32 x, SInt32 y, Color c)
{
    if (!Rect<SInt32>(Size<SInt32>(ISize.Width-1, ISize.Height-1)).Contains(x, y))
        return;

    addCommand(DICommand_SetPixel32(this, x, y, c, true));
}

bool DrawableImage::SetPixels(const Rect<SInt32>& inputRect, DIPixelProvider& provider)
{
    Rect<SInt32> destRect;
    if (!Rect<SInt32>(Size<SInt32>(ISize.Width, ISize.Height)).IntersectRect(&destRect, inputRect))
        return false;

    bool result;
    DICommand_SetPixels cmd(this, destRect, provider, &result);
    addCommand(cmd);

    // Command will execute immediately in addCommand, because it specifies RC_CPU_Return.
    SF_DEBUG_ASSERT(cmd.GetCPUCaps() & DICommand::RC_CPU_Return, "Expected to wait for return value.");
    return result;
}

// Threshold
void DrawableImage::Threshold(  DrawableImage* source,
                                const Rect<SInt32>& sourceRect, const Point<SInt32>& destPoint,
                                DrawableImage::OperationType op,
                                UInt32 threshold, UInt32 color, UInt32 mask, bool copySource)
{
    addCommand(DICommand_Threshold(this, source, sourceRect, destPoint, op, threshold, color, mask, copySource));
}





}}; // namespace Scaleform::Render

