/**************************************************************************

Filename    :   FxPlayerSWFtoTextureD3D1x.cpp
Content     :   Sample SWF/GFX file player leveraging GFxPlayer API
Created     :
Authors     :   Michael Antonov, Andrew Reise

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/


#include "FxPlayerSWFToTextureD3D1x.h"




struct Vertex
{
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

void MatrixMult(float *po, const float *pa, const float *pb)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(po,i,j) = M(pa, i,0) * M(pb, 0,j) + M(pa, i,1) * M(pb, 1,j) + 
            M(pa, i,2) * M(pb, 2,j) + M(pa, i,3) * M(pb, 3,j);
}

void VectorMult(float *po, const float *pa, float x, float y, float z, float w)
{
    po[0] = M(pa,0,0) * x + M(pa,1,0) * y + M(pa,2,0) * z + M(pa,3,0) * w;
    po[1] = M(pa,0,1) * x + M(pa,1,1) * y + M(pa,2,1) * z + M(pa,3,1) * w;
    po[2] = M(pa,0,2) * x + M(pa,1,2) * y + M(pa,2,2) * z + M(pa,3,2) * w;
    po[3] = M(pa,0,3) * x + M(pa,1,3) * y + M(pa,2,3) * z + M(pa,3,3) * w;
}

void VectorMult(float *po, const float *pa, const float *v)
{
    po[0] = M(pa,0,0) * v[0] + M(pa,1,0) * v[1] + M(pa,2,0) * v[2] + M(pa,3,0) * v[3];
    po[1] = M(pa,0,1) * v[0] + M(pa,1,1) * v[1] + M(pa,2,1) * v[2] + M(pa,3,1) * v[3];
    po[2] = M(pa,0,2) * v[0] + M(pa,1,2) * v[1] + M(pa,2,2) * v[2] + M(pa,3,2) * v[3];
    po[3] = M(pa,0,3) * v[0] + M(pa,1,3) * v[1] + M(pa,2,3) * v[2] + M(pa,3,3) * v[3];
}

void VectorInvHomog(float *v)
{
    v[0] *= v[3];
    v[1] *= v[3];
    v[2] *= v[3];
    v[3] = 1;
}

void MakePerspective(float *pp, float fov, float aspect, float z0, float z1)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(pp,i,j) = 0;

    float dz = z1-z0;
    float sinfov = sin(fov*0.5f);
    float cotfov = cos(fov*0.5f) / sinfov;

    M(pp,0,0) = cotfov/aspect;
    M(pp,1,1) = cotfov;
    M(pp,2,2) = -(z0 + z1) / dz;
    M(pp,2,3) = -1;
    M(pp,3,2) = -2 * z0 * z1 / dz;
}

void MakeIdentity(float *pp)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(pp,i,j) = 0;

    M(pp,0,0) = 1;
    M(pp,1,1) = 1;
    M(pp,2,2) = 1;
    M(pp,3,3) = 1;
}

void MakeRotateY(float *pp, float angle)
{
    float s = sin(angle);
    float c = cos(angle);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(pp,i,j) = 0;

    M(pp,0,0) = c;
    M(pp,2,2) = c;
    M(pp,2,0) = -s;
    M(pp,0,2) = s;
    M(pp,1,1) = 1;
    M(pp,3,3) = 1;
}

void MakeRotateX(float *pp, float angle)
{
    float s = sin(angle);
    float c = cos(angle);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(pp,i,j) = 0;

    M(pp,1,1) = c;
    M(pp,2,2) = c;
    M(pp,2,1) = -s;
    M(pp,1,2) = s;
    M(pp,0,0) = 1;
    M(pp,3,3) = 1;
}


void MakeRotateZ(float *pp, float angle)
{
    float s = sin(angle);
    float c = cos(angle);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(pp,i,j) = 0;

    M(pp,0,0) = c;
    M(pp,2,2) = c;
    M(pp,2,0) = -s;
    M(pp,0,2) = s;
    M(pp,1,1) = 1;
    M(pp,3,3) = 1;
}

void Translate(float *pp, float x, float y, float z)
{
    for (int i = 0; i < 4; i++)
        M(pp, 3,i) += x * M(pp, 0,i) + y * M(pp, 1,i) + z * M(pp, 2,i);
}

void MatrixTranspose(float *po, const float *pa)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(po,i,j) = M(pa,j,i);

}

float Cofactor(const float *pa, int i, int j)
{
    const int subs[4][3] = {{1,2,3},{0,2,3},{0,1,3},{0,1,2}};

#define SUBM(m,a,b) M(m,subs[i][a],subs[j][b])

    float a;
    a =  SUBM(pa, 0,0) * SUBM(pa, 1,1) * SUBM(pa, 2,2);
    a += SUBM(pa, 1,0) * SUBM(pa, 2,1) * SUBM(pa, 0,2);
    a += SUBM(pa, 2,0) * SUBM(pa, 0,1) * SUBM(pa, 1,2);
    a -= SUBM(pa, 0,0) * SUBM(pa, 2,1) * SUBM(pa, 1,2);
    a -= SUBM(pa, 1,0) * SUBM(pa, 0,1) * SUBM(pa, 2,2);
    a -= SUBM(pa, 2,0) * SUBM(pa, 1,1) * SUBM(pa, 0,2);

    return ((i + j) & 1) ? -a : a;
}

void MatrixInverse(float *po, const float *pa)
{
    float c[16];
    float det = 0;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(c,i,j) = Cofactor(pa, i,j);

    for (int i = 0; i < 4; i++)
        det += M(c, 0,i) * M(pa, 0,i);

    det = 1.0f / det;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            M(po, j,i) = det * M(c, i,j);
}


void    SWFToTextureD3D1xApp::SetupMatrices()
{
    float mv[16], rot[16], lap[16], mat[16], mvp[16], mvpt[16];

    MakeIdentity(lap);
    Translate(lap, 0, 0, -2.5f * Zoom);
    MakeRotateX(rot, MeshRotationX * 3.141592f * 0.00555555f);
    MatrixMult(mat, rot, lap);
    MakeRotateZ(rot, MeshRotationZ * 3.141592f * 0.00555555f);
    MatrixMult(mv, rot, mat);

    MakePerspective(Proj, 3.141592f * 0.25f, float(RTWidth)/float(RTHeight), 0.1f, 100);

    MatrixInverse(InvProj, Proj);
    MatrixInverse(InvMV, mv);
    MatrixMult(mvp, mv, Proj);
    MatrixTranspose(mvpt, mvp);

    pContext->UpdateSubresource(VShaderConst, 0, NULL, mvpt, 0, 0);
}

// Rendering
void    SWFToTextureD3D1xApp::RenderMovie()
{
    if (!pRenderTexture)
        return;

    Ptr<ID3D1x(RenderTargetView) > poldRT;
    Ptr<ID3D1x(DepthStencilView) > poldDS;

    pContext->OMGetRenderTargets(1, &poldRT.GetRawRef(), &poldDS.GetRawRef() );
    pContext->OMSetRenderTargets(1, &pRenderTextureView.GetRawRef(), pRTDepthStencil);

    D3Dx(VIEWPORT) vp;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.Width    = (D3DxVIEWPORT_COORD)RTWidth;
    vp.Height   = (D3DxVIEWPORT_COORD)RTHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    pContext->RSSetViewports(1, &vp);

    const float clear[] = {0,0,0,0};
    pContext->ClearRenderTargetView(pRenderTextureView, clear);
    pContext->ClearDepthStencilView(pRTDepthStencil, D3Dx(CLEAR_DEPTH) | D3Dx(CLEAR_STENCIL), 1.0f, 0);

    if (pMovie)
    {
        Render::Renderer2D* prenderer = pRenderThread->GetRenderer2D();
        MovieDisplayHandle displayHandle = pMovie->GetDisplayHandle();;
        if (displayHandle.NextCapture(prenderer->GetContextNotify()))
        {
            prenderer->Display(displayHandle);
        }
    }

    pContext->OMSetRenderTargets(1, &poldRT.GetRawRef(), poldDS);
}

void    SWFToTextureD3D1xApp::RenderMovieTexture()
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

    D3Dx(VIEWPORT) vp;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.Width    = (D3DxVIEWPORT_COORD)GetViewSize().Width;;
    vp.Height   = (D3DxVIEWPORT_COORD)GetViewSize().Height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    pContext->RSSetViewports(1, &vp);

    const float one[] = {1,1,1,1};
    pContext->OMSetBlendState(pBlendState, one, 0xfffffff);
    pContext->RSSetState(pRSFill);
    pContext->OMSetDepthStencilState(pDepthTest, 0);
    pContext->VSSetShader(p3DVShader NULL_SHADER_CLASS);
    pContext->VSSetConstantBuffers(0, 1, &VShaderConst.GetRawRef());
    pContext->IASetInputLayout(p3DILayout);
    pContext->IASetPrimitiveTopology(D3Dx(PRIMITIVE_TOPOLOGY_TRIANGLESTRIP));
    pContext->PSSetShader(pTex2dShader NULL_SHADER_CLASS);
    //pContext->PSSetSamplers(0, 1, &pTex2dSampler.GetRawRef());
    pContext->PSSetShaderResources(0, 1, &pRenderTextureSV.GetRawRef());
    unsigned stride = sizeof(Vertex);
    unsigned offset = 0;
    pContext->IASetVertexBuffers(0, 1, &pCubeVertexBuffer.GetRawRef(), &stride, &offset);

    pContext->Draw(4, 0);

    ID3Dx(ShaderResourceView)* srs[2] = {0,0};

    pContext->PSSetShaderResources(0, 2, srs);
    pContext->PSSetShader(0 NULL_SHADER_CLASS);
}

bool    SWFToTextureD3D1xApp::SetupRTTexture()
{
    D3Dx(TEXTURE2D_DESC) texdesc;
    memset(&texdesc, 0, sizeof(texdesc));
    texdesc.Width = RTWidth;
    texdesc.Height = RTHeight;
    texdesc.MipLevels = 1;
    texdesc.ArraySize = 1;
    texdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texdesc.SampleDesc.Count = 1;
    texdesc.SampleDesc.Quality = 0;
    texdesc.Usage = D3Dx(USAGE_DEFAULT);
    texdesc.BindFlags = D3Dx(BIND_RENDER_TARGET) | D3Dx(BIND_SHADER_RESOURCE);
    texdesc.CPUAccessFlags = 0;
    texdesc.MiscFlags = 0;
    pDevice->CreateTexture2D(&texdesc, NULL, &pRenderTexture.GetRawRef());

    pDevice->CreateRenderTargetView(pRenderTexture, NULL, &pRenderTextureView.GetRawRef());
    pDevice->CreateShaderResourceView(pRenderTexture, NULL, &pRenderTextureSV.GetRawRef());

    texdesc.Width = RTWidth;
    texdesc.Height = RTHeight;
    texdesc.MipLevels = 1;
    texdesc.ArraySize = 1;
    texdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    texdesc.SampleDesc.Count = 1;
    texdesc.SampleDesc.Quality = 0;
    texdesc.Usage = D3Dx(USAGE_DEFAULT);
    texdesc.BindFlags = D3Dx(BIND_DEPTH_STENCIL);
    texdesc.CPUAccessFlags = 0;
    texdesc.MiscFlags = 0;
    pDevice->CreateTexture2D(&texdesc, NULL, &pRTDepthStencilBuf.GetRawRef());

    D3Dx(DEPTH_STENCIL_VIEW_DESC) dsv;
    memset(&dsv, 0, sizeof(dsv));
    dsv.Format = texdesc.Format;
    dsv.ViewDimension = D3Dx(DSV_DIMENSION_TEXTURE2D);
    dsv.Texture2D.MipSlice = 0;
    pDevice->CreateDepthStencilView( pRTDepthStencilBuf, &dsv, &pRTDepthStencil.GetRawRef());

    return 1;
}
 
bool SWFToTextureD3D1xApp::OnInit(Platform::ViewConfig& config)
{
    if (!FxPlayerAppBase::OnInit(config))
        return false;


    pPlatformHAL = (D3D1x::HAL*) AppBase::pDevice->GetHAL();
    pDevice = pPlatformHAL->pDevice;
    pContext = pPlatformHAL->pDeviceContext;
    pRenderTarget = pPlatformHAL->pRenderTargetView;
    pDepthStencil = pPlatformHAL->pDepthStencilView;

    pPlatformHAL->AddNotify(this);

    SetupRTTexture();

    D3Dx(BUFFER_DESC) bd;
    memset(&bd, 0, sizeof(D3Dx(BUFFER_DESC)));
    bd.Usage = D3Dx(USAGE_DEFAULT);
    bd.BindFlags = D3Dx(BIND_VERTEX_BUFFER);
    bd.ByteWidth = sizeof(g_cubeVertices);
    D3Dx(SUBRESOURCE_DATA) vd;
    vd.pSysMem = g_cubeVertices;
    vd.SysMemPitch = vd.SysMemSlicePitch = 0;
    pDevice->CreateBuffer(&bd, &vd, &pCubeVertexBuffer.GetRawRef());

    memset(&bd, 0, sizeof(D3Dx(BUFFER_DESC)));
    bd.Usage = D3Dx(USAGE_DEFAULT);
    bd.BindFlags = D3Dx(BIND_CONSTANT_BUFFER);

    bd.ByteWidth = sizeof(float) * 16;
    pDevice->CreateBuffer(&bd, NULL, &VShaderConst.GetRawRef());

    Ptr<ID3D10Blob> pshader;
    Ptr<ID3D10Blob> pmsg;
    HRESULT hr;

    static const char *p3dVShaderText = 
        "cbuffer VSConstants {\n"
        "  float4x4 mvp;\n"
        "}\n"
        "void main(float4     pos  : POSITION,\n"
        "          float2     tc0  : TEXCOORD0,\n"
        "          out float2 otc0 : TEXCOORD0,\n"
        "          out float4 opos : SV_Position)\n"
        "{ opos = mul(pos, mvp); otc0 = tc0; }\n"
        ;

#if (SF_D3D_VERSION == 10)
    hr = D3D10CompileShader(p3dVShaderText, strlen(p3dVShaderText), NULL,
        NULL, NULL, "main", "vs_4_0", 0, &pshader.GetRawRef(), &pmsg.GetRawRef());
#else
    hr = D3DX11CompileFromMemory(p3dVShaderText, strlen(p3dVShaderText), NULL, NULL, NULL, "main",
        "vs_4_0", 0, 0, NULL, &pshader.GetRawRef(), &pmsg.GetRawRef(), NULL);
#endif

    if (FAILED(hr))
    {
        SF_DEBUG_WARNING1(1, "VertexShader errors:\n %s ", pmsg->GetBufferPointer() );
        return 0;
    }
    static D3Dx(INPUT_ELEMENT_DESC) VertexDecl[] =
    {
        {"POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3Dx(INPUT_PER_VERTEX_DATA), 0},
        {"TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3Dx(INPUT_PER_VERTEX_DATA), 0},
    };
    pDevice->CreateVertexShader(pshader->GetBufferPointer(), pshader->GetBufferSize() NULL_SHADER_LINKAGE, &p3DVShader.GetRawRef());
    pDevice->CreateInputLayout(VertexDecl, 2, pshader->GetBufferPointer(), pshader->GetBufferSize(), &p3DILayout.GetRawRef());

    static const char *pTex2dShaderText = 
        "Texture2D tex : register(t0);\n"
        "SamplerState samp\n"
        "{\n"
        "  Filter = MIN_MAG_MIP_LINEAR;\n"
        "};\n"
        "void main(float2 tc0        : TEXCOORD0,\n"
        "          out float4 ocolor : SV_Target)\n"
        "{ ocolor = tex.Sample(samp, tc0);\n}\n";

#if (SF_D3D_VERSION == 10)
    hr = D3D10CompileShader(pTex2dShaderText, strlen(pTex2dShaderText), NULL,
        NULL, NULL, "main", "ps_4_0", 0, &pshader.GetRawRef(), &pmsg.GetRawRef());
#else
    hr = D3DX11CompileFromMemory(pTex2dShaderText, strlen(pTex2dShaderText), NULL, NULL, NULL, "main",
        "ps_4_0", 0, 0, NULL, &pshader.GetRawRef(), &pmsg.GetRawRef(), NULL);
#endif
    if (FAILED(hr))
    {
        SF_DEBUG_WARNING1(1, "PixelShader errors:\n %s ", pmsg->GetBufferPointer() );
        return 0;
    }
    pDevice->CreatePixelShader(pshader->GetBufferPointer(), pshader->GetBufferSize() NULL_SHADER_LINKAGE, &pTex2dShader.GetRawRef());

    D3Dx(DEPTH_STENCIL_DESC) ds;
    memset(&ds, 0, sizeof(D3Dx(DEPTH_STENCIL_DESC)));
    ds.DepthFunc = D3Dx(COMPARISON_ALWAYS);
    ds.DepthEnable = 0;
    ds.DepthWriteMask = D3Dx(DEPTH_WRITE_MASK_ZERO);
    ds.FrontFace.StencilDepthFailOp = ds.BackFace.StencilDepthFailOp = D3Dx(STENCIL_OP_KEEP);
    ds.FrontFace.StencilFailOp = ds.BackFace.StencilFailOp = D3Dx(STENCIL_OP_KEEP);
    ds.FrontFace.StencilPassOp = ds.BackFace.StencilPassOp = D3Dx(STENCIL_OP_KEEP);
    ds.FrontFace.StencilFunc = ds.BackFace.StencilFunc = D3Dx(COMPARISON_ALWAYS);
    pDevice->CreateDepthStencilState(&ds, &pDepthTest.GetRawRef());

    D3Dx(RASTERIZER_DESC) rs;
    memset(&rs, 0, sizeof(D3Dx(RASTERIZER_DESC)));
    rs.FillMode = D3Dx(FILL_SOLID);
    rs.CullMode = D3Dx(CULL_NONE);
    rs.ScissorEnable = 0;
    rs.MultisampleEnable = 0;
    rs.AntialiasedLineEnable = 1;
    pDevice->CreateRasterizerState(&rs, &pRSFill.GetRawRef());

#if (SF_D3D_VERSION == 10)
#define BLEND(enable,srcC,dstC,Cop,srcA,dstA,Aop,mask) \
    { 0, {enable}, D3Dx(srcC), D3Dx(dstC), D3Dx(Cop), D3Dx(srcA), D3Dx(dstA), D3Dx(Aop), {mask} }

#else
#define BLEND(enable,srcC,dstC,Cop,srcA,dstA,Aop,mask) \
    { 0, 0, {{enable, D3Dx(srcC), D3Dx(dstC), D3Dx(Cop), D3Dx(srcA), D3Dx(dstA), D3Dx(Aop), mask}} }
#endif

    const D3Dx(BLEND_DESC) blend = BLEND(1, BLEND_ONE, BLEND_INV_SRC_ALPHA, BLEND_OP_ADD,
        BLEND_ONE, BLEND_INV_SRC_ALPHA, BLEND_OP_ADD, D3Dx(COLOR_WRITE_ENABLE_ALL));
    pDevice->CreateBlendState(&blend, &pBlendState.GetRawRef());
#undef BLEND
    return true;
}

void SWFToTextureD3D1xApp::OnShutdown()
{
    if (pDevice)
    {
        ID3Dx(Buffer)* buf = 0;
        unsigned n = 0;
        pContext->IASetVertexBuffers(0, 1, &buf, &n, &n);
        pContext->OMSetDepthStencilState(0, 0);
    }
    pRenderTexture = 0;
    pRenderTextureView = 0;
    pRenderTextureSV = 0;
    pRTDepthStencil = 0;
    pRTDepthStencilBuf = 0;
    pCubeVertexBuffer = 0;
    VShaderConst = 0;
    pDepthTest = 0;
    pRSFill = 0;
    pBlendState = 0;
    p3DVShader = 0;
    pTex2dShader = 0;
    p3DILayout = 0;
    FxPlayerAppBase::OnShutdown();
}

#undef M
