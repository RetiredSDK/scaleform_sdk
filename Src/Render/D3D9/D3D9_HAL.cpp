/**************************************************************************

Filename    :   D3D9_HAL.cpp
Content     :   D3D9 Renderer HAL Prototype implementation.
Created     :   May 2009
Authors     :   Michael Antonov

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

// This removes the need to link with dxguid.lib.
#define DIRECT3D_VERSION 0x0900
#include <InitGuid.h>

#include "Kernel/SF_Debug.h"
#include "Kernel/SF_Random.h"
#include "Render/D3D9/D3D9_HAL.h"
#include "Render/Render_BufferGeneric.h"
#include "Kernel/SF_HeapNew.h"
#include "Render/D3D9/D3D9_Events.h"
#if SF_CC_MSVC < 1700
#include <d3dx9.h>
#endif

#include <stdio.h>

#if SF_CC_MSVC >= 1600 // MSVC 2010
#include <crtdefs.h>
#endif // SF_CC_MSVC >= 1600 // MSVC 2010

namespace Scaleform { namespace Render { namespace D3D9 {

// Defines all D3Dx color channels for D3DRS_COLORWRITEENABLE.
#define D3DCOLORWRITEENABLE_ALL D3DCOLORWRITEENABLE_ALPHA | D3DCOLORWRITEENABLE_RED | \
    D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_GREEN


// ***** HAL_D3D9

HAL::HAL(ThreadCommandQueue* commandQueue)
:   Render::ShaderHAL<ShaderManager, ShaderInterface>(commandQueue),
    pDevice(0),
    Cache(Memory::GetGlobalHeap(), MeshCacheParams::PC_Defaults),
    PrevBatchType(PrimitiveBatch::DP_None),
    // Mask/Stencil vars
    StencilChecked(false), StencilAvailable(false), MultiBitStencil(false),
    DepthBufferAvailable(false),
    StencilOpInc(D3DSTENCILOP_REPLACE)
{
}

HAL::~HAL()
{
    ShutdownHAL();
}

// *** RenderHAL_D3D9 Implementation
bool HAL::InitHAL(const D3D9::HALInitParams& params)
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_InitHAL), __FUNCTION__);

    if ( !initHAL(params))
        return false;

    if (!params.pD3DDevice)
        return 0; 

    pDevice = params.pD3DDevice;
    pDevice->AddRef();

    // Detect shader level features.
    D3DCAPSx caps;
    D3DDEVICE_CREATION_PARAMETERS cparams;
    pDevice->GetDeviceCaps(&caps);
    pDevice->GetCreationParameters(&cparams);

    if (!Cache.Initialize(pDevice, !(params.ConfigFlags&HALConfig_StaticBuffers)) ||
        !SManager.Initialize(this))
    {
        ShutdownHAL();
        return false;
    }

    // Create Texture manager if needed.
    if (params.pTextureManager)
        pTextureManager = params.GetTextureManager();
    else
    {
        D3DCapFlags ourCaps;
        ourCaps.InitFromHWCaps(caps, cparams);

        // Determine D3D9Ex usage.
        IDirect3DDevice9Ex* d3d9exPtr;
        if ( SUCCEEDED(pDevice->QueryInterface(IID_IDirect3DDevice9Ex, (void**)&d3d9exPtr)) && d3d9exPtr)
        {
            d3d9exPtr->Release();
            ourCaps.Flags |= D3DCapFlags::Cap_D3D9Ex;
        }

        pTextureManager = 
            *SF_HEAP_AUTO_NEW(this) TextureManager(pDevice, ourCaps,
                                                   params.RenderThreadId, pRTCommandQueue);
        if (!pTextureManager)
        {
            ShutdownHAL();
            return false;
        }
    }

    Matrices = *SF_HEAP_AUTO_NEW(this) MatrixState(this);

    // Create RenderBufferManager if needed.
    if (params.pRenderBufferManager)
        pRenderBufferManager = params.pRenderBufferManager;
    else
    {
        // Create the default render target, and manager.
        pRenderBufferManager = *SF_HEAP_AUTO_NEW(this) RenderBufferManagerGeneric(RBGenericImpl::DSSM_EqualOrBigger);
        if ( !pRenderBufferManager || !createDefaultRenderBuffer())
        {
            ShutdownHAL();
            return false;
        }
    }

    // Detect stencil op.
    if (caps.StencilCaps & D3DSTENCILCAPS_INCR)
    {
        StencilOpInc = D3DSTENCILOP_INCR;
    }
    else if (caps.StencilCaps & D3DSTENCILCAPS_INCRSAT)
    {
        StencilOpInc = D3DSTENCILOP_INCRSAT;
    }
    else
    {   // Stencil ops not available.
        StencilOpInc = D3DSTENCILOP_REPLACE;
    }

    memcpy(&PresentParams, &params.PresentParams, sizeof(D3DPRESENT_PARAMETERS));
    HALState|= HS_ModeSet;
    notifyHandlers(HAL_Initialize);
    return true;
}

// Returns back to original mode (cleanup)
bool HAL::ShutdownHAL()
{
    if (!(HALState & HS_ModeSet))
        return true;

    if (!shutdownHAL())
        return false;

    destroyRenderBuffers();
    pRenderBufferManager.Clear();

    // Do TextureManager::Reset to ensure shutdown on the current thread.
    if ( pTextureManager )
        pTextureManager->Reset();
    pTextureManager.Clear();
    SManager.Reset();
    Cache.Reset();
     
    if (pDevice)
        pDevice->Release();
    pDevice = 0;

    return true;
}

void HAL::PrepareForReset()
{
    SF_ASSERT(HALState & HS_ModeSet);
    if (HALState & HS_ReadyForReset)
        return;

    notifyHandlers(HAL_PrepareForReset);

    destroyRenderBuffers();

    pRenderBufferManager->Reset();
    pTextureManager->PrepareForReset();
    Cache.Reset();    

    HALState |= HS_ReadyForReset;
}

// - RestoreAfterReset called after reset to restore needed variables.
bool HAL::RestoreAfterReset()
{
    if (!IsInitialized())
        return false;
    if (!(HALState & HS_ReadyForReset))
        return true;

    if (!Cache.Initialize(pDevice, Cache.UsesDynamicMeshes()))
        return false;

    pTextureManager->RestoreAfterReset();

    if (!createDefaultRenderBuffer())
        return false;

     notifyHandlers(HAL_RestoreAfterReset);

     HALState &= ~HS_ReadyForReset;
     return true;
}

    
// ***** Rendering

bool HAL::BeginScene()
{
    if ( !Render::HAL::BeginScene())
        return false;

    ScopedRenderEvent GPUEvent(GetEvent(Event_BeginScene), __FUNCTION__ "-SetState");

    // Blending render states.
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);    

    // Not necessary of not alpha testing:
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);  // Important!

    union 
    {
        float fbias;
        DWORD d;
    } bias;
    bias.fbias = -0.75f;

    pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE,FALSE);

    pDevice->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, bias.d );
    pDevice->SetSamplerState(0, D3DSAMP_ELEMENTINDEX, 0);
    pDevice->SetSamplerState(1, D3DSAMP_ELEMENTINDEX, 0);

    // Set texture coordinate indices to match their stages, as we will be using the programmable pipeline.
    for ( unsigned i = 0; i < 8; i++ )
        pDevice->SetTextureStageState(i, D3DTSS_TEXCOORDINDEX, i);

    // Textures off by default.
    pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);

    // No ZWRITE by default
    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
    pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN |
        D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);

    // Turn off back-face culling.
    pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

    // Disable fog.
    pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); 

    // Start the scene
    if (!(VMCFlags&HALConfig_NoSceneCalls))
        pDevice->BeginScene();

    SManager.BeginScene();
    ShaderData.BeginScene();

    return true;
}

bool HAL::EndScene()
{
    if ( !Render::HAL::EndScene())
        return false;

    SManager.EndScene();

    // 'undo' instancing setup, if it was set.
    pDevice->SetStreamSourceFreq(0, 1);
    pDevice->SetStreamSourceFreq(1, 1);
    PrevBatchType = PrimitiveBatch::DP_None;

    if (!(VMCFlags&HALConfig_NoSceneCalls))
        pDevice->EndScene();

    return true;
}

// Updates D3D HW Viewport and ViewportMatrix based on provided viewport
// and view rectangle.
void HAL::updateViewport()
{
    D3DVIEWPORTx vp;
    Rect<int>    vpRect;

    if (HALState & HS_ViewValid)
    {
        int dx = ViewRect.x1 - VP.Left,
            dy = ViewRect.y1 - VP.Top;
        
        // Modify HW matrix and viewport to clip.
        CalcHWViewMatrix(Viewport::View_HalfPixelOffset, &Matrices->View2D, ViewRect, dx, dy);
        Matrices->SetUserMatrix(Matrices->User);
        Matrices->ViewRect    = ViewRect;
        Matrices->UVPOChanged = 1;

        /*
        // TBD: Prepend UserMatrix here is incorrect for nested viewport-based
        // mask clipping; what's needed is a complex combination of viewport and
        // coordinate adjustment. Until this is done, mask viewport clipping will be
        // in the wrong place for UserMatrix.
        if (UserMatrix != Matrix2F::Identity)
        {
            Rect<int> viewportRect;
            Rect<int> userViewRect(
                ViewRect.x1 + (int)UserMatrix.Tx(),
                ViewRect.y1 + (int)UserMatrix.Ty(),
                Size<int>((int)(UserMatrix.Sx() * (float)ViewRect.Width()),
                          (int)(UserMatrix.Sy() * (float)ViewRect.Height())));

            VP.GetClippedRect(&viewportRect);
            viewportRect.IntersectRect(&vpRect, userViewRect);
        }
        */

        if ( !(HALState & HS_InRenderTarget) )
		{
			Viewport vp = VP;
			vp.Left     = ViewRect.x1;
			vp.Top      = ViewRect.y1;
			vp.Width    = ViewRect.Width();
			vp.Height   = ViewRect.Height();
            vp.SetStereoViewport(Matrices->S3DDisplay);
			vpRect.SetRect(vp.Left, vp.Top, vp.Left + vp.Width, vp.Top + vp.Height);
		}
        else
            vpRect.SetRect(VP.Left, VP.Top, VP.Left + VP.Width, VP.Top + VP.Height);
    }

    vp.X        = vpRect.x1;
    vp.Y        = vpRect.y1;

    // DX9 can't handle a vp with zero area.
    vp.Width    = (DWORD)Alg::Max<int>(vpRect.Width(), 1);
    vp.Height   = (DWORD)Alg::Max<int>(vpRect.Height(), 1);

    vp.MinZ     = 0.0f;
    vp.MaxZ     = 0.0f;
    pDevice->SetViewport(&vp);
}

// Draws a range of pre-cached and preprocessed primitives
void HAL::DrawProcessedPrimitive(Primitive* pprimitive,
                                       PrimitiveBatch* pstart, PrimitiveBatch *pend)
{
    SF_AMP_SCOPE_RENDER_TIMER(__FUNCTION__, Amp_Profile_Level_High);
    ScopedRenderEvent GPUEvent(GetEvent(Event_DrawPrimitive), __FUNCTION__);

    if (!checkState(HS_InDisplay, __FUNCTION__) ||
        !pprimitive->GetMeshCount() )
        return;

    // If in overdraw profile mode, and this primitive is part of a mask, draw it in color mode.
    static bool drawingMask = false;
    if ( !Profiler.ShouldDrawMask() && !drawingMask && (HALState & HS_DrawingMask) )
    {
        drawingMask = true;
        pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALL );
        pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE );
        DrawProcessedPrimitive(pprimitive, pstart, pend);
        pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0 );
        pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE );
        drawingMask = false;
    }

    SF_ASSERT(pend != 0);

    PrimitiveBatch* pbatch = pstart ? pstart : pprimitive->Batches.GetFirst();

    ShaderData.BeginPrimitive();

    unsigned bidx = 0;
    while (pbatch != pend)
    {        
        // pBatchMesh can be null in case of error, such as VB/IB lock failure.
        MeshCacheItem* pmesh = (MeshCacheItem*)pbatch->GetCacheItem();
        unsigned       meshIndex = pbatch->GetMeshIndex();
        unsigned       batchMeshCount = pbatch->GetMeshCount();

        if (pmesh)
        {
            Profiler.SetBatch((UPInt)pprimitive, bidx);

            unsigned fillFlags = FillFlags;
            if ( batchMeshCount > 0 )
                fillFlags |= pprimitive->Meshes[0].M.Has3D() ? FF_3DProjection : 0;

            const ShaderManager::Shader& pShader =
                SManager.SetPrimitiveFill(pprimitive->pFill, fillFlags, pbatch->Type, pbatch->pFormat, batchMeshCount, Matrices,
                &pprimitive->Meshes[meshIndex], &ShaderData);

            if ((HALState & HS_ViewValid) && pShader ) 
            {
                SF_ASSERT((pbatch->Type != PrimitiveBatch::DP_Failed) &&
                    (pbatch->Type != PrimitiveBatch::DP_Virtual));

                // Draw the object with cached mesh.
                if (pbatch->Type != PrimitiveBatch::DP_Instanced)
                {
                    setLinearStreamSource(pbatch->Type);
                }
                else
                {

                    setInstancedStreamSource(pbatch->GetMeshCount());  
                }
                UPInt   indexOffset = pmesh->IBAllocOffset / sizeof (IndexType);

                pDevice->SetIndices(pmesh->pIndexBuffer->GetHWBuffer());
                pDevice->SetStreamSource(0, pmesh->pVertexBuffer->GetHWBuffer(),
                    (UINT)pmesh->VBAllocOffset, pbatch->pFormat->Size);               
                if (pbatch->Type != PrimitiveBatch::DP_Instanced)
                {
                    drawIndexedPrimitive(pmesh->IndexCount, (unsigned)(pmesh->VBAllocSize / pbatch->pFormat->Size), 
                        pmesh->MeshCount, indexOffset, 0 );
                }
                else
                {
                    drawIndexedInstanced(pmesh->IndexCount, (unsigned)(pmesh->VBAllocSize / pbatch->pFormat->Size), 
                        pbatch->GetMeshCount(), indexOffset, 0);
                }
     
            }

            pmesh->GPUFence = Cache.GetRenderSync()->InsertFence();
            pmesh->MoveToCacheListFront(MCL_ThisFrame);
        }

        pbatch = pbatch->GetNext();
        bidx++;
    }
}

void HAL::DrawProcessedComplexMeshes(ComplexMesh* complexMesh,
                                     const StrideArray<HMatrix>& matrices)
{    
    SF_AMP_SCOPE_RENDER_TIMER(__FUNCTION__, Amp_Profile_Level_High);
    ScopedRenderEvent GPUEvent(GetEvent(Event_DrawComplex), __FUNCTION__);

    typedef ComplexMesh::FillRecord   FillRecord;
    typedef PrimitiveBatch::BatchType BatchType;

    MeshCacheItem* pmesh = (MeshCacheItem*)complexMesh->GetCacheItem();
    if (!checkState(HS_InDisplay, __FUNCTION__) || !pmesh)
        return;

    // If in overdraw profile mode, and this primitive is part of a mask, draw it in color mode.
    static bool drawingMask = false;
    if ( !Profiler.ShouldDrawMask() && !drawingMask && (HALState & HS_DrawingMask) )
    {
        drawingMask = true;
        pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALL );
        pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE );
        DrawProcessedComplexMeshes(complexMesh, matrices);
        pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0 );
        pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE );
        drawingMask = false;
    }

    const FillRecord* fillRecords = complexMesh->GetFillRecords();
    unsigned    fillCount     = complexMesh->GetFillRecordCount();
    unsigned    instanceCount = (unsigned)matrices.GetSize();
    BatchType   batchType = PrimitiveBatch::DP_Single;
    unsigned    formatIndex;
    unsigned    maxDrawCount = 1;
    unsigned    vertexBaseIndex = 0;
    unsigned    vertexSize = 0;
    unsigned    indexBufferOffset = (unsigned)(pmesh->IBAllocOffset / sizeof(IndexType));

    if (instanceCount > 1 && SManager.HasInstancingSupport())
    {
        maxDrawCount = Alg::Min(instanceCount, Cache.GetParams().MaxBatchInstances);
        batchType = PrimitiveBatch::DP_Instanced;
        formatIndex = 1;
    }
    else
    {
        batchType = PrimitiveBatch::DP_Single;
        formatIndex = 0;
        setLinearStreamSource(batchType);
    }

    const Matrix2F* textureMatrices = complexMesh->GetFillMatrixCache();
    pDevice->SetIndices(pmesh->pIndexBuffer->GetHWBuffer());
    for (unsigned fillIndex = 0; fillIndex < fillCount; fillIndex++)
    {
        const FillRecord& fr = fillRecords[fillIndex];

        Profiler.SetBatch((UPInt)complexMesh, fillIndex);

        unsigned fillFlags = FillFlags;
        unsigned startIndex = 0;
        if ( instanceCount > 0 )
        {
            const HMatrix& hm = matrices[0];
            fillFlags |= hm.Has3D() ? FF_3DProjection : 0;

            for (unsigned i = 0; i < instanceCount; i++)
            {
                const HMatrix& hm = matrices[startIndex + i];
                if (!(Profiler.GetCxform(hm.GetCxform()) == Cxform::Identity))
                    fillFlags |= FF_Cxform;
            }
        }

        // Apply fill.
        PrimitiveFillType fillType = Profiler.GetFillType(fr.pFill->GetType());
        const ShaderManager::Shader& pso = SManager.SetFill(fillType, fillFlags, batchType, fr.pFormats[formatIndex], &ShaderData);

        // Optimization: Modify stream source only when VertexSize changes.
        if ( fr.pFormats[formatIndex]->Size != vertexSize )
        {
            vertexSize = fr.pFormats[formatIndex]->Size;
            pDevice->SetStreamSource(0, pmesh->pVertexBuffer->GetHWBuffer(), (UINT)(fr.VertexByteOffset + pmesh->VBAllocOffset),
                vertexSize);
            vertexBaseIndex = 0;
        }
        else
        {
            // Identical size vertex meshes should be allocated consecutively,
            // as this is needed for SetStreamSource optimization to work.
            SF_ASSERT(fr.VertexByteOffset == (fillRecords[fillIndex-1].VertexByteOffset +
                vertexSize * fillRecords[fillIndex-1].VertexCount));
        }


        UByte textureCount = fr.pFill->GetTextureCount();
        bool solid = (fillType == PrimFill_None || fillType == PrimFill_Mask || fillType == PrimFill_SolidColor);

        for (unsigned i = 0; i < instanceCount; i++)
        {            
            const HMatrix& hm = matrices[startIndex + i];

            ShaderData.SetMatrix(pso, Uniform::SU_mvp, complexMesh->GetVertexMatrix(), hm, Matrices, 0, i%maxDrawCount);
            if (solid)
                ShaderData.SetColor(pso, Uniform::SU_cxmul, Profiler.GetColor(fr.pFill->GetSolidColor()), 0, i%maxDrawCount);
            else if (fillFlags & FF_Cxform)
                ShaderData.SetCxform(pso, Profiler.GetCxform(hm.GetCxform()), 0, i%maxDrawCount);

            for (unsigned tm = 0, stage = 0; tm < textureCount; tm++)
            {
                ShaderData.SetMatrix(pso, Uniform::SU_texgen, textureMatrices[fr.FillMatrixIndex[tm]], tm, i%maxDrawCount);
                Texture* ptex = (Texture*)fr.pFill->GetTexture(tm);
                ShaderData.SetTexture(pso, Uniform::SU_tex, ptex, fr.pFill->GetFillMode(tm), stage);
                stage += ptex->GetPlaneCount();
            }

            bool lastPrimitive = (i == instanceCount-1);
            if ( batchType != PrimitiveBatch::DP_Instanced )
            {
                ShaderData.Finish(1);
                drawIndexedPrimitive(fr.IndexCount, fr.VertexCount, 1, fr.IndexOffset + indexBufferOffset, vertexBaseIndex);
                AccumulatedStats.Primitives++;
                if ( !lastPrimitive )
                    ShaderData.BeginPrimitive();
            }
            else if (( (i+1) % maxDrawCount == 0 && i != 0) || lastPrimitive )
            {
                unsigned drawCount = maxDrawCount;
                if ( lastPrimitive && (i+1) % maxDrawCount != 0)
                    drawCount = (i+1) % maxDrawCount;
                setInstancedStreamSource(drawCount);
                ShaderData.Finish(drawCount);
                drawIndexedInstanced(fr.IndexCount, fr.VertexCount, drawCount, fr.IndexOffset + indexBufferOffset, vertexBaseIndex);
                AccumulatedStats.Primitives++;
                if ( !lastPrimitive )
                    ShaderData.BeginPrimitive();
            }
        }
        vertexBaseIndex += fr.VertexCount;

    } // for (fill record)

    pmesh->GPUFence = Cache.GetRenderSync()->InsertFence();
    pmesh->MoveToCacheListFront(MCL_ThisFrame);
}

//--------------------------------------------------------------------
// *** Mask / Stencil support
//--------------------------------------------------------------------

// Mask support is implemented as a stack, enabling for a number of optimizations:
//
// 1. Large "Clipped" marks are clipped to a custom viewport, allowing to save on
//    fill-rate when rendering both the mask and its content. The mask area threshold
//    that triggers this behavior is determined externally.
//      - Clipped masks can be nested, but not batched. When erased, clipped masks
//        clear the clipped intersection area.
// 2. Small masks can be Batched, having multiple mask areas with multiple mask
//    content items inside.
//      - Small masks can contain clipped masks either regular or clipped masks.
// 3. Mask area dimensions are provided as HMatrix, which maps a unit rectangle {0,0,1,1}
//    to a mask bounding rectangle. This rectangle can be rotated (non-axis aligned),
//    allowing for more efficient fill.
// 4. PopMask stack optimization is implemented that does not erase nested masks; 
//    Stencil Reference value is changed instead. Erase of a mask only becomes
//    necessary if another PushMask_BeginSubmit is called, in which case previous
//    mask bounding rectangles are erased. This setup avoids often unnecessary erase 
//    operations when drawing content following a nested mask.
//      - To implement this MaskStack keeps a previous "stale" MaskPrimitive
//        located above the MaskStackTop.

void HAL::PushMask_BeginSubmit(MaskPrimitive* prim)
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_Mask), __FUNCTION__);
    if (!checkState(HS_InDisplay, __FUNCTION__))
        return;

    Profiler.SetDrawMode(1);

    if (!StencilAvailable && !DepthBufferAvailable)
    {
        if (!checkMaskBufferCaps())
            return;
    }
    
    // These states are applicable to most stencil operations below.
    if (StencilAvailable)
    {
        pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
        pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
        pDevice->SetRenderState(D3DRS_STENCILMASK, 0xFF);
        pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
        pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
    }

    bool viewportValid = (HALState & HS_ViewValid) != 0;

    // Erase previous mask if it existed above our current stack top.
    if (MaskStackTop && (MaskStack.GetSize() > MaskStackTop) && viewportValid)
    {
        // Erase rectangles of these matrices; must be done even for clipped masks.
        if (StencilAvailable && (MultiBitStencil && (StencilOpInc != D3DSTENCILOP_REPLACE)))
        {
            // Any stencil of value greater then MaskStackTop should be set to it;
            // i.e. replace when (MaskStackTop < stencil value).
            DWORD maxStencilValue = (DWORD)MaskStackTop;
            pDevice->SetRenderState(D3DRS_STENCILREF, maxStencilValue);
            pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);
            pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

            MaskPrimitive* erasePrim = MaskStack[MaskStackTop].pPrimitive;
            drawMaskClearRectangles(erasePrim->GetMaskAreaMatrices(), erasePrim->GetMaskCount());
        }
    }

    MaskStack.Resize(MaskStackTop+1);
    MaskStackEntry &e = MaskStack[MaskStackTop];
    e.pPrimitive       = prim;
    e.OldViewportValid = viewportValid;
    e.OldViewRect      = ViewRect; // TBD: Must assign
    MaskStackTop++;

    HALState |= HS_DrawingMask;

    if (prim->IsClipped() && viewportValid)
    {
        Rect<int> boundClip;

        // Apply new viewport clipping.
        if (!Matrices->OrientationSet)
        {
            const Matrix2F& m = prim->GetMaskAreaMatrix(0).GetMatrix2D();

            // Clipped matrices are always in View coordinate space, to allow
            // matrix to be use for erase operation above. This means that we don't
            // have to do an EncloseTransform.
            SF_ASSERT((m.Shx() == 0.0f) && (m.Shy() == 0.0f));
            boundClip = Rect<int>(VP.Left + (int)m.Tx(), VP.Top + (int)m.Ty(),
                                  VP.Left + (int)(m.Tx() + m.Sx()), VP.Top + (int)(m.Ty() + m.Sy()));
        }
        else
        {
            Matrix2F m = prim->GetMaskAreaMatrix(0).GetMatrix2D();
            m.Append(Matrices->Orient2D);

            RectF rect = m.EncloseTransform(RectF(0,0,1,1));
            boundClip = Rect<int>(VP.Left + (int)rect.x1, VP.Top + (int)rect.y1,
                                  VP.Left + (int)rect.x2, VP.Top + (int)rect.y2);
        }
        
        if (!ViewRect.IntersectRect(&ViewRect, boundClip))
        {
            ViewRect.Clear();
            HALState &= ~HS_ViewValid;
            viewportValid = false;
        }
        updateViewport();
        
        // Clear full viewport area, which has been resized to our smaller bounds.
        if ((MaskStackTop == 1) && viewportValid)
        {
            if (StencilAvailable)
                pDevice->Clear(0, 0, D3DCLEAR_STENCIL, 0, 0.0f, 0);
            else if (DepthBufferAvailable)
                pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0); // Z -> 1.0f
        }
    }

    else if ((MaskStackTop == 1) && viewportValid)
    {
        // Clear view rectangles.
        if (StencilAvailable)
        {
            // Unconditionally overwrite stencil rectangles with REF value of 0.
            pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
            pDevice->SetRenderState(D3DRS_STENCILREF, 0);
            pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
            pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

            drawMaskClearRectangles(prim->GetMaskAreaMatrices(), prim->GetMaskCount());
            pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
        }
        else
        {
            // Depth clears bounds. Don't use drawMaskClearRectangles yet as it doesn't
            // set proper Z.
            UPInt maskCount = prim->GetMaskCount();
            for (UPInt i = 0; i< maskCount; i++)
            {
                const Matrix2F &m = prim->GetMaskAreaMatrix(i).GetMatrix2D();
                RectF           bounds(m.EncloseTransform(RectF(1.0f)));
                Rect<int>       boundClip((int)bounds.x1, (int)bounds.y1,
                                          (int)bounds.x2, (int)bounds.y2);
                boundClip.Offset(VP.Left, VP.Top);

                if (boundClip.IntersectRect(&boundClip, ViewRect))
                {
                    D3DRECT r = { boundClip.x1, boundClip.y1, boundClip.x2, boundClip.y2 };
                    pDevice->Clear(1, &r, D3DCLEAR_ZBUFFER, 0, 1.0f, 0); // Z -> 1.0f
                }
            }
        }
    }


    if (StencilAvailable)
    {
        bool canIncDec = (MultiBitStencil && (StencilOpInc != D3DSTENCILOP_REPLACE));

        // Increment only if we support it.
        if (canIncDec)
        {
            pDevice->SetRenderState(D3DRS_STENCILREF, (DWORD)(MaskStackTop-1));
            pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
            pDevice->SetRenderState(D3DRS_STENCILPASS, StencilOpInc);
        }
        else if (MaskStackTop == 1)
        {
            pDevice->SetRenderState(D3DRS_STENCILREF, 1);
            pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
            pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
        }
        else
        {   // If not supported, no change.
            pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
        }
    }
    else if (DepthBufferAvailable)
    {
        if (MaskStackTop == 1)
        {
            // Set the correct render states in order to not modify the color buffer
            // but write the default Z-value everywhere. According to the shader code: should be 0.
            pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA);
            pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
            pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
            pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
        }
        else
        {
            // No color write. Incr/Decr not supported.
            pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
            pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
            pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        }
    }
    ++AccumulatedStats.Masks;
}


void HAL::EndMaskSubmit()
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_Mask), 0, false);
    Profiler.SetDrawMode(0);

    if (!checkState(HS_InDisplay|HS_DrawingMask, __FUNCTION__))
        return;
    HALState &= ~HS_DrawingMask;    
    SF_ASSERT(MaskStackTop);

    pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALL);
    
    if (StencilAvailable)
    {
        // We draw only where the (MaskStackTop <= stencil), i.e. where the latest mask was drawn.
        // However, we don't change the stencil buffer
        pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);
        pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP); 
        // Stencil counter.
        pDevice->SetRenderState(D3DRS_STENCILREF, (DWORD)MaskStackTop);
        pDevice->SetRenderState(D3DRS_STENCILMASK, 0xFF);
    }
    else if (DepthBufferAvailable)
    {
        // Disable the Z-write and write only where the mask had written
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
        pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_EQUAL);
    }
}


void HAL::PopMask()
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_PopMask), __FUNCTION__);
    if (!checkState(HS_InDisplay, __FUNCTION__))
        return;

    if (!StencilAvailable && !DepthBufferAvailable)
        return;
    SF_ASSERT(MaskStackTop);
    MaskStackTop--;

    if (MaskStack[MaskStackTop].pPrimitive->IsClipped())
    {
        // Restore viewport
        ViewRect = MaskStack[MaskStackTop].OldViewRect;

        if (MaskStack[MaskStackTop].OldViewportValid)
            HALState |= HS_ViewValid;
        else
            HALState &= ~HS_ViewValid;
        updateViewport();
    }

    // Disable mask or decrement stencil reference value.
    if (StencilAvailable)
    {
        if (MaskStackTop == 0)
            pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
        else
        {
            // Change ref value down, so that we can draw using previous mask.
            pDevice->SetRenderState(D3DRS_STENCILREF, (DWORD)MaskStackTop);
            pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
        }
    }
    else if (DepthBufferAvailable)
    {
        // Disable the Z-write and write only where the mask had written
        pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
        pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
    }
}


bool HAL::checkMaskBufferCaps()
{
    if (!StencilChecked)
    {
        // Test for depth-stencil presence.
        IDirect3DSurfaceX *pdepthStencilSurface = 0;
        pDevice->GetDepthStencilSurface(&pdepthStencilSurface);
        if (pdepthStencilSurface)
        {
            D3DSURFACE_DESC sd;
            pdepthStencilSurface->GetDesc(&sd);

            switch(sd.Format)
            {
            case D3DFMT_D24S8:
            case D3DFMT_D24X4S4:
//#if (SF_D3D_VERSION == 9)
            case D3DFMT_D24FS8:
//#endif
                MultiBitStencil = 1;
            case D3DFMT_D15S1:
                StencilAvailable = 1;
                break;
            default:
                SF_DEBUG_ASSERT1(1, "Unexpected DepthStencil format: 0x%08x\n", sd.Format);
                break;
            }

            pdepthStencilSurface->Release();
            pdepthStencilSurface = 0;
            DepthBufferAvailable = 1;
        }
        else
            StencilAvailable = 0;

        StencilChecked = 1;
    }

    if (!StencilAvailable && !DepthBufferAvailable)
    {
#ifdef SF_BUILD_DEBUG
        static bool StencilWarned = 0;
        if (!StencilWarned)
        {
            SF_DEBUG_WARNING(1, "RendererHAL::PushMask_BeginSubmit used, but stencil is not available");
            StencilWarned = 1;
        }
#endif
        return false;
    }
    return true;
}

//--------------------------------------------------------------------
// Background clear helper, expects viewport coordinates.
void HAL::clearSolidRectangle(const Rect<int>& r, Color color)
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_Clear), __FUNCTION__);
    color = Profiler.GetClearColor(color);
    if (color.GetAlpha() == 0xFF && !(VP.Flags & Viewport::View_Stereo_AnySplit))
    {
        // Do more efficient HW clear. Device::Clear expects render-target coordinates.
        D3DRECT  cr = { r.x1 + VP.Left, r.y1 + VP.Top,
                        r.x2 + VP.Left, r.y2 + VP.Top };
        D3DCOLOR d3dc = D3DCOLOR_XRGB(color.GetRed(), color.GetGreen(), color.GetBlue());
        pDevice->Clear(1, &cr, D3DCLEAR_TARGET, d3dc, 1.0f,  0);
    }
    else
    {
        float colorf[4];
        color.GetRGBAFloat(colorf, colorf+1, colorf+2, colorf+3);
        Matrix2F m((float)r.Width(), 0.0f, (float)r.x1,
            0.0f, (float)r.Height(), (float)r.y1);

        Matrix2F  mvp(m, Matrices->UserView);

        unsigned fillflags = 0;
        const ShaderManager::Shader& pso = SManager.SetFill(PrimFill_SolidColor, fillflags, PrimitiveBatch::DP_Single, 
            MappedXY16iAlphaSolid[PrimitiveBatch::DP_Single], &ShaderData);
        ShaderData.SetMatrix(pso, Uniform::SU_mvp, mvp);
        ShaderData.SetUniform(pso, Uniform::SU_cxmul, colorf, 4);
        ShaderData.Finish(1);

        setLinearStreamSource(PrimitiveBatch::DP_Batch);
        pDevice->SetStreamSource(0, Cache.pMaskEraseBatchVertexBuffer.GetPtr(),
                                 0, sizeof(VertexXY16iAlpha));
        drawPrimitive(6, 1);
    }
}



//--------------------------------------------------------------------
// *** BlendMode Stack support
//--------------------------------------------------------------------

void HAL::applyBlendModeImpl(BlendMode mode, bool sourceAc, bool forceAc )
{    
    ScopedRenderEvent GPUEvent(GetEvent(Event_ApplyBlend), __FUNCTION__);

    static const UInt32 BlendOps[BlendOp_Count] = 
    {
        D3DBLENDOP_ADD,         // BlendOp_ADD
        D3DBLENDOP_MAX,         // BlendOp_MAX
        D3DBLENDOP_MIN,         // BlendOp_MIN
        D3DBLENDOP_REVSUBTRACT, // BlendOp_REVSUBTRACT
    };

    static const UInt32 BlendFactors[BlendFactor_Count] = 
    {
        D3DBLEND_ZERO,          // BlendFactor_ZERO
        D3DBLEND_ONE,           // BlendFactor_ONE
        D3DBLEND_SRCALPHA,      // BlendFactor_SRCALPHA
        D3DBLEND_INVSRCALPHA,   // BlendFactor_INVSRCALPHA
        D3DBLEND_DESTCOLOR,     // BlendFactor_DESTCOLOR
        D3DBLEND_INVDESTCOLOR,  // BlendFactor_INVDESTCOLOR
    };

    if (!pDevice)
        return;


    pDevice->SetRenderState(D3DRS_BLENDOP, BlendOps[BlendModeTable[mode].Operator]);
    pDevice->SetRenderState(D3DRS_DESTBLEND, BlendFactors[BlendModeTable[mode].DestColor]);
    if ( sourceAc && BlendFactors[BlendModeTable[mode].SourceColor] == D3DBLEND_SRCALPHA )
        pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
    else
        pDevice->SetRenderState(D3DRS_SRCBLEND, BlendFactors[BlendModeTable[mode].SourceColor]);        

    if (VP.Flags & Viewport::View_AlphaComposite || forceAc)
    {
        pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
        pDevice->SetRenderState(D3DRS_BLENDOPALPHA, BlendOps[BlendModeTable[mode].Operator]);
        pDevice->SetRenderState(D3DRS_SRCBLENDALPHA, BlendFactors[BlendModeTable[mode].SourceAlpha]);
        pDevice->SetRenderState(D3DRS_DESTBLENDALPHA, BlendFactors[BlendModeTable[mode].DestAlpha]);
    }
    else
    {
        pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, FALSE);
    }
}

RenderTarget* HAL::CreateRenderTarget(IDirect3DSurface9* pcolor, IDirect3DSurface9* pdepth)
{
    D3DSURFACE_DESC sdesc;
    ImageSize dsSize(0), rtSize(0);

    if (SUCCEEDED(pcolor->GetDesc(&sdesc)))
        rtSize.SetSize(sdesc.Width, sdesc.Height);

    RenderTarget* ptarget = pRenderBufferManager->CreateRenderTarget(rtSize, RBuffer_User, Image_R8G8B8A8, 0);

    Ptr<DepthStencilBuffer> pdsb = 0;
    if (pdepth && SUCCEEDED(pdepth->GetDesc(&sdesc)))
    {
        dsSize.SetSize(sdesc.Width, sdesc.Height);
        pdsb = *SF_HEAP_AUTO_NEW(this) DepthStencilBuffer(0, dsSize);
    }

    RenderTargetData::UpdateData(ptarget, pcolor, pdsb, pdepth);
    return ptarget;
}

RenderTarget* HAL::CreateRenderTarget(Render::Texture* texture, bool needsStencil)
{
    D3D9::Texture* pt = (D3D9::Texture*)texture;

    // Cannot render to textures which have multiple HW representations.
    if ( !pt || pt->TextureCount != 1 )
        return 0;

    IDirect3DSurface9* prenderSurface = 0, *pdsSurface = 0;
    RenderTarget* prt = pRenderBufferManager->CreateRenderTarget(
        texture->GetSize(), RBuffer_Texture, texture->GetFormat(), texture);
    if ( !prt )
        return 0;
    pt->pTextures[0].pTexture->GetSurfaceLevel(0,&prenderSurface);

    Ptr<DepthStencilBuffer> pdsb;
    if ( needsStencil )
    {
        pdsb = *pRenderBufferManager->CreateDepthStencilBuffer(prt->GetTexture()->GetSize());
        if ( pdsb )
        {
            DepthStencilSurface* surf = (D3D9::DepthStencilSurface*)pdsb->GetSurface();
            if ( surf )
                pdsSurface = surf->pDepthStencilSurface;
        }
    }
    RenderTargetData::UpdateData(prt, prenderSurface, pdsb, pdsSurface );
    prenderSurface->Release();

    return prt;
}

RenderTarget* HAL::CreateTempRenderTarget(const ImageSize& size, bool needsStencil)
{
    RenderTarget* prt = pRenderBufferManager->CreateTempRenderTarget(size);
    if ( !prt )
        return 0;

    RenderTargetData* phd = (RenderTargetData*)prt->GetRenderTargetData();
    if ( phd && (!needsStencil || phd->pDSSurface))
        return prt;

    Ptr<IDirect3DSurface9> prenderSurface = 0;
    IDirect3DSurface9* pdsSurface = 0;
    D3D9::Texture* pt = (D3D9::Texture*)prt->GetTexture();

    // Cannot render to textures which have multiple HW representations.
    SF_ASSERT(pt->TextureCount == 1); 
    pt->pTextures[0].pTexture->GetSurfaceLevel(0,&prenderSurface.GetRawRef());

    Ptr<DepthStencilBuffer> pdsb;
    if ( needsStencil )
    {
        pdsb = *pRenderBufferManager->CreateDepthStencilBuffer(prt->GetTexture()->GetSize());
        if ( pdsb )
        {
            DepthStencilSurface* surf = (D3D9::DepthStencilSurface*)pdsb->GetSurface();
            if ( surf )
                pdsSurface = surf->pDepthStencilSurface;
        }
    }

    RenderTargetData::UpdateData(prt, prenderSurface, pdsb, pdsSurface);
    return prt;
}

bool HAL::SetRenderTarget(RenderTarget* ptarget, bool setState)
{
    // When changing the render target while in a scene, we must flush all drawing.
    if ( HALState & HS_InScene)
        Flush();

    // Cannot set the bottom level render target if already in display.
    if ( HALState & HS_InDisplay )
        return false;

    D3DSURFACE_DESC rtDesc;
    RenderTargetEntry entry;
    RenderTargetData* prtdata = (D3D9::RenderTargetData*)ptarget->GetRenderTargetData();
    IDirect3DSurface9* pd3dsurface= prtdata->pRenderSurface;
    if ( FAILED(pd3dsurface->GetDesc(&rtDesc)) )
        return false;

    if ( setState )
    {
        pDevice->SetRenderTarget(0, pd3dsurface);
        if ( prtdata->pDSSurface )
            pDevice->SetDepthStencilSurface(prtdata->pDSSurface);
    }
    entry.pRenderTarget = ptarget;

    // Replace the stack entry at the bottom, or if the stack is empty, add one.
    if ( RenderTargetStack.GetSize() > 0 )
        RenderTargetStack[0] = entry;
    else
        RenderTargetStack.PushBack(entry);
    return true;
}

void HAL::PushRenderTarget(const RectF& frameRect, RenderTarget* prt, unsigned flags)
{
    GetEvent(Event_RenderTarget).Begin(__FUNCTION__);
    HALState |= HS_InRenderTarget;
    RenderTargetEntry entry;
    entry.pRenderTarget = prt;
    entry.OldViewport = VP;
    entry.OldViewRect = ViewRect;
    entry.OldMatrixState.CopyFrom(Matrices);
    Matrices->SetUserMatrix(Matrix2F::Identity);

	if ( RenderTargetStack.GetSize() > 0 )
	{
		IDirect3DSurface9* pDeviceSurface = 0;
		pDevice->GetRenderTarget( 0, &pDeviceSurface );
		RenderTargetData* phd = (D3D9::RenderTargetData*)prt->GetRenderTargetData();
		RenderTargetEntry& currentEntry = RenderTargetStack.Back();
		RenderTargetData* pCurrentTargetData = (D3D9::RenderTargetData*)currentEntry.pRenderTarget->GetRenderTargetData();
		char buffer[128] = { 0 };
		sprintf( buffer, "Push render target: Device: 0x%p, Current: 0x%p, New: 0x%p\n", 
			pDeviceSurface, pCurrentTargetData->pRenderSurface, phd->pRenderSurface );
		OutputDebugString( buffer );
		pDeviceSurface->Release();
	}
	else
	{
		OutputDebugString( "Render target stack size == 0 before PushRenderTarget\n" );
	}

    // Setup the render target/depth stencil on the device.
    if ( !prt )
    {
        SF_DEBUG_WARNING(1, __FUNCTION__ " - invalid render target.");
        RenderTargetStack.PushBack(entry);
        return;
    }

    // Unbind the texture if it is bound (can't have a texture bound as an input and target).
    pTextureManager->SetSamplerState(0, 0);
    pTextureManager->SetSamplerState(1, 0);

    RenderTargetData* phd = (D3D9::RenderTargetData*)prt->GetRenderTargetData();
    pDevice->SetRenderTarget(0, phd->pRenderSurface);
    if ( phd->pDSSurface )
        pDevice->SetDepthStencilSurface(phd->pDSSurface);
    else
        pDevice->SetDepthStencilSurface(0);

    ++AccumulatedStats.RTChanges;

    // Clear, if not specifically excluded
    if ( (flags & PRT_NoClear) == 0 )
    {    
        pDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0,0,0,0), 1.0f,  0);
    }

    // Setup viewport.
    Rect<int> viewRect = prt->GetRect(); // On the render texture, might not be the entire surface.
    const ImageSize& bs = prt->GetBufferSize();
    VP = Viewport(bs.Width, bs.Height, viewRect.x1, viewRect.y1, viewRect.Width(), viewRect.Height());    
    ViewRect.x1 = (int)frameRect.x1;
    ViewRect.y1 = (int)frameRect.y1;
    ViewRect.x2 = (int)frameRect.x2;
    ViewRect.y2 = (int)frameRect.y2;

    // Must offset the 'original' viewrect, otherwise the 3D compensation matrix will be offset.
    Matrices->ViewRectOriginal.Offset(-entry.OldViewport.Left, -entry.OldViewport.Top);
    Matrices->UVPOChanged = true;
    HALState |= HS_ViewValid;
    updateViewport();

    RenderTargetStack.PushBack(entry);
}

void HAL::PopRenderTarget(unsigned)
{
	IDirect3DSurface9 *pDeviceSurface = 0, *pCurrentSurface = 0, *pOldSurface = 0;

    ScopedRenderEvent GPUEvent(GetEvent(Event_RenderTarget), __FUNCTION__, false);

    RenderTargetEntry& entry = RenderTargetStack.Back();
    RenderTarget* prt = entry.pRenderTarget;
	
	D3D9::RenderTargetData* debugData = (D3D9::RenderTargetData*)entry.pRenderTarget->GetRenderTargetData();
	pCurrentSurface = debugData->pRenderSurface;

    prt->SetInUse(false);
    if ( prt->GetType() == RBuffer_Temporary )
    {
        // Strip off the depth stencil surface/buffer from temporary targets.
        D3D9::RenderTargetData* plasthd = (D3D9::RenderTargetData*)prt->GetRenderTargetData();
        if ( plasthd->pDSSurface )
        {
            plasthd->pDSSurface->Release();
            plasthd->pDSSurface = 0;
        }
        plasthd->pDepthStencilBuffer = 0;
    }

    Matrices->CopyFrom(&entry.OldMatrixState);
    ViewRect = entry.OldViewRect;
    VP = entry.OldViewport;

    RenderTargetStack.PopBack();
    RenderTargetData* phd = 0;
    if ( RenderTargetStack.GetSize() > 0 )
    {
        RenderTargetEntry& back = RenderTargetStack.Back();
        phd = (D3D9::RenderTargetData*)back.pRenderTarget->GetRenderTargetData();

		pOldSurface = phd->pRenderSurface;
    }

    if ( RenderTargetStack.GetSize() == 1 )
        HALState &= ~HS_InRenderTarget;

    // Unbind the texture if it is bound (can't have a texture bound as an input and target).
    pTextureManager->SetSamplerState(0, 0);
    pTextureManager->SetSamplerState(1, 0);

    // Restore the old render target on the device.
    pDevice->SetRenderTarget(0, phd->pRenderSurface);
    if ( phd->pDSSurface )
        pDevice->SetDepthStencilSurface(phd->pDSSurface);
    else
        pDevice->SetDepthStencilSurface(0);

    ++AccumulatedStats.RTChanges;

    // Reset the viewport to the last render target on the stack.
    HALState |= HS_ViewValid;
    updateViewport();

	pDevice->GetRenderTarget( 0, &pDeviceSurface );
	char buffer[128] = { 0 };
	sprintf( buffer, "pop render target: Device: 0x%p, Old: 0x%p, Current: 0x%p\n", 
		pDeviceSurface, pOldSurface, pCurrentSurface );
	OutputDebugString( buffer );
	pDeviceSurface->Release();

}

bool HAL::createDefaultRenderBuffer()
{
    ImageSize rtSize;

    if ( GetDefaultRenderTarget() )
    {
        RenderTarget* prt = GetDefaultRenderTarget();
        rtSize = prt->GetSize();
    }
    else
    {
        IDirect3DSurface9* prenderTarget = 0;
        IDirect3DSurface9* pdsTarget = 0;
        D3DSURFACE_DESC rtDesc;
        if (FAILED(pDevice->GetRenderTarget(0, &prenderTarget)) ||             
            FAILED(prenderTarget->GetDesc(&rtDesc)) )
        {
            return false;
        }
        rtSize = ImageSize(rtDesc.Width, rtDesc.Height);

        Ptr<DepthStencilBuffer> pdsb = 0;
        D3DSURFACE_DESC dsDesc;
        ImageSize dsSize(0);
        if ( SUCCEEDED(pDevice->GetDepthStencilSurface(&pdsTarget)) &&
            SUCCEEDED(pdsTarget->GetDesc(&dsDesc)))
        {
            dsSize.SetSize(dsDesc.Width, dsDesc.Height);
            pdsb = *SF_HEAP_AUTO_NEW(this) DepthStencilBuffer(0, dsSize);
        }
        Ptr<RenderTarget> ptarget = *SF_HEAP_AUTO_NEW(this) RenderTarget(0, RBuffer_Default, rtSize );
        RenderTargetData::UpdateData(ptarget, prenderTarget, pdsb, pdsTarget );

        if ( pdsTarget )
            pdsTarget->Release();
        prenderTarget->Release();

        if ( !SetRenderTarget(ptarget))
            return false;
    }

    return pRenderBufferManager->Initialize(pTextureManager, Image_B8G8R8A8, rtSize);
}

void HAL::PushFilters(FilterPrimitive* prim)
{
    GetEvent(Event_Filter).Begin(__FUNCTION__);
    if (!checkState(HS_InDisplay, __FUNCTION__))
        return;

    FilterStackEntry e = {prim, 0};

    // Do not render filters if the profile does not support it (unfiltered content will be rendered).
    if (!shouldRenderFilters(prim))
    {
        FilterStack.PushBack(e);
        return;
    }

    // Queue the profiler off of whether masks should be draw or not.
    if ( !Profiler.ShouldDrawMask() )
    {
        Profiler.SetDrawMode(2);

        unsigned fillflags = 0;
        float colorf[4];
        Profiler.GetColor(0xFFFFFFFF).GetRGBAFloat(colorf);
        const ShaderManager::Shader& pso = SManager.SetFill(PrimFill_SolidColor, fillflags,
            PrimitiveBatch::DP_Batch,  MappedXY16iAlphaSolid[PrimitiveBatch::DP_Batch], &ShaderData);
        Matrix2F mvp(prim->GetFilterAreaMatrix().GetMatrix2D(), Matrices->UserView);
        ShaderData.SetMatrix(pso, Uniform::SU_mvp, mvp);
        ShaderData.SetUniform(pso, Uniform::SU_cxmul, colorf, 4);
        ShaderData.Finish(1);

        setLinearStreamSource(PrimitiveBatch::DP_Batch);
        pDevice->SetStreamSource(0, Cache.pMaskEraseBatchVertexBuffer.GetPtr(),
            0, sizeof(VertexXY16iAlpha));
        drawPrimitive(6,1);
        FilterStack.PushBack(e);
        return;
    }

    if ( (HALState & HS_CachedFilter) )
    {
        FilterStack.PushBack(e);
        return;
    }

    // Disable masking from previous target, if this filter primitive doesn't have any masking.
    if ( MaskStackTop != 0 && !prim->GetMaskPresent() && prim->GetCacheState() != FilterPrimitive::Cache_Target )
    {
        if ( StencilAvailable )
            pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
        else if ( DepthBufferAvailable )
            pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALL);
    }

    HALState |= HS_DrawingFilter;

    if ( prim->GetCacheState() ==  FilterPrimitive::Cache_Uncached )
    {
        // Draw the filter from scratch.
        const Matrix2F& m = e.pPrimitive->GetFilterAreaMatrix().GetMatrix2D();
        e.pRenderTarget = *CreateTempRenderTarget(ImageSize((UInt32)m.Sx(), (UInt32)m.Sy()), prim->GetMaskPresent());
        RectF frameRect(m.Tx(), m.Ty(), m.Tx() + m.Sx(), m.Ty() + m.Sy());
        PushRenderTarget(frameRect, e.pRenderTarget);
        applyBlendMode(BlendModeStack.GetSize()>=1 ? BlendModeStack.Back() : Blend_Normal, false, true);

        // If this primitive has masking, then clear the entire area to the current mask level, because 
        // the depth stencil target may be different, and thus does not contain the previously written values.
        if ( prim->GetMaskPresent())
        {
            if (StencilAvailable)
                pDevice->Clear(0, 0, D3DCLEAR_STENCIL, 0, 0.0f, (DWORD)MaskStackTop);
            else if (DepthBufferAvailable)
                pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0); // Z -> 1.0f
        }
    }
    else
    {
        // Drawing a cached filter, ignore all draw calls until the corresponding PopFilters.
        // Keep track of the level at which we need to draw the cached filter, by adding entries to the stack.
        HALState |= HS_CachedFilter;
        CachedFilterIndex = (int)FilterStack.GetSize();
		GetRQProcessor().SetQueueEmitFilter(RenderQueueProcessor::QPF_Filters);
    }
    FilterStack.PushBack(e);
}

void HAL::drawUncachedFilter(const FilterStackEntry& e)
{
    const FilterSet* filters = e.pPrimitive->GetFilters();
    unsigned filterCount = filters->GetFilterCount();
    const Filter* filter = 0;
    unsigned pass = 0, passes = 0;

    // Invalid primitive or rendertarget.
    if ( !e.pPrimitive || !e.pRenderTarget )
        return;

    // Bind the render target.
    SF_ASSERT(RenderTargetStack.Back().pRenderTarget == e.pRenderTarget);
    const int MaxTemporaryTextures = 3;
    Ptr<RenderTarget> temporaryTextures[MaxTemporaryTextures];
    memset(temporaryTextures, 0, sizeof temporaryTextures);

    // Fill our the source target.
    ImageSize size = e.pRenderTarget->GetSize();
    temporaryTextures[0] = e.pRenderTarget;

    setLinearStreamSource(PrimitiveBatch::DP_Batch);
    pDevice->SetStreamSource(0, Cache.pMaskEraseBatchVertexBuffer.GetPtr(),
                             0, sizeof(VertexXY16iAlpha));

    pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALL);
    // Overlay mode isn't actually supported, it contains the blend mode for filter sub-targets.
    applyBlendMode(Blend_Overlay, true, false);

    // Render filter(s).
    unsigned shaders[ShaderManager::MaximumFilterPasses];
    for ( unsigned i = 0; i < filterCount; ++i )
    {
        filter = filters->GetFilter(i);
        passes = SManager.GetFilterPasses(filter, FillFlags, shaders);

        // All shadows (except those hiding the object) need the original texture.
        bool requireSource = false;
        if ( filter->GetFilterType() >= Filter_Shadow &&
             filter->GetFilterType() <= Filter_Blur_End )
        {
            temporaryTextures[Target_Original] = temporaryTextures[Target_Source];
            requireSource = true;
        }

        // Now actually render the filter.
        for (pass = 0; pass < passes; ++pass)
        {
            // Render the final pass directly to the target surface.
            if (pass == passes-1 && i == filterCount-1)
                break;

            // Create a destination texture if required.
            if ( !temporaryTextures[1] )
            {
                temporaryTextures[1] = *CreateTempRenderTarget(size, false);
            }

            IDirect3DSurface9* psurface = ((D3D9::RenderTargetData*)temporaryTextures[1]->GetRenderTargetData())->pRenderSurface;
            pDevice->SetRenderTarget(0, psurface);
            pDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0,0,0,0), 1.0f,  0);
            ++AccumulatedStats.RTChanges;
            
            // Scale to the size of the destination.
            RenderTarget* prt = temporaryTextures[1];
            const Rect<int>& viewRect = prt->GetRect(); // On the render texture, might not be the entire surface.
            const ImageSize& bs = prt->GetBufferSize();
            VP = Viewport(bs.Width, bs.Height, viewRect.x1, viewRect.y1, viewRect.Width(), viewRect.Height());    
            ViewRect = Rect<int>(viewRect.x1, viewRect.y1, viewRect.x2, viewRect.y2);
            HALState |= HS_ViewValid;
            updateViewport();

            Matrix2F mvp = Matrix2F::Scaling(2,-2) * Matrix2F::Translation(-0.5f, -0.5f);                          
            mvp.Tx() -= 1.0f/size.Width;   // D3D9 1/2 pixel center offset
            mvp.Ty() += 1.0f/size.Height;

            SManager.SetFilterFill(mvp, Cxform::Identity, filter, temporaryTextures, shaders, pass, passes, 
                MappedXY16iAlphaTexture[PrimitiveBatch::DP_Single], &ShaderData);
            drawPrimitive(6,1);
            pTextureManager->SetSamplerState(0, 0);
            pTextureManager->SetSamplerState(1, 0);

            // If we require the original source, create a new target for the source.
            if ( requireSource && pass == 0)
                temporaryTextures[0] = *CreateTempRenderTarget(size, false);

            // Setup for the next pass.
            Alg::Swap(temporaryTextures[0], temporaryTextures[1]);
        }
    }

    // If there were no passes, assume we were doing a cacheAsBitmap.
    bool cacheAsBitmap = passes == 0;
    SF_DEBUG_ASSERT(!cacheAsBitmap || filterCount == 1, "Expected exactly one cacheAsBitmap filter.");

    // Cache the 2nd last step so it might be available as a cached filter next time.
    if (temporaryTextures[Target_Source] && (Profiler.IsFilterCachingEnabled() || cacheAsBitmap))
    {
        // If there were no passes, assume we were doing a cacheAsBitmap.
        RenderTarget* cacheResults[2] = { temporaryTextures[0], temporaryTextures[2] };        
        e.pPrimitive->SetCacheResults(cacheAsBitmap ? FilterPrimitive::Cache_Target : FilterPrimitive::Cache_PreTarget, cacheResults, cacheAsBitmap ? 1 : 2);
        ((D3D9::RenderTargetData*)cacheResults[0]->GetRenderTargetData())->CacheID = reinterpret_cast<UPInt>(e.pPrimitive.GetPtr());
        if ( cacheResults[1] )
            ((D3D9::RenderTargetData*)cacheResults[1]->GetRenderTargetData())->CacheID = reinterpret_cast<UPInt>(e.pPrimitive.GetPtr());
    }
    else
    {
        // This is required, or else disabling filter caching may produce incorrect results.
        e.pPrimitive->SetCacheResults(FilterPrimitive::Cache_Uncached, 0, 0);
    }
    

    // Pop the temporary target, begin rendering to the previous surface.
    PopRenderTarget();

    // Re-[en/dis]able masking from previous target, if available.
    if ( MaskStackTop != 0 )
    {
        if ( StencilAvailable )
            pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE );
        else if ( DepthBufferAvailable )
            pDevice->SetRenderState(D3DRS_ZENABLE, TRUE );
    }

    // Now actually draw the filtered sub-scene to the target below.
    if (passes != 0)
    {
        // 'Real' filter.
        const Matrix2F& mvp = Matrices->UserView * e.pPrimitive->GetFilterAreaMatrix().GetMatrix2D();
        const Cxform&   cx  = e.pPrimitive->GetFilterAreaMatrix().GetCxform();
        SManager.SetFilterFill(mvp, cx, filter, temporaryTextures, shaders, pass, passes, 
            MappedXY16iAlphaTexture[PrimitiveBatch::DP_Single], &ShaderData);
        applyBlendMode(BlendModeStack.GetSize()>=1 ? BlendModeStack.Back() : Blend_Normal, true, true);
        drawPrimitive(6,1);
        applyBlendMode(BlendModeStack.GetSize()>=1 ? BlendModeStack.Back() : Blend_Normal, false, (HALState&HS_InRenderTarget) != 0);
    }
    else
    {
        // CacheAsBitmap
        drawCachedFilter(e.pPrimitive);
    }

    // Re-[en/dis]able masking from previous target, if available.
    if ( HALState & HS_DrawingMask )
        pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0 );

    // Cleanup.
    for ( unsigned i = 0; i < MaxTemporaryTextures; ++i )
    {
        pTextureManager->SetSamplerState(i, 0);
        if (temporaryTextures[i])
            temporaryTextures[i]->SetInUse(false);
    }
    AccumulatedStats.Filters += filters->GetFilterCount();
}

void HAL::drawCachedFilter(FilterPrimitive* primitive)
{
    setLinearStreamSource(PrimitiveBatch::DP_Batch);
    pDevice->SetStreamSource(0, Cache.pMaskEraseBatchVertexBuffer.GetPtr(),
                             0, sizeof(VertexXY16iAlpha));

    const int MaxTemporaryTextures = 3;
    switch(primitive->GetCacheState())
    {
        // We have one-step from final target. Render it to a final target now.
        case FilterPrimitive::Cache_PreTarget:
        {
            const FilterSet* filters = primitive->GetFilters();
            UPInt filterIndex = filters->GetFilterCount()-1;
            const Filter* filter = filters->GetFilter(filterIndex);
            unsigned shaders[ShaderManager::MaximumFilterPasses];
            unsigned passes = SManager.GetFilterPasses(filter, FillFlags, shaders);

            // Fill out the temporary textures from the cached results.
            Ptr<RenderTarget> temporaryTextures[MaxTemporaryTextures];
            memset(temporaryTextures, 0, sizeof temporaryTextures);
            RenderTarget* results[2];
            primitive->GetCacheResults(results, 2);
            temporaryTextures[0] = results[0];
            ImageSize size = temporaryTextures[0]->GetSize();
            temporaryTextures[1] = *CreateTempRenderTarget(size, false);
            temporaryTextures[2] = results[1];
            PushRenderTarget(RectF((float)size.Width,(float)size.Height), temporaryTextures[1]);

            // Render to the target.
            Matrix2F mvp = Matrix2F::Scaling(2,-2) * Matrix2F::Translation(-0.5f, -0.5f);
            mvp.Tx() -= 1.0f/size.Width;   // D3D9 1/2 pixel center offset
            mvp.Ty() += 1.0f/size.Height;
            SManager.SetFilterFill(mvp, Cxform::Identity, filter, temporaryTextures, shaders, passes-1, passes, 
                MappedXY16iAlphaTexture[PrimitiveBatch::DP_Single], &ShaderData);
            applyBlendMode(BlendModeStack.GetSize()>=1 ? BlendModeStack.Back() : Blend_Normal, true, true);
            drawPrimitive(6,1);
            pTextureManager->SetSamplerState(0, 0);
            pTextureManager->SetSamplerState(1, 0);
            PopRenderTarget();

            // Re-[en/dis]able masking from previous target, if available.
            if ( MaskStackTop != 0 )
            {
                if ( StencilAvailable )
                    pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE );
                else if ( DepthBufferAvailable )
                    pDevice->SetRenderState(D3DRS_ZENABLE, TRUE );
            }

            // Re-[en/dis]able masking from previous target, if available.
            if ( HALState & HS_DrawingMask )
                pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0 );

            // Set this as the final cache result, and then render it.
            RenderTarget* prt = temporaryTextures[1];
            primitive->SetCacheResults(FilterPrimitive::Cache_Target, &prt, 1);
            ((D3D9::RenderTargetData*)prt->GetRenderTargetData())->CacheID = reinterpret_cast<UPInt>(primitive);
            drawCachedFilter(primitive);

            // Cleanup.
            for ( unsigned i = 0; i < MaxTemporaryTextures; ++i )
            {
                if (temporaryTextures[i])
                    temporaryTextures[i]->SetInUse(false);
            }
            break;
        }

        // We have a final filtered texture. Just apply it to a screen quad.
        case FilterPrimitive::Cache_Target:
        {
            unsigned fillFlags = (FillFlags|FF_Cxform|FF_AlphaWrite);
            const ShaderManager::Shader& pso = SManager.SetFill(PrimFill_Texture, fillFlags, PrimitiveBatch::DP_Single, 
                MappedXY16iAlphaTexture[PrimitiveBatch::DP_Single], &ShaderData);

            RenderTarget* results;
            primitive->GetCacheResults(&results, 1);
            Texture* ptexture = (D3D9::Texture*)results->GetTexture();
            const Matrix2F& mvp = Matrices->UserView * primitive->GetFilterAreaMatrix().GetMatrix2D();
            const Rect<int>& srect = results->GetRect();
            Matrix2F texgen;
            texgen.AppendTranslation((float)srect.x1, (float)srect.y1);
            texgen.AppendScaling((float)srect.Width() / ptexture->GetSize().Width, (float)srect.Height() / ptexture->GetSize().Height);

            const Cxform & cx = primitive->GetFilterAreaMatrix().GetCxform();
            ShaderData.SetCxform(pso, cx);
            ShaderData.SetUniform(pso, Uniform::SU_mvp, &mvp.M[0][0], 8 );
            ShaderData.SetUniform(pso, Uniform::SU_texgen, &texgen.M[0][0], 8 );
            ShaderData.SetTexture(pso, Uniform::SU_tex, ptexture, ImageFillMode(Wrap_Clamp, Sample_Linear));
            ShaderData.Finish(1);

            applyBlendMode(BlendModeStack.GetSize()>=1 ? BlendModeStack.Back() : Blend_Normal, true, true);
            drawPrimitive(6,1);
            applyBlendMode(BlendModeStack.GetSize()>=1 ? BlendModeStack.Back() : Blend_Normal, false, (HALState&HS_InRenderTarget)!=0);
            pTextureManager->SetSamplerState(0, 0);
            pTextureManager->SetSamplerState(1, 0);

            // Cleanup.
            results->SetInUse(false);
            if ( !Profiler.IsFilterCachingEnabled() )
                primitive->SetCacheResults(FilterPrimitive::Cache_Uncached, 0, 0);
            break;
        }

        // Should have been one of the other two caching types.
        default: SF_ASSERT(0); break;
    }
}


void HAL::setBatchUnitSquareVertexStream()
{
    setLinearStreamSource(PrimitiveBatch::DP_Batch);
    pDevice->SetStreamSource(0, Cache.pMaskEraseBatchVertexBuffer.GetPtr(),
        0, sizeof(VertexXY16iAlpha));
}

void HAL::drawPrimitive(unsigned indexCount, unsigned meshCount)
{
    pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, indexCount / 3);

    SF_UNUSED(meshCount);
#if !defined(SF_BUILD_SHIPPING)
    AccumulatedStats.Meshes += meshCount;
    AccumulatedStats.Triangles += indexCount / 3;
    AccumulatedStats.Primitives++;
#endif
}

void HAL::drawIndexedPrimitive( unsigned indexCount, unsigned vertexCount, unsigned meshCount, UPInt indexOffset, unsigned vertexBaseIndex)
{
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, (INT)vertexBaseIndex, 0, vertexCount, (UINT)indexOffset, indexCount / 3 );

    SF_UNUSED(meshCount);
#if !defined(SF_BUILD_SHIPPING)
    AccumulatedStats.Meshes += meshCount;
    AccumulatedStats.Triangles += indexCount / 3;
    AccumulatedStats.Primitives++;
#endif
}

void HAL::drawIndexedInstanced( unsigned indexCount, unsigned vertexCount, unsigned meshCount, UPInt indexOffset, unsigned vertexBaseIndex)
{
    pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, (INT)vertexBaseIndex, 0, vertexCount, (UINT)indexOffset, indexCount / 3 );

    SF_UNUSED(meshCount);
#if !defined(SF_BUILD_SHIPPING)
    AccumulatedStats.Meshes += meshCount;
    AccumulatedStats.Triangles += (indexCount / 3) * meshCount;
    AccumulatedStats.Primitives++;
#endif
}


bool HAL::shouldRenderFilters(const FilterPrimitive* prim) const
{
    if ( SManager.HasDynamicLoopingSupport() )
        return true;

    // If the profile doesn't support dynamic loops, check to see if there are any ColorMatrix
    // filters, which can still be rendered. If there are, allow filtering still.
    const FilterSet* filters = prim->GetFilters();
    unsigned filterCount = filters->GetFilterCount();
    for ( unsigned f = 0; f < filterCount; ++f )
    {
        const Filter* filter = filters->GetFilter(f);
        if ( filter->GetFilterType() == Filter_ColorMatrix )
            return true;
    }
    return false;
}

Render::RenderEvent& HAL::GetEvent(EventType eventType)
{
#if !defined(SF_BUILD_SHIPPING)
    static D3D9::RenderEvent D3D9Events[Event_Count];
    return D3D9Events[eventType];
#else
    // Shipping builds just return a default event, which does nothing.
    return Render::HAL::GetEvent(eventType);
#endif
}

void HAL::drawScreenQuad()
{
    // Set the vertices, and Draw
    setLinearStreamSource(PrimitiveBatch::DP_Batch);
    pDevice->SetStreamSource(0, Cache.pMaskEraseBatchVertexBuffer.GetPtr(),
        0, sizeof(VertexXY16iAlpha));
	drawPrimitive(6,1);
}

}}} // Scaleform::Render::D3D9

