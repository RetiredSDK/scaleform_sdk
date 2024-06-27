/**************************************************************************

Filename    :   FxPlayerTextureInSWFGL.cpp
Content     :   Sample SWF/GFX file player leveraging GFxPlayer API
Created     :
Authors     :   Michael Antonov, Andrew Reisse

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

// This option specifies that external image files (DDS, etc) will be
// preloaded instead of loaded on demand during playback.
#define FXPLAYER_PRELOAD_IMAGES

// GFx includes
#include "GFile.h"
#include "GImage.h"
#include "GFxPlayer.h"
#include "GFxLoader.h"
#include "GFxLog.h"
#include "GString.h"
#include "GFxRenderConfig.h"
#include "GStd.h"
#include "GTimer.h"

#include "GFxFontLib.h"
#include "GImageInfo.h"
#include "GFxImageResource.h"

#ifdef GFC_OS_MAC
#include <OpenGL/glu.h>
#else
#define GL_GLEXT_PROTOTYPES
#include <GL/glu.h>
#include <GL/glext.h>
#endif
#include <unistd.h>

// Adds the word "Debug" to the application
// title if in debug build mode
#ifdef GFC_BUILD_DEBUG
#define GFC_DEBUG_STRING    " " GFC_BUILD_STRING
#else
#define GFC_DEBUG_STRING
#endif

#if defined(FXPLAYER_X11)
    // OpenGL application class
    #include "../Common/OpenGLX11App.h"
    #undef None
    #define FXPLAYER_APP    OpenGLX11App
    // Window name
    #define     FXPLAYER_APP_TITLE  "Scaleform RenderTexture Sample OpenGL v" GFC_FX_VERSION_STRING GFC_DEBUG_STRING

#elif defined(GFC_OS_MAC)
    // OpenGL application class
    #include "../Common/OpenGLMacApp.h"
    #undef None
    #define FXPLAYER_APP    OpenGLMacApp
    // Window name
    #define     FXPLAYER_APP_TITLE  "Scaleform RenderTexture Sample OpenGL v" GFC_FX_VERSION_STRING GFC_DEBUG_STRING
#endif

// Standard includes
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

//#include "../FxPlayer/FxPlayerAlloc.h"

#include "../../../Bin/FxPlayer/fxplayer.swf.h"

#include "../FxPlayer/FxPlayerLog.h"

#include "../Common/FontConfigParser.h"

// ***** Player Application class

class   FxPlayerApp : public FXPLAYER_APP
{
public:
    // Loaded movie data
    GFxLoader           Loader;
    GFxMovieInfo        MovieInfo;
    GPtr<GFxMovieDef>   pMovieDef;
    GPtr<GFxMovieView>  pMovie;

    bool                ReloadMovie;

    // Movie timing state
    float       SpeedScale;         // Advance speed, def 1.0f
    SInt        FrameCounter;       // Frames rendered, for FPS
    UInt        TessTriangles;      // Tess triangles for log.
    // Time ticks: always rely on a timer, for FPS
    UInt64      TimeStartTicks;     // Ticks during the start of playback
    UInt64      TimeTicks;          // Current ticks
    UInt64      LastLoggedFps;      // Time ticks during last FPS log
    UInt64      NextTicksTime;      // Ticks when next advance should be called.
    // Movie logical ticks: either timer or setting controlled
    UInt64      MovieStartTicks;
    UInt64      MovieLastTicks;
    UInt64      MovieTicks;

    // Renderer we use
    GPtr<GFxRenderConfig> pRenderConfig;
    GPtr<GFxRenderStats>  pRenderStats;

    // View width and height
    SInt                ViewWidth, ViewHeight;

    // Running antialiased or not (for lines)
    //AAModeType            AAMode;
    // Set if wireframe ins enabled.
    bool                Wireframe;

    // Scale toggle, on by default
    bool                ScaleEnable;


    // Rendering state
    bool                DoLoop;
    bool                DoRender;
    bool                DoSound;
    bool                NoControlKeys;


    bool                ClippingEnable;

    // Viewport transformation
    Float               Zoom;
    Float               ZoomStart;
    GPointF             Move;
    GPointF             MoveStart;
    GRenderer::Matrix   UserMatrix;

    enum TrackingState
    {
        None,
        Zooming,
        Moving,
    };
    TrackingState       MouseTracking;
    SInt                MouseX;
    SInt                MouseY;
    SInt                MouseDownX;
    SInt                MouseDownY;

    // This variable is set when the movie is paused in the player.
    bool                Paused;
    // Store playstate when paused, so that we can restore it.
    GFxMovie::PlayState PausedState;

    enum AAModeType
    {
        AAMode_None,        // No anti-aliasing is used.
        AAMode_EdgeAA,      // Edge AA is used (if supported by GRenderer).
        AAMode_FSAA         // HW Full-screen AA is used (if supported by device).
    };

    enum    HudStateType
    {
        Hud_Hidden,
        Hud_Stats,
        Hud_Help
    };

    HudStateType    HudState;
    Float       ScaleX, ScaleY;
    AAModeType  AAMode;
    bool        Background;
    Float       TexLodBias;

    // Set to play movie as fast as possible
    bool    FastForward;
    bool    MeasurePerformance;
    Float   ExitTimeout;
    UInt    SleepDelay; // Some consoles use this

    // Last FPS and stats
    Float               LastFPS;
    GRenderer::Stats    LastStats;
    UInt                LastFrame; // Frame reported by HUD
    // This flag is set when UpdateHudText needs to be called
    bool                NeedHudUpdate;
    // Hud text, blended over the player
    char                HudText[2048];
    char                MessageText[1024];
    GViewport           HudViewport;
    GPtr<GFxMovieView>  pHud;

    // Curve error
    Float               CurvePixelError;

    // Width, height during sizing
    SInt                SizeWidth, SizeHeight;
    bool                SizingEntered;

    // The requested language
    GString   RequestedLanguage;

    // PlaybackFile
    char    FileName[256];
    char    ShortFileName[64];


    GLuint                  RenderTextureId;
    GLuint                  RenderTextureFbo;

    SInt                    RTWidth, RTHeight;
    Float                   MeshRotation;
    UInt                    LastRotationTick;
    bool                    CubeWireframe;

    static FxPlayerApp      *pApp;


    FxPlayerApp();
    ~FxPlayerApp();

    virtual bool           OnArgsParsed(const FxArgs& args);
    virtual void           InitArgDescriptions(FxArgs* args);

    // Called from main() after settings are initialized to execute
    // most of the program logic. Responsible for setting up the window,
    // loading movies and containing the message loop.
    virtual int             Run();

    // Load a new movie from a file and initialize timing
    bool            LoadMovie(const char *pfilename);


    // Helper function to update HUD.
    // Uses LastFPS and LastStats; those variables must be updated separately.
    void            UpdateHudText();
    // Updates the view size based on the ScaleEnable flag and window size.
    void            UpdateViewSize();

    void            ResetUserMatrix();
    void            UpdateUserMatrix();
    GSizeF          GetMovieScaleSize();

    bool            SetupRTTexture();
    void            SetupMatrices();
    void            RenderMesh();

    // *** Overrides

    // Sizing; by default, re-initalizes the renderer
    virtual void    OnSize(SInt w, SInt h);
    virtual void    OnSizeEnter(bool enterSize);
    virtual void    OnDropFiles(char *path);

    // Input
    virtual void    OnKey(KeyCode, unsigned char asciiCode, unsigned int wcharCode, unsigned int mods, bool downFlag);
    virtual void    OnMouseButton(unsigned mouseIndex, unsigned int button, bool downFlag, int x, int y,
        unsigned int mods);
    virtual void    OnMouseWheel(unsigned mouseIndex, int zdelta, int x, int y, unsigned int mods);
    virtual void    OnMouseMove(unsigned mouseIndex, int x, int y, int unsigned mods);


    // Helper used to convert key codes and route them to GFxPlayer
    void            KeyEvent(GFxKey::Code keyCode, unsigned char asciiCode, unsigned int wcharCode, unsigned int mods, bool down);
};


// File opener class.
class FxPlayerFileOpener : public GFxFileOpener
{
public:
    virtual GFile* OpenFile(const char *purl)
    {
        if (!strcmp(purl, "  fxplayer.swf"))
            return new GMemoryFile(purl, fxplayer_swf, sizeof(fxplayer_swf));

        return GFxFileOpener::OpenFile(purl);
    }
};


// "fscommand" callback, handles notification callbacks from ActionScript.
class FxPlayerFSCallback : public GFxFSCommandHandler
{
public:
    virtual void Callback(GFxMovieView* pmovie, const char* pcommand, const char* parg)
    {
        GFxLog *plog = pmovie->GetLog();
        if (plog)
        {
            plog->LogMessage("FsCallback: '%s' '%s'\n", pcommand, parg);
        }

        if (!strcmp(pcommand, "wireframe") && FxPlayerApp::pApp)
            FxPlayerApp::pApp->CubeWireframe = !strcmp(parg, "1");
        else if (!strcmp(pcommand, "exit") && FxPlayerApp::pApp)
            FxPlayerApp::pApp->QuitFlag = 1;
    }
};


class FxPlayerUserEventHandler : public GFxUserEventHandler
{
    FxPlayerApp* pApp;
public:

    FxPlayerUserEventHandler(FxPlayerApp *papp)
    {
        pApp = papp;
    }

    virtual void HandleEvent(GFxMovieView* pmovie, const GFxEvent& event)
    {
        switch(event.Type)
        {
        default:
            break;

        case GFxEvent::DoShowMouse:
            pApp->ShowCursor(true);
            break;
        case GFxEvent::DoHideMouse:
            pApp->ShowCursor(false);
            break;
        }
    }
};




// ***** Main function implementation

int GCDECL main(int argc, char *argv[])
{
	GFxSystem gfxInit;

#ifdef FXPLAYER_USE_SYSALLOCATOR
    // Must set custom memory hooks before
    // creating FxPlayerApp or any other GFx objects
    SysAllocator    Allocator;
    GMemory::SetAllocator(&Allocator);
    GMemory::SetBlockAllocator(&Allocator);
#endif

    int res = 1;

    {
        FxPlayerApp app;

        app.AppMain(argc, argv);

#ifndef GFC_NO_THREADSUPPORT
        GThread::FinishAllThreads();
#endif

    }

    return res;
}



// ***** FxPlayerApp Implementation

FxPlayerApp::FxPlayerApp()
{
    ReloadMovie     = false;
    Wireframe   = 0;
    // Scale toggle, on by default
    ScaleEnable = 1;
    ClippingEnable = 1;
    Paused      = 0;
    PausedState = GFxMovie::Playing;

    ScaleX = ScaleY     = 1.0f;
    TexLodBias          = -0.5f;
    AAMode              = AAMode_EdgeAA;
    BitDepth            = 32;
    Background          = 1;

    MeasurePerformance  = 0;
    FullScreen          = 0;

    // No font config used by default.
    FastForward         = 0;

    ExitTimeout         = 0.0f;
    SleepDelay          = 31;

    // Clear file
    FileName[0]         = 0;
    ShortFileName[0]    = 0;

    // Clear timing
    SpeedScale          = 1.0f;
    FrameCounter        = 0;
    TessTriangles       = 0;

    TimeStartTicks      = 0;
    TimeTicks           = 0;
    NextTicksTime       = 0;
    LastLoggedFps       = 0;
    MovieStartTicks     = 0;
    MovieLastTicks      = 0;
    MovieTicks          = 0;

    LastFPS             = 0.0f;
    LastFrame           = 0;
    NeedHudUpdate       = 1;
    HudText[0]          = 0;
    MessageText[0]      = 0;

    HudState            = Hud_Hidden;

    DoLoop          = 1;
    DoRender        = 1;
    DoSound         = 0;
    NoControlKeys   = 0;


    ViewWidth   = 0;
    ViewHeight  = 0;

    Zoom = 1.0;
    Move = GPointF(0.0);

    MouseX = 0;
    MouseY = 0;
    MouseTracking   = None;

    SizingEntered = 0;

    CurvePixelError = 1.0f;

    MeshRotation            = 0;
    LastRotationTick        = 0;
    CubeWireframe           = 0;
    pApp = this;
}

FxPlayerApp *FxPlayerApp::pApp = 0;

FxPlayerApp::~FxPlayerApp()
{
}

struct Vertex
{
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

void    FxPlayerApp::RenderMesh()
{
    UInt    ticks = GTimer::GetTicks()/1000;

    // 1/10 revolution per second
    float dt = 0.0f;
    {
        float t  = (float)((double)fmod((double)ticks, 20000.0) / 20000.0) * 360;
        float lt = (float)((double)fmod((double)LastRotationTick, 20000.0) / 20000.0) * 360;
        dt = t - lt;
    }

    LastRotationTick    = ticks;
    MeshRotation        += dt;

    if (MeshRotation > 360)
        MeshRotation -= 360;
    if (MeshRotation < 0.0f)
        MeshRotation += 360;


    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, RenderTextureFbo);
    glViewport(0,0,RTWidth,RTHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,-4,-5.5, 1,0,0, -0.1,1,0);
    glRotated(MeshRotation, 0,1,0);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_FRAGMENT_PROGRAM_ARB);
    glDisable(GL_VERTEX_PROGRAM_ARB);
    glUseProgram(0);
    glColorMask(1,1,1,1);
    glClearColor(0,0,1,0.4f);
    glClearDepth(1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.1, 1);
    glPolygonMode(GL_FRONT_AND_BACK, CubeWireframe ? GL_LINE : GL_FILL);
    glLineWidth(6.0);
    glEnable(GL_LINE_SMOOTH);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), g_cubeVertices);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColor4ub(180,0,0,255);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glColor4ub(180,180,0,255);
    glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
    glColor4ub(0,180,180,255);
    glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
    glColor4ub(0,180,0,255);
    glDrawArrays(GL_TRIANGLE_STRIP,12, 4);
    glColor4ub(0,0,180,255);
    glDrawArrays(GL_TRIANGLE_STRIP,16, 4);
    glColor4ub(180,0,180,255);
    glDrawArrays(GL_TRIANGLE_STRIP,20, 4);

    glDisableClientState(GL_VERTEX_ARRAY);

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(1);
    glDisable(GL_LINE_SMOOTH);

    glBindTexture(GL_TEXTURE_2D, RenderTextureId);
    glGenerateMipmapEXT(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool    FxPlayerApp::SetupRTTexture()
{
    GLuint rbs[2];

    // Create texture and framebuffer
    glGenFramebuffersEXT(1, &RenderTextureFbo);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, RenderTextureFbo);

    glGenTextures(1, &RenderTextureId);
    glBindTexture(GL_TEXTURE_2D, RenderTextureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, RTWidth,RTHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glGenerateMipmapEXT(GL_TEXTURE_2D);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, RenderTextureId, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffersEXT(2, rbs);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rbs[0]);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, RTWidth,RTHeight);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rbs[0]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

    if (pMovie)
    {
        GFxResource*	  pres = pMovie->GetMovieDef()->GetResource("texture1");
        GFxImageResource* pimageRes = 0;
        if (pres && pres->GetResourceType() == GFxResource::RT_Image)
            pimageRes = (GFxImageResource*)pres;

        if (pimageRes)
        {
            // We know that the imageInfo is GImageInfo since we didn't override image creator.
            GImageInfo* pimageInfo = (GImageInfo*)pimageRes->GetImageInfo();

            if (pimageInfo)
            {
                GPtr<GTextureOGL> ptexture = *pRenderer->CreateTexture();
                ptexture->InitTexture(RenderTextureId);
                pimageInfo->SetTexture(ptexture);
            }
        }
    }

    return 1;
}


//  Sample translator implementation that can be used for testing.
/*
class TranslatorImpl : public GFxTranslator
{
public:
    // wwMode can be GFxTranslator::WWT_NoHangulWrap (Korean),
    // GFxTranslator::WWT_Prohibition (used in Japanese) or
    // GFxTranslator::WWT_Asian (Chinese). Also GFxTranslator::WWT_Hyphenation
    // might be used for very simple hyphenation. OnWordWrapping virtual 
    // method might be overridden to implement custom word-wrapping rules.
    TranslatorImpl(UInt wwMode = GFxTranslator::WWT_Default) :
      GFxTranslator(wwMode) {}

    virtual UInt    GetCaps() const         
    { 
        return Cap_StripTrailingNewLines; 
    }
    virtual void    Translate(TranslateInfo* ptranslateInfo)
    {
        // Translated strings start with $$sign
        const wchar_t* pkey = ptranslateInfo->GetKey();
        if (pkey[0] == '$')
        {
            GFxWStringBuffer buffer;
            size_t l = G_wcslen(pkey);
            buffer.Resize(l + 100);
            wchar_t* pb = buffer.GetBuffer();

            //G_wcscpy(pb, buffer.GetLength(), pkey+1);
            //ptranslateInfo->SetResult(buffer.ToWStr());

            G_wcscpy(pb, buffer.GetLength(), L"<font color='#00FF33'>*TR[<font color='#FF3300'>");
            G_wcscat(pb, buffer.GetLength(), pkey+1);
            G_wcscat(pb, buffer.GetLength(), L"</font>]</font>");
            ptranslateInfo->SetResultHtml(buffer.ToWStr());
        }
        // example of using GetInstanceName()
        else if (G_strcmp(ptranslateInfo->GetInstanceName(), "plainText") == 0)
        {
            ptranslateInfo->SetResult("PLAIN");
        }
    }
};
*/

void FxPlayerApp::InitArgDescriptions(FxArgs* args)
{
    FXPLAYER_APP::InitArgDescriptions(args);

    FxArgDesc options []=
    {
        //      {"","--------------spacer example------------------\n","",FxCmdOption::Spacer,""},
        {"",    "FileName",            FxArgs::StringOption | FxArgs::Positional, NULL,
        "GFX or SWF file to load at startup"},
        {"s",   "ScaleFactor",         FxArgs::FloatOption, "1.0",
        "<factor> Scale the movie window size by the specified factor."},
        {"na",  "noAA",                FxArgs::Flag, "", "Use no anti-aliasing."},
        {"fsa", "FSAA",                FxArgs::Flag, "", "Use use fullscreen HW AA."},
        {"nsf", "NoSystemFont",        FxArgs::Flag, "", "No system font - disables GFxFontProviderWin32."},
        {"nfc", "NoFontConfig",        FxArgs::Flag, "", "Disable autoloading of font config file in movie's path."},
        {"fc",  "FontConfigFile",      FxArgs::StringOption, "", "<fname> Load a font config file."},
        {"fl",  "FontLibFile",         FxArgs::StringOption, NULL,
        "<fname>  Specifies a SWF/GFX file to load into GFxFontLib."},
        {"i",   "DisplayHudOnStartup", FxArgs::Flag, "", "Display info HUD on startup.",},
        {"vp",  "VerboseParse",        FxArgs::Flag, "", "Verbose parse - print SWF parse log."},
        {"vps", "VerboseParseShape",   FxArgs::Flag, "" ,"Verbose parse shape - print SWF shape parse log."},
        {"vpa", "VerboseParseAction",  FxArgs::Flag, "", "Verbose parse action - print SWF actions during parse."},
        {"vfq", "NoLogChildFilnames",  FxArgs::Flag, "", "Do not print SWF filename for ActionScript errors in child movies."},
        {"vfr", "LogRootFilenames",    FxArgs::Flag, "","Print SWF filename for ActionScript errors in root movies."},
        {"vfp", "LogFilePath",         FxArgs::Flag, "", "Print full file path for ActionScript errors."},
        {"va",  "VerboseActions",      FxArgs::Flag, "", "Verbose actions - display ActionScript execution log."},
        {"q",   "Quiet",               FxArgs::Flag, "", "Quiet. Do not display errors or trace statements."},
        {"qae", "SuppressASErrors",    FxArgs::Flag, "", "Quiet. Suppress ActionScript errors."},
        {"ml",  "LodBias",             FxArgs::FloatOption, "-0.5",
        "<bias>  Specify the texture LOD bias (float, default -0.5)"},
        {"p",   "PerfomanceTest",      FxArgs::Flag, "", "Performance test - run without delay and log FPS."},
        {"ff",  "FastForward",         FxArgs::Flag, "", "Fast forward - run one frame per update."},
        {"1",   "PlayOnce",            FxArgs::Flag, "", "Play once; exit when/if movie reaches the last frame."},
        {"nr",  "NoRendering",         FxArgs::Flag, "", "Disable rendering (for batch tests)"},
        {"nck", "NoControlKeys",       FxArgs::Flag, "", "Disable all player related control keys."},
        {"nh", "NoHud",                FxArgs::Flag, "", "Do not load HUD SWF."},
        {"t",   "ExitTimeout",         FxArgs::FloatOption, "0.0",
        "<sec>    Timeout and exit after the specified number of seconds."},
#if defined(FXPLAYER_RENDER_DIRECT3D) && (GFC_D3D_VERSION != 10)
        {"dyn", "DynamicTextures" ,    FxArgs::Flag, "", "Use dynamic textures (D3D)."},
#endif
        {"","",FxArgs::ArgEnd,"",""},
    };
    args->AddDesriptions(options);
}

bool FxPlayerApp::OnArgsParsed(const FxArgs& args)
{
    if (!FXPLAYER_APP::OnArgsParsed(args))
        return false;

    if (args.HasValue("FileName"))
    {
        G_strcpy(FileName, 256, args.GetString("FileName").ToCStr());
    }
    ScaleX = ScaleY = args.GetFloat("ScaleFactor");
    DoRender = !args.GetBool("NoRendering");
    FastForward =  args.GetBool("FastForward");
    ExitTimeout =  args.GetFloat("ExitTimeout");
    if (args.GetBool("DisplayHudOnStartup"))
        HudState = Hud_Stats;
    DoLoop = !args.GetBool("PlayOnce");

    NoControlKeys = args.GetBool("NoControlKeys");

    return true;
}


SInt    FxPlayerApp::Run()
{

    // Set the verbose flags.
    UInt verboseFlags = 0;

    if (Arguments.GetBool("VerboseParse"))
        verboseFlags |= GFxParseControl::VerboseParse;
    if (Arguments.GetBool("VerboseParseShape"))
        verboseFlags |= GFxParseControl::VerboseParseShape;
    if (Arguments.GetBool("VerboseParseAction"))
        verboseFlags |= GFxParseControl::VerboseParseAction;

    GPtr<GFxParseControl> pparseControl = *new GFxParseControl(verboseFlags);
    Loader.SetParseControl(pparseControl);

    // File callback.
    GPtr<GFxFileOpener> pfileOpener = *new FxPlayerFileOpener;
    Loader.SetFileOpener(pfileOpener);

#ifdef GFC_OS_MAC
    // Keep images for renderer changes
    GPtr<GFxImageCreator> pImageCreator = *new GFxImageCreator(1);
    Loader.SetImageCreator(pImageCreator);
#endif


    // Set log, but only if not quiet
    if (!Arguments.GetBool("Quiet"))
        Loader.SetLog(GPtr<GFxLog>(*new GFxPlayerLog()));


    // Creating a new font cache manager
    //GFxFontCacheManager::TextureConfig fontCacheConfig;
    //fontCacheConfig.TextureWidth = ...
    //fontCacheConfig...
    //Loader.SetFontCacheManager(GPtr<GFxFontCacheManager>(*new GFxFontCacheManager(fontCacheConfig)));

    // Modification of the existing font cache manager
    GFxFontCacheManager::TextureConfig fontCacheConfig;
    //    fontCacheConfig.TextureWidth   = 1024;
    //    fontCacheConfig.TextureHeight  = 1024;
    //    fontCacheConfig.MaxSlotHeight  = 48;
    //    fontCacheConfig.SlotPadding    = 2;
    //    fontCacheConfig.MaxNumTextures = 1;
    Loader.GetFontCacheManager()->SetTextureConfig(fontCacheConfig);
    Loader.GetFontCacheManager()->EnableDynamicCache(true);
    Loader.GetFontCacheManager()->SetMaxRasterScale(1.25f);

    //GFxFontPackParams::TextureConfig fontPackConfig;
    //fontPackConfig....
    //Loader.GetFontPackParams()->SetTextureConfig(fontPackConfig);
    //Loader.GetFontPackParams()->SetGlyphCountLimit(1000);
    Loader.SetFontPackParams(0);

    char *apppath = GetAppPath();

    if (strlen(FileName)==0 && sizeof(FileName) - 20 > strlen(apppath))
    {
        strcpy(FileName, apppath);
#ifdef GFC_OS_MAC
        strcat(FileName, "/Contents/Window_texture.swf");
#else
        strcat(FileName, "/Bin/RenderTexture/Window_texture.swf");
#endif
    }

    // Create a system font provider on Windows. If this is not done,
    // system font characters will be displayed as squares.
//    if (!NoSystemFont)
//    {
//        GPtr<GFxFontProviderMac> fontProvider = *new GFxFontProviderMac(::GetDC(0));
  //      Loader.SetFontProvider(fontProvider);
//    }


    // Load movie for the stats display
    // GFxLoader::LoadWaitCompletion should be set from threaded loading for HUD movie.
    // Otherwise HUD will no be shown because is Advance method gets call only once when the
    // movie is not ready yet
    GPtr<GFxMovieDef> pHudDef = *Loader.CreateMovie("  fxplayer.swf",
        GFxLoader::LoadAll|GFxLoader::LoadOrdered
        |GFxLoader::LoadKeepBindData|GFxLoader::LoadWaitCompletion);
    if (pHudDef)
    {
        pHud = *pHudDef->CreateInstance();
        if (pHud)
        {
            pHud->SetBackgroundAlpha(0);

#ifdef FXPLAYER_FONT_SIZE
            pHud->Invoke("_root.setHudFontSize", "%d", FXPLAYER_FONT_SIZE);
#endif
        }
    }

    bool loadMovie = strlen(FileName)>0;

    if (!loadMovie)
    {
//        PrintUsage();
        return 1;
    }

    // Get info about the width & height of the movie.
    if (!loadMovie || !Loader.GetMovieInfo(FileName, &MovieInfo))
    {
        if (loadMovie)
            fprintf(stderr, "Error: failed to get info about %s\n", FileName);

        ViewWidth   = 1024;
        ViewHeight  = 768;

        //return 1;
    }
    else
    {
        ViewWidth   = (SInt) (MovieInfo.Width * ScaleX);
        ViewHeight  = (SInt) (MovieInfo.Height * ScaleY);
    }


    if (DoRender)
    {
        // Set options based on arguments
        FullScreen      = Arguments.GetBool("FullScreen");;
        FSAntialias     = (AAMode == AAMode_FSAA) ? 1 : 0;
        BitDepth        = BitDepth;

        if (FullScreen)
        {
            ScaleX = 1024.0f / ViewWidth;
            ScaleY = 768.0f / ViewHeight;
            ViewWidth       = 1024;
            ViewHeight      = 768;
        }


        // Enable file drop.
        SupportDropFiles = 1;
        SizableWindow    = 1;
        SInt w = ViewWidth, h = ViewHeight;
        SetupWindowParams params;
#ifdef GFC_OS_MAC
        params.X = params.Y = 0;
#else
        params.X = params.Y = 100;
#endif
        params.FullScreen = FullScreen;
        if (!SetupWindow(FXPLAYER_APP_TITLE, ViewWidth, ViewHeight, params))
            return 1;

        RTWidth = 256;
        RTHeight = 256;
        SetupRTTexture();

        // It is important to initialize these sizes, in case OnSizeEnter gets called.
        SizeWidth  = Width;
        SizeHeight = Height;

        // Width & Height might be changed by SetupWindow call above
        if (w != Width || h != Height)
            UpdateViewSize();

        // Create renderer
        if (!CreateRenderer())
            return 1;

        // Set renderer on loader so that it is also applied to all children.
        pRenderConfig = *new GFxRenderConfig(GetRenderer());
        Loader.SetRenderConfig(pRenderConfig);

        // Create a renderer stats object since we will be tracking statistics.
        pRenderStats = *new GFxRenderStats();
        Loader.SetRenderStats(pRenderStats);

    }

    // Load movie and initialize timing.
    if (loadMovie && !LoadMovie(FileName))
    {
        //return 1;
    }


    while (1)
    {
        TimeTicks = GTimer::GetTicks()/1000;

        if (DoRender && !FastForward)
            MovieTicks = TimeTicks;
        else // Simulate time.
            MovieTicks = MovieLastTicks + (UInt32) (1000.0f / MovieInfo.FPS);

        int     deltaTicks  = MovieTicks - MovieLastTicks;
        float   deltaT      = deltaTicks / 1000.f;

        MovieLastTicks = MovieTicks;

        // Check auto exit timeout counter.
        if ((ExitTimeout > 0) &&
            (MovieTicks - MovieStartTicks > (UInt32) (ExitTimeout * 1000)) )
            break;

        // Process messages and exit if necessary.
        if (!ProcessMessages())
            break;

        if (!IsVisible())
        {
            SleepTillMessage(200);
            continue;
        }

        // *** Advance/Render movie

        // This is technically necessary only for D3D
        DisplayStatus status = CheckDisplayStatus();
        if (status == DisplayStatus_Unavailable)
        {
            SleepMilliSecs(10);
            continue;
        }
        if (status == DisplayStatus_NeedsReset)
        {
            RecreateRenderer();
        }

        // Potential out-of bounds range is not a problem here,
        // because it will be adjusted for inside of the player.
        if (pMovie)
        {
            pMovie->SetViewport(Width,Height, (Width-ViewWidth)/2, (Height-ViewHeight)/2,
                ViewWidth, ViewHeight);
            pMovie->SetBackgroundAlpha(Background ? 1.0f : 0.05f);

            Float timeTillNextTicks;

            if (!Paused)
                timeTillNextTicks = pMovie->Advance(deltaT * SpeedScale, 0);
            else
                timeTillNextTicks = 0.05f;

            NextTicksTime = TimeTicks + (UInt32)(timeTillNextTicks * 1000.0f);
            if (NextTicksTime < TimeTicks) // wrap-around check.
                NextTicksTime = TimeTicks;
        }

        if (DoRender)
        {
            RenderMesh();

            // Renderer-specific preparation (Disable depth testing)
            PrepareRendererForFrame();
            GetRenderer()->BeginFrame();

            // Clear the entire buffer.
            Clear(GColor::Blue);

        // Enable wireframe if requested.
        if (Wireframe)
            SetWireframe(1);
        }

        if (pMovie)
            pMovie->Display();

        FrameCounter++;


        if (DoRender)
        {
            SetWireframe(0);

            if (pMovie && (LastFrame != pMovie->GetCurrentFrame()))
                NeedHudUpdate = 1;

            // Get stats every frame
            GRenderer::Stats    renderStats;
            GetRenderer()->GetRenderStats(&renderStats, 1);
            // If ballpark triangle count changed, need update
            if (((renderStats.Triangles >> 11) != (LastStats.Triangles >> 11)) ||
                (renderStats.Primitives != LastStats.Primitives))
                NeedHudUpdate = 1;
            LastStats = renderStats;

            if (NeedHudUpdate && pHud)
            {
                UpdateHudText();
                HudViewport = GViewport(GetWidth(), GetHeight(),
                    SInt(GetWidth()*GetSafeArea()),
                    SInt(GetHeight()*GetSafeArea()),
                    SInt(GetWidth() - 2*GetWidth()*GetSafeArea()),
                    SInt(GetHeight() - 2*GetHeight()*GetSafeArea()));

                pHud->SetViewport(HudViewport);
                pHud->Invoke("_root.setHudText", "%s", HudText);
                pHud->Invoke("_root.setMessageText", "%s", MessageText);
                if (!pMovie)
                    pHud->Invoke("_root.setHudSize", "%d %d", 0, 0);
            }

            // Draw the HUD screen if it is displayed.
            if (pHud && (!pMovie || HudState != Hud_Hidden) /*&& HudText[0]*/)
            {
                SetWireframe(0);
                GRenderer::Matrix m;
                GetRenderer()->SetUserMatrix(m);
                pHud->Display();
                GetRenderer()->SetUserMatrix(UserMatrix);

                GetRenderer()->GetRenderStats(&renderStats, 1);
            }

            // Flip buffers to display the scene
            PresentFrame();
            GetRenderer()->EndFrame();

            if (!pMovie || (!MeasurePerformance && !FastForward))
            {
                // Don't hog the CPU.
                if (pMovie)
                {
                    TimeTicks = GTimer::GetTicks() / 1000;
                    if (TimeTicks < NextTicksTime)
                        SleepTillMessage(NextTicksTime - TimeTicks);
                }
                else
                {
                    SleepTillMessage(2000);
                }
            }
            else
            {
                // Log the frame rate every second or so.
                if (TimeTicks - LastLoggedFps > 1000)
                {
                    float   delta = (TimeTicks - LastLoggedFps) / 1000.f;

                    char buff[512];

                    LastFPS = (delta > 0) ? FrameCounter / delta : 0.0f;

                    TessTriangles = pRenderStats->GetTessStatistics();

                    // Display frame rate in title
                    G_sprintf(buff, 512, FXPLAYER_APP_TITLE " (fps:%3.1f)", LastFPS);
                    SetWindowTitle(buff);

                    // Update HUD
                    NeedHudUpdate = 1;

                    LastLoggedFps = TimeTicks;
                    FrameCounter = 0;
                }
            }
        }

        // If we're reached the end of the movie, exit.
        if (!DoLoop && pMovie &&
            (pMovie->GetCurrentFrame() + 1 == pMovieDef->GetFrameCount()) )
            break;
    }


    // Release logic? -> TBD

    pMovie      = 0;

    return 0;
}

/*
GImageInfoBase* GFxImageCreateCallback(const GFxImageCreateInfo& info, Handle userHandle)
{
    GUNUSED(userHandle);
    switch(info.Type)
    {
        case GFxImageCreateInfo::Input_None:
            return new GImageInfo();
        case GFxImageCreateInfo::Input_Image:
            return new GImageInfo(info.pImage);

        case GFxImageCreateInfo::Input_File:

#ifdef FXPLAYER_PRELOAD_IMAGES
            // VisitImages will do the pre-loading.
            return new GImageInfo(0, info.FileInfo.TargetWidth, info.FileInfo.TargetHeight);
#else
            if (info.FileInfo.Format == GFxFileConstants::Image_TGA)
                return new GImageInfo(0, info.FileInfo.TargetWidth, info.FileInfo.TargetHeight);
            else
                return new GImageFileInfo(info.FileInfo.TargetWidth, info.FileInfo.TargetHeight);
#endif

    }
    return 0;
}

*/

/*
// An example of ExternalInterface handler implementation
class CustomEIHandler : public GFxExternalInterface
{
public:
    void Callback(GFxMovieView* pmovieView, const char* methodName, const GFxValue* args, UInt argCount)
    {
        GUNUSED(pmovieView);
        printf("\nCallback! %s, nargs = %d\n", (methodName)?methodName:"(null)", argCount);
        for (UInt i = 0; i < argCount; ++i)
        {
            printf("  arg(%d) = ", i);
            switch(args[i].GetType())
            {
            case GFxValue::VT_String: printf("%s", args[i].GetString()); break;
            case GFxValue::VT_Number: printf("%f", args[i].GetNumber()); break;
            case GFxValue::VT_Boolean: printf("%s", (args[i].GetBool())?"true":"false"); break;
            // etc...
            }
            printf("\n");
        }
        wchar_t localBuf[100];
        wcscpy(localBuf, L"Oppa!");     // just to demonstrate how to return local wide char strings
        pmovieView->SetExternalInterfaceRetVal(GFxValue(localBuf));
        // or, the most simple way to return a value is as follows:
        //pmovieView->SetExternalInterfaceRetVal(GFxValue("Oppa!"));
    }
};
*/

// Load a new movie from a file and initialize timing
bool    FxPlayerApp::LoadMovie(const char *pfilename)
{
    // Try to load the new movie
    GPtr<GFxMovieDef>   pnewMovieDef;
    GPtr<GFxMovieView>  pnewMovie;
    GFxMovieInfo        newMovieInfo;

    // Get info about the width & height of the movie.
    if (!Loader.GetMovieInfo(pfilename, &newMovieInfo, 0, GFxLoader::LoadKeepBindData))
    {
        fprintf(stderr, "Error: Failed to get info about %s\n", pfilename);
        return 0;
    }

    UInt loadConstants = GFxLoader::LoadAll;
    /*
    if (newMovieInfo.IsStripped())
    {
        Loader.SetImageCreateCallback(GFxImageCreateCallback, 0);
        loadConstants &= (~GFxLoader::LoadImageData);
    }
    else
    {
        // For normal '.swf' files use default image implementation.
        Loader.SetImageCreateCallback(0, 0);
    }
    */

    // Load the actual new movie and crate instance.
    // Don't use library: this will ensure that the memory is released.
    pnewMovieDef = *Loader.CreateMovie(pfilename, loadConstants|GFxLoader::LoadOrdered|GFxLoader::LoadKeepBindData);
    if (!pnewMovieDef)
    {
        fprintf(stderr, "Error: Failed to create a movie from '%s'\n", pfilename);
        return 0;
    }

    pnewMovie = *pnewMovieDef->CreateInstance(false);
    if (!pnewMovie)
    {
        fprintf(stderr, "Error: Failed to create movie instance\n");
        return 0;
    }

    // If this succeeded, replace the old movie with the new one.
    pMovieDef   = pnewMovieDef;
    pMovie      = pnewMovie;
    memcpy(&MovieInfo, &newMovieInfo, sizeof(GFxMovieInfo));

    // This should only be true if this is the GFxPlayer application
    // Make sure to comment this out or set the value to false in your game
    pMovie->SetVariable("_global.gfxPlayer", GFxValue(true));


    // Set ActionScript verbosity / etc.
    GPtr<GFxActionControl> pactionControl = *new GFxActionControl();
    pactionControl->SetVerboseAction(Arguments.GetBool("VerboseActions"));
    pactionControl->SetActionErrorSuppress(Arguments.GetBool("SuppressASErrors"));
    pactionControl->SetLogRootFilenames(Arguments.GetBool("LogRootFilenames"));
    pactionControl->SetLogChildFilenames(!Arguments.GetBool("NoLogChildFilnames"));
    pactionControl->SetLongFilenames(Arguments.GetBool("LogFilePath"));
    pMovie->SetActionControl(pactionControl);

    // Install handlers.
    pMovie->SetFSCommandHandler(GPtr<GFxFSCommandHandler>(*new FxPlayerFSCallback()));
    pMovie->SetUserEventHandler(GPtr<GFxUserEventHandler>(*new FxPlayerUserEventHandler(this)));

    // setting ExternalInterface handler
    //GPtr<CustomEIHandler> pei = *new CustomEIHandler();
    //pMovie->SetExternalInterface(pei);

    // init first frame
    pMovie->Advance(0.0f, 0);

    // Renderer
    if (DoRender)
    {
        if (AAMode == AAMode_EdgeAA)
            pRenderConfig->SetRenderFlags(pRenderConfig->GetRenderFlags() | GFxRenderConfig::RF_EdgeAA);
    }

    if (DoSound)
    {   // TBD:
        //  GFxSoundPlayer* psound = NULL;
        //      psound = GFxSoundPlayer::CreatePlayer ();
        //      pMovie->SetSoundPlayer(psound);
    }

    // Copy short filename (i.e. after last '/'),
    // but only if the source isn't the same buffer.
    if (FileName != pfilename)
    {
        SPInt len = strlen(pfilename);
        for (SPInt i=len; i>0; i--)
        {
            if (pfilename[i]=='/' || pfilename[i]=='\\')
            {
                pfilename = pfilename+i+1;
                break;
            }
        }
        G_strcpy(FileName, 256, pfilename);
    }


    // Disable pause.
    Paused          = 0;

    // Init timing for the new piece.
    FrameCounter    = 0;
    // Time ticks: always rely on a timer
    TimeStartTicks  = GTimer::GetTicks()/1000;
    NextTicksTime   = TimeStartTicks;
    LastLoggedFps   = TimeStartTicks;
    // Movie logical ticks: either timer or setting controlled
    MovieStartTicks = (DoRender && !FastForward) ? TimeStartTicks : 0;
    MovieLastTicks  = MovieStartTicks;
    // Set the Hud to update
    NeedHudUpdate = 1;

    // Update the view
    UpdateViewSize();

    GFxResource*	  pres = pMovie->GetMovieDef()->GetResource("texture1");
    GFxImageResource* pimageRes = 0;
    if (pres && pres->GetResourceType() == GFxResource::RT_Image)
        pimageRes = (GFxImageResource*)pres;

    if (pimageRes)
    {
        GPtr<GTextureOGL> pTexture = *pRenderer->CreateTexture();
        pTexture->InitTexture(RenderTextureId, 0);

        // Store the original image info's width and height.
        GImageInfo* pimageInfo = (GImageInfo*)pimageRes->GetImageInfo();
        // Convert image to texture; keep image dimensions as target size.
        pimageInfo->SetTexture(pTexture.GetPtr(),
                               pimageInfo->GetWidth(), pimageInfo->GetHeight());
    }

    return 1;
}


// Called when sizing begins and ends.
void    FxPlayerApp::OnSizeEnter(bool enterSize)
{

    // When leaving size, adjust to new widtj/height.
    if (!enterSize)
    {
        SizingEntered = 0;

        if (GetRenderer() && ((SizeWidth != Width) || (SizeHeight != Height)))
        {
            ResizeWindow(SizeWidth, SizeHeight);
            UpdateViewSize();
        }
    }
    else
    {
        // Set SizingEntered flag so that we can differentiate size-grip
        // resize from instantaneous resize (maximize).
        SizingEntered = 1;
    }
}

// Sizing; by default, re-initalizes the renderer
void    FxPlayerApp::OnSize(SInt w, SInt h)
{
    if (GetRenderer())
    {
        SizeWidth = w;
        SizeHeight= h;

        if (!SizingEntered && CheckDisplayStatus() == DisplayStatus_Ok)
        {
            // Commit sizing immediately if it was due to maximize.
            OnSizeEnter(0);
        }
        else
        {
            if (!(FSAntialias && FSAASupported))
                PresentFrame();
        }
    }
}

void    FxPlayerApp::ResetUserMatrix()
{
    Move = GPointF(0.0f);
    Zoom = 1.0f;
    UpdateUserMatrix();
}

void    FxPlayerApp::UpdateUserMatrix()
{
    if (!GetRenderer())
        return;
    GRenderer::Matrix m;
    m.AppendScaling(Zoom);
    m.AppendTranslation(Move.x * GFxMovie::GetRenderPixelScale(), Move.y * GFxMovie::GetRenderPixelScale());
    GetRenderer()->SetUserMatrix(m);
    UserMatrix = m;
    UpdateHudText();
}

GSizeF  FxPlayerApp::GetMovieScaleSize()
{
    GSizeF  scale;
    scale.Width     = (pMovie->GetVisibleFrameRect().Width() / ViewWidth);
    scale.Height    = (pMovie->GetVisibleFrameRect().Height() / ViewHeight);
    return scale;
}


// Updates the view size based on the ScaleEnable flag and window size.
void    FxPlayerApp::UpdateViewSize()
{
    if (ScaleEnable)
    {
        SInt width = G_Max(Width, 4);
        SInt height= G_Max(Height, 4);

        if (ClippingEnable)
        {
            // Determine movie size and location based on the aspect ratio
            float hw;
            if (MovieInfo.Height != 0 && MovieInfo.Width != 0)
                hw = (Float) MovieInfo.Height / (Float) MovieInfo.Width;
            else
                hw = (Float) height / (Float) width;
            if (width * hw > height)
            {
                // Use height as the basis for aspect ratio
                ViewWidth   = (SInt)((float) height / hw);
                ViewHeight  = height;
            }
            else
            {
                // Use width
                ViewWidth   = width;
                ViewHeight  = (SInt) (width * hw);
            }
        }
        else
        {
            ViewWidth = width;
            ViewHeight = height;
        }
        // Compute input scale
        ScaleX = (Float) ViewWidth / (Float) MovieInfo.Width;
        ScaleY = (Float) ViewHeight / (Float) MovieInfo.Height;
    }
    else
    {
        // No scaling, just center the image
        ViewWidth   = MovieInfo.Width;
        ViewHeight  = MovieInfo.Height;
        ScaleX = ScaleY = 1.0f;
    }
}


// Helper function to update HUD.
// Uses LastFPS and LastStats; those variables must be updated separately.
void    FxPlayerApp::UpdateHudText()
{
    if (!pMovie)
    {
        G_strcpy(HudText, sizeof(HudText), "");
#ifdef FXPLAYER_FILEPATH
        if (IsConsole())
            G_strcpy(MessageText, sizeof(MessageText), "Copy a SWF/GFX file to\n" FXPLAYER_FILEPATH);
        else
#endif
            G_strcpy(MessageText, sizeof(MessageText), "Drag and drop SWF/GFX file here");
        return;
    }
    else
        MessageText[0]=0;

    if (pMovie)
        LastFrame = pMovie->GetCurrentFrame();
    else
        LastFrame = 0;

    // Stroke type
    UInt32  stroke       = GFxRenderConfig::RF_StrokeCorrect;
    bool    optTriangles = false;

    if (pRenderConfig)
    {
        stroke = (pRenderConfig->GetRenderFlags() & GFxRenderConfig::RF_StrokeMask);
        optTriangles = (pRenderConfig->GetRenderFlags() & GFxRenderConfig::RF_OptimizeTriangles) != 0;
    }

// Display a custom message if stroke is #ifdef-ed out.
#ifndef GFC_NO_FXPLAYER_STROKER
    const char * pstrokeType = "Correct";
    if (stroke == GFxRenderConfig::RF_StrokeNormal)
        pstrokeType = "Normal";
#else
    const char * pstrokeType = "Correct [#disabled]";
    if (stroke == GFxRenderConfig::RF_StrokeNormal)
        pstrokeType = "Normal [#disabled]";
#endif

    if (stroke == GFxRenderConfig::RF_StrokeHairline)
        pstrokeType = "Hairline";


    // AA Type
    const char * pAAType = "Edge AA";

    switch(AAMode)
    {
    case AAMode_None:
        pAAType = "None";
        break;
    case AAMode_EdgeAA:

// Display a custom message if edge AA is #ifdef-ed out.
#ifndef GFC_NO_FXPLAYER_EDGEAA
        pAAType = "Edge AA";
        {
            // Report if EdgeAA is not supported by renderer.
            GRenderer::RenderCaps caps;
            caps.CapBits = 0;
            if (GetRenderer())
                GetRenderer()->GetRenderCaps(&caps);
            if (!(caps.CapBits & GRenderer::Cap_FillGouraud))
                pAAType = "Edge AA (Not Supported)";
            else if (!(caps.CapBits & GRenderer::Cap_FillGouraudTex))
                pAAType = "Edge AA (Limited)";
        }
#else
        pAAType = "Edge AA [#disabled]";
#endif

        break;
    case AAMode_FSAA:
        if (FSAASupported)
            pAAType = "HW FSAA";
        else
            pAAType = "HW FSAA (Not Supported)";
        break;
    }

#ifdef   FXPLAYER_MEMORY_TRACKSIZES
    GAllocator*            palloc = GMemory::GetAllocator();
    const GAllocatorStats* pstats = palloc->GetStats();
#endif

    // Update hud text
        G_sprintf(HudText, 2048,
        "Playback Info (F1/F2)\n\n"
        "Filename:  %s\n"
        "           SWF %d (%dx%d@%.f)\n"
        "           %d/%d frames%s\n"
        "FPS:       %3.1f\n"
#ifdef   FXPLAYER_MEMORY_TRACKSIZES
        "MemUse:    %dK / %dK @ %d\n"
#endif
        "NewTess:   %d Tri/s\n"
        "Triangles: %d @ %d DP\n"
        "Lines:     %d\n"
        "CurveErr:  %3.1f (Ctrl - or +)\n"
        "Stroke:    %s\n"
        "Zoom:      %3.2f\n"
        //"Move:      x:%3.1f y:%3.1f"
        "AA Mode:   %s %s"
                    //"FontCfg:   %s"
                    ,

        FileName,
        MovieInfo.Version,
        MovieInfo.Width, MovieInfo.Height, MovieInfo.FPS,
        LastFrame, MovieInfo.FrameCount, Paused ? " (Paused)" : "",
        LastFPS,
#ifdef   FXPLAYER_MEMORY_TRACKSIZES
        (pstats->GetSizeAllocated()+1023) / 1024,
        (pstats->GetSizeUsed()+1023) / 1024,
        (pstats->AllocCount - pstats->FreeCount),
#endif
        TessTriangles,
        LastStats.Triangles, LastStats.Primitives,
        LastStats.Lines,
        CurvePixelError,
        pstrokeType,
        Zoom,
        //Move.x/20, Move.y/20,
        pAAType,
        optTriangles ? "*Opt" : ""
        );

    if (HudState == Hud_Help)
    {
        G_strcat(HudText, 2048,
            "\n\n"
            "Keys:\n"
            "  CTRL S          Toggle scaled display\n"
            "  CTRL W          Toggle wireframe\n"
            "  CTRL A          Toggle antialiasing mode\n"
            "  CTRL U          Toggle fullscreen\n"
            "  CTRL F          Toggle fast mode (FPS)\n"
            "  CTRL G          Toggle fast forward\n"
            "  CTRL P          Toggle pause\n"
          //"  CTRL N          Next font config\n"
            "  CTRL R          Restart the movie\n"
            "  CTRL D          Toggle stage clipping\n"
            "  CTRL C          Toggle stage culling\n"
            "  CTRL O          Toggle triangle optimization\n"
            "  CTRL Right      Step back one frame\n"
            "  CTRL Left       Step forward one frame\n"
            "  CTRL PageUp     Step back 10 frames\n"
            "  CTRL PageDown   Step forward 10 frames\n"
            "  CTRL -,+        Curve tolerance down, up\n"
            "  F1              Toggle Info Help\n"
            "  F2              Toggle Info Stats\n"
            "  CTRL Q          Quit"
            );
    }

    NeedHudUpdate = 0;
}


// Handle dropped file
void    FxPlayerApp::OnDropFiles(char *path)
{
    ResetCursor();
    ResetUserMatrix();
    LoadMovie(path);
    BringMainWindowOnTop();
}

void FxPlayerApp::OnKey(KeyCode keyCode, unsigned char asciiCode,
                        unsigned int wcharCode, unsigned int mods, bool downFlag)
{
    if (!pMovie)
        return;

//  GFxLog* plog = pMovie->GetLog();
    bool ctrl = mods & FxApp::KM_Control;

    if (keyCode == FxApp::Control)
        return;

    if (keyCode == FxApp::Escape && downFlag)
    {
        // Cancel mouse manipulation
        if (MouseTracking != None)
        {
            MouseTracking = None;
            Zoom = ZoomStart;
            Move = MoveStart;
            UpdateUserMatrix();
            return;
        }
    }


    if (keyCode == FxApp::F1 && downFlag)
        goto toggle_hud;
    if (keyCode == FxApp::F2 && downFlag)
        goto toggle_stats;

    // Handle Ctrl-Key combinations
    if (ctrl && downFlag)
    {

        switch(keyCode)
        {
            case 'Q':
                QuitFlag = 1;
                return;

                // minus
            case 109: // 219 '['
            case 189: // 219 '['
                CurvePixelError = G_Min(10.0f, CurvePixelError + 0.5f);
                pRenderConfig->SetMaxCurvePixelError(CurvePixelError);
                UpdateHudText();
                break;

                // plus
            case 107: // 221 ']':
            case 187: // 221 ']':
                CurvePixelError = G_Max(0.5f, CurvePixelError - 0.5f);
                pRenderConfig->SetMaxCurvePixelError(CurvePixelError);
                UpdateHudText();
                break;

            case 'W':
                // Toggle wireframe.
                Wireframe = !Wireframe;
                break;

                // Switch to a next stroke type.
            case 'T':
                {
                    UInt32  rf      = pRenderConfig->GetRenderFlags();
                    UInt32  stroke  = rf & GFxRenderConfig::RF_StrokeMask;

                    switch(stroke)
                    {
                    case GFxRenderConfig::RF_StrokeHairline:  stroke = GFxRenderConfig::RF_StrokeNormal; break;
                    case GFxRenderConfig::RF_StrokeNormal:    stroke = GFxRenderConfig::RF_StrokeCorrect; break;
                    case GFxRenderConfig::RF_StrokeCorrect:   stroke = GFxRenderConfig::RF_StrokeHairline; break;
                    }
                    pRenderConfig->SetRenderFlags((rf & ~GFxRenderConfig::RF_StrokeMask) | stroke);
                    UpdateHudText();
                }
                break;

            case 'P':
                // Toggle paused state.
                NeedHudUpdate = 1;
                Paused = !Paused;
                // Note that toggling play state through pMovie->SetPlayState would only pause root clip,
                // not children. So instead we just set the global variable above which prevents Advance.
                // However, we may still need to save/restore state in frame.
                if (Paused)
                    PausedState = pMovie->GetPlayState();
                else
                    pMovie->SetPlayState(PausedState);
                break;

            case 'R':
                Paused = 0;
                pMovie->Restart();
                break;

            case FxApp::Left:
                pMovie->GotoFrame(pMovie->GetCurrentFrame()-1);
        onkey_finish_seek:
                Paused = 1;
                NeedHudUpdate = 1;
                pMovie->SetPlayState(GFxMovie::Playing);
                // Ensure tag actions are executed. This may change frame state to Stopped.
                pMovie->Advance(0.0f);
                PausedState = pMovie->GetPlayState();
                break;
            case FxApp::Right:
                pMovie->GotoFrame(pMovie->GetCurrentFrame()+1);
                goto onkey_finish_seek;

            case FxApp::PageUp:
                pMovie->GotoFrame(
                    G_Max<UInt>(0, pMovie->GetCurrentFrame()-10) );
                goto onkey_finish_seek;
            case FxApp::PageDown:
                pMovie->GotoFrame(
                    G_Min<UInt>(pMovie->GetCurrentFrame()+10, MovieInfo.FrameCount-1));
                goto onkey_finish_seek;

            case 'H':
                // Toggle info hud.
            toggle_hud:
                switch(HudState)
                {
                    case Hud_Hidden:  HudState = Hud_Help;     break;
                    case Hud_Stats:   HudState = Hud_Help;     break;
                    case Hud_Help:    HudState = Hud_Hidden;   break;
                }
                NeedHudUpdate = 1;
                break;

            case 'I':
                // Toggle info stats.
            toggle_stats:
                switch(HudState)
                {
                    case Hud_Hidden:  HudState = Hud_Stats;    break;
                    case Hud_Stats:   HudState = Hud_Hidden;   break;
                    case Hud_Help:    HudState = Hud_Stats;    break;
                }
                NeedHudUpdate = 1;
                break;

            case 'A':
                {
                    bool    renderChange = 0;
                    bool    edgeChange   = 0;

                    switch(AAMode)
                    {
                        case AAMode_None:
                            AAMode = AAMode_EdgeAA;
                            edgeChange = 1;
                            break;
                        case AAMode_EdgeAA:
                            AAMode = AAMode_FSAA;
                            edgeChange = renderChange = 1;
                            break;
                        case AAMode_FSAA:
                            AAMode = AAMode_None;
                            renderChange = 1;
                            break;
                    }
                    NeedHudUpdate = 1;

                    // FSAA toggle
                    if (renderChange)
                    {
                        SwitchFSAA(AAMode == AAMode_FSAA);
                    }
                    if (edgeChange && pMovie)
                    {
                        UInt32 rendererFlags = pRenderConfig->GetRenderFlags() & ~GFxRenderConfig::RF_EdgeAA;
                        if (AAMode == AAMode_EdgeAA)
                            rendererFlags |= GFxRenderConfig::RF_EdgeAA;
                        pRenderConfig->SetRenderFlags(rendererFlags);
                    }

                }
                break;

            case 'U':
                pRenderConfig->SetRenderer(0);
                SwitchFullScreenMode();
                pRenderConfig->SetRenderer(GetRenderer());
                SetupRTTexture();
                UpdateViewSize();
                SetWindowTitle(FXPLAYER_APP_TITLE);
                break;

            case 'S':
                // Toggler scale
                ScaleEnable = !ScaleEnable;
                UpdateViewSize();
                break;

            case 'D':
                // Toggler clipping
                ClippingEnable = !ClippingEnable;
                UpdateViewSize();
                break;

            case 'G':
                FastForward = !FastForward;
                break;

            case 'B':
                // toggle background color.
                Background = !Background;
                break;

            case 'F':
                MeasurePerformance = !MeasurePerformance;
                pRenderStats->GetTessStatistics(); // Clear stats
                LastFPS = 0;
                NeedHudUpdate = 1;

                if (!MeasurePerformance)
                    SetWindowTitle(FXPLAYER_APP_TITLE);
                break;

            case 'Z':
                ResetUserMatrix();
                break;

            case 'C':
                // Toggle viewport culling.
                if (pMovie && pRenderConfig)
                {
                    UInt32 rendererFlags = pRenderConfig->GetRenderFlags();
                    pRenderConfig->SetRenderFlags(rendererFlags ^ GFxRenderConfig::RF_NoViewCull);
                }
                break;

            case 'O':
                if (pMovie && pRenderConfig)
                {
                    UInt32 rendererFlags = pRenderConfig->GetRenderFlags();
                    pRenderConfig->SetRenderFlags(rendererFlags ^ GFxRenderConfig::RF_OptimizeTriangles);
                }
                UpdateHudText();
                break;
            default:
            	break;
        } // switch(keyCode)
    } // if (ctrl)

    else
    { // if (!ctrl)

        // Inform the player about keystroke
        if (!ctrl)
            KeyEvent((GFxKey::Code)keyCode, asciiCode, wcharCode, mods, downFlag);
    }
}


// Helper used to convert key codes and route them to GFxPlayer
void FxPlayerApp::KeyEvent(GFxKey::Code keyCode, unsigned char asciiCode,
                           unsigned int wcharCode, unsigned int mods, bool down)
{
    if (keyCode != GFxKey::VoidSymbol)
    {
        if (pMovie)
        {
            GFxKeyEvent event(down ? GFxEvent::KeyDown : GFxKeyEvent::KeyUp, keyCode, asciiCode, wcharCode);
            event.SpecialKeysState.SetShiftPressed(mods & FxApp::KM_Shift ? 1 : 0);
            event.SpecialKeysState.SetCtrlPressed(mods & FxApp::KM_Control ? 1 : 0);
            event.SpecialKeysState.SetAltPressed(mods & FxApp::KM_Alt ? 1 : 0);
            event.SpecialKeysState.SetNumToggled(mods & FxApp::KM_Num ? 1 : 0);
            event.SpecialKeysState.SetCapsToggled(mods & FxApp::KM_Caps ? 1 : 0);
            event.SpecialKeysState.SetScrollToggled(mods & FxApp::KM_Scroll ? 1 : 0);
            pMovie->HandleEvent(event);
        }
    }
}

void    FxPlayerApp::OnMouseButton(unsigned mouseIndex, unsigned int button, bool downFlag,
                                   int x, int y, unsigned int mods)
{
    if (!pMovie)
        return;

    bool ControlKeyDown = mods & FxApp::KM_Control;
    MouseX = x;
    MouseY = y;

    // Adjust x, y to viewport.
    GSizeF  s = GetMovieScaleSize();
    Float   mX = ((x - (Width-ViewWidth)/2)) * s.Width;
    Float   mY = ((y - (Height-ViewHeight)/2)) * s.Height;

    GRenderer::Matrix m;
    m.AppendScaling(Zoom);
    m.AppendTranslation(Move.x,Move.y);
    GRenderer::Point p = m.TransformByInverse(GRenderer::Point(mX, mY));

    x = (int) (p.x / s.Width);
    y = (int) (p.y / s.Height);

    // Update mouse state
    if (downFlag)
    {
        MouseDownX = MouseX;
        MouseDownY = MouseY;

        if (button==0 && ControlKeyDown)
            MouseTracking = Zooming;
        else if (button==1 && ControlKeyDown)
            MouseTracking = Moving;

        if (MouseTracking != None)
        {
            ZoomStart = Zoom;
            MoveStart = Move;
            return;
        }

        GFxMouseEvent event(GFxEvent::MouseDown, button, x, y, 0.0f, mouseIndex);
        pMovie->HandleEvent(event);
    }
    else
    {
        if (MouseTracking != None)
        {
            MouseTracking = None;
            return;
        }

        GFxMouseEvent event(GFxEvent::MouseUp, button, x, y, 0.0f, mouseIndex);
        pMovie->HandleEvent(event);
    }
}

void    FxPlayerApp::OnMouseWheel(unsigned mouseIndex, int zdelta, int x, int y, unsigned int mods)
{
    bool ControlKeyDown = mods & FxApp::KM_Control;

    if (ControlKeyDown)// && MouseTracking == None)
    {
        ZoomStart = Zoom;

        Float dZoom = Zoom;
        Zoom += 0.02f * (zdelta/128) * Zoom;

        if (Zoom < 0.02f)
            Zoom = dZoom;

        dZoom -= Zoom;

        GSizeF  s = GetMovieScaleSize();
        Float   mX = ((x - (Width-ViewWidth)/2)) * s.Width;
        Float   mY = ((y - (Height-ViewHeight)/2)) * s.Height;
        GRenderer::Matrix m;
        m.AppendScaling(ZoomStart);
        m.AppendTranslation(Move.x,Move.y);
        GRenderer::Point p = m.TransformByInverse(GRenderer::Point(mX, mY));
        mX = (Float) (int) (p.x / s.Width);
        mY = (Float) (int) (p.y / s.Height);

        Move.x += s.Width * dZoom * mX;
        Move.y += s.Height * dZoom * mY;

        UpdateUserMatrix();
        return;
    }

    if (!pMovie)
        return;

    GSizeF  s = GetMovieScaleSize();

    // Adjust x, y to viewport.
    Float mX = ((x - (Width-ViewWidth)/2)) * s.Width;
    Float mY = ((y - (Height-ViewHeight)/2)) * s.Height;

    GRenderer::Matrix m;
    m.AppendScaling(Zoom);
    m.AppendTranslation(Move.x,Move.y);
    GRenderer::Point p = m.TransformByInverse(GRenderer::Point(mX, mY));

    x = (int) (p.x / s.Width);
    y = (int) (p.y / s.Height);

    GFxMouseEvent event(GFxEvent::MouseWheel, 0, x, y, (Float)((zdelta/ 1/* XXX WHEEL_DELTA*/)*3), mouseIndex);
    pMovie->HandleEvent(event);
}

void    FxPlayerApp::OnMouseMove(unsigned mouseIndex, int x, int y, unsigned int mods)
{
    Float dX = (Float) MouseX - x;
    Float dY = (Float) MouseY - y;
    MouseX = x;
    MouseY = y;

    // Used by NotifyMouseState in the main loop
    if (!pMovie)
        return;

    GSizeF  s = GetMovieScaleSize();

    if (MouseTracking == Zooming)
    {
        Float dZoom = Zoom;
        Zoom += 0.01f * dY * Zoom;

        if (Zoom < 0.02f)
            Zoom = dZoom;

        dZoom -= Zoom;

        Float mX = ((MouseDownX - (Width-ViewWidth)/2)) * s.Width;
        Float mY = ((MouseDownY - (Height-ViewHeight)/2)) * s.Height;
        GRenderer::Matrix m;
        m.AppendScaling(ZoomStart);
        m.AppendTranslation(MoveStart.x,MoveStart.y);
        GRenderer::Point p = m.TransformByInverse(GRenderer::Point(mX, mY));
        mX = (Float) (int) (p.x / s.Width);
        mY = (Float) (int) (p.y / s.Height);

        Move.x += s.Width * dZoom * mX;
        Move.y += s.Height * dZoom * mY;

        UpdateUserMatrix();
        return;
    }
    if (MouseTracking == Moving)
    {
        Move.x -= s.Width * dX;
        Move.y -= s.Height * dY;

        UpdateUserMatrix();
        return;
    }


    // Adjust x, y to viewport.
    Float mX = ((x - (Width-ViewWidth)/2)) * s.Width;
    Float mY = ((y - (Height-ViewHeight)/2)) * s.Height;

    GRenderer::Matrix m;
    m.AppendScaling(Zoom);
    m.AppendTranslation(Move.x,Move.y);
    GRenderer::Point p = m.TransformByInverse(GRenderer::Point(mX, mY));

    x = (int) (p.x / s.Width);
    y = (int) (p.y / s.Height);

    GFxMouseEvent event(GFxEvent::MouseMove, 0, x, y, 0.0f, mouseIndex);
    pMovie->HandleEvent(event);

    /*
    // Mouse HitTest debugging logic

    Double xmouse = pMovie->GetVariableDouble("_root._xmouse");
    Double ymouse = pMovie->GetVariableDouble("_root._ymouse");

    int hitTest = pMovie->HitTest(x, y, GFxMovieView::HitTest_Shapes);

    pMovie->GetLog()->LogMessage("pMovie->HitTest: %d\n", hitTest);

    x = (SInt)(float(x) * MovieInfo.Width) / ViewWidth;
    y = (SInt)(float(y) * MovieInfo.Height) / ViewHeight;

    const char* pi = pMovie->Invoke("_root.hitTest", "%f%f%d", xmouse, ymouse, 1);
    pMovie->GetLog()->LogMessage("_root.hitTest: %s\n", pi);
    */
}


