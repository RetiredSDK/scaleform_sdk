/**************************************************************************

Filename    :   FxPlayerTextureInSWFD3D9.cpp
Content     :   Sample SWF/GFX file player leveraging GFxPlayer API
Created     :
Authors     :   Michael Antonov, Andrew Reise

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/


#include "FxPlayerTextureInSWFD3D9.h"
using namespace Render;
using namespace D3D9;

#define     GFC_2PI             (2*3.1415926f)

// Used for functions that have an extra last argument of NULL in D3D9 only
#define NULL9                   , NULL

struct Vertex
{
    enum
    {
        FVF = D3DFVF_XYZ | D3DFVF_TEX1
    };
    float x, y, z;
    float tu, tv;
};

Vertex g_cubeVertices[] =
{
    {-1.0f, 1.0f,-1.0f,  0.0f,0.0f },
    { 1.0f, 1.0f,-1.0f,  1.0f,0.0f },
    {-1.0f,-1.0f,-1.0f,  0.0f,1.0f },
    { 1.0f,-1.0f,-1.0f,  1.0f,1.0f },

    {-1.0f, 1.0f, 1.0f,  1.0f,0.0f },
    {-1.0f,-1.0f, 1.0f,  1.0f,1.0f },
    { 1.0f, 1.0f, 1.0f,  0.0f,0.0f },
    { 1.0f,-1.0f, 1.0f,  0.0f,1.0f },

    {-1.0f, 1.0f, 1.0f,  0.0f,0.0f },
    { 1.0f, 1.0f, 1.0f,  1.0f,0.0f },
    {-1.0f, 1.0f,-1.0f,  0.0f,1.0f },
    { 1.0f, 1.0f,-1.0f,  1.0f,1.0f },

    {-1.0f,-1.0f, 1.0f,  0.0f,0.0f },
    {-1.0f,-1.0f,-1.0f,  1.0f,0.0f },
    { 1.0f,-1.0f, 1.0f,  0.0f,1.0f },
    { 1.0f,-1.0f,-1.0f,  1.0f,1.0f },

    { 1.0f, 1.0f,-1.0f,  0.0f,0.0f },
    { 1.0f, 1.0f, 1.0f,  1.0f,0.0f },
    { 1.0f,-1.0f,-1.0f,  0.0f,1.0f },
    { 1.0f,-1.0f, 1.0f,  1.0f,1.0f },

    {-1.0f, 1.0f,-1.0f,  1.0f,0.0f },
    {-1.0f,-1.0f,-1.0f,  1.0f,1.0f },
    {-1.0f, 1.0f, 1.0f,  0.0f,0.0f },
    {-1.0f,-1.0f, 1.0f,  0.0f,1.0f }
};


void    TextureInSWFD3D9App::SetupMatrices()
{
    // For our world matrix, we will just leave it as the identity
    D3DXMATRIXA16 matWorld;
    D3DXMatrixRotationY( &matWorld, MeshRotation );
    pDevice->SetTransform( D3DTS_WORLD, &matWorld );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.

    D3DXVECTOR3 vEyePt( 0.0f, 4.0f, -5.5f );
    D3DXVECTOR3 vLookatPt( -1.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( -0.1f, 1.0f, 0.0f );

    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    pDevice->SetTransform( D3DTS_VIEW, &matView );


    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DXToRadian( 45.0f ),
        /*640.0f / 480.0f*/1.0f, 0.1f, 100.0f );
    pDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

// Rendering
void    TextureInSWFD3D9App::RenderMesh()
{
    if (!pRenderTexture)
        return;

    IDirect3DSurfaceX *poldSurface      = 0;
    IDirect3DSurfaceX *poldDepthSurface = 0;
    IDirect3DSurfaceX *psurface         = 0;

    pRenderTexture->GetSurfaceLevel(0, &psurface);

    // Save both RT and depth-stencil.
    pDevice->GetRenderTarget(0, &poldSurface);
    pDevice->GetDepthStencilSurface(&poldDepthSurface);

    // Set texture as render target
    if (!FAILED(pDevice->SetRenderTarget(0, psurface )))
    {
        // Set stencil; this will disable it if not available.
        pDevice->SetDepthStencilSurface(pStencilSurface);
    }


    static D3DCOLOR clearColor = D3DCOLOR_ARGB(90,0,0,255);

    pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
        clearColor, 1.0f, 0 );

    UInt64    ticks = Timer::GetTicks() / 1000;

    // 1/10 revolution per second
    float dt = 0.0f;
    {
        float t  = (float)((double)fmod((double)ticks, 20000.0) / 20000.0) * GFC_2PI;
        float lt = (float)((double)fmod((double)LastRotationTick, 20000.0) / 20000.0) * GFC_2PI;
        dt = t - lt;
    }

    LastRotationTick    = ticks;
    MeshRotation        += dt;

    if (MeshRotation > GFC_2PI)
        MeshRotation -= GFC_2PI;
    if (MeshRotation < 0.0f)
        MeshRotation += GFC_2PI;

    // Setup the world, view, and projection matrices
    SetupMatrices();

    pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

    D3DVIEWPORTx vp;
    vp.X        = 0;
    vp.Y        = 0;
    vp.Width    = RTWidth;
    vp.Height   = RTHeight;
    vp.MinZ     = 0.0f;
    vp.MaxZ     = 1.0f;
    pDevice->SetViewport(&vp);

    pDevice->BeginScene();

    pDevice->SetPixelShader(0);
    pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
    pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
    pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

    // Blending
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    //pDevice->SetRenderState(D3DRS_BLENDFACTOR, 0x60606060);

    pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

    pDevice->SetRenderState(D3DRS_FILLMODE, CubeWireframe ? D3DFILL_WIREFRAME : D3DFILL_SOLID);

    pDevice->SetTexture( 0, 0 );


    pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, FALSE);

    pDevice->SetStreamSource( 0, pCubeVertexBuffer, 0, sizeof(Vertex) );
    pDevice->SetFVF( Vertex::FVF );
    pDevice->SetVertexShader(0);



    pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255,180,0,0));
    pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,  0, 2 );
    pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255,180,180,0));
    pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,  4, 2 );
    pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255,0,180,180));
    pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,  8, 2 );

    pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255,0,180,0));
    pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 12, 2 );
    pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255,0,0,180));
    pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 16, 2 );
    pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255,180,0,180));
    pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 20, 2 );

    pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

    pDevice->EndScene();

    // Restore the render target
    pDevice->SetRenderTarget(0, poldSurface);
    pDevice->SetDepthStencilSurface(poldDepthSurface);

    if (psurface)
        psurface->Release();
    if (poldSurface)
        poldSurface->Release();
    if (poldDepthSurface)
        poldDepthSurface->Release();

    // Need to do this so that mipmaps are updated.
    pRenderTexture->AddDirtyRect(0);
}

// also recreates if lost
bool    TextureInSWFD3D9App::SetupRTTexture()
{
    if (FAILED( pDevice->CreateTexture(
        RTWidth,RTHeight,0,
        D3DUSAGE_RENDERTARGET|D3DUSAGE_AUTOGENMIPMAP, D3DFMT_A8R8G8B8,
        D3DPOOL_DEFAULT, &pRenderTexture.GetRawRef(), 0) ))
        return 0;

    pDevice->CreateDepthStencilSurface( RTWidth,RTHeight, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0,
        TRUE, &pStencilSurface.GetRawRef(), NULL);

    return 1;
}

bool TextureInSWFD3D9App::CreateVertexBuffer()
{
    pDevice->CreateVertexBuffer( 24*sizeof(Vertex),0, Vertex::FVF,
        D3DPOOL_MANAGED, &pCubeVertexBuffer.GetRawRef() NULL9 );
    void *pVertices = NULL;

    pCubeVertexBuffer->Lock( 0, sizeof(g_cubeVertices), (void**)&pVertices, 0 );

    memcpy( pVertices, g_cubeVertices, sizeof(g_cubeVertices) );
    pCubeVertexBuffer->Unlock();
    return true;
}

bool TextureInSWFD3D9App::OnInit( Platform::ViewConfig& config )
{
    SF_UNUSED(config);
    pPlatformHAL = (D3D9::HAL*) AppBase::pDevice->GetHAL();
    pDevice = (IDirect3DDeviceX*)pPlatformHAL->pDevice;
    pPlatformHAL->AddNotify(this);
    return true;
}

D3D9::Texture* TextureInSWFD3D9App::CreateHWTexture()
{
    D3D9::TextureManager * pmanager = (D3D9::TextureManager*)pPlatformHAL->GetTextureManager(); 
    return (D3D9::Texture*)pmanager->CreateTexture( pRenderTexture, ImageSize(RTWidth, RTHeight));
}

void TextureInSWFD3D9App::OnShutdown()
{
    if (pDevice)
    {
        pDevice->SetStreamSource( 0, 0, 0, 0);
    }
}
