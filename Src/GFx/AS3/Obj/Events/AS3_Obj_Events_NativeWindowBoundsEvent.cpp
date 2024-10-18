//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_NativeWindowBoundsEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_NativeWindowBoundsEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class Rectangle;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_events
{
    const ThunkInfo NativeWindowBoundsEvent_ti[4] = {
        {ThunkInfo::EmptyFunc, &AS3::fl_geom::RectangleTI, "afterBounds", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_geom::RectangleTI, "beforeBounds", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_events::EventTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_events
{
    NativeWindowBoundsEvent::NativeWindowBoundsEvent(ClassTraits::Traits& t)
    : Class(t)
    , MOVE("move")
    , MOVING("moving")
    , RESIZE("resize")
    , RESIZING("resizing")
    {
//##protect##"class_::NativeWindowBoundsEvent::NativeWindowBoundsEvent()"
//##protect##"class_::NativeWindowBoundsEvent::NativeWindowBoundsEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo NativeWindowBoundsEvent::mi[NativeWindowBoundsEvent::MemberInfoNum] = {
        {"MOVE", NULL, OFFSETOF(Classes::fl_events::NativeWindowBoundsEvent, MOVE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"MOVING", NULL, OFFSETOF(Classes::fl_events::NativeWindowBoundsEvent, MOVING), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"RESIZE", NULL, OFFSETOF(Classes::fl_events::NativeWindowBoundsEvent, RESIZE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"RESIZING", NULL, OFFSETOF(Classes::fl_events::NativeWindowBoundsEvent, RESIZING), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    NativeWindowBoundsEvent::NativeWindowBoundsEvent(VM& vm)
    : Traits(vm, AS3::fl_events::NativeWindowBoundsEventCI)
    {
//##protect##"ClassTraits::NativeWindowBoundsEvent::NativeWindowBoundsEvent()"
//##protect##"ClassTraits::NativeWindowBoundsEvent::NativeWindowBoundsEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::Event(vm, AS3::fl_events::NativeWindowBoundsEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::NativeWindowBoundsEvent(*this));

    }

    Pickable<Traits> NativeWindowBoundsEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeWindowBoundsEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo NativeWindowBoundsEventTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "NativeWindowBoundsEvent", "flash.events", &fl_events::EventTI,
        TypeInfo::None
    };

    const ClassInfo NativeWindowBoundsEventCI = {
        &NativeWindowBoundsEventTI,
        ClassTraits::fl_events::NativeWindowBoundsEvent::MakeClassTraits,
        0,
        ClassTraits::fl_events::NativeWindowBoundsEvent::MemberInfoNum,
        4,
        0,
        NULL,
        ClassTraits::fl_events::NativeWindowBoundsEvent::mi,
        InstanceTraits::fl_events::NativeWindowBoundsEvent_ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

