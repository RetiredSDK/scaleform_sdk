//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_SoundChannel.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Media_SoundChannel.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Media_SoundTransform.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::fl_media::SoundChannel, Instances::fl_media::SoundChannel::mid_leftPeakGet, Value::Number> TFunc_Instances_SoundChannel_leftPeakGet;
typedef ThunkFunc0<Instances::fl_media::SoundChannel, Instances::fl_media::SoundChannel::mid_positionGet, Value::Number> TFunc_Instances_SoundChannel_positionGet;
typedef ThunkFunc0<Instances::fl_media::SoundChannel, Instances::fl_media::SoundChannel::mid_rightPeakGet, Value::Number> TFunc_Instances_SoundChannel_rightPeakGet;
typedef ThunkFunc0<Instances::fl_media::SoundChannel, Instances::fl_media::SoundChannel::mid_soundTransformGet, SPtr<Instances::fl_media::SoundTransform> > TFunc_Instances_SoundChannel_soundTransformGet;
typedef ThunkFunc1<Instances::fl_media::SoundChannel, Instances::fl_media::SoundChannel::mid_soundTransformSet, const Value, Instances::fl_media::SoundTransform*> TFunc_Instances_SoundChannel_soundTransformSet;
typedef ThunkFunc0<Instances::fl_media::SoundChannel, Instances::fl_media::SoundChannel::mid_stop, const Value> TFunc_Instances_SoundChannel_stop;

template <> const TFunc_Instances_SoundChannel_leftPeakGet::TMethod TFunc_Instances_SoundChannel_leftPeakGet::Method = &Instances::fl_media::SoundChannel::leftPeakGet;
template <> const TFunc_Instances_SoundChannel_positionGet::TMethod TFunc_Instances_SoundChannel_positionGet::Method = &Instances::fl_media::SoundChannel::positionGet;
template <> const TFunc_Instances_SoundChannel_rightPeakGet::TMethod TFunc_Instances_SoundChannel_rightPeakGet::Method = &Instances::fl_media::SoundChannel::rightPeakGet;
template <> const TFunc_Instances_SoundChannel_soundTransformGet::TMethod TFunc_Instances_SoundChannel_soundTransformGet::Method = &Instances::fl_media::SoundChannel::soundTransformGet;
template <> const TFunc_Instances_SoundChannel_soundTransformSet::TMethod TFunc_Instances_SoundChannel_soundTransformSet::Method = &Instances::fl_media::SoundChannel::soundTransformSet;
template <> const TFunc_Instances_SoundChannel_stop::TMethod TFunc_Instances_SoundChannel_stop::Method = &Instances::fl_media::SoundChannel::stop;

namespace Instances { namespace fl_media
{
    SoundChannel::SoundChannel(InstanceTraits::Traits& t)
    : Instances::fl_events::EventDispatcher(t)
//##protect##"instance::SoundChannel::SoundChannel()$data"
//##protect##"instance::SoundChannel::SoundChannel()$data"
    {
//##protect##"instance::SoundChannel::SoundChannel()$code"
//##protect##"instance::SoundChannel::SoundChannel()$code"
    }

    void SoundChannel::leftPeakGet(Value::Number& result)
    {
//##protect##"instance::SoundChannel::leftPeakGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundChannel::leftPeakGet()");
//##protect##"instance::SoundChannel::leftPeakGet()"
    }
    void SoundChannel::positionGet(Value::Number& result)
    {
//##protect##"instance::SoundChannel::positionGet()"
#ifdef GFX_ENABLE_SOUND
        float position = 0.0f;
        if (pSoundObject)
            position = pSoundObject->GetPosition();
        result = position;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundChannel::positionGet()");
#endif
//##protect##"instance::SoundChannel::positionGet()"
    }
    void SoundChannel::rightPeakGet(Value::Number& result)
    {
//##protect##"instance::SoundChannel::rightPeakGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundChannel::rightPeakGet()");
//##protect##"instance::SoundChannel::rightPeakGet()"
    }
    void SoundChannel::soundTransformGet(SPtr<Instances::fl_media::SoundTransform>& result)
    {
//##protect##"instance::SoundChannel::soundTransformGet()"
#ifdef GFX_ENABLE_SOUND
        Value v;
        if (!GetVM().ConstructBuiltinValue(v, "flash.media.SoundTransform"))
            return;
        SPtr<Instances::fl_media::SoundTransform> trans = static_cast<Instances::fl_media::SoundTransform*>(v.GetObject());
        if (pSoundObject)
        {
            Value r;
            trans->volumeSet(r, pSoundObject->GetVolume() / 100);
            trans->panSet(r, pSoundObject->GetPan() / 100);
        }
        result = trans;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundChannel::soundTransformGet()");
#endif
//##protect##"instance::SoundChannel::soundTransformGet()"
    }
    void SoundChannel::soundTransformSet(const Value& result, Instances::fl_media::SoundTransform* value)
    {
//##protect##"instance::SoundChannel::soundTransformSet()"
#ifdef GFX_ENABLE_SOUND
        SF_UNUSED(result);
        if (pSoundObject)
        {
            int volume = (SInt32)(value->Volume * 100);
            pSoundObject->SetVolume(volume);
            int pan = (SInt32)(value->Pan * 100);
            pSoundObject->SetPan(pan);
        }
#else
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("SoundChannel::soundTransformSet()");
#endif
//##protect##"instance::SoundChannel::soundTransformSet()"
    }
    void SoundChannel::stop(const Value& result)
    {
//##protect##"instance::SoundChannel::stop()"
#ifdef GFX_ENABLE_SOUND
        SF_UNUSED(result);
        if (pSoundObject)
            pSoundObject->Stop();
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundChannel::stop()");
#endif
//##protect##"instance::SoundChannel::stop()"
    }

    SPtr<Instances::fl_media::SoundTransform> SoundChannel::soundTransformGet()
    {
        SPtr<Instances::fl_media::SoundTransform> result;
        soundTransformGet(result);
        return result;
    }
//##protect##"instance$methods"
#ifdef GFX_ENABLE_SOUND
    void SoundChannel::DispatchEventSoundComplete()
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        ASString eventType = asvm.GetStringManager().CreateConstString("soundComplete");
        SPtr<fl_events::Event> eventObj = CreateEventObject(eventType);
        eventObj->Target = this;
        DispatchSingleEvent(eventObj, false);
    }
#endif
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_media
{
    const ThunkInfo SoundChannel::ti[SoundChannel::ThunkInfoNum] = {
        {TFunc_Instances_SoundChannel_leftPeakGet::Func, &AS3::fl::NumberTI, "leftPeak", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_SoundChannel_positionGet::Func, &AS3::fl::NumberTI, "position", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_SoundChannel_rightPeakGet::Func, &AS3::fl::NumberTI, "rightPeak", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_SoundChannel_soundTransformGet::Func, &AS3::fl_media::SoundTransformTI, "soundTransform", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_SoundChannel_soundTransformSet::Func, NULL, "soundTransform", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_SoundChannel_stop::Func, NULL, "stop", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

    SoundChannel::SoundChannel(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::SoundChannel::SoundChannel()"
//##protect##"InstanceTraits::SoundChannel::SoundChannel()"
        SetMemSize(sizeof(Instances::fl_media::SoundChannel));

    }

    void SoundChannel::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<SoundChannel&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_media
{
    SoundChannel::SoundChannel(VM& vm)
    : Traits(vm, AS3::fl_media::SoundChannelCI)
    {
//##protect##"ClassTraits::SoundChannel::SoundChannel()"
//##protect##"ClassTraits::SoundChannel::SoundChannel()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_media::SoundChannel(vm, AS3::fl_media::SoundChannelCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> SoundChannel::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SoundChannel(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_media
{
    const TypeInfo SoundChannelTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "SoundChannel", "flash.media", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo SoundChannelCI = {
        &SoundChannelTI,
        ClassTraits::fl_media::SoundChannel::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_media::SoundChannel::ThunkInfoNum,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_media::SoundChannel::ti,
        NULL,
    };
}; // namespace fl_media


}}} // namespace Scaleform { namespace GFx { namespace AS3

