//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_Microphone.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Media_Microphone.h"
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

namespace InstanceTraits { namespace fl_media
{
    const ThunkInfo Microphone_ti[16] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "activityLevel", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "gain", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "gain", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "index", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "muted", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "name", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "rate", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "rate", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "silenceLevel", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "silenceTimeout", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_media::SoundTransformTI, "soundTransform", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "soundTransform", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "useEchoSuppression", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "setLoopBack", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, NULL, "setSilenceLevel", NULL, Abc::NS_Public, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "setUseEchoSuppression", NULL, Abc::NS_Public, CT_Method, 1, 1},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_media
{
    Microphone::Microphone(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Microphone::Microphone()"
//##protect##"class_::Microphone::Microphone()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_media
{
    const ThunkInfo Microphone_ti[1] = {
        {ThunkInfo::EmptyFunc, &AS3::fl_media::MicrophoneTI, "getMicrophone", NULL, Abc::NS_Public, CT_Method, 0, 1},
    };
    Microphone::Microphone(VM& vm)
    : Traits(vm, AS3::fl_media::MicrophoneCI)
    {
//##protect##"ClassTraits::Microphone::Microphone()"
//##protect##"ClassTraits::Microphone::Microphone()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_media::MicrophoneCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_media::Microphone(*this));

    }

    Pickable<Traits> Microphone::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Microphone(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_media
{
    const TypeInfo MicrophoneTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "Microphone", "flash.media", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo MicrophoneCI = {
        &MicrophoneTI,
        ClassTraits::fl_media::Microphone::MakeClassTraits,
        1,
        0,
        16,
        0,
        ClassTraits::fl_media::Microphone_ti,
        NULL,
        InstanceTraits::fl_media::Microphone_ti,
        NULL,
    };
}; // namespace fl_media


}}} // namespace Scaleform { namespace GFx { namespace AS3

