//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_EventPhase.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_EventPhase.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_events
{
    EventPhase::EventPhase(ClassTraits::Traits& t)
    : Class(t)
    , AT_TARGET(2)
    , BUBBLING_PHASE(3)
    , CAPTURING_PHASE(1)
    {
//##protect##"class_::EventPhase::EventPhase()"
//##protect##"class_::EventPhase::EventPhase()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo EventPhase::mi[EventPhase::MemberInfoNum] = {
        {"AT_TARGET", NULL, OFFSETOF(Classes::fl_events::EventPhase, AT_TARGET), Abc::NS_Public, SlotInfo::BT_UInt, 1},
        {"BUBBLING_PHASE", NULL, OFFSETOF(Classes::fl_events::EventPhase, BUBBLING_PHASE), Abc::NS_Public, SlotInfo::BT_UInt, 1},
        {"CAPTURING_PHASE", NULL, OFFSETOF(Classes::fl_events::EventPhase, CAPTURING_PHASE), Abc::NS_Public, SlotInfo::BT_UInt, 1},
    };

    EventPhase::EventPhase(VM& vm)
    : Traits(vm, AS3::fl_events::EventPhaseCI)
    {
//##protect##"ClassTraits::EventPhase::EventPhase()"
//##protect##"ClassTraits::EventPhase::EventPhase()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_events::EventPhaseCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::EventPhase(*this));

    }

    Pickable<Traits> EventPhase::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) EventPhase(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo EventPhaseTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "EventPhase", "flash.events", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo EventPhaseCI = {
        &EventPhaseTI,
        ClassTraits::fl_events::EventPhase::MakeClassTraits,
        0,
        ClassTraits::fl_events::EventPhase::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_events::EventPhase::mi,
        NULL,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

