/**************************************************************************

Filename    :   GL_HAL.h
Content     :   Renderer HAL Prototype header.
Created     :   
Authors     :   

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_SF_Render_GL_HAL_H
#define INC_SF_Render_GL_HAL_H

#include "Render/Render_HAL.h"
#include "Render/GL/GL_MeshCache.h"
#include "Render/GL/GL_Shader.h"
#include "Render/GL/GL_Texture.h"
#include "Render/Render_ShaderHAL.h"    // Must be included after platform specific shader includes.

namespace Scaleform { namespace Render { namespace GL {

// HALConfigFlags enumeration defines system-specific HAL configuration
// flags passed into InitHAL though HALInitParams.
enum HALConfigFlags
{
    // Only compile shaders when they are actually used. This can reduce startup-times,
    // however, compiling shaders dynamically can cause performance spikes during playback.
    // Note that if binary shaders are available in the OpenGL/ES implementation and not explicitly
    // disabled by using HALConfig_DisableBinaryShaders, this flag is ignored, and all shaders are
    // loaded at startup. They subsequently will be loaded from disk, which is much faster.
    HALConfig_DynamicShaderCompile  = 0x00000001,

    // Disables the use of binary shaders (loading and saving), even if the OpenGL/ES implementation
    // has the required support for it. 
    HALConfig_DisableBinaryShaders  = 0x00000002,
};

// GL::HALInitParams provides OpenGL-specific rendering initialization
// parameters for HAL::InitHAL.

struct HALInitParams : public Render::HALInitParams
{
    String BinaryShaderPath;
    bool NoVAO;
    bool NoInstancing;

    HALInitParams(UInt32 halConfigFlags = 0,
                  ThreadId renderThreadId = ThreadId(),
                  const String& binaryShaderPath = String(),
                  bool noVao = false,
                  bool noInstancing = false) : 
        Render::HALInitParams(0, halConfigFlags, renderThreadId),
        BinaryShaderPath(binaryShaderPath),
        NoVAO(noVao),
        NoInstancing(noInstancing)
    { }

    // GL::TextureManager accessors for correct type.
    void            SetTextureManager(TextureManager* manager) { pTextureManager = manager; }
    TextureManager* GetTextureManager() const       { return (TextureManager*) pTextureManager.GetPtr(); }
};

enum CapFlags
{
    Cap_Align           = MVF_Align,

    Cap_NoBatching      = 0x010,

    // Caps for buffers in mesh cache. Static buffers are still used even if none of these caps are set.
    Cap_MapBuffer       = 0x020,
    Cap_BufferUpdate    = 0x040,
    Cap_UseMeshBuffers  = Cap_MapBuffer | Cap_BufferUpdate,

    // Caps for shaders. 
    Cap_NoDynamicLoops  = 0x080, // profile does not support dynamic looping.
    Cap_BinaryShaders   = 0x100, // profile supports loading binary shaders (GLES 2.0)

    // Caps for drawing.
    Cap_Instancing      = 0x200, // profile supports instancing (DrawArraysInstanced, and GLSL1.4+).
    
    Cap_NoVAO           = 0x400, // disable vertex array objects
    
    // GL_MAX_VERTEX_UNIFORM_VECTORS, or a different value on certain devices
    Cap_MaxUniforms       = 0xffff0000,
    Cap_MaxUniforms_Shift = 16,
    
    Caps_Standard         = Cap_MapBuffer
};

class MatrixState : public Render::MatrixState
{
public:
    MatrixState(HAL* phal) : Render::MatrixState((Render::HAL*)phal)
    { }

    MatrixState() : Render::MatrixState()
    { }

protected:
    virtual void        recalculateUVPOC() const;
};

class HAL : public Render::ShaderHAL<ShaderManager, ShaderInterface>
#ifdef SF_GL_RUNTIME_LINK
    , public GL::Extensions
#endif
{
public:
    bool                 MultiBitStencil;
    int                  EnabledVertexArrays;
    bool                 FilterVertexBufferSet;
    int                  BlendEnable;

    MeshCache            Cache;

    Ptr<TextureManager>  pTextureManager;
    
    // Previous batching mode
    PrimitiveBatch::BatchType PrevBatchType;

    unsigned&            Caps;

    // Self-accessor used to avoid constructor warning.
    HAL*      GetHAL() { return this; }

public:    
    

    HAL(ThreadCommandQueue* commandQueue = 0);
    virtual ~HAL();   

    // *** HAL Initialization and Shutdown

    // Initializes HAL for rendering.
    virtual bool        InitHAL(const GL::HALInitParams& params);

    // ShutdownHAL shuts down rendering, releasing resources allocated in InitHAL.
    virtual bool        ShutdownHAL();


    // Used when the current gl context is lost (GLES on some platforms)
    // or becomes incompatible with the new video mode
    virtual bool        ResetContext();

    // *** Rendering

    virtual bool        BeginFrame();
    virtual void        FinishFrame();
    virtual bool        BeginScene();
    virtual bool        EndScene();

    // Bracket the displaying of a frame from a movie.
    // Fill the background color, and set up default transforms, etc.
    virtual void        beginDisplay(BeginDisplayData* data);

    // Updates HW Viewport and ViewportMatrix based on the current
    // values of VP, ViewRect and ViewportValid.
    virtual void        updateViewport();


    virtual void        DrawProcessedPrimitive(Primitive* pprimitive,
                                               PrimitiveBatch* pstart, PrimitiveBatch *pend);

    virtual void        DrawProcessedComplexMeshes(ComplexMesh* p,
                                                   const StrideArray<HMatrix>& matrices);
    
    // *** Mask Support
    virtual void    PushMask_BeginSubmit(MaskPrimitive* primitive);    
    virtual void    EndMaskSubmit();
    virtual void    PopMask();

    virtual void    clearSolidRectangle(const Rect<int>& r, Color color);

    bool SetVertexArray(const VertexFormat* pFormat, MeshCacheItem* pmesh, unsigned vboffset = 0);
    bool SetVertexArray(const VertexFormat* pFormat, GLuint buffer, GLuint vao);


    // *** BlendMode
    virtual void       applyBlendModeImpl(BlendMode mode, bool sourceAc = false, bool forceAc = false);



    virtual Render::TextureManager* GetTextureManager() const
    {
        return pTextureManager.GetPtr();
    }

    virtual RenderTarget*   CreateRenderTarget(GLuint fbo);
    virtual RenderTarget*   CreateRenderTarget(Render::Texture* texture, bool needsStencil);
    virtual RenderTarget*   CreateTempRenderTarget(const ImageSize& size, bool needsStencil);
    virtual bool            SetRenderTarget(RenderTarget* target, bool setState = 1);
    virtual void            PushRenderTarget(const RectF& frameRect, RenderTarget* prt, unsigned flags=0);
    virtual void            PopRenderTarget(unsigned flags = 0);

    virtual bool            createDefaultRenderBuffer();

    // *** Filters
    virtual void          PushFilters(FilterPrimitive* primitive);
    virtual void          drawUncachedFilter(const FilterStackEntry& e);
    virtual void          drawCachedFilter(FilterPrimitive* primitive);
    
    virtual class MeshCache&       GetMeshCache()        { return Cache; }

    virtual float         GetViewportScaling() const { return 1.0f; }

    virtual void    MapVertexFormat(PrimitiveFillType fill, const VertexFormat* sourceFormat,
                                    const VertexFormat** single,
                                    const VertexFormat** batch, const VertexFormat** instanced, 
                                    unsigned meshType = MeshCacheItem::Mesh_Regular);

    const ShaderObject* GetStaticShader(ShaderDesc::ShaderType shaderType);

    void     DrawFilter(const Matrix2F& mvp, const Cxform & cx, const Filter* filter, Ptr<RenderTarget> * targets, 
                        unsigned* shaders, unsigned pass, unsigned passCount, const VertexFormat* pvf, 
                        BlurFilterState& leBlur, bool isLastPass);

    // Check whether the given extension exists in the current profile.
    bool                CheckExtension(const char *name);

    // Check whether the input major/minor version pair is greater or equal to the current profile version.
    bool                CheckGLVersion(unsigned reqMajor, unsigned reqMinor);


protected:
    ImageSize           getFboInfo(GLint fbo, GLint& currentFBO, bool useCurrent);

    // Returns whether the profile can render any of the filters contained in the FilterPrimitive.
    // If a profile does not support dynamic looping (Cap_NoDynamicLoops), no blur/shadow type filters
    // can be rendered, in which case this may return false, however, ColorMatrix filters can still be rendered.
    bool                shouldRenderFilters(const FilterPrimitive* prim) const;

    virtual void        setBatchUnitSquareVertexStream();
    virtual void        drawPrimitive(unsigned indexCount, unsigned meshCount);
    void                drawIndexedPrimitive( unsigned indexCount, unsigned meshCount, UByte* indexPtr);
    void                drawIndexedInstanced( unsigned indexCount, unsigned meshCount, UByte* indexPtr);

    // Simply sets a quad vertex buffer and draws.
    virtual void        drawScreenQuad();

    // *** Events
    virtual Render::RenderEvent& GetEvent(EventType eventType);

    // Cached versions read from GL_VERSION string.
    unsigned            MajorVersion, MinorVersion;
    // Cached GL_EXTENSIONS string.
    String              Extensions;
};

//--------------------------------------------------------------------
// RenderTargetData, used for both RenderTargets and DepthStencilSurface implementations.
class RenderTargetData : public RenderBuffer::RenderTargetData
{
public:
    friend class HAL;

    HAL*                    pHAL;
    GLuint                  FBOID;                  // Framebuffer object's ID.

    static void UpdateData( RenderBuffer* buffer, HAL* phal, GLuint fboID, DepthStencilBuffer* pdsb)
    {
        if ( !buffer )
            return;

        RenderTargetData* poldHD = (GL::RenderTargetData*)buffer->GetRenderTargetData();
        if ( !poldHD )
        {
            poldHD = SF_NEW RenderTargetData(buffer, phal, fboID, pdsb);
            buffer->SetRenderTargetData(poldHD);
            return;
        }
        poldHD->pDepthStencilBuffer = pdsb;
    }

    ~RenderTargetData();
    HAL* GetHAL() const     { return pHAL; }

private:
    RenderTargetData( RenderBuffer* buffer, HAL* hal, GLuint fboID, DepthStencilBuffer* pdsb ) : 
       RenderBuffer::RenderTargetData(buffer, pdsb), pHAL(hal), FBOID(fboID)
    { }
};


}}} // Scaleform::Render::GL

#endif
