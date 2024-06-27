/**************************************************************************

Filename    :   FxPlayerSWFtoTextureD3D1x.h
Content     :   Sample SWF/GFX file player leveraging GFxPlayer API
Created     :
Authors     :   Michael Antonov, Andrew Reise

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef FX_PlayerSWFtoTextureD3D1x_H
#define FX_PlayerSWFtoTextureD3D1x_H

#include "../Common/FxPlayerAppBase.h"
#include "Render/D3D1x/D3D1x_HAL.h"

#if (SF_D3D_VERSION == 10)
    #include <d3d10.h>
    #include <d3dx10.h>
    #define GRendererD3D1x      GRendererD3D10
    #define GTextureD3D1x       GTextureD3D10

    // add D3D10 or ID3D10 before classes and enums that are similar in D3D10/11
    #define D3Dx(name)      D3D10_##name
    #define ID3Dx(name)     ID3D10##name

    // context is new in D3D11
//    #define pContext pDevice

    #define ID3D1xDeviceContext           ID3Dx(Device)
    #define NULL_SHADER_CLASS   
    #define NULL_SHADER_LINKAGE

    #define IDIRECT3DDEVICE ID3D10Device
    #define IDIRECT3DCONTEXT ID3D10Device
    #define D3DVIEWPORT D3D10_VIEWPORT
    #define D3DxVIEWPORT_COORD            int

#else
    #include <d3d11.h>
    #include <d3dx11.h>
    #define GRendererD3D1x      GRendererD3D11
    #define GTextureD3D1x       GTextureD3D11

    // add D3D11_ or ID3D11 before classes and enums that are similar in D3D10/11
    #define D3Dx(name)      D3D11_##name
    #define ID3Dx(name)     ID3D11##name

    #define ID3D1xDeviceContext         ID3D11DeviceContext
    #define NULL_SHADER_CLASS           , NULL, 0
    #define NULL_SHADER_LINKAGE         , NULL

    #define IDIRECT3DDEVICE ID3D11Device
    #define IDIRECT3DCONTEXT ID3D11DeviceContext
    #define D3DVIEWPORT D3D11_VIEWPORT
    #define D3DxVIEWPORT_COORD          FLOAT
#endif

class   SWFToTextureD3D1xApp : public FxPlayerAppBase, public HALNotify
{
public:
    SWFToTextureD3D1xApp() 
    {
        LastRotationTick = 0;
        MeshRotationX = -30;
        MeshRotationZ = -30;
        RTWidth = 1024;
        RTHeight = 1024;
    }


    virtual bool            OnInit(Platform::ViewConfig& config);
    virtual void            OnShutdown();       
    bool            SetupRTTexture();
    void            SetupMatrices();
    void            RenderMovie();
    void            RenderMovieTexture();

    enum TrackingState
    {
        None,
        Zooming,
        Moving,
        Tilting,
        Centering,
    };

    Ptr<ID3Dx(Texture2D)>           pRenderTexture;
    Ptr<ID3Dx(RenderTargetView)>    pRenderTextureView;
    Ptr<ID3Dx(ShaderResourceView)>  pRenderTextureSV;
    Ptr<ID3Dx(DepthStencilView)>    pRTDepthStencil;
    Ptr<ID3Dx(Texture2D)>           pRTDepthStencilBuf;
    Ptr<ID3Dx(Buffer)>              pCubeVertexBuffer;
    Ptr<ID3Dx(Buffer)>              VShaderConst;
    Ptr<ID3Dx(DepthStencilState)>   pDepthTest;
    Ptr<ID3Dx(RasterizerState)>     pRSFill;
    Ptr<ID3Dx(BlendState)>          pBlendState;
    Ptr<ID3Dx(VertexShader)>        p3DVShader;
    Ptr<ID3Dx(PixelShader)>         pTex2dShader;
    Ptr<ID3Dx(InputLayout)>         p3DILayout;

    ID3Dx(RenderTargetView)*        pRenderTarget;
    ID3Dx(DepthStencilView)*        pDepthStencil;

    D3D1x::HAL*              pPlatformHAL; 
    IDIRECT3DDEVICE*       pDevice;
    IDIRECT3DCONTEXT*       pContext;

    TrackingState           TextureTilt;

    int                     RTWidth, RTHeight;
    float                   MeshRotationX;
    float                   MeshRotationZ;
    UInt64                  LastRotationTick;
    float                   InvMV[16];
    float                   Proj[16], InvProj[16];
    bool                    CubeWireframe;

    Ptr<MovieDef>   pBGDef;
    Ptr<Movie>  pBG;
};



#endif
