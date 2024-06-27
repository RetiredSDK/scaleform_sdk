/**********************************************************************

PublicHeader:   Render
Filename    :   Render_ShaderHAL.h
Content     :   Provides common functionality for HALs which have ShaderManagers
                as their primary rendering pipelines
Created     :   2012/09/18
Authors     :   Bart Muzzin

Copyright   :   Copyright 2012 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

***********************************************************************/

#ifndef INC_SF_Render_ShaderHAL_H
#define INC_SF_Render_ShaderHAL_H

#include "Render/Render_HAL.h"
namespace Scaleform { namespace Render {

template <class ShaderManagerType, class ShaderInterfaceType>
class ShaderHAL : public HAL
{
public:
    typename ShaderManagerType::Shader Shader;

    ShaderHAL(ThreadCommandQueue *commandQueue = 0);

    // *** DrawableImage
    virtual void DrawableCxform( Render::Texture** tex, const Matrix2F* texgen, const Cxform* cx);
    virtual void DrawableCompare( Render::Texture** tex, const Matrix2F* texgen );
    virtual void DrawableCopyChannel( Render::Texture** tex, const Matrix2F* texgen, const Matrix4F* cxmul ) 
    { DrawableMerge(tex, texgen, cxmul); }
    virtual void DrawableMerge( Render::Texture** tex, const Matrix2F* texgen, const Matrix4F* cxmul );
    virtual void DrawableCopyPixels( Render::Texture** tex, const Matrix2F* texgen, const Matrix2F& mvp, bool mergeAlpha, bool destAlpha );
    virtual void DrawablePaletteMap( Render::Texture** tex, const Matrix2F* texgen, const Matrix2F& mvp, unsigned channelMask, const UInt32* values);
    virtual void DrawableCopyback( Render::Texture* tex, const Matrix2F& mvp, const Matrix2F& texgen );

    ShaderManagerType            SManager;      // Holds shader code, responsible applying ShaderInterace data to the pipeline.
    ShaderInterfaceType          ShaderData;    // Holds data about currently executing pipeline (shaders, uniforms, etc).

protected:

    // *** Initialization/Shutdown
    virtual bool initHAL(const HALInitParams& params);
    virtual bool shutdownHAL();

    virtual void setBatchUnitSquareVertexStream() = 0;
    virtual void drawPrimitive(unsigned indexCount, unsigned meshCount) = 0;

    virtual void drawMaskClearRectangles(const HMatrix* matrices, UPInt count);

    // Cached mappings of VertexXY16iAlpha vertex format.
    VertexFormat* MappedXY16iAlphaTexture[PrimitiveBatch::DP_DrawableCount];
    VertexFormat* MappedXY16iAlphaSolid[PrimitiveBatch::DP_DrawableCount];
};

//------------------------------------------------------------------------------------------------------------
template<class ShaderManagerType, class ShaderInterfaceType>
inline ShaderHAL<ShaderManagerType, ShaderInterfaceType>::ShaderHAL(ThreadCommandQueue *commandQueue) : 
    HAL(commandQueue),
    SManager(&Profiler),
    ShaderData(getThis()) 
{
    memset(MappedXY16iAlphaTexture, 0, sizeof(MappedXY16iAlphaTexture));
    memset(MappedXY16iAlphaSolid, 0, sizeof(MappedXY16iAlphaSolid));
}


template<class ShaderManagerType, class ShaderInterfaceType>
inline void ShaderHAL<ShaderManagerType, ShaderInterfaceType>::DrawableCxform( Render::Texture** tex, const Matrix2F* texgen, const Cxform* cx)
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_DICxform), __FUNCTION__);
    SManager.SetDrawableCxform(tex, texgen, RenderTargetStack.Back().pRenderTarget->GetSize(), cx, 
        MappedXY16iAlphaTexture[PrimitiveBatch::DP_Single], &ShaderData, ShaderManagerType::GetDrawableImageFlags() );
    drawScreenQuad();
}

template<class ShaderManagerType, class ShaderInterfaceType>
inline void ShaderHAL<ShaderManagerType, ShaderInterfaceType>::DrawableCompare( Render::Texture** tex, const Matrix2F* texgen )
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_DICompare), __FUNCTION__);
    SManager.SetDrawableCompare(tex, texgen, RenderTargetStack.Back().pRenderTarget->GetSize(), 
        MappedXY16iAlphaTexture[PrimitiveBatch::DP_Single], &ShaderData, ShaderManagerType::GetDrawableImageFlags() );
    drawScreenQuad();
}

template<class ShaderManagerType, class ShaderInterfaceType>
inline void ShaderHAL<ShaderManagerType, ShaderInterfaceType>::DrawableMerge( Render::Texture** tex, const Matrix2F* texgen, const Matrix4F* cxmul )
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_DIMerge), __FUNCTION__);
    SManager.SetDrawableMergeFill(tex, texgen, RenderTargetStack.Back().pRenderTarget->GetSize(), 
        cxmul, MappedXY16iAlphaTexture[PrimitiveBatch::DP_Single], &ShaderData, ShaderManagerType::GetDrawableImageFlags() );

    drawScreenQuad();
}

template<class ShaderManagerType, class ShaderInterfaceType>
inline void ShaderHAL<ShaderManagerType, ShaderInterfaceType>::DrawableCopyPixels( Render::Texture** tex, const Matrix2F* texgen, const Matrix2F& mvp, bool mergeAlpha, bool destAlpha )
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_DICopyPixels), __FUNCTION__);
    SManager.SetDrawableCopyPixelsFill(tex, texgen, RenderTargetStack.Back().pRenderTarget->GetSize(), mvp,
        mergeAlpha, destAlpha, MappedXY16iAlphaTexture[PrimitiveBatch::DP_Single], &ShaderData, 
        ShaderManagerType::GetDrawableImageFlags() );

    drawScreenQuad();
}

template<class ShaderManagerType, class ShaderInterfaceType>
inline void ShaderHAL<ShaderManagerType, ShaderInterfaceType>::DrawablePaletteMap( Render::Texture** tex, const Matrix2F* texgen, const Matrix2F& mvp, unsigned channelMask, const UInt32* values)
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_DIPaletteMap), __FUNCTION__);

    // Create a temporary texture with the palette map. There may be a more efficient way to do this; however, using
    // uniforms seems unworkable, due to shader constant slot constraints.
    ImageData data;
    Render::TextureManager* mgr = GetTextureManager();
    Ptr<Render::Texture> ptex = *mgr->CreateTexture(mgr->GetDrawableImageFormat(), 1, ImageSize(256, 4), ImageUse_Map_Mask, 0);
    if ( !ptex->Map(&data, 0, 1) )
        return;
    for ( int channel = 0; channel < 4; ++channel )
    {
        UInt32* dataPtr = (UInt32*)data.GetScanline(channel);
        if ( channelMask & (1<<channel))
        {
            memcpy(dataPtr, values + channel*256, 256*sizeof(UInt32));
        }
        else
        {
            // Channel was not provided, just do a straight mapping.
            for ( unsigned i = 0; i < 256; ++i )
                *dataPtr++ = (i << (channel*8));
        }
    }
    if (!ptex->Unmap())
        return;

    // First pass overwrites everything.
    applyBlendMode(Blend_OverwriteAll, true, true);
    SManager.SetDrawablePaletteMap(tex, texgen, RenderTargetStack.Back().pRenderTarget->GetSize(), mvp,
        ptex, MappedXY16iAlphaTexture[PrimitiveBatch::DP_Single], &ShaderData, ShaderManagerType::GetDrawableImageFlags() );

    drawScreenQuad();
}

template<class ShaderManagerType, class ShaderInterfaceType>
inline void ShaderHAL<ShaderManagerType, ShaderInterfaceType>::DrawableCopyback( Render::Texture* source, const Matrix2F& mvpOriginal, const Matrix2F& texgen )
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_DICopyback), __FUNCTION__);

    // Set shader constants.
    unsigned fillFlags = 0;
    const typename ShaderManagerType::Shader& pso = SManager.SetFill(PrimFill_Texture, fillFlags, PrimitiveBatch::DP_Single, 
        MappedXY16iAlphaTexture[PrimitiveBatch::DP_Single], &ShaderData);    

    Matrix2F mvp = mvpOriginal;
    if (ShaderManagerType::GetDrawableImageFlags() & ShaderManagerType::Base::CPF_HalfPixelOffset)
    {
        // D3D9 1/2 pixel center offset
        mvp.Tx() -= 1.0f/RenderTargetStack.Back().pRenderTarget->GetSize().Width;   
        mvp.Ty() += 1.0f/RenderTargetStack.Back().pRenderTarget->GetSize().Height;
    }

    ShaderData.SetMatrix(pso,  ShaderManagerType::UniformType::SU_mvp,    mvp);
    ShaderData.SetMatrix(pso,  ShaderManagerType::UniformType::SU_texgen, texgen);
    ShaderData.SetTexture(pso, ShaderManagerType::UniformType::SU_tex,    source, ImageFillMode());
    ShaderData.Finish(1);

    drawScreenQuad();
}

template<class ShaderManagerType, class ShaderInterfaceType>
inline bool ShaderHAL<ShaderManagerType, ShaderInterfaceType>::initHAL(const HALInitParams& params)
{
    if (!Render::HAL::initHAL(params))
        return false;

    // Map the vertex format that we use internally for DrawableImage/Filters/Clears
    MapVertexFormat(PrimFill_Texture, &VertexXY16iAlpha::Format, 
        (const VertexFormat**)&MappedXY16iAlphaTexture[PrimitiveBatch::DP_Single],
        (const VertexFormat**)&MappedXY16iAlphaTexture[PrimitiveBatch::DP_Batch], 
        (const VertexFormat**)&MappedXY16iAlphaTexture[PrimitiveBatch::DP_Instanced],
        MeshCacheItem::Mesh_Regular);
    MapVertexFormat(PrimFill_SolidColor, &VertexXY16iAlpha::Format, 
        (const VertexFormat**)&MappedXY16iAlphaSolid[PrimitiveBatch::DP_Single],
        (const VertexFormat**)&MappedXY16iAlphaSolid[PrimitiveBatch::DP_Batch], 
        (const VertexFormat**)&MappedXY16iAlphaSolid[PrimitiveBatch::DP_Instanced],
        MeshCacheItem::Mesh_Regular);

    return true;
}

template<class ShaderManagerType, class ShaderInterfaceType>
inline bool ShaderHAL<ShaderManagerType, ShaderInterfaceType>::shutdownHAL()
{
    if (!Render::HAL::shutdownHAL())
        return false;

    for (unsigned i = 0; i < PrimitiveBatch::DP_DrawableCount; ++i )
    {
        if (MappedXY16iAlphaTexture[i])
            MappedXY16iAlphaTexture[i]->pSysFormat = 0;
        MappedXY16iAlphaTexture[i] = 0;
        if (MappedXY16iAlphaSolid[i])
            MappedXY16iAlphaSolid[i]->pSysFormat = 0;
        MappedXY16iAlphaSolid[i] = 0;
    }
    return true;
}

template<class ShaderManagerType, class ShaderInterfaceType>
inline void ShaderHAL<ShaderManagerType, ShaderInterfaceType>::drawMaskClearRectangles(const HMatrix* matrices, UPInt count)
{
    ScopedRenderEvent GPUEvent(GetEvent(Event_MaskClear), "HAL::drawMaskClearRectangles");

    // This operation is used to clear bounds for masks.
    // Potential issue: Since our bounds are exact, right/bottom pixels may not
    // be drawn due to HW fill rules.
    //  - This shouldn't matter if a mask is tessellated within bounds of those
    //    coordinates, since same rules are applied to those render shapes.
    //  - EdgeAA must be turned off for masks, as that would extrude the bounds.

    unsigned fillflags = 0;

    const typename ShaderManagerType::Shader& pso = SManager.SetFill(PrimFill_SolidColor, fillflags, PrimitiveBatch::DP_Batch, 
        MappedXY16iAlphaSolid[PrimitiveBatch::DP_Batch], &ShaderData);
    unsigned drawRangeCount = 0;

    setBatchUnitSquareVertexStream();

    for (UPInt i = 0; i < count; i+= (UPInt)drawRangeCount)
    {
        drawRangeCount = Alg::Min<unsigned>((unsigned)count, SF_RENDER_MAX_BATCHES);

        for (unsigned j = 0; j < drawRangeCount; j++)
        {
            ShaderData.SetMatrix(pso, ShaderManagerType::UniformType::SU_mvp, Matrix2F::Identity, matrices[i+j], Matrices, 0, j);

            // Color writes should be disabled, so although the shader does have a cxmul uniform, we don't really need to set it.
            const float colorf[] = {1,0,0,0.5f};
            ShaderData.SetUniform(pso, ShaderManagerType::UniformType::SU_cxmul, colorf, 4);
        }
        ShaderData.Finish(drawRangeCount);
        drawPrimitive(drawRangeCount * 6, drawRangeCount);
    }
}


}}; // Scaleform::Render

#endif // INC_SF_Render_ShaderHAL_H
