/**************************************************************************

Filename    :   FxPlayerTextureInSWFD3D9.h
Content     :   Sample SWF/GFX file player leveraging GFxPlayer API
Created     :
Authors     :   Michael Antonov, Andrew Reise

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef FX_PlayerTextureInSWFD3D9_H
#define FX_PlayerTextureInSWFD3D9_H

#include "../Common/FxPlayerAppBase.h"
#include "Render/D3D9/D3D9_HAL.h"
#include "d3dx9math.h"



class   TextureInSWFD3D9App : public FxPlayerAppBase, public HALNotify
{
public:
    TextureInSWFD3D9App() 
    {
        CubeWireframe       = 0;
        MeshRotation        = 0.0f;
        LastRotationTick    = 0;
        pMyHWTexture        = 0;
        RTWidth             = 256;
        RTHeight            = 256;
    }

    virtual bool            OnInit(Platform::ViewConfig& config);
    virtual void            OnShutdown();      
    virtual bool            CreateVertexBuffer();
    D3D9::Texture*         CreateHWTexture();
    bool            SetupRTTexture();
    void            SetupMatrices();
    void            RenderMesh();

    enum TrackingState
    {
        None,
        Zooming,
        Moving,
        Tilting,
        Centering,
    };

    Ptr<IDirect3DTextureX>  pRenderTexture;
    Ptr<IDirect3DSurfaceX>  pStencilSurface;
    Ptr<IDirect3DVertexBufferX>     pCubeVertexBuffer;

    D3D9::HAL*              pPlatformHAL; 
    IDirect3DDeviceX*       pDevice;

    Ptr<D3D9::Texture>              pMyHWTexture;
    int                             RTWidth, RTHeight;
    float                           MeshRotation;
    UInt64                          LastRotationTick;
    bool                            CubeWireframe;
};



#endif
