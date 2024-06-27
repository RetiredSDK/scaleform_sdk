/**************************************************************************

Filename    :   FxRenderThread.h
Content     :   RenderThread class used by GFxPlayer. Includes extra
                HUD support and timing logic.
Created     :   Dec, 2010
Authors     :   Art Bolgar, Michael Antonov

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef SF_FxRenderThread_H
#define SF_FxRenderThread_H

#include "Kernel/SF_Types.h"
#include "Platform/Platform_RenderThread.h"
#include "Render/Render_GlyphCacheConfig.h"

using namespace Scaleform;

// Render thread class.
class FxRenderThread : public Platform::RenderThread
{
public:
    FxRenderThread(Scaleform::RTCommandQueue::ThreadingType threadingType);
    virtual ~FxRenderThread() {}

    enum ProfileMode
    {
        Profile_None,
        Profile_Batch,
        Profile_Overdraw
    };

    void        SetProfileMode(ProfileMode mode)
    {
        UInt64 oldFlags = (ProfileModes >> Render::ProfileViews::Channel_Flags);
        switch(mode)
        {
        default:
            ProfileModes = 0;
            break;
        case Profile_Batch:
            ProfileModes = (UInt64(Render::ProfileViews::Profile_Batch  |255) << Render::ProfileViews::Channel_Green) |
                           (UInt64(Render::ProfileViews::Profile_Batch  |255) << Render::ProfileViews::Channel_Red) |
                           (UInt64(Render::ProfileViews::Profile_Batch  |255) << Render::ProfileViews::Channel_Blue);
            break;
        case Profile_Overdraw:
            ProfileModes = (UInt64(Render::ProfileViews::Profile_Fill   | 16) << Render::ProfileViews::Channel_Green) |
                           (UInt64(Render::ProfileViews::Profile_Mask   | 32) << Render::ProfileViews::Channel_Red) |
                           (UInt64(Render::ProfileViews::Profile_Blend  | 16) << Render::ProfileViews::Channel_Blue);
            break;
        }

        // Don't overwrite the flags channel.
        UInt64 flagMask = 0xFFFF;
        flagMask <<= Render::ProfileViews::Channel_Flags;
        ProfileModes &= ~flagMask;
        ProfileModes |= (oldFlags << Render::ProfileViews::Channel_Flags);
    }

    void        SetProfileFlag( UInt16 flag, bool set )
    {
        UInt64 newFlags = (ProfileModes >> Render::ProfileViews::Channel_Flags);
        if ( set )
            newFlags |= flag;
        else
            newFlags &= ~flag;

        UInt64 flagMask = 0xFFFF;
        flagMask <<= Render::ProfileViews::Channel_Flags;
        ProfileModes &= ~flagMask;
        ProfileModes |= (newFlags << Render::ProfileViews::Channel_Flags);
    }

    bool        GetProfileFlag( UInt16 flag )
    {
        return ((ProfileModes >> Render::ProfileViews::Channel_Flags) & flag) == flag;
    }


    // A separate display handle is maintained explicitly for HUD.
    void    SetHUDDisplayHandle(const Render::TreeRootDisplayHandle& handle)
    {
        if (handle == 0) RemoveDisplayHandle(DHCAT_Overlay);
        else             AddDisplayHandle(handle, DHCAT_Overlay);
    }

    // User matrix for main movie.
    void    SetUserMatrix(const Render::Matrix2F& m)
    {
        PushCall(&FxRenderThread::setUserMatrix, m);
    }
    void    SetHUDUserMatrix(const Render::Matrix2F& m)
    {
        PushCall(&FxRenderThread::setHUDUserMatrix, m);
    }

    // Queues up Present call without draw, only used for windowed resize.
    void    PresentOnResize()
    {
        PushCall(&FxRenderThread::presentOnResize);
    }

    void SetFontCacheConfig(Render::GlyphCacheParams fontCacheConfig)
    {    
        PushCall(&FxRenderThread::setFontCacheConfig, fontCacheConfig);
    }

    // LastDisplayTicks is the time directly associated with displaying
    // the tree, which is the cost of {NextCapture + Display}.
    // LastDrawFrameTicks is the timing for the entire DrawFrame call,
    // which includes the HUD, Clear and Present logic.
    UInt64      GetLastDisplayTicks() const   { return LastDisplayTicks; }
    UInt64      GetLastDrawFrameTicks() const { return LastDrawFrameTicks; }
    
protected:    

    void setUserMatrix(const Render::Matrix2F& m)
    {
        UserMatrix = m;
    }
    void setHUDUserMatrix(const Render::Matrix2F& m)
    {
        HUDUserMatrix = m;
    }
    void setFontCacheConfig(Render::GlyphCacheParams fontCacheConfig);

    // Override drawFrame to provide custom implementation.
    virtual void drawFrame();
    virtual void drawDisplayHandle(Platform::RenderThread::DisplayHandleDesc& desc,
                                   const Render::Viewport& vp, bool capture);
    virtual void finishFrame();
    virtual UInt64 getProfileMode() const { return ProfileModes; }

    void         presentOnResize();

private:    
    Render::Matrix2F                UserMatrix;
    Render::Matrix2F				HUDUserMatrix;

    UInt32                          LastDisplayTicks;
    UInt32                          LastDrawFrameTicks;

    UInt32                          LastDisplayTicksAccum;
    UInt32                          LastDrawFrameTicksAccum;

    UInt64                          ProfileModes;	

  //  FxRenderThread& operator=(const FxRenderThread&) { return *this; }
};


#endif // SF_FxRenderThread_H
