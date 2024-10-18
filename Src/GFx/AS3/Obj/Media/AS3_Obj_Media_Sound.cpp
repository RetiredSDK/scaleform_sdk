//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_Sound.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Media_Sound.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Media_ID3Info.h"
#include "AS3_Obj_Media_SoundChannel.h"
#include "AS3_Obj_Media_SoundLoaderContext.h"
#include "AS3_Obj_Media_SoundTransform.h"
#include "../Net/AS3_Obj_Net_URLRequest.h"
#include "../Events/AS3_Obj_Events_IOErrorEvent.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

    template <>
    SF_INLINE
    Value::Number GetMethodDefArg<Instances::fl_media::Sound, Instances::fl_media::Sound::mid_play, 0, Value::Number>(AS3::StringManager&)
    {
        return 0;
    }

} // namespace Impl
typedef ThunkFunc0<Instances::fl_media::Sound, Instances::fl_media::Sound::mid_bytesLoadedGet, UInt32> TFunc_Instances_Sound_bytesLoadedGet;
typedef ThunkFunc0<Instances::fl_media::Sound, Instances::fl_media::Sound::mid_bytesTotalGet, SInt32> TFunc_Instances_Sound_bytesTotalGet;
typedef ThunkFunc0<Instances::fl_media::Sound, Instances::fl_media::Sound::mid_id3Get, SPtr<Instances::fl_media::ID3Info> > TFunc_Instances_Sound_id3Get;
typedef ThunkFunc0<Instances::fl_media::Sound, Instances::fl_media::Sound::mid_isBufferingGet, bool> TFunc_Instances_Sound_isBufferingGet;
typedef ThunkFunc0<Instances::fl_media::Sound, Instances::fl_media::Sound::mid_lengthGet, Value::Number> TFunc_Instances_Sound_lengthGet;
typedef ThunkFunc0<Instances::fl_media::Sound, Instances::fl_media::Sound::mid_urlGet, ASString> TFunc_Instances_Sound_urlGet;
typedef ThunkFunc0<Instances::fl_media::Sound, Instances::fl_media::Sound::mid_close, const Value> TFunc_Instances_Sound_close;
typedef ThunkFunc2<Instances::fl_media::Sound, Instances::fl_media::Sound::mid_load, const Value, Instances::fl_net::URLRequest*, Instances::fl_media::SoundLoaderContext*> TFunc_Instances_Sound_load;
typedef ThunkFunc3<Instances::fl_media::Sound, Instances::fl_media::Sound::mid_play, Value, Value::Number, SInt32, Instances::fl_media::SoundTransform*> TFunc_Instances_Sound_play;

template <> const TFunc_Instances_Sound_bytesLoadedGet::TMethod TFunc_Instances_Sound_bytesLoadedGet::Method = &Instances::fl_media::Sound::bytesLoadedGet;
template <> const TFunc_Instances_Sound_bytesTotalGet::TMethod TFunc_Instances_Sound_bytesTotalGet::Method = &Instances::fl_media::Sound::bytesTotalGet;
template <> const TFunc_Instances_Sound_id3Get::TMethod TFunc_Instances_Sound_id3Get::Method = &Instances::fl_media::Sound::id3Get;
template <> const TFunc_Instances_Sound_isBufferingGet::TMethod TFunc_Instances_Sound_isBufferingGet::Method = &Instances::fl_media::Sound::isBufferingGet;
template <> const TFunc_Instances_Sound_lengthGet::TMethod TFunc_Instances_Sound_lengthGet::Method = &Instances::fl_media::Sound::lengthGet;
template <> const TFunc_Instances_Sound_urlGet::TMethod TFunc_Instances_Sound_urlGet::Method = &Instances::fl_media::Sound::urlGet;
template <> const TFunc_Instances_Sound_close::TMethod TFunc_Instances_Sound_close::Method = &Instances::fl_media::Sound::close;
template <> const TFunc_Instances_Sound_load::TMethod TFunc_Instances_Sound_load::Method = &Instances::fl_media::Sound::load;
template <> const TFunc_Instances_Sound_play::TMethod TFunc_Instances_Sound_play::Method = &Instances::fl_media::Sound::play;

namespace Instances { namespace fl_media
{
    Sound::Sound(InstanceTraits::Traits& t)
    : Instances::fl_events::EventDispatcher(t)
//##protect##"instance::Sound::Sound()$data"
//##protect##"instance::Sound::Sound()$data"
    {
//##protect##"instance::Sound::Sound()$code"
#ifdef GFX_ENABLE_SOUND
        Streaming = false;
		pMovieDef = NULL;
#endif
//##protect##"instance::Sound::Sound()$code"
    }

    void Sound::bytesLoadedGet(UInt32& result)
    {
//##protect##"instance::Sound::bytesLoadedGet()"
#ifdef GFX_ENABLE_SOUND
        result = 0;
        if (pSoundObject)
            result = pSoundObject->GetBytesLoaded();
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::bytesLoadedGet()");
#endif
//##protect##"instance::Sound::bytesLoadedGet()"
    }
    void Sound::bytesTotalGet(SInt32& result)
    {
//##protect##"instance::Sound::bytesTotalGet()"
#ifdef GFX_ENABLE_SOUND
        result = 0;
        if (pSoundObject)
            result = pSoundObject->GetBytesTotal();
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::bytesTotalGet()");
#endif
//##protect##"instance::Sound::bytesTotalGet()"
    }
    void Sound::id3Get(SPtr<Instances::fl_media::ID3Info>& result)
    {
//##protect##"instance::Sound::id3Get()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::id3Get()");
//##protect##"instance::Sound::id3Get()"
    }
    void Sound::isBufferingGet(bool& result)
    {
//##protect##"instance::Sound::isBufferingGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::isBufferingGet()");
//##protect##"instance::Sound::isBufferingGet()"
    }
    void Sound::lengthGet(Value::Number& result)
    {
//##protect##"instance::Sound::lengthGet()"
#ifdef GFX_ENABLE_SOUND
        float length = 0.0f;
        if (pSoundObject)
            length = pSoundObject->GetDuration();
        result = length;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::lengthGet()");
#endif
//##protect##"instance::Sound::lengthGet()"
    }
    void Sound::urlGet(ASString& result)
    {
//##protect##"instance::Sound::urlGet()"
#ifdef GFX_ENABLE_SOUND
        result = SoundURL;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::urlGet()");
#endif
//##protect##"instance::Sound::urlGet()"
    }
    void Sound::close(const Value& result)
    {
//##protect##"instance::Sound::close()"
#ifdef GFX_ENABLE_SOUND
        SF_UNUSED(result);
        if (pSoundObject)
        {
            pSoundObject->Stop();
            pSoundObject = NULL;
        }
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::close()");
#endif
//##protect##"instance::Sound::close()"
    }
    void Sound::load(const Value& result, Instances::fl_net::URLRequest* stream, Instances::fl_media::SoundLoaderContext* context)
    {
//##protect##"instance::Sound::load()"
#ifdef GFX_ENABLE_SOUND
        SF_UNUSED(result);
        if (pSoundObject)
        {
            if (stream)
                SoundURL = stream->GetUrl().ToCStr();
            if (context)
                Streaming = context->bufferTime > 0 ? true : false;
            pSoundObject->LoadFile(SoundURL, Streaming);
        }
#else
        SF_UNUSED3(result, stream, context);
        WARN_NOT_IMPLEMENTED("Sound::load()");
#endif
//##protect##"instance::Sound::load()"
    }
    void Sound::play(Value& result, Value::Number startTime, SInt32 loops, Instances::fl_media::SoundTransform* sndTransform)
    {
//##protect##"instance::Sound::play()"
#ifdef GFX_ENABLE_SOUND
        Value v, r;
        if (!GetVM().ConstructBuiltinValue(v, "flash.media.SoundChannel"))
            return;
        SPtr<Instances::fl_media::SoundChannel> pchan = static_cast<Instances::fl_media::SoundChannel*>(v.GetObject());
        pchan->pSoundObject = pSoundObject;
        pChannel = pchan;

        if (pSoundObject)
            pSoundObject->Play((SInt32)startTime, loops);

        if (sndTransform)
            pchan->soundTransformSet(r, sndTransform);

        result = pchan;
#else
        SF_UNUSED4(result, startTime, loops, sndTransform);
        WARN_NOT_IMPLEMENTED("Sound::play()");
#endif
//##protect##"instance::Sound::play()"
    }

    SPtr<Instances::fl_media::ID3Info> Sound::id3Get()
    {
        SPtr<Instances::fl_media::ID3Info> result;
        id3Get(result);
        return result;
    }
//##protect##"instance$methods"
#ifdef GFX_ENABLE_SOUND
    void Sound::AS3Constructor(unsigned argc, const Value* argv)
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        pSoundObject = *SF_HEAP_NEW(asvm.GetMovieImpl()->GetHeap()) SoundObject(asvm, this);
        SF_ASSERT(pSoundObject);

        if (pSoundResource)
            pSoundObject->AttachResource(pSoundResource);

        if (argc >= 1 && asvm.IsOfType(argv[0], "flash.net.URLRequest", asvm.GetCurrentAppDomain()))
        {
            Instances::fl_net::URLRequest* req = static_cast<Instances::fl_net::URLRequest*>(argv[0].GetObject());
            Instances::fl_media::SoundLoaderContext* cntx = NULL;
            if (argc >= 2 && asvm.IsOfType(argv[1], "flash.media.SoundLoaderContext", asvm.GetCurrentAppDomain()))
                cntx = static_cast<Instances::fl_media::SoundLoaderContext*>(argv[0].GetObject());
            Value r;
            load(r, req, cntx);
        }
    }

    void Sound::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        EventDispatcher::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<Instances::fl_media::SoundChannel, Mem_Stat>(prcc, pChannel, op SF_DEBUG_ARG(*this));
    }

    void Sound::InitInstance(bool extCall)
    {
        if (!extCall)
            CreateLibraryObject();
    }

    bool Sound::CreateLibraryObject()
    {
        if (!pSoundResource)
        {
            ASVM& asvm = static_cast<ASVM&>(GetVM());
            pMovieDef = asvm.GetResourceMovieDef(this);

            if (pMovieDef && GetTraits().IsUserDefined())
            {
                ASString className = GetInstanceTraits().GetQualifiedName(Traits::qnfWithDot);
                ResourceBindData resBindData;
                if (!asvm.GetMovieImpl()->FindExportedResource(pMovieDef, &resBindData, className.ToCStr()))
                    return false;

                if (resBindData.pResource)
                {
                    if (resBindData.pResource->GetResourceType() & Resource::RT_SoundSample)
                        pSoundResource = static_cast<SoundResource*>(resBindData.pResource.GetPtr());
                }
                return true;
            }
        }
        return false;
    }

    void Sound::DispatchEventOpen()
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        SPtr<fl_events::Event> eventObj = CreateEventObject(asvm.GetBuiltin(AS3Builtin_open));
        eventObj->Target = this;
        DispatchSingleEvent(eventObj, false);
    }
    void Sound::DispatchEventComplete()
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        SPtr<fl_events::Event> eventObj = CreateEventObject(asvm.GetBuiltin(AS3Builtin_complete));
        eventObj->Target = this;
        DispatchSingleEvent(eventObj, false);
    }
    void Sound::DispatchEventSoundComplete()
    {
        if (pChannel)
            pChannel->DispatchEventSoundComplete();
    }
    void Sound::DispatchEventIOError()
    {
        SPtr<fl_events::IOErrorEvent> eventObj = CreateIOErrorEventObject("soundIOError");
        eventObj->Target = this;
        DispatchSingleEvent(eventObj, false);
    }
#endif
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_media
{
    const ThunkInfo Sound::ti[Sound::ThunkInfoNum] = {
        {TFunc_Instances_Sound_bytesLoadedGet::Func, &AS3::fl::uintTI, "bytesLoaded", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Sound_bytesTotalGet::Func, &AS3::fl::int_TI, "bytesTotal", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Sound_id3Get::Func, &AS3::fl_media::ID3InfoTI, "id3", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Sound_isBufferingGet::Func, &AS3::fl::BooleanTI, "isBuffering", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Sound_lengthGet::Func, &AS3::fl::NumberTI, "length", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Sound_urlGet::Func, &AS3::fl::StringTI, "url", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Sound_close::Func, NULL, "close", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Sound_load::Func, NULL, "load", NULL, Abc::NS_Public, CT_Method, 1, 2},
        {TFunc_Instances_Sound_play::Func, NULL, "play", NULL, Abc::NS_Public, CT_Method, 0, 3},
    };

    Sound::Sound(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::Sound::Sound()"
//##protect##"InstanceTraits::Sound::Sound()"
        SetMemSize(sizeof(Instances::fl_media::Sound));

    }

    void Sound::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<Sound&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_media
{
    Sound::Sound(VM& vm)
    : Traits(vm, AS3::fl_media::SoundCI)
    {
//##protect##"ClassTraits::Sound::Sound()"
//##protect##"ClassTraits::Sound::Sound()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_media::Sound(vm, AS3::fl_media::SoundCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> Sound::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Sound(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_media
{
    const TypeInfo SoundTI = {
        TypeInfo::CompileTime,
        "Sound", "flash.media", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo SoundCI = {
        &SoundTI,
        ClassTraits::fl_media::Sound::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_media::Sound::ThunkInfoNum,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_media::Sound::ti,
        NULL,
    };
}; // namespace fl_media


}}} // namespace Scaleform { namespace GFx { namespace AS3

