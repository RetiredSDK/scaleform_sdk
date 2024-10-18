//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_SyncEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_SyncEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
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
    const ThunkInfo SyncEvent_ti[4] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "changeList", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "changeList", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_events::EventTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_events
{
    SyncEvent::SyncEvent(ClassTraits::Traits& t)
    : Class(t)
    , SYNC("sync")
    {
//##protect##"class_::SyncEvent::SyncEvent()"
//##protect##"class_::SyncEvent::SyncEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo SyncEvent::mi[SyncEvent::MemberInfoNum] = {
        {"SYNC", NULL, OFFSETOF(Classes::fl_events::SyncEvent, SYNC), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    SyncEvent::SyncEvent(VM& vm)
    : Traits(vm, AS3::fl_events::SyncEventCI)
    {
//##protect##"ClassTraits::SyncEvent::SyncEvent()"
//##protect##"ClassTraits::SyncEvent::SyncEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::Event(vm, AS3::fl_events::SyncEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::SyncEvent(*this));

    }

    Pickable<Traits> SyncEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SyncEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo SyncEventTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "SyncEvent", "flash.events", &fl_events::EventTI,
        TypeInfo::None
    };

    const ClassInfo SyncEventCI = {
        &SyncEventTI,
        ClassTraits::fl_events::SyncEvent::MakeClassTraits,
        0,
        ClassTraits::fl_events::SyncEvent::MemberInfoNum,
        4,
        0,
        NULL,
        ClassTraits::fl_events::SyncEvent::mi,
        InstanceTraits::fl_events::SyncEvent_ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

