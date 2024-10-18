//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_ActivityEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_ActivityEvent.h"
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

namespace InstanceTraits { namespace fl_events
{
    const ThunkInfo ActivityEvent_ti[4] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "activating", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "activating", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_events::EventTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_events
{
    ActivityEvent::ActivityEvent(ClassTraits::Traits& t)
    : Class(t)
    , ACTIVITY("activity")
    {
//##protect##"class_::ActivityEvent::ActivityEvent()"
//##protect##"class_::ActivityEvent::ActivityEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo ActivityEvent::mi[ActivityEvent::MemberInfoNum] = {
        {"ACTIVITY", NULL, OFFSETOF(Classes::fl_events::ActivityEvent, ACTIVITY), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    ActivityEvent::ActivityEvent(VM& vm)
    : Traits(vm, AS3::fl_events::ActivityEventCI)
    {
//##protect##"ClassTraits::ActivityEvent::ActivityEvent()"
//##protect##"ClassTraits::ActivityEvent::ActivityEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::Event(vm, AS3::fl_events::ActivityEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::ActivityEvent(*this));

    }

    Pickable<Traits> ActivityEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ActivityEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo ActivityEventTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "ActivityEvent", "flash.events", &fl_events::EventTI,
        TypeInfo::None
    };

    const ClassInfo ActivityEventCI = {
        &ActivityEventTI,
        ClassTraits::fl_events::ActivityEvent::MakeClassTraits,
        0,
        ClassTraits::fl_events::ActivityEvent::MemberInfoNum,
        4,
        0,
        NULL,
        ClassTraits::fl_events::ActivityEvent::mi,
        InstanceTraits::fl_events::ActivityEvent_ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

