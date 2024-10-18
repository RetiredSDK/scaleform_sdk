//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_GesturePhase.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_GesturePhase.h"
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
    GesturePhase::GesturePhase(ClassTraits::Traits& t)
    : Class(t)
    , ALL("all")
    , BEGIN("begin")
    , END("end")
    , UPDATE("update")
    {
//##protect##"class_::GesturePhase::GesturePhase()"
//##protect##"class_::GesturePhase::GesturePhase()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo GesturePhase::mi[GesturePhase::MemberInfoNum] = {
        {"ALL", NULL, OFFSETOF(Classes::fl_events::GesturePhase, ALL), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"BEGIN", NULL, OFFSETOF(Classes::fl_events::GesturePhase, BEGIN), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"END", NULL, OFFSETOF(Classes::fl_events::GesturePhase, END), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"UPDATE", NULL, OFFSETOF(Classes::fl_events::GesturePhase, UPDATE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    GesturePhase::GesturePhase(VM& vm)
    : Traits(vm, AS3::fl_events::GesturePhaseCI)
    {
//##protect##"ClassTraits::GesturePhase::GesturePhase()"
//##protect##"ClassTraits::GesturePhase::GesturePhase()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_events::GesturePhaseCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::GesturePhase(*this));

    }

    Pickable<Traits> GesturePhase::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) GesturePhase(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo GesturePhaseTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "GesturePhase", "flash.events", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo GesturePhaseCI = {
        &GesturePhaseTI,
        ClassTraits::fl_events::GesturePhase::MakeClassTraits,
        0,
        ClassTraits::fl_events::GesturePhase::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_events::GesturePhase::mi,
        NULL,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

