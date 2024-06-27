/**************************************************************************

Filename    :   FxPlayerSWFtoTextureD3D9.h
Content     :   Sample SWF/GFX file player leveraging GFxPlayer API
Created     :
Authors     :   Michael Antonov, Andrew Reise

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef FX_PlayerSWFtoTextureD3D9_H
#define FX_PlayerSWFtoTextureD3D9_H

#include "../Common/FxPlayerAppBase.h"
#include "Render/D3D9/D3D9_HAL.h"
#include "d3dx9math.h"



class   SWFToTextureD3D9App : public FxPlayerAppBase, public HALNotify
{
public:
    SWFToTextureD3D9App() 
    {
        LastRotationTick = 0;
        MeshRotationX = -30;
        MeshRotationZ = -30;
        RTWidth = 1024;
        RTHeight = 1024;
    }


    virtual bool            OnInit(Platform::ViewConfig& config);

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

    Ptr<IDirect3DTextureX>  pRenderTexture;
    Ptr<IDirect3DSurfaceX>  pStencilSurface;
    Ptr<IDirect3DVertexBufferX>     pCubeVertexBuffer;

    D3D9::HAL*              pPlatformHAL; 
    IDirect3DDeviceX*       pDevice;

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
