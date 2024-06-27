/**************************************************************************

Filename    :   FxPlayerSWFtoTextureD3D9.cpp
Content     :   Sample SWF/GFX file player leveraging GFxPlayer API
Created     :
Authors     :   Michael Antonov, Andrew Reise

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/


#include "FxPlayerSWFtoTextureD3D9.h"

// Used for functions that have an extra last argument of NULL in D3D9 only
#define NULL9                   , NULL
#define     GFC_2PI             (2*3.1415926f)


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
    {-1.0f, 1.0f, 0.0f,  0.0f,0.0f },
    { 1.0f, 1.0f, 0.0f,  1.0f,0.0f },
    {-1.0f,-1.0f, 0.0f,  0.0f,1.0f },
    { 1.0f,-1.0f, 0.0f,  1.0f,1.0f },
};

#define M(x,r,c) x[(r)*4+(c)]
#define Mt(x,c,r) x[(r)*4+(c)]

static void MatrixMult(float *O, const float *A, const float *B)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(O, i,j) = M(A, i,0) * M(B, 0,j) + M(A, i,1) * M(B, 1,j) + M(A, i,2) * M(B, 2,j) + M(A, i,3) * M(B, 3,j);
}

#if 0
static void VectorMult(float *O, const float *A, float x, float y, float z, float w)
{
    O[0] = Mt(A,0,0) * x + Mt(A,0,1) * y + Mt(A,0,2) * z + Mt(A,0,3) * w;
    O[1] = Mt(A,1,0) * x + Mt(A,1,1) * y + Mt(A,1,2) * z + Mt(A,1,3) * w;
    O[2] = Mt(A,2,0) * x + Mt(A,2,1) * y + Mt(A,2,2) * z + Mt(A,2,3) * w;
    O[3] = Mt(A,3,0) * x + Mt(A,3,1) * y + Mt(A,3,2) * z + Mt(A,3,3) * w;
}

static void VectorMult(float *O, const float *A, const float *v)
{
    O[0] = Mt(A,0,0) * v[0] + Mt(A,0,1) * v[1] + Mt(A,0,2) * v[2] + Mt(A,0,3) * v[3];
    O[1] = Mt(A,1,0) * v[0] + Mt(A,1,1) * v[1] + Mt(A,1,2) * v[2] + Mt(A,1,3) * v[3];
    O[2] = Mt(A,2,0) * v[0] + Mt(A,2,1) * v[1] + Mt(A,2,2) * v[2] + Mt(A,2,3) * v[3];
    O[3] = Mt(A,3,0) * v[0] + Mt(A,3,1) * v[1] + Mt(A,3,2) * v[2] + Mt(A,3,3) * v[3];
}

static void VectorInvHomog(float *v)
{
    v[0] *= v[3];
    v[1] *= v[3];
    v[2] *= v[3];
    v[3] = 1;
}
#endif

static void MakePerspective(float *P, float fov, float aspect, float z0, float z1)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(P,i,j) = 0;

    float dz = z1-z0;
    float sinfov = sin(fov*0.5f);
    float cotfov = cos(fov*0.5f) / sinfov;

    M(P,0,0) = cotfov/aspect;
    M(P,1,1) = cotfov;
    M(P,2,2) = -(z0 + z1) / dz;
    M(P,2,3) = -1;
    M(P,3,2) = -2 * z0 * z1 / dz;
}

static void MakeIdentity(float *P)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(P,i,j) = 0;

    M(P,0,0) = 1;
    M(P,1,1) = 1;
    M(P,2,2) = 1;
    M(P,3,3) = 1;
}

static void MakeRotateX(float *P, float angle)
{
    float s = sin(angle);
    float c = cos(angle);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(P,i,j) = 0;

    M(P,1,1) = c;
    M(P,2,2) = c;
    M(P,2,1) = -s;
    M(P,1,2) = s;
    M(P,0,0) = 1;
    M(P,3,3) = 1;
}

static void MakeRotateZ(float *P, float angle)
{
    float s = sin(angle);
    float c = cos(angle);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(P,i,j) = 0;

    M(P,0,0) = c;
    M(P,2,2) = c;
    M(P,2,0) = -s;
    M(P,0,2) = s;
    M(P,1,1) = 1;
    M(P,3,3) = 1;
}

static void Translate(float *P, float x, float y, float z)
{
    for (int i = 0; i < 4; i++)
        M(P, 3,i) += x * M(P, 0,i) + y * M(P, 1,i) + z * M(P, 2,i);
}

static float Cofactor(const float *A, int I, int J)
{
    const int subs[4][3] = {{1,2,3},{0,2,3},{0,1,3},{0,1,2}};
#define SubM(m,i,j) M(m,subs[I][i],subs[J][j])

    float a = SubM(A, 0,0) * SubM(A, 1,1) * SubM(A, 2,2);
    a      += SubM(A, 1,0) * SubM(A, 2,1) * SubM(A, 0,2);
    a      += SubM(A, 2,0) * SubM(A, 0,1) * SubM(A, 1,2);
    a      -= SubM(A, 0,0) * SubM(A, 2,1) * SubM(A, 1,2);
    a      -= SubM(A, 1,0) * SubM(A, 0,1) * SubM(A, 2,2);
    a      -= SubM(A, 2,0) * SubM(A, 1,1) * SubM(A, 0,2);

    return ((I + J) & 1) ? -a : a;
#undef SubM
}

static void MatrixInverse(float *O, const float *A)
{
    float C[16];
    float det = 0;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(C,i,j) = Cofactor(A, i,j);

    for (int i = 0; i < 4; i++)
        det += M(C, 0,i) * M(A, 0,i);

    det = 1.0f / det;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(O, j,i) = det * M(C, i,j);
}

void    SWFToTextureD3D9App::SetupMatrices()
{
    float mv[16], rot[16], lap[16], mat[16];

    MakeIdentity(lap);
    Translate(lap, 0, 0, -2.5f * Zoom);
    MakeRotateX(rot, MeshRotationX * 3.141592f * 0.00555555f);
    MatrixMult(mat, rot, lap);
    MakeRotateZ(rot, MeshRotationZ * 3.141592f * 0.00555555f);
    MatrixMult(mv, rot, mat);

    MakePerspective(Proj, 3.141592f * 0.25f, float(RTWidth)/float(RTHeight), 0.1f, 100);

    MatrixInverse(InvProj, Proj);
    MatrixInverse(InvMV, mv);

    D3DXMATRIXA16 matWorld;
    D3DXMatrixIdentity(&matWorld);
    pDevice->SetTransform( D3DTS_WORLD, &matWorld );

    pDevice->SetTransform( D3DTS_VIEW, (D3DMATRIX*) mv );
    pDevice->SetTransform( D3DTS_PROJECTION, (D3DMATRIX*) Proj );
}

// Rendering
void    SWFToTextureD3D9App::RenderMovie()
{
    IDirect3DSurfaceX *poldSurface      = 0;
    IDirect3DSurfaceX *poldDepthSurface = 0;
    IDirect3DSurfaceX *psurface         = 0;

    pRenderTexture->GetSurfaceLevel(0, &psurface);

    // Save both RT and depth-stencil.
    pDevice->GetRenderTarget(0, &poldSurface);
    pDevice->GetDepthStencilSurface(&poldDepthSurface);
    pDevice->Clear( 0, NULL, D3DCLEAR_TARGET,
        D3DCOLOR_ARGB(0,0,0,0), 1.0f, 0 );

    // Set texture as render target
    if (!FAILED(pDevice->SetRenderTarget(0, psurface )))
    {
        // Set stencil; this will disable it if not available.
        pDevice->SetDepthStencilSurface(pStencilSurface);
    }

    D3DVIEWPORTx vp;
    vp.X        = 0;
    vp.Y        = 0;
    vp.Width    = RTWidth;
    vp.Height   = RTHeight;
    vp.MinZ     = 0.0f;
    vp.MaxZ     = 1.0f;
    pDevice->SetViewport(&vp);

    pDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
        D3DCOLOR_ARGB(0,0,0,0), 1.0f, 0 );

    if (pMovie)
    {     
        Render::Renderer2D* prenderer = pRenderThread->GetRenderer2D();
        MovieDisplayHandle displayHandle = pMovie->GetDisplayHandle();;
        if (displayHandle.NextCapture(prenderer->GetContextNotify()))
        {
            prenderer->Display(displayHandle);
        }
    }

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

void    SWFToTextureD3D9App::RenderMovieTexture()
{
    UInt64    ticks = Timer::GetTicks() / 1000;

    if (TextureTilt == Centering)
    {
        float dt = 0.0f;
        float t  = (float)((double)fmod((double)ticks, 7500.0) / 7500.0) * 360;
        float lt = (float)((double)fmod((double)LastRotationTick, 7500.0) / 7500.0) * 360;
        dt       = t - lt;

        LastRotationTick    = ticks;
        if (MeshRotationX > 0.0f)
        {
            MeshRotationX        -= dt;
            if (MeshRotationX < 0.0f)
                MeshRotationX = 0.0f;
        }
        else if (MeshRotationX < 0.0f)
        {
            MeshRotationX        += dt;
            if (MeshRotationX > 0.0f)
                MeshRotationX = 0.0f;
        }

        if (MeshRotationZ > 0.0f)
        {
            MeshRotationZ        -= dt;
            if (MeshRotationZ < 0.0f)
                MeshRotationZ = 0.0f;
        }
        else if (MeshRotationZ < 0.0f)
        {
            MeshRotationZ        += dt;
            if (MeshRotationZ > 0.0f)
                MeshRotationZ = 0.0f;
        }

        if (MeshRotationZ == 0.0f && MeshRotationX == 0.0f)
        {
            TextureTilt = None;
        }
    }
    else if (TextureTilt == None && (ticks - LastRotationTick) >= 20)
    {
        float tiltMax   = 10.5f;
        float tiltDelta = 0.2f;

        if (MeshRotationZ > -tiltMax && MeshRotationX == 0 || MeshRotationX < -tiltMax)
            MeshRotationZ -= tiltDelta;

        if (MeshRotationX < tiltMax && MeshRotationZ < -tiltMax)
            MeshRotationX += tiltDelta;

        if (MeshRotationZ < tiltMax && MeshRotationX > tiltMax)
            MeshRotationZ += tiltDelta;

        if (MeshRotationX > -tiltMax && MeshRotationZ > tiltMax)
            MeshRotationX -= tiltDelta;

        LastRotationTick = ticks;
    }
    else if (TextureTilt != None)
        LastRotationTick = ticks;

    MeshRotationX = fmod(MeshRotationX, 360.0f);
    MeshRotationZ = fmod(MeshRotationZ, 360.0f);

    if (MeshRotationX > 45.0f)
        MeshRotationX = 45.0f;
    if (MeshRotationX < -45.0f)
        MeshRotationX = -45.0f;

    if (MeshRotationZ > 45.0f)
        MeshRotationZ = 45.0f;
    if (MeshRotationZ < -45.0f)
        MeshRotationZ = -45.0f;


    // Setup the world, view, and projection matrices
    SetupMatrices();

    pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

    pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

    D3DVIEWPORTx vp;
    vp.X        = 0;
    vp.Y        = 0;
    vp.Width    = GetViewSize().Width;
    vp.Height   = GetViewSize().Height;
    vp.MinZ     = 0.0f;
    vp.MaxZ     = 1.0f;
    pDevice->SetViewport(&vp);

    pDevice->BeginScene();

    pDevice->SetPixelShader(0);
    pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
    pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

    pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

    // Blending
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    pDevice->SetTexture( 0, pRenderTexture );

    pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, FALSE);

    pDevice->SetStreamSource( 0, pCubeVertexBuffer, 0, sizeof(Vertex) );
    pDevice->SetFVF( Vertex::FVF );
    pDevice->SetVertexShader(0);

    pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP,  0, 2 );

    // Unbind render texture, so it can be updated.
    pDevice->SetTexture( 0, 0 );


    pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

    pDevice->EndScene();
}

bool    SWFToTextureD3D9App::SetupRTTexture()
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
 
bool SWFToTextureD3D9App::OnInit(Platform::ViewConfig& config)
{
    if (!FxPlayerAppBase::OnInit(config))
        return false;


    pPlatformHAL = (D3D9::HAL*) AppBase::pDevice->GetHAL();
    pDevice = (IDirect3DDeviceX*)pPlatformHAL->pDevice;
    pPlatformHAL->AddNotify(this);

    SetupRTTexture();

    pDevice->CreateVertexBuffer( 24*sizeof(Vertex),0, Vertex::FVF,
        D3DPOOL_MANAGED, &pCubeVertexBuffer.GetRawRef() NULL9 );
    void *pVertices = NULL;
#if (SF_D3D_VERSION == 9)
    pCubeVertexBuffer->Lock( 0, sizeof(g_cubeVertices), (void**)&pVertices, 0 );
#endif
    memcpy( pVertices, g_cubeVertices, sizeof(g_cubeVertices) );
    pCubeVertexBuffer->Unlock();

    return true;
}

#undef M
