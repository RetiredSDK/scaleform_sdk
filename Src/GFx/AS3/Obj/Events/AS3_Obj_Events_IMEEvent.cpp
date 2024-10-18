//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_IMEEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_IMEEvent.h"
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
typedef ThunkFunc0<Instances::fl_events::IMEEvent, Instances::fl_events::IMEEvent::mid_clone, SPtr<Instances::fl_events::Event> > TFunc_Instances_IMEEvent_clone;
typedef ThunkFunc0<Instances::fl_events::IMEEvent, Instances::fl_events::IMEEvent::mid_toString, ASString> TFunc_Instances_IMEEvent_toString;

template <> const TFunc_Instances_IMEEvent_clone::TMethod TFunc_Instances_IMEEvent_clone::Method = &Instances::fl_events::IMEEvent::clone;
template <> const TFunc_Instances_IMEEvent_toString::TMethod TFunc_Instances_IMEEvent_toString::Method = &Instances::fl_events::IMEEvent::toString;

namespace Instances { namespace fl_events
{
    IMEEvent::IMEEvent(InstanceTraits::Traits& t)
    : Instances::fl_events::TextEvent(t)
//##protect##"instance::IMEEvent::IMEEvent()$data"
//##protect##"instance::IMEEvent::IMEEvent()$data"
    {
//##protect##"instance::IMEEvent::IMEEvent()$code"
//##protect##"instance::IMEEvent::IMEEvent()$code"
    }

    void IMEEvent::clone(SPtr<Instances::fl_events::Event>& result)
    {
//##protect##"instance::IMEEvent::clone()"
        SF_UNUSED1(result);
        // Interface methods have empty implementations.
//##protect##"instance::IMEEvent::clone()"
    }
    void IMEEvent::toString(ASString& result)
    {
//##protect##"instance::IMEEvent::toString()"
        SF_UNUSED1(result);
        // Interface methods have empty implementations.
//##protect##"instance::IMEEvent::toString()"
    }

    SPtr<Instances::fl_events::Event> IMEEvent::clone()
    {
        SPtr<Instances::fl_events::Event> result;
        clone(result);
        return result;
    }
//##protect##"instance$methods"
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_events
{
    const ThunkInfo IMEEvent::ti[IMEEvent::ThunkInfoNum] = {
        {TFunc_Instances_IMEEvent_clone::Func, &AS3::fl_events::EventTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_IMEEvent_toString::Func, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

    IMEEvent::IMEEvent(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::IMEEvent::IMEEvent()"
//##protect##"InstanceTraits::IMEEvent::IMEEvent()"
        SetMemSize(sizeof(Instances::fl_events::IMEEvent));

    }

    void IMEEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<IMEEvent&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits

namespace Classes { namespace fl_events
{
    IMEEvent::IMEEvent(ClassTraits::Traits& t)
    : Class(t)
    , IME_COMPOSITION("imeComposition")
    {
//##protect##"class_::IMEEvent::IMEEvent()"
//##protect##"class_::IMEEvent::IMEEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo IMEEvent::mi[IMEEvent::MemberInfoNum] = {
        {"IME_COMPOSITION", NULL, OFFSETOF(Classes::fl_events::IMEEvent, IME_COMPOSITION), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    IMEEvent::IMEEvent(VM& vm)
    : Traits(vm, AS3::fl_events::IMEEventCI)
    {
//##protect##"ClassTraits::IMEEvent::IMEEvent()"
//##protect##"ClassTraits::IMEEvent::IMEEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::IMEEvent(vm, AS3::fl_events::IMEEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::IMEEvent(*this));

    }

    Pickable<Traits> IMEEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IMEEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo IMEEventTI = {
        TypeInfo::CompileTime,
        "IMEEvent", "flash.events", &fl_events::TextEventTI,
        TypeInfo::None
    };

    const ClassInfo IMEEventCI = {
        &IMEEventTI,
        ClassTraits::fl_events::IMEEvent::MakeClassTraits,
        0,
        ClassTraits::fl_events::IMEEvent::MemberInfoNum,
        InstanceTraits::fl_events::IMEEvent::ThunkInfoNum,
        0,
        NULL,
        ClassTraits::fl_events::IMEEvent::mi,
        InstanceTraits::fl_events::IMEEvent::ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

