//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Sampler_Sample.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Sampler_Sample.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace Instances { namespace fl_sampler
{
    Sample::Sample(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
    , stack()
    , time()
//##protect##"instance::Sample::Sample()$data"
//##protect##"instance::Sample::Sample()$data"
    {
//##protect##"instance::Sample::Sample()$code"
//##protect##"instance::Sample::Sample()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_sampler
{
    const MemberInfo Sample::mi[Sample::MemberInfoNum] = {
        {"stack", NULL, OFFSETOF(Instances::fl_sampler::Sample, stack), Abc::NS_Public, SlotInfo::BT_ObjectCpp, 1},
        {"time", NULL, OFFSETOF(Instances::fl_sampler::Sample, time), Abc::NS_Public, SlotInfo::BT_Number, 1},
    };


    Sample::Sample(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::Sample::Sample()"
//##protect##"InstanceTraits::Sample::Sample()"
        SetMemSize(sizeof(Instances::fl_sampler::Sample));

    }

    void Sample::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<Sample&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_sampler
{
    Sample::Sample(VM& vm)
    : Traits(vm, AS3::fl_sampler::SampleCI)
    {
//##protect##"ClassTraits::Sample::Sample()"
//##protect##"ClassTraits::Sample::Sample()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_sampler::Sample(vm, AS3::fl_sampler::SampleCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> Sample::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Sample(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_sampler
{
    const TypeInfo SampleTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "Sample", "flash.sampler", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo SampleCI = {
        &SampleTI,
        ClassTraits::fl_sampler::Sample::MakeClassTraits,
        0,
        0,
        0,
        InstanceTraits::fl_sampler::Sample::MemberInfoNum,
        NULL,
        NULL,
        NULL,
        InstanceTraits::fl_sampler::Sample::mi,
    };
}; // namespace fl_sampler


}}} // namespace Scaleform { namespace GFx { namespace AS3

