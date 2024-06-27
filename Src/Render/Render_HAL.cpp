/**************************************************************************

Filename    :   Render_HAL.cpp
Content     :   Non-platform specific HAL implementated
Created     :   
Authors     :   

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "Render_HAL.h"
#include "Kernel/SF_Debug.h"
#include "Render/Render_Bundle.h"
#include "Render/Render_Queue.h"
#include "Render/Render_DrawableImage.h"
#include "Render/Render_DrawableImage_Queue.h"

namespace Scaleform { namespace Render {

MatrixState::MatrixState( HAL* phal ) : UVPOChanged(0), OrientationSet(0), S3DDisplay(StereoCenter), pHAL(phal)
{
    // All platforms (except GL) use this as their 'full viewport' quad. 
    // Note that D3D9 and X360 require a half-pixel offset applied to match pixel centers, but
    // this depends on the size of the target so it can't be done here.
    FullViewportMVP = Matrix2F::Scaling(2,-2) * Matrix2F::Translation(-0.5f, -0.5f);
}

MatrixState::MatrixState() : UVPOChanged(0), OrientationSet(0), S3DDisplay(StereoCenter), pHAL(NULL)
{
    FullViewportMVP = Matrix2F::Scaling(2,-2) * Matrix2F::Translation(-0.5f, -0.5f);
}

void MatrixState::SetUserMatrix(const Matrix2F& user)
{
    UVPOChanged = 1;
    User = user;
    UserView = View2D * (User * Orient2D);
    User3D = User;
    User3D.M[0][3] *= View2D.M[0][0] / User.M[0][0];
    User3D.M[1][3] *= View2D.M[1][1] / User.M[1][1];
}

void MatrixState::SetViewportMatrix(const Matrix2F& vp)
{
    View2D = vp;
    UserView = View2D * (User * Orient2D);
}

Viewport MatrixState::SetOrientation(const Viewport& vp)
{
    OrientationSet = 0;
    UVPOChanged = 1;

    switch (vp.Flags & Viewport::View_Orientation_Mask)
    {
    case Viewport::View_Orientation_Normal:
        Orient2D.SetIdentity();
        Orient3D.SetIdentity();
        break;

    case Viewport::View_Orientation_R90:
    case Viewport::View_Orientation_L90:
        {
            OrientationSet = 1;

            float flipm = ((vp.Flags & Viewport::View_Orientation_Mask) == Viewport::View_Orientation_L90 ? -1.0f : 1.0f);
            Orient2D.SetMatrix(0, -flipm, flipm < 0 ? 0 : (float)vp.BufferWidth,
                               flipm, 0,  flipm < 0 ? (float)vp.BufferHeight : 0);
            Orient3D.M[0][0] = 0;
            Orient3D.M[0][1] = flipm;
            Orient3D.M[1][1] = 0;
            Orient3D.M[1][0] = -flipm;
        }
        break;
    }

    UserView = View2D * (User * Orient2D);

    Viewport viewport;
    PointF tl = Orient2D.Transform(PointF((float)vp.Left, (float)vp.Top));
    PointF br = Orient2D.Transform(PointF(float(vp.Left+vp.Width), float(vp.Top+vp.Height)));
    viewport.Flags = vp.Flags;
    viewport.Left = (int)ceilf(Alg::Min(tl.x, br.x));
    viewport.Top = (int)ceilf(Alg::Min(tl.y, br.y));
    viewport.Width = (int)ceilf(fabsf(tl.x - br.x));
    viewport.Height = (int)ceilf(fabsf(tl.y - br.y));
    if (viewport.Flags & Viewport::View_UseScissorRect)
    {
        PointF sctl = Orient2D.Transform(PointF((float)vp.ScissorLeft, (float)vp.ScissorTop));
        PointF scbr = Orient2D.Transform(PointF(float(vp.ScissorLeft+vp.ScissorWidth),
                                                float(vp.ScissorTop+vp.ScissorHeight)));
        viewport.Flags = vp.Flags;
        viewport.ScissorLeft = (int)ceilf(Alg::Min(sctl.x, scbr.x));
        viewport.ScissorTop = (int)ceilf(Alg::Min(sctl.y, scbr.y));
        viewport.ScissorWidth = (int)ceilf(fabsf(sctl.x - scbr.x));
        viewport.ScissorHeight = (int)ceilf(fabsf(sctl.y - scbr.y));
    }
    viewport.BufferWidth = vp.BufferWidth;
    viewport.BufferHeight = vp.BufferHeight;

    return viewport;
}

void MatrixState::recalculateUVPOC() const
{
    if (UVPOChanged)
    {
        // Recalculated the view compensation matrix.
        if ( ViewRect != ViewRectOriginal && !ViewRectOriginal.IsNull())
        {
            Point<int> dc = ViewRect.Center() - ViewRectOriginal.Center();
            float      dx = ((float)ViewRectOriginal.Width()) / ViewRect.Width();
            float      dy = ((float)ViewRectOriginal.Height()) / ViewRect.Height();
            float      ox = 2.0f * dc.x / ViewRect.Width();
            float      oy = 2.0f * dc.y / ViewRect.Height();
            ViewRectCompensated3D.MultiplyMatrix(Matrix4F::Translation(-ox, oy, 0), Matrix4F::Scaling(dx, dy, 1));
        }
        else
        {
            ViewRectCompensated3D = Matrix4F::Identity;
        }

        const Matrix4F& Projection = updateStereoProjection();
        Matrix4F UO(User3D, ViewRectCompensated3D);
        Matrix4F VRP(Orient3D, Projection);
        UVPO = Matrix4F(Matrix4F(UO, VRP), View3D);
        UVPOChanged = 0;
    }
}

void MatrixState::Copy(MatrixState* outmat, MatrixState* inmat)
{
    outmat->View2D = inmat->View2D;
    outmat->View3D = inmat->View3D;
    outmat->Proj3D = inmat->Proj3D;
    outmat->Proj3DLeft = inmat->Proj3DLeft;
    outmat->Proj3DRight = inmat->Proj3DRight;

    outmat->User = inmat->User;
    outmat->User3D = inmat->User3D;
    outmat->Orient2D = inmat->Orient2D;
    outmat->Orient3D = inmat->Orient3D;

    outmat->ViewRectOriginal = inmat->ViewRectOriginal;
    outmat->ViewRect = inmat->ViewRect;

    outmat->UserView = inmat->UserView;
    outmat->UVPO = inmat->UVPO;

    outmat->ViewRectCompensated3D = inmat->ViewRectCompensated3D; 

    // Always set "change" to be true, in case there are any caching dependencies in the HALs.
    // This will just cause the UVPO to be recalculated anytime it is copied from another source.
    outmat->UVPOChanged = true; 
    outmat->OrientationSet = inmat->OrientationSet;

    outmat->S3DParams = inmat->S3DParams;
    outmat->S3DDisplay = inmat->S3DDisplay;
    
    // Seems a bit squirrelly, but done so that we can have a default constructor for the class
    // in order for RenderTargetEntry to be able to directly instantiate a MatrixState instance.
    outmat->pHAL = inmat->pHAL;
}

void MatrixState::CopyFrom(MatrixState* state)
{
    Copy(this, state);
}

void MatrixState::CopyTo(MatrixState* state)
{
    Copy(state, this);
}

const Matrix4F& MatrixState::updateStereoProjection(float factor) const
{
    if (S3DDisplay != StereoCenter)
    {
        float eyeZ = -View3D.M[2][3];
        if (S3DDisplay == StereoLeft)
        {
            getStereoProjectionMatrix(&Proj3DLeft, NULL, Proj3D, eyeZ, factor);
            return Proj3DLeft;
        }
        else if (S3DDisplay == StereoRight)
        {
            getStereoProjectionMatrix(NULL, &Proj3DRight, Proj3D, eyeZ, factor);
            return Proj3DRight;
        }
    }
    return Proj3D;
}

void Viewport::SetStereoViewport(unsigned display)
{
	switch (Flags & View_Stereo_AnySplit)
	{
	case View_Stereo_SplitV:
		Height = Height >> 1;
		Top = Top >> 1;
		if (display == StereoRight)
			Top += BufferHeight >> 1;
		break;

	case View_Stereo_SplitH:
		Width = Width >> 1;
		Left = Left >> 1;
		if (display == StereoRight)
			Left += BufferWidth >> 1;
		break;
	}
}

//
// Stereo projection matrix is a horizontally offset version of regular mono 
// projection matrix, shifted in X.
//
// Essentially, the camera separation  = interaxial / screen width;  (scaled 
// by a distortion scale factor)
//
void MatrixState::getStereoProjectionMatrix(
                                    Matrix4F *left, 		    // dest perspective matrix ptr for left eye
                                    Matrix4F *right, 	        // dest perspective matrix ptr for right eye
                                    const Matrix4F &original, 	// original (mono) perspective matrix
                                    float screenDist,           // eye distance to screen, eye Z 
                                    float factor)   const

{
    Matrix4F postProjectionMove;
    Matrix4F preProjectionMove;
    Matrix4F tmpMat;
    float postParam, preParam;

    postParam = S3DParams.Distortion * factor * S3DParams.EyeSeparationCm / S3DParams.DisplayWidthCm;
    preParam = - postParam * screenDist * original.M[3][2] / original.M[0][0];
    if (preParam < 0)
        preParam = -preParam;

    if (left)
    {
        postProjectionMove.M[0][3]  = -postParam;
        preProjectionMove.M[0][3] =  preParam;

        tmpMat = original * preProjectionMove;
        *left = postProjectionMove * tmpMat;
    }

    if (right)
    {
        postProjectionMove.M[0][3]  =  postParam;
        preProjectionMove.M[0][3] = -preParam;

        tmpMat = original * preProjectionMove;
        *right = postProjectionMove * tmpMat;
    }
}

Matrix2F& MatrixState::GetFullViewportMatrix()
{
    return FullViewportMVP;
}

const Matrix4F& MatrixState::GetUVP() const
{
    recalculateUVPOC();
    return UVPO;
}

const Matrix4F& MatrixState::GetUVP( const Rect<int> & viewRect ) const
{
    if ( viewRect != ViewRect )
    {
        ViewRect = viewRect;
        UVPOChanged = true;
    }
    recalculateUVPOC();
    return UVPO;
}

//---------------------------------------------------------------------------------------
HAL::HAL(ThreadCommandQueue *commandQueue)  : 
    HALState(0),
    CurrentPass(Display_All),
    VMCFlags(0),
    FillFlags(0),
    RenderThreadID(0),
    pHeap(0),
    pRTCommandQueue(commandQueue),
    pRenderBufferManager(0),
    QueueProcessor(Queue, getThis()),
    MaskStackTop(0),
    CachedFilterIndex(-1),
	CachedFilterPrepIndex(-1),
    NextProfileMode(0)
{ 
    pHeap = Memory::GetGlobalHeap();
    Link_RenderStats(); 
}

bool HAL::initHAL(const HALInitParams& params)
{
    VMCFlags = params.ConfigFlags;
    RenderThreadID = params.RenderThreadId;

    // If no RendeThreadID is supplied, assume that the render thread is the one calling InitHAL.
    if ( RenderThreadID == 0 )
        RenderThreadID = GetCurrentThreadId();

    return Queue.Initialize(params.RenderQueueSize);
}

bool HAL::shutdownHAL()
{
    if (!(HALState & HS_ModeSet))
        return true;
    notifyHandlers(HAL_Shutdown);

    Queue.Shutdown();

    // Remove ModeSet and other state flags.
    HALState = 0;    
    return true;
}

bool HAL::BeginFrame()
{
    GetEvent(Event_Frame).Begin(__FUNCTION__);
    if (!checkState(HS_ModeSet, __FUNCTION__))
        return false;

    if (HALState & HS_ReadyForReset)
        return false;

    HALState |= HS_InFrame;
    GetRQProcessor().BeginFrame();
    GetMeshCache().BeginFrame();
    GetTextureManager()->BeginFrame();

    return true;
}

void HAL::EndFrame()
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_Frame), 0, false);
    if (!checkState(HS_ModeSet|HS_InFrame, __FUNCTION__))
        return;

    RenderBufferManager* prbm = GetRenderBufferManager();
    if ( prbm )
        prbm->EndFrame();
    GetMeshCache().EndFrame();
    GetTextureManager()->EndFrame();
    HALState &= ~HS_InFrame;

}

void HAL::FinishFrame()
{
    // Nothing by default
}

class HALBeginDisplayItem : public RenderQueueItem::Interface
{
public:
    static HALBeginDisplayItem Instance;
    virtual void EmitToHAL(RenderQueueItem&item, RenderQueueProcessor&qp) 
    {
        BeginDisplayData* data = (BeginDisplayData*)item.GetData();
        qp.GetHAL()->beginDisplay(data);
    }
};
class HALEndDisplayItem : public RenderQueueItem::Interface
{
public:
    static HALEndDisplayItem Instance;
    virtual void EmitToHAL(RenderQueueItem&, RenderQueueProcessor&qp) 
    {
        qp.GetHAL()->endDisplay();
    }
};
HALBeginDisplayItem HALBeginDisplayItem::Instance;
HALEndDisplayItem   HALEndDisplayItem::Instance;

void HAL::BeginDisplay(Color backgroundColor, const Viewport& vpin)
{
    if (!checkState(HS_InFrame, __FUNCTION__))
        return;

    BeginDisplayData entry(backgroundColor, vpin);
    BeginDisplayData* data = BeginDisplayDataList.Alloc(entry);

    // If BeginScene has not be called, BeginDisplay cannot be queued, because it is 
    // presumed that there is no matching EndScene call. This would not flush rendering
    // once it is completed, and thus Present would display no content. This is valid
    // in the case of a single movie rendering within a scene. Otherwise, Begin/EndScene
    // should be called.
    if ( !(HALState & HS_InScene) )
        beginDisplay(data);
    else
        Draw(&HALBeginDisplayItem::Instance, data);
}


void HAL::EndDisplay()
{
    // If BeginDisplay called BeginScene, we must call EndDisplay directly (not queued), because
    // otherwise rendering will not be flushed (because EndScene would not be called). This would
    // cause no display if Present were called.
    if (!(HALState & HS_SceneInDisplay))
        Draw(&HALEndDisplayItem::Instance);
    else
    {
        Flush();
        endDisplay();
    }
}


//---------------------------------------------------------------------------------------
void HAL::beginDisplay(BeginDisplayData* data)
{
    GetEvent(Event_Display).Begin(__FUNCTION__);
    if (!checkState(HS_InFrame, __FUNCTION__))
        return;
    HALState |= HS_InDisplay;

    Color backgroundColor = data->BackgroundColor;
    const Viewport& vpin  = data->VP;
    BeginDisplayDataList.Free(data);

    // BeginScene automatically calls BeginScene if necessary.
    if (!(HALState & HS_InScene))
    {
        BeginScene();
        HALState |= HS_SceneInDisplay;
    }

    applyBlendMode(CurrentBlendState);

    beginMaskDisplay();
    Profiler.SetDrawMode(0);

    VP = Matrices->SetOrientation(vpin);
    if (VP.GetClippedRect(&ViewRect))
        HALState |= HS_ViewValid;
    else
        HALState &= ~HS_ViewValid;

    updateViewport();

    // Clear the background with a solid quad, if background has alpha > 0.
    if (backgroundColor.GetAlpha() > 0)
        clearSolidRectangle(Rect<int>(vpin.Width, vpin.Height), backgroundColor);
}

void HAL::endDisplay()
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_Display), 0, false);
    if (!checkState(HS_InDisplay, __FUNCTION__))
        return;    

    endMaskDisplay();
    SF_ASSERT(BlendModeStack.GetSize() == 0);

    if (HALState & HS_SceneInDisplay)
    {
        EndScene();
        HALState &= ~HS_SceneInDisplay;
    }

    // Must clear - but clear after EndScene, because it may do a Flush. Clearing this
    // flag beforehand would cause all the flushed items to fail, because we were not
    // currently in display.
    HALState &= ~HS_InDisplay;
}

void HAL::CalcHWViewMatrix(unsigned vpFlags, Matrix* pmatrix, const Rect<int>& viewRect, int dx, int dy)
{
    float       vpWidth = (float)viewRect.Width();
    float       vpHeight= (float)viewRect.Height();

    float       xhalfPixelAdjust = 0.0f;
    float       yhalfPixelAdjust = 0.0f;
    if (vpFlags & Viewport::View_HalfPixelOffset)
    {
        xhalfPixelAdjust = (viewRect.Width() > 0) ? (1.0f / vpWidth) : 0.0f;
        yhalfPixelAdjust = (viewRect.Height()> 0) ? (1.0f / vpHeight) : 0.0f;
    }

    pmatrix->SetIdentity();
    if (vpFlags & Viewport::View_IsRenderTexture)
    {
        pmatrix->Sx() = 2.0f  / vpWidth;
        pmatrix->Sy() = 2.0f /  vpHeight;
        pmatrix->Tx() = -1.0f - pmatrix->Sx() * ((float)dx) - xhalfPixelAdjust; 
        pmatrix->Ty() = -1.0f - pmatrix->Sy() * ((float)dy) - yhalfPixelAdjust;
    }
    else
    {
        pmatrix->Sx() = 2.0f  / vpWidth;
        pmatrix->Sy() = -2.0f / vpHeight;
        pmatrix->Tx() = -1.0f - pmatrix->Sx() * ((float)dx) - xhalfPixelAdjust; 
        pmatrix->Ty() = 1.0f  - pmatrix->Sy() * ((float)dy) + yhalfPixelAdjust;
    }
}


void HAL::Flush()
{
    GetRQProcessor().Flush();
}

bool HAL::BeginScene()
{
    GetEvent(Event_Scene).Begin(__FUNCTION__);
    if (!checkState(HS_InFrame, __FUNCTION__))
        return false;

    if ( GetTextureManager() )
        GetTextureManager()->BeginScene();

    // Set the blend mode state. If applyBlendMode is called subsequently to BeginScene, 
    // that blend state, instead of the default will be applied.
    CurrentBlendState.Mode     = Blend_None;
    CurrentBlendState.SourceAc = false;
    CurrentBlendState.ForceAc  = false;

    Profiler.SetProfileViews(NextProfileMode);
    HALState |= HS_InScene;
    return true;
}

bool HAL::EndScene()
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_Scene), 0, false);
    if (!checkState(HS_InFrame|HS_InScene, __FUNCTION__))
        return false;

    // Flush all rendering on EndScene.
    Flush();

    if ( GetTextureManager() )
        GetTextureManager()->EndScene();

    // Finally, clear the flag.
    HALState &= ~HS_InScene;
    return true;
}

RenderTarget* HAL::GetDefaultRenderTarget()
{
    if (RenderTargetStack.GetSize() == 0 )
        return 0;
    return RenderTargetStack[0].pRenderTarget;
}

void HAL::destroyRenderBuffers()
{
    RenderTargetStack.Clear();
}

PrimitiveFill*  HAL::CreatePrimitiveFill(const PrimitiveFillData &data)
{
    return SF_HEAP_NEW(pHeap) PrimitiveFill(data);
}

void HAL::checkState_EmitWarnings(unsigned stateFlags, const char* funcName)
{    
    SF_UNUSED2(stateFlags, funcName);
#ifdef SF_BUILD_DEBUG
    // Outputs debug warnings for missing states.
    struct WarnHelper
    {
        unsigned CheckFlags, HALState;
        WarnHelper(unsigned cf, unsigned hs) : CheckFlags(cf), HALState(hs) { }

        bool operator ()(unsigned checkBit, unsigned requiredBits) const
        {
            return (CheckFlags & checkBit) &&
                   ((HALState & (requiredBits | checkBit)) == requiredBits);
        }
    };

    WarnHelper needWarning(stateFlags, HALState);

    // TBD: WE need a better solution then secondary mask for when to NOT display warnings.
    //      Once BeginFrame fails, for example, there is no need to warn on all other calls.
    SF_DEBUG_WARNING1(needWarning(HS_ModeSet, 0),
                      "%s failed - Mode Not Set", funcName);
    SF_DEBUG_WARNING1(needWarning(HS_InFrame, 0),
                      "%s failed - Begin/EndFrame missing/failed.", funcName);
    SF_DEBUG_WARNING1(needWarning(HS_InDisplay, HS_InFrame|HS_ModeSet),
                      "%s failed - Begin/EndDisplay missing/failed.", funcName);
    SF_DEBUG_WARNING1(needWarning(HS_DeviceValid, 0),
                      "%s failed - Device Lost or not valid", funcName);

    SF_DEBUG_WARNING1(needWarning(HS_DrawingMask, HS_InFrame|HS_InDisplay),
                      "%s failed - PushMask_BeginSubmit call missing", funcName);
    SF_DEBUG_WARNING1(needWarning(HS_DrawingFilter, HS_InFrame|HS_InDisplay),
                      "%s failed - PushFilter call missing", funcName);
#endif
}

void HAL::DrawBundleEntries( BundleIterator ibundles, Renderer2DImpl* r2d )
{
    if ( CurrentPass == Display_All && IsPrepassRequired() )
    {
        SetDisplayPass(Display_Prepass);
        DrawBundleEntries(ibundles, r2d);
        SetDisplayPass(Display_Final);
        DrawBundleEntries(ibundles, r2d);
        SetDisplayPass(Display_All);
    }
    else
    {
        switch(CurrentPass)
        {
        case Display_All:
        case Display_Final:
			GetRQProcessor().SetQueueEmitFilter(RenderQueueProcessor::QPF_All);
			GetRQProcessor().SetQueuePrepareFilter(RenderQueueProcessor::QPF_All);
            break;
        case Display_Prepass:
			GetRQProcessor().SetQueueEmitFilter(RenderQueueProcessor::QPF_Filters);
            GetRQProcessor().SetQueuePrepareFilter(RenderQueueProcessor::QPF_Filters);
            break;
        }

        while(ibundles)
        {
            ibundles->DrawBundleEntry(r2d);
            ibundles++;
        }
    }
}

// Draws a RenderQueueItem by placing it into a queue.

void HAL::Draw(const RenderQueueItem& item)
{    
    SF_AMP_SCOPE_RENDER_TIMER(__FUNCTION__, Amp_Profile_Level_Medium);

    // Must be in display, unless this is a queued BeginDisplay render item.
    if (item.GetInterface() != &HALBeginDisplayItem::Instance && 
        !checkState(HS_InDisplay, __FUNCTION__))
        return;

    RenderQueueProcessor& qp = GetRQProcessor();
    RenderQueueItem* pitem = Queue.ReserveHead();
    if (!pitem)
    {
        qp.ProcessQueue(RenderQueueProcessor::QPM_One);
        pitem = Queue.ReserveHead();
        SF_ASSERT(pitem);
    }

    // We can add our primitive.
    // On Consoles, this may end up building up multiple primitives since cache
    // eviction will not rely on lock but will wait instead.
    *pitem = item;    
    Queue.AdvanceHead();

    // Process as many items as possible.
    qp.ProcessQueue(RenderQueueProcessor::QPM_Any);
}

HAL::BlendModeDescriptor HAL::BlendModeTable[Blend_Count] =
{
    { HAL::BlendOp_ADD,         HAL::BlendFactor_SRCALPHA,      HAL::BlendFactor_INVSRCALPHA, HAL::BlendFactor_ONE,       HAL::BlendFactor_INVSRCALPHA  }, // None
    { HAL::BlendOp_ADD,         HAL::BlendFactor_SRCALPHA,      HAL::BlendFactor_INVSRCALPHA, HAL::BlendFactor_ONE,       HAL::BlendFactor_INVSRCALPHA  }, // Normal
    { HAL::BlendOp_ADD,         HAL::BlendFactor_SRCALPHA,      HAL::BlendFactor_INVSRCALPHA, HAL::BlendFactor_ONE,       HAL::BlendFactor_INVSRCALPHA  }, // Layer      // UNSUPPORTED.
                                                                                 
    { HAL::BlendOp_ADD,         HAL::BlendFactor_DESTCOLOR,     HAL::BlendFactor_INVSRCALPHA, HAL::BlendFactor_SRCALPHA,  HAL::BlendFactor_INVSRCALPHA  }, // Multiply
    { HAL::BlendOp_ADD,         HAL::BlendFactor_INVDESTCOLOR,  HAL::BlendFactor_ONE,         HAL::BlendFactor_ONE,       HAL::BlendFactor_INVSRCALPHA  }, // Screen
                                                                                 
    { HAL::BlendOp_MAX,         HAL::BlendFactor_SRCALPHA,      HAL::BlendFactor_ONE,         HAL::BlendFactor_SRCALPHA,  HAL::BlendFactor_ONE          }, // Lighten
    { HAL::BlendOp_MIN,         HAL::BlendFactor_SRCALPHA,      HAL::BlendFactor_ONE,         HAL::BlendFactor_SRCALPHA,  HAL::BlendFactor_ONE          }, // Darken

    { HAL::BlendOp_ADD,         HAL::BlendFactor_SRCALPHA,      HAL::BlendFactor_INVSRCALPHA, HAL::BlendFactor_ONE,       HAL::BlendFactor_INVSRCALPHA  }, // Difference // UNSUPPORTED.
                                                                                 
    { HAL::BlendOp_ADD,         HAL::BlendFactor_SRCALPHA,      HAL::BlendFactor_ONE,         HAL::BlendFactor_ZERO,      HAL::BlendFactor_ONE          }, // Add
    { HAL::BlendOp_REVSUBTRACT, HAL::BlendFactor_SRCALPHA,      HAL::BlendFactor_ONE,         HAL::BlendFactor_ZERO,      HAL::BlendFactor_ONE          }, // Subtract

    { HAL::BlendOp_ADD,         HAL::BlendFactor_INVDESTCOLOR,  HAL::BlendFactor_INVSRCALPHA, HAL::BlendFactor_SRCALPHA,  HAL::BlendFactor_INVSRCALPHA  }, // Invert
                                                                                 
    { HAL::BlendOp_ADD,         HAL::BlendFactor_ZERO,          HAL::BlendFactor_ZERO,        HAL::BlendFactor_ONE,       HAL::BlendFactor_ONE          }, // Alpha     // UNSUPPORTED.
    { HAL::BlendOp_ADD,         HAL::BlendFactor_ZERO,          HAL::BlendFactor_ZERO,        HAL::BlendFactor_ONE,       HAL::BlendFactor_ONE          }, // Erase     // UNSUPPORTED.
    { HAL::BlendOp_ADD,         HAL::BlendFactor_SRCALPHA,      HAL::BlendFactor_INVSRCALPHA, HAL::BlendFactor_ONE,       HAL::BlendFactor_INVSRCALPHA  }, // Overlay   // UNSUPPORTED.
    { HAL::BlendOp_ADD,         HAL::BlendFactor_SRCALPHA,      HAL::BlendFactor_INVSRCALPHA, HAL::BlendFactor_ONE,       HAL::BlendFactor_INVSRCALPHA  }, // Hardlight // UNSUPPORTED.

    // The following are used internally.
    { HAL::BlendOp_ADD,         HAL::BlendFactor_ONE,           HAL::BlendFactor_ZERO,        HAL::BlendFactor_ZERO,      HAL::BlendFactor_ONE          }, // Overwrite - overwrite the destination.
    { HAL::BlendOp_ADD,         HAL::BlendFactor_ONE,           HAL::BlendFactor_ZERO,        HAL::BlendFactor_ONE,       HAL::BlendFactor_ZERO         }, // OverwriteAll - overwrite the destination (including alpha).
    { HAL::BlendOp_ADD,         HAL::BlendFactor_ONE,           HAL::BlendFactor_ONE,         HAL::BlendFactor_ONE,       HAL::BlendFactor_ONE          }, // FullAdditive - add all components together, without multiplication.
};                                           

void HAL::PushBlendMode(BlendMode mode)
{
    if (!checkState(HS_InDisplay, __FUNCTION__))
        return;

    BlendModeStack.PushBack(mode);
    applyBlendMode(mode, false, (HALState& HS_InRenderTarget) != 0 );
}

void HAL::PopBlendMode()
{
    if (!checkState(HS_InDisplay, __FUNCTION__))
        return;

    UPInt stackSize = BlendModeStack.GetSize();
    SF_ASSERT(stackSize != 0);
    BlendModeStack.PopBack();
    applyBlendMode((stackSize>1) ? BlendModeStack[stackSize-2] : Blend_Normal, 
        false, (HALState& HS_InRenderTarget) != 0 );
}

void HAL::applyBlendMode(BlendMode mode, bool sourceAc, bool forceAc)
{
    // TODO: Enable blend mode redudancy checking.
    // Check for redundant setting of blend states.
    //if (CurrentBlendState.Mode == mode &&
    //    CurrentBlendState.SourceAc == sourceAc &&
    //    CurrentBlendState.ForceAc == forceAc )
    //{
    //    return;
    //}

    ScopedRenderEvent GPUEvent(GetEvent(Event_ApplyBlend), __FUNCTION__);

    // Detect invalid blend modes (debug)
    SF_ASSERT(((unsigned) mode) < Blend_Count);
    // For release, just set a default blend mode
    if (((unsigned) mode) >= Blend_Count)
        mode = Blend_None;

    // Check for overriding
    mode = Profiler.GetBlendMode(mode);

    // Multiply requires different fill mode, save it in the HAL's fill flags.
    FillFlags &= ~(FF_BlendMask);
    if ( mode == Blend_Multiply || mode == Blend_Screen )
        FillFlags |= FF_Multiply;
    else if (mode == Blend_Invert)
        FillFlags |= FF_Invert;

    // Apply or remove blending fill flag.
    if (mode > Blend_Normal)
        FillFlags |= FF_Blending;
    else
        FillFlags &= ~FF_Blending;

    // Now actually apply it.
    CurrentBlendState.Mode = mode;
    CurrentBlendState.SourceAc = sourceAc;
    CurrentBlendState.ForceAc = forceAc;
    applyBlendModeImpl(mode, sourceAc, forceAc);
}

void HAL::applyBlendMode(const HALBlendState& state)
{
    applyBlendMode(state.Mode, state.SourceAc, state.ForceAc);
}

void HAL::PrepareFilters(FilterPrimitive* prim)
{
    if (!checkState(HS_InDisplay, __FUNCTION__))
        return;

    // We are drawing a profile mode, which will not use the cached results, and will 
    // not require a change in the queue filtering.
    if ( !Profiler.ShouldDrawMask() || !prim)
        return;

    // If the filter pointer is 0, then we are 'unpreparing'. This happens after the filter
    // and all its contents have been prepared.
    bool unprepare = (prim->GetFilters() == 0);

    // If we are cached in some way (or we are 'unpreparing').
    if ( prim->GetCacheState() != FilterPrimitive::Cache_Uncached || unprepare)
    {
        if ( !unprepare )
        {
            // The filter is being prepared, determine whether the results are cached.
            RenderTarget* results[FilterPrimitive::MaximumCachedResults];
            prim->GetCacheResults(results, FilterPrimitive::MaximumCachedResults);

            // Make sure that the first result (which is always required) is valid, and has the CacheID relating to
            // this FilterPrimitive. If other results exist, make sure that they are valid as well.
            bool validCache = true;
            for ( unsigned cr = 0; cr < FilterPrimitive::MaximumCachedResults; ++cr )
            {
                if ( !results[cr] )
                {
                    validCache = (cr != 0);
                    break;
                }

                if ( results[cr]->GetStatus() == RTS_Lost || results[cr]->GetStatus() == RTS_Unresolved ||
                    results[cr]->GetRenderTargetData()->CacheID != reinterpret_cast<UPInt>(prim) )
                {
                    validCache = false;
                    break;
                }
            }

            // Must increase the prep index always, so we know when to remove the prepare filter.
            CachedFilterPrepIndex++;

            // Cache isn't valid, uncache the results.
            if (!validCache)
            {
                prim->SetCacheResults(FilterPrimitive::Cache_Uncached, 0, 0);
                return;
            }

            // If there are valid cache results, then we must set the queue processor to skip
            // anything in the queue, except other filter prepares. Because the filter is cached,
            // we do not need to prepare any geometry inside it, as it will be contained within 
            // the cached results. 
            if (CachedFilterPrepIndex == 0 )
            {
                for ( unsigned cr = 0; cr < FilterPrimitive::MaximumCachedResults; ++cr )
                {
                    if ( results[cr] )
                        results[cr]->SetInUse(true);
                }
                GetRQProcessor().SetQueuePrepareFilter(RenderQueueProcessor::QPF_Filters);
            }
        }
        else if ( CachedFilterPrepIndex >= 0 )
        {
            // When filters are 'unprepared' we need to set the render queue to continue preparing
            // primitives from that point on. However, if we are in the prepass, make sure it is
            // still only processing filters.
            if (CachedFilterPrepIndex == 0 && CurrentPass != Display_Prepass)
                GetRQProcessor().SetQueuePrepareFilter(RenderQueueProcessor::QPF_All);
            else if (CachedFilterPrepIndex == 0 && CurrentPass == Display_Prepass )
                GetRQProcessor().SetQueuePrepareFilter(RenderQueueProcessor::QPF_Filters);
            --CachedFilterPrepIndex;
        }
    }
    else if (prim->GetCacheState() == FilterPrimitive::Cache_Uncached)
    {
        if (CurrentPass == Display_Prepass)
        {
            // Uncached, and in the prepass, or 'both', need to prepare everything.
            GetRQProcessor().SetQueuePrepareFilter(RenderQueueProcessor::QPF_All);
        }

        // If we're currently within a cached filter, and we hit an uncached filter, we still increase the
        // cached prep index, just so we know where the real cached filter ends.
        if (!unprepare && CachedFilterPrepIndex >= 0)
            CachedFilterPrepIndex++;
    }
}

void HAL::GetStats(Stats* pstats, bool clear)
{
	// Cannot call GetStats within a scene - rendering may not be flushed, primitives
	// will not be drawn, and stats will be inaccurate.
	SF_ASSERT( (HALState & HS_InScene) == 0 );
	*pstats = AccumulatedStats;
	if (clear)
		AccumulatedStats.Clear();
}

void HAL::PopFilters()
{
    // Do not render filters if the profile does not support it.
    ScopedRenderEvent GPUEvent(GetEvent(Event_Filter), __FUNCTION__, false);
    if (!shouldRenderFilters(FilterStack.Back().pPrimitive))
    {
        FilterStack.Pop();
        return;
    }

    FilterStackEntry e;
    e = FilterStack.Pop();

    if ( !Profiler.ShouldDrawMask() )
    {
        if ( FilterStack.GetSize() == 0 )
            Profiler.SetDrawMode(0);
        return;
    }

    // If doing a cached filter, and haven't reached the level at which it will be displayed, ignore the pop.
    if ( (HALState & HS_CachedFilter) && (CachedFilterIndex < (int)FilterStack.GetSize()) )
        return;

    CachedFilterIndex = -1;
    if ( HALState & HS_CachedFilter )
    {
        drawCachedFilter(e.pPrimitive);
        GetRQProcessor().SetQueueEmitFilter(RenderQueueProcessor::QPF_All);
        HALState &= ~HS_CachedFilter;
    }
    else
    {
        drawUncachedFilter(e);
    }

    if ( FilterStack.GetSize() == 0 )
        HALState &= ~HS_DrawingFilter;
}


void HAL::PushView3D( const Matrix3F &m )
{
    Matrices->View3D = m; 
    Matrices->UVPOChanged = 1; 
    ViewMatrix3DStack.PushBack(m);
}


void HAL::PushProj3D( const Matrix4F &m )
{
    Matrices->Proj3D = m; 
    Matrices->UVPOChanged = 1; 
    ProjectionMatrix3DStack.PushBack(m);
}

void HAL::PopView3D()
{
    ViewMatrix3DStack.PopBack(); 
    Matrices->View3D = ViewMatrix3DStack.GetSize() ? ViewMatrix3DStack.Back() : Matrix3F::Identity;  
    Matrices->UVPOChanged = 1;
}

void HAL::PopProj3D()
{
    ProjectionMatrix3DStack.PopBack(); 
    Matrices->Proj3D = ProjectionMatrix3DStack.GetSize() ? ProjectionMatrix3DStack.Back() : Matrix4F::Identity;  
    Matrices->UVPOChanged = 1;
}

unsigned HAL::DrawableCommandGetFlags(const DICommand* pcmd) const
{
    if ( !pcmd )
        return 0;
    switch(pcmd->GetType())
    {
        case DICommandType_Map:             return DICommand::RC_GPU | DICommand::RC_GPU_NoRT;
        case DICommandType_Unmap:           return DICommand::RC_GPU | DICommand::RC_GPU_NoRT;
        case DICommandType_CreateTexture:   return DICommand::RC_GPU | DICommand::RC_GPU_NoRT;

        case DICommandType_Clear:           return DICommand::RC_GPU | DICommand::RC_GPUPreference;
        case DICommandType_ApplyFilter:     return DICommand::RC_GPU | DICommand::RC_GPUPreference;
        case DICommandType_Draw:            return DICommand::RC_GPU | DICommand::RC_GPUPreference;
        case DICommandType_CopyChannel:     return DICommand::RC_GPU | DICommand::RC_GPUPreference;
        case DICommandType_CopyPixels:      return DICommand::RC_GPU | DICommand::RC_GPUPreference;
        case DICommandType_ColorTransform:  return DICommand::RC_GPU | DICommand::RC_GPUPreference;
        case DICommandType_Compare:         return DICommand::RC_GPU | DICommand::RC_GPUPreference;
        case DICommandType_FillRect:        return DICommand::RC_GPU | DICommand::RC_GPUPreference;
        case DICommandType_FloodFill:       return 0;
        case DICommandType_Merge:           return DICommand::RC_GPU | DICommand::RC_GPUPreference;
        case DICommandType_Noise:           return 0;
        case DICommandType_PaletteMap:      return DICommand::RC_GPU | DICommand::RC_GPUPreference;
        case DICommandType_PerlinNoise:     return 0;
        case DICommandType_Scroll:          return DICommand::RC_GPU | DICommand::RC_GPUPreference;
        case DICommandType_Threshold:       return DICommand::RC_GPU;
    default:
        return 0;
    }
}

void HAL::PushUserData(const UserDataState::Data* data)
{
    UserDataStack.PushBack(data);
}

void HAL::PopUserData()
{
    UserDataStack.Pop();
}

}} // Scaleform::Render
