//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_Capabilities.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_System_Capabilities.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../../../../GFx/IME/GFx_IMEManager.h"
#include "../../AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_system
{
    Capabilities::Capabilities(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Capabilities::Capabilities()"
//##protect##"class_::Capabilities::Capabilities()"
    }
    void Capabilities::avHardwareDisableGet(bool& result)
    {
//##protect##"class_::Capabilities::avHardwareDisableGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::avHardwareDisableGet()");
//##protect##"class_::Capabilities::avHardwareDisableGet()"
    }
    void Capabilities::hasAccessibilityGet(bool& result)
    {
//##protect##"class_::Capabilities::hasAccessibilityGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::hasAccessibilityGet()");
//##protect##"class_::Capabilities::hasAccessibilityGet()"
    }
    void Capabilities::hasAudioGet(bool& result)
    {
//##protect##"class_::Capabilities::hasAudioGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::hasAudioGet()");
//##protect##"class_::Capabilities::hasAudioGet()"
    }
    void Capabilities::hasAudioEncoderGet(bool& result)
    {
//##protect##"class_::Capabilities::hasAudioEncoderGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::hasAudioEncoderGet()");
//##protect##"class_::Capabilities::hasAudioEncoderGet()"
    }
    void Capabilities::hasEmbeddedVideoGet(bool& result)
    {
//##protect##"class_::Capabilities::hasEmbeddedVideoGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::hasEmbeddedVideoGet()");
//##protect##"class_::Capabilities::hasEmbeddedVideoGet()"
    }
    void Capabilities::hasIMEGet(bool& result)
    {
//##protect##"class_::Capabilities::hasIMEGet()"
#ifndef SF_NO_IME_SUPPORT

		ASVM& asvm = static_cast<ASVM&>(GetVM());
		MovieImpl* pmovieImpl = asvm.GetMovieImpl();   

		IMEManagerBase* pimeManager = pmovieImpl->GetIMEManager();
		if(pimeManager != NULL)
		{
			result = true;
			return;
		}
		result = false;
#else
		result = false;
#endif

//##protect##"class_::Capabilities::hasIMEGet()"
    }
    void Capabilities::hasMP3Get(bool& result)
    {
//##protect##"class_::Capabilities::hasMP3Get()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::hasMP3Get()");
//##protect##"class_::Capabilities::hasMP3Get()"
    }
    void Capabilities::hasPrintingGet(bool& result)
    {
//##protect##"class_::Capabilities::hasPrintingGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::hasPrintingGet()");
//##protect##"class_::Capabilities::hasPrintingGet()"
    }
    void Capabilities::hasScreenBroadcastGet(bool& result)
    {
//##protect##"class_::Capabilities::hasScreenBroadcastGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::hasScreenBroadcastGet()");
//##protect##"class_::Capabilities::hasScreenBroadcastGet()"
    }
    void Capabilities::hasScreenPlaybackGet(bool& result)
    {
//##protect##"class_::Capabilities::hasScreenPlaybackGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::hasScreenPlaybackGet()");
//##protect##"class_::Capabilities::hasScreenPlaybackGet()"
    }
    void Capabilities::hasStreamingAudioGet(bool& result)
    {
//##protect##"class_::Capabilities::hasStreamingAudioGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::hasStreamingAudioGet()");
//##protect##"class_::Capabilities::hasStreamingAudioGet()"
    }
    void Capabilities::hasStreamingVideoGet(bool& result)
    {
//##protect##"class_::Capabilities::hasStreamingVideoGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::hasStreamingVideoGet()");
//##protect##"class_::Capabilities::hasStreamingVideoGet()"
    }
    void Capabilities::hasTLSGet(bool& result)
    {
//##protect##"class_::Capabilities::hasTLSGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::hasTLSGet()");
//##protect##"class_::Capabilities::hasTLSGet()"
    }
    void Capabilities::hasVideoEncoderGet(bool& result)
    {
//##protect##"class_::Capabilities::hasVideoEncoderGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::hasVideoEncoderGet()");
//##protect##"class_::Capabilities::hasVideoEncoderGet()"
    }
    void Capabilities::isDebuggerGet(bool& result)
    {
//##protect##"class_::Capabilities::isDebuggerGet()"
        result = false;
//##protect##"class_::Capabilities::isDebuggerGet()"
    }
    void Capabilities::languageGet(ASString& result)
    {
//##protect##"class_::Capabilities::languageGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::languageGet()");
//##protect##"class_::Capabilities::languageGet()"
    }
    void Capabilities::localFileReadDisableGet(bool& result)
    {
//##protect##"class_::Capabilities::localFileReadDisableGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::localFileReadDisableGet()");
//##protect##"class_::Capabilities::localFileReadDisableGet()"
    }
    void Capabilities::manufacturerGet(ASString& result)
    {
//##protect##"class_::Capabilities::manufacturerGet()"
        
        result = "Scaleform ";
        ASString osName = GetStringManager().CreateEmptyString();
        getOSName(osName);
        result += osName;

//##protect##"class_::Capabilities::manufacturerGet()"
    }
    void Capabilities::osGet(ASString& result)
    {
//##protect##"class_::Capabilities::osGet()"
    
        getOSName(result);

//##protect##"class_::Capabilities::osGet()"
    }
    void Capabilities::pixelAspectRatioGet(Value::Number& result)
    {
//##protect##"class_::Capabilities::pixelAspectRatioGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::pixelAspectRatioGet()");
//##protect##"class_::Capabilities::pixelAspectRatioGet()"
    }
    void Capabilities::playerTypeGet(ASString& result)
    {
//##protect##"class_::Capabilities::playerTypeGet()"
        // Specifies the type of runtime environment. This property can have one of the following values:
        //     * "ActiveX" for the Flash Player ActiveX control used by Microsoft Internet Explorer
        //     * "Desktop" for the Adobe AIR runtime (except for SWF content loaded by an HTML page, which has Capabilities.playerType set to "PlugIn")
        //     * "External" for the external Flash Player or in test mode
        //     * "PlugIn" for the Flash Player browser plug-in (and for SWF content loaded by an HTML page in an AIR application)
        //     * "StandAlone" for the stand-alone Flash Player
        //  The server string is PT.
        result = GetStringManager().CreateConstString("StandAlone");
//##protect##"class_::Capabilities::playerTypeGet()"
    }
    void Capabilities::screenColorGet(ASString& result)
    {
//##protect##"class_::Capabilities::screenColorGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::screenColorGet()");
//##protect##"class_::Capabilities::screenColorGet()"
    }
    void Capabilities::screenDPIGet(Value::Number& result)
    {
//##protect##"class_::Capabilities::screenDPIGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::screenDPIGet()");
//##protect##"class_::Capabilities::screenDPIGet()"
    }
    void Capabilities::screenResolutionXGet(Value::Number& result)
    {
//##protect##"class_::Capabilities::screenResolutionXGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::screenResolutionXGet()");
//##protect##"class_::Capabilities::screenResolutionXGet()"
    }
    void Capabilities::screenResolutionYGet(Value::Number& result)
    {
//##protect##"class_::Capabilities::screenResolutionYGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::screenResolutionYGet()");
//##protect##"class_::Capabilities::screenResolutionYGet()"
    }
    void Capabilities::serverStringGet(ASString& result)
    {
//##protect##"class_::Capabilities::serverStringGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::Capabilities::serverStringGet()");
//##protect##"class_::Capabilities::serverStringGet()"
    }
    void Capabilities::versionGet(ASString& result)
    {
//##protect##"class_::Capabilities::versionGet()"
        
        // Specifies the Flash Player or Adobe® AIR® platform and version information. The format of the 
        // version number is: platform majorVersion,minorVersion,buildNumber,internalBuildNumber. Possible 
        // values for platform are "WIN", ` "MAC", "LNX", and "AND". Here are some examples of version 
        // information:
        //      WIN 9,0,0,0  // Flash Player 9 for Windows
        //      MAC 7,0,25,0   // Flash Player 7 for Macintosh
        //      LNX 9,0,115,0  // Flash Player 9 for Linux
        //      AND 10,2,150,0 // Flash Player 10 for Android

        // PPS: We return WIN for platforms not handled by Adobe. This may not be useful for developers..
        //      Perhaps introduce custom versions for platforms that we handle?

#if defined(SF_OS_DARWIN)
        result = "MAC 10,1,0,0";
#elif defined (SF_OS_ANDROID)
        result = "AND 10,1,0,0";
#elif defined(SF_OS_LINUX)
        result = "LNX 10,1,0,0";
#else
        result = "WIN 10,1,0,0";
#endif

//##protect##"class_::Capabilities::versionGet()"
    }
//##protect##"class_$methods"

    void Capabilities::getOSName(ASString& result)
    {
#if defined(SF_OS_WIN32)
        result = "Windows";
#elif defined(SF_OS_LINUX)
        result = "Linux";
#elif defined(SF_OS_DARWIN)
        result = "Mac OS";

#elif defined(SF_OS_ANDROID)
        result = "Android";
#elif defined(SF_OS_IPHONE)
        result = "iPhone";

#elif defined(SF_OS_XBOX360)
        result = "XBox 360";
#elif defined(SF_OS_3DS)
        result = "3DS";
#elif defined(SF_OS_PSVITA)
        result = "PSVITA";
#elif defined(SF_OS_PS3)
        result = "Playstation 3";
#elif defined(SF_OS_WII)
        result = "Wii";
#else
        result = "Other";
#endif
    }

//##protect##"class_$methods"

}} // namespace Classes

typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_avHardwareDisableGet, bool> TFunc_Classes_Capabilities_avHardwareDisableGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_hasAccessibilityGet, bool> TFunc_Classes_Capabilities_hasAccessibilityGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_hasAudioGet, bool> TFunc_Classes_Capabilities_hasAudioGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_hasAudioEncoderGet, bool> TFunc_Classes_Capabilities_hasAudioEncoderGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_hasEmbeddedVideoGet, bool> TFunc_Classes_Capabilities_hasEmbeddedVideoGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_hasIMEGet, bool> TFunc_Classes_Capabilities_hasIMEGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_hasMP3Get, bool> TFunc_Classes_Capabilities_hasMP3Get;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_hasPrintingGet, bool> TFunc_Classes_Capabilities_hasPrintingGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_hasScreenBroadcastGet, bool> TFunc_Classes_Capabilities_hasScreenBroadcastGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_hasScreenPlaybackGet, bool> TFunc_Classes_Capabilities_hasScreenPlaybackGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_hasStreamingAudioGet, bool> TFunc_Classes_Capabilities_hasStreamingAudioGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_hasStreamingVideoGet, bool> TFunc_Classes_Capabilities_hasStreamingVideoGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_hasTLSGet, bool> TFunc_Classes_Capabilities_hasTLSGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_hasVideoEncoderGet, bool> TFunc_Classes_Capabilities_hasVideoEncoderGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_isDebuggerGet, bool> TFunc_Classes_Capabilities_isDebuggerGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_languageGet, ASString> TFunc_Classes_Capabilities_languageGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_localFileReadDisableGet, bool> TFunc_Classes_Capabilities_localFileReadDisableGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_manufacturerGet, ASString> TFunc_Classes_Capabilities_manufacturerGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_osGet, ASString> TFunc_Classes_Capabilities_osGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_pixelAspectRatioGet, Value::Number> TFunc_Classes_Capabilities_pixelAspectRatioGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_playerTypeGet, ASString> TFunc_Classes_Capabilities_playerTypeGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_screenColorGet, ASString> TFunc_Classes_Capabilities_screenColorGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_screenDPIGet, Value::Number> TFunc_Classes_Capabilities_screenDPIGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_screenResolutionXGet, Value::Number> TFunc_Classes_Capabilities_screenResolutionXGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_screenResolutionYGet, Value::Number> TFunc_Classes_Capabilities_screenResolutionYGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_serverStringGet, ASString> TFunc_Classes_Capabilities_serverStringGet;
typedef ThunkFunc0<Classes::fl_system::Capabilities, Classes::fl_system::Capabilities::mid_versionGet, ASString> TFunc_Classes_Capabilities_versionGet;

template <> const TFunc_Classes_Capabilities_avHardwareDisableGet::TMethod TFunc_Classes_Capabilities_avHardwareDisableGet::Method = &Classes::fl_system::Capabilities::avHardwareDisableGet;
template <> const TFunc_Classes_Capabilities_hasAccessibilityGet::TMethod TFunc_Classes_Capabilities_hasAccessibilityGet::Method = &Classes::fl_system::Capabilities::hasAccessibilityGet;
template <> const TFunc_Classes_Capabilities_hasAudioGet::TMethod TFunc_Classes_Capabilities_hasAudioGet::Method = &Classes::fl_system::Capabilities::hasAudioGet;
template <> const TFunc_Classes_Capabilities_hasAudioEncoderGet::TMethod TFunc_Classes_Capabilities_hasAudioEncoderGet::Method = &Classes::fl_system::Capabilities::hasAudioEncoderGet;
template <> const TFunc_Classes_Capabilities_hasEmbeddedVideoGet::TMethod TFunc_Classes_Capabilities_hasEmbeddedVideoGet::Method = &Classes::fl_system::Capabilities::hasEmbeddedVideoGet;
template <> const TFunc_Classes_Capabilities_hasIMEGet::TMethod TFunc_Classes_Capabilities_hasIMEGet::Method = &Classes::fl_system::Capabilities::hasIMEGet;
template <> const TFunc_Classes_Capabilities_hasMP3Get::TMethod TFunc_Classes_Capabilities_hasMP3Get::Method = &Classes::fl_system::Capabilities::hasMP3Get;
template <> const TFunc_Classes_Capabilities_hasPrintingGet::TMethod TFunc_Classes_Capabilities_hasPrintingGet::Method = &Classes::fl_system::Capabilities::hasPrintingGet;
template <> const TFunc_Classes_Capabilities_hasScreenBroadcastGet::TMethod TFunc_Classes_Capabilities_hasScreenBroadcastGet::Method = &Classes::fl_system::Capabilities::hasScreenBroadcastGet;
template <> const TFunc_Classes_Capabilities_hasScreenPlaybackGet::TMethod TFunc_Classes_Capabilities_hasScreenPlaybackGet::Method = &Classes::fl_system::Capabilities::hasScreenPlaybackGet;
template <> const TFunc_Classes_Capabilities_hasStreamingAudioGet::TMethod TFunc_Classes_Capabilities_hasStreamingAudioGet::Method = &Classes::fl_system::Capabilities::hasStreamingAudioGet;
template <> const TFunc_Classes_Capabilities_hasStreamingVideoGet::TMethod TFunc_Classes_Capabilities_hasStreamingVideoGet::Method = &Classes::fl_system::Capabilities::hasStreamingVideoGet;
template <> const TFunc_Classes_Capabilities_hasTLSGet::TMethod TFunc_Classes_Capabilities_hasTLSGet::Method = &Classes::fl_system::Capabilities::hasTLSGet;
template <> const TFunc_Classes_Capabilities_hasVideoEncoderGet::TMethod TFunc_Classes_Capabilities_hasVideoEncoderGet::Method = &Classes::fl_system::Capabilities::hasVideoEncoderGet;
template <> const TFunc_Classes_Capabilities_isDebuggerGet::TMethod TFunc_Classes_Capabilities_isDebuggerGet::Method = &Classes::fl_system::Capabilities::isDebuggerGet;
template <> const TFunc_Classes_Capabilities_languageGet::TMethod TFunc_Classes_Capabilities_languageGet::Method = &Classes::fl_system::Capabilities::languageGet;
template <> const TFunc_Classes_Capabilities_localFileReadDisableGet::TMethod TFunc_Classes_Capabilities_localFileReadDisableGet::Method = &Classes::fl_system::Capabilities::localFileReadDisableGet;
template <> const TFunc_Classes_Capabilities_manufacturerGet::TMethod TFunc_Classes_Capabilities_manufacturerGet::Method = &Classes::fl_system::Capabilities::manufacturerGet;
template <> const TFunc_Classes_Capabilities_osGet::TMethod TFunc_Classes_Capabilities_osGet::Method = &Classes::fl_system::Capabilities::osGet;
template <> const TFunc_Classes_Capabilities_pixelAspectRatioGet::TMethod TFunc_Classes_Capabilities_pixelAspectRatioGet::Method = &Classes::fl_system::Capabilities::pixelAspectRatioGet;
template <> const TFunc_Classes_Capabilities_playerTypeGet::TMethod TFunc_Classes_Capabilities_playerTypeGet::Method = &Classes::fl_system::Capabilities::playerTypeGet;
template <> const TFunc_Classes_Capabilities_screenColorGet::TMethod TFunc_Classes_Capabilities_screenColorGet::Method = &Classes::fl_system::Capabilities::screenColorGet;
template <> const TFunc_Classes_Capabilities_screenDPIGet::TMethod TFunc_Classes_Capabilities_screenDPIGet::Method = &Classes::fl_system::Capabilities::screenDPIGet;
template <> const TFunc_Classes_Capabilities_screenResolutionXGet::TMethod TFunc_Classes_Capabilities_screenResolutionXGet::Method = &Classes::fl_system::Capabilities::screenResolutionXGet;
template <> const TFunc_Classes_Capabilities_screenResolutionYGet::TMethod TFunc_Classes_Capabilities_screenResolutionYGet::Method = &Classes::fl_system::Capabilities::screenResolutionYGet;
template <> const TFunc_Classes_Capabilities_serverStringGet::TMethod TFunc_Classes_Capabilities_serverStringGet::Method = &Classes::fl_system::Capabilities::serverStringGet;
template <> const TFunc_Classes_Capabilities_versionGet::TMethod TFunc_Classes_Capabilities_versionGet::Method = &Classes::fl_system::Capabilities::versionGet;

namespace ClassTraits { namespace fl_system
{
    const ThunkInfo Capabilities::ti[Capabilities::ThunkInfoNum] = {
        {TFunc_Classes_Capabilities_avHardwareDisableGet::Func, &AS3::fl::BooleanTI, "avHardwareDisable", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_hasAccessibilityGet::Func, &AS3::fl::BooleanTI, "hasAccessibility", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_hasAudioGet::Func, &AS3::fl::BooleanTI, "hasAudio", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_hasAudioEncoderGet::Func, &AS3::fl::BooleanTI, "hasAudioEncoder", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_hasEmbeddedVideoGet::Func, &AS3::fl::BooleanTI, "hasEmbeddedVideo", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_hasIMEGet::Func, &AS3::fl::BooleanTI, "hasIME", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_hasMP3Get::Func, &AS3::fl::BooleanTI, "hasMP3", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_hasPrintingGet::Func, &AS3::fl::BooleanTI, "hasPrinting", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_hasScreenBroadcastGet::Func, &AS3::fl::BooleanTI, "hasScreenBroadcast", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_hasScreenPlaybackGet::Func, &AS3::fl::BooleanTI, "hasScreenPlayback", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_hasStreamingAudioGet::Func, &AS3::fl::BooleanTI, "hasStreamingAudio", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_hasStreamingVideoGet::Func, &AS3::fl::BooleanTI, "hasStreamingVideo", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_hasTLSGet::Func, &AS3::fl::BooleanTI, "hasTLS", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_hasVideoEncoderGet::Func, &AS3::fl::BooleanTI, "hasVideoEncoder", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_isDebuggerGet::Func, &AS3::fl::BooleanTI, "isDebugger", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_languageGet::Func, &AS3::fl::StringTI, "language", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_localFileReadDisableGet::Func, &AS3::fl::BooleanTI, "localFileReadDisable", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_manufacturerGet::Func, &AS3::fl::StringTI, "manufacturer", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_osGet::Func, &AS3::fl::StringTI, "os", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_pixelAspectRatioGet::Func, &AS3::fl::NumberTI, "pixelAspectRatio", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_playerTypeGet::Func, &AS3::fl::StringTI, "playerType", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_screenColorGet::Func, &AS3::fl::StringTI, "screenColor", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_screenDPIGet::Func, &AS3::fl::NumberTI, "screenDPI", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_screenResolutionXGet::Func, &AS3::fl::NumberTI, "screenResolutionX", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_screenResolutionYGet::Func, &AS3::fl::NumberTI, "screenResolutionY", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_serverStringGet::Func, &AS3::fl::StringTI, "serverString", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Classes_Capabilities_versionGet::Func, &AS3::fl::StringTI, "version", NULL, Abc::NS_Public, CT_Get, 0, 0},
    };
    Capabilities::Capabilities(VM& vm)
    : Traits(vm, AS3::fl_system::CapabilitiesCI)
    {
//##protect##"ClassTraits::Capabilities::Capabilities()"
//##protect##"ClassTraits::Capabilities::Capabilities()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_system::CapabilitiesCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_system::Capabilities(*this));

    }

    Pickable<Traits> Capabilities::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Capabilities(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_system
{
    const TypeInfo CapabilitiesTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "Capabilities", "flash.system", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo CapabilitiesCI = {
        &CapabilitiesTI,
        ClassTraits::fl_system::Capabilities::MakeClassTraits,
        ClassTraits::fl_system::Capabilities::ThunkInfoNum,
        0,
        0,
        0,
        ClassTraits::fl_system::Capabilities::ti,
        NULL,
        NULL,
        NULL,
    };
}; // namespace fl_system


}}} // namespace Scaleform { namespace GFx { namespace AS3

