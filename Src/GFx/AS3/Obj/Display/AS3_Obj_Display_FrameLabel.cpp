//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_FrameLabel.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_FrameLabel.h"
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
typedef ThunkFunc0<Instances::fl_display::FrameLabel, Instances::fl_display::FrameLabel::mid_frameGet, SInt32> TFunc_Instances_FrameLabel_frameGet;
typedef ThunkFunc0<Instances::fl_display::FrameLabel, Instances::fl_display::FrameLabel::mid_nameGet, ASString> TFunc_Instances_FrameLabel_nameGet;

template <> const TFunc_Instances_FrameLabel_frameGet::TMethod TFunc_Instances_FrameLabel_frameGet::Method = &Instances::fl_display::FrameLabel::frameGet;
template <> const TFunc_Instances_FrameLabel_nameGet::TMethod TFunc_Instances_FrameLabel_nameGet::Method = &Instances::fl_display::FrameLabel::nameGet;

namespace Instances { namespace fl_display
{
    FrameLabel::FrameLabel(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
//##protect##"instance::FrameLabel::FrameLabel()$data"
    , FrameNumber(~0u)
    , FrameName(GetVM().GetStringManager().CreateEmptyString())
//##protect##"instance::FrameLabel::FrameLabel()$data"
    {
//##protect##"instance::FrameLabel::FrameLabel()$code"
//##protect##"instance::FrameLabel::FrameLabel()$code"
    }

    void FrameLabel::frameGet(SInt32& result)
    {
//##protect##"instance::FrameLabel::frameGet()"
        SF_UNUSED1(result);
        result = (SInt32)FrameNumber;
//##protect##"instance::FrameLabel::frameGet()"
    }
    void FrameLabel::nameGet(ASString& result)
    {
//##protect##"instance::FrameLabel::nameGet()"
        SF_UNUSED1(result);
        result = FrameName;
//##protect##"instance::FrameLabel::nameGet()"
    }

//##protect##"instance$methods"
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_display
{
    const ThunkInfo FrameLabel::ti[FrameLabel::ThunkInfoNum] = {
        {TFunc_Instances_FrameLabel_frameGet::Func, &AS3::fl::int_TI, "frame", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_FrameLabel_nameGet::Func, &AS3::fl::StringTI, "name", NULL, Abc::NS_Public, CT_Get, 0, 0},
    };

    FrameLabel::FrameLabel(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::FrameLabel::FrameLabel()"
//##protect##"InstanceTraits::FrameLabel::FrameLabel()"
        SetMemSize(sizeof(Instances::fl_display::FrameLabel));

    }

    void FrameLabel::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<FrameLabel&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_display
{
    FrameLabel::FrameLabel(VM& vm)
    : Traits(vm, AS3::fl_display::FrameLabelCI)
    {
//##protect##"ClassTraits::FrameLabel::FrameLabel()"
//##protect##"ClassTraits::FrameLabel::FrameLabel()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_display::FrameLabel(vm, AS3::fl_display::FrameLabelCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> FrameLabel::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FrameLabel(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_display
{
    const TypeInfo FrameLabelTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "FrameLabel", "flash.display", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo FrameLabelCI = {
        &FrameLabelTI,
        ClassTraits::fl_display::FrameLabel::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_display::FrameLabel::ThunkInfoNum,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_display::FrameLabel::ti,
        NULL,
    };
}; // namespace fl_display


}}} // namespace Scaleform { namespace GFx { namespace AS3

