//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_StatusEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_StatusEvent.h"
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
    const ThunkInfo StatusEvent_ti[6] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "code", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "code", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "level", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "level", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_events::EventTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_events
{
    StatusEvent::StatusEvent(ClassTraits::Traits& t)
    : Class(t)
    , STATUS("status")
    {
//##protect##"class_::StatusEvent::StatusEvent()"
//##protect##"class_::StatusEvent::StatusEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo StatusEvent::mi[StatusEvent::MemberInfoNum] = {
        {"STATUS", NULL, OFFSETOF(Classes::fl_events::StatusEvent, STATUS), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    StatusEvent::StatusEvent(VM& vm)
    : Traits(vm, AS3::fl_events::StatusEventCI)
    {
//##protect##"ClassTraits::StatusEvent::StatusEvent()"
//##protect##"ClassTraits::StatusEvent::StatusEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::Event(vm, AS3::fl_events::StatusEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::StatusEvent(*this));

    }

    Pickable<Traits> StatusEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) StatusEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo StatusEventTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "StatusEvent", "flash.events", &fl_events::EventTI,
        TypeInfo::None
    };

    const ClassInfo StatusEventCI = {
        &StatusEventTI,
        ClassTraits::fl_events::StatusEvent::MakeClassTraits,
        0,
        ClassTraits::fl_events::StatusEvent::MemberInfoNum,
        6,
        0,
        NULL,
        ClassTraits::fl_events::StatusEvent::mi,
        InstanceTraits::fl_events::StatusEvent_ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

