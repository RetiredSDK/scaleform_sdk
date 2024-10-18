//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_FullScreenEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_FullScreenEvent.h"
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
    const ThunkInfo FullScreenEvent_ti[3] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "fullScreen", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_events::EventTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_events
{
    FullScreenEvent::FullScreenEvent(ClassTraits::Traits& t)
    : Class(t)
    , FULL_SCREEN("fullScreen")
    {
//##protect##"class_::FullScreenEvent::FullScreenEvent()"
//##protect##"class_::FullScreenEvent::FullScreenEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo FullScreenEvent::mi[FullScreenEvent::MemberInfoNum] = {
        {"FULL_SCREEN", NULL, OFFSETOF(Classes::fl_events::FullScreenEvent, FULL_SCREEN), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    FullScreenEvent::FullScreenEvent(VM& vm)
    : Traits(vm, AS3::fl_events::FullScreenEventCI)
    {
//##protect##"ClassTraits::FullScreenEvent::FullScreenEvent()"
//##protect##"ClassTraits::FullScreenEvent::FullScreenEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::Event(vm, AS3::fl_events::FullScreenEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::FullScreenEvent(*this));

    }

    Pickable<Traits> FullScreenEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FullScreenEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo FullScreenEventTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "FullScreenEvent", "flash.events", &fl_events::ActivityEventTI,
        TypeInfo::None
    };

    const ClassInfo FullScreenEventCI = {
        &FullScreenEventTI,
        ClassTraits::fl_events::FullScreenEvent::MakeClassTraits,
        0,
        ClassTraits::fl_events::FullScreenEvent::MemberInfoNum,
        3,
        0,
        NULL,
        ClassTraits::fl_events::FullScreenEvent::mi,
        InstanceTraits::fl_events::FullScreenEvent_ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

