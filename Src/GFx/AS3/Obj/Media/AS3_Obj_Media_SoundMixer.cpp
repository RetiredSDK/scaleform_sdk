//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_SoundMixer.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Media_SoundMixer.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Utils/AS3_Obj_Utils_ByteArray.h"
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
    const ThunkInfo SoundMixer_ti[2] = {
        {ThunkInfo::EmptyFunc, NULL, "bufferTime", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "soundTransform", NULL, Abc::NS_Public, CT_Set, 1, 1},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_media
{
    SoundMixer::SoundMixer(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::SoundMixer::SoundMixer()"
//##protect##"class_::SoundMixer::SoundMixer()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_media
{
    const ThunkInfo SoundMixer_ti[3] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "areSoundsInaccessible", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "computeSpectrum", NULL, Abc::NS_Public, CT_Method, 1, 3},
        {ThunkInfo::EmptyFunc, NULL, "stopAll", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };
    SoundMixer::SoundMixer(VM& vm)
    : Traits(vm, AS3::fl_media::SoundMixerCI)
    {
//##protect##"ClassTraits::SoundMixer::SoundMixer()"
//##protect##"ClassTraits::SoundMixer::SoundMixer()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_media::SoundMixerCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_media::SoundMixer(*this));

    }

    Pickable<Traits> SoundMixer::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SoundMixer(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_media
{
    const TypeInfo SoundMixerTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "SoundMixer", "flash.media", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo SoundMixerCI = {
        &SoundMixerTI,
        ClassTraits::fl_media::SoundMixer::MakeClassTraits,
        3,
        0,
        2,
        0,
        ClassTraits::fl_media::SoundMixer_ti,
        NULL,
        InstanceTraits::fl_media::SoundMixer_ti,
        NULL,
    };
}; // namespace fl_media


}}} // namespace Scaleform { namespace GFx { namespace AS3

