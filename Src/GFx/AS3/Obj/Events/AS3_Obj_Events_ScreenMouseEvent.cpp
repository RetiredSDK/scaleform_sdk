//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_ScreenMouseEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_ScreenMouseEvent.h"
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
    const ThunkInfo ScreenMouseEvent_ti[4] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "screenX", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "screenY", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_events::EventTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_events
{
    ScreenMouseEvent::ScreenMouseEvent(VM& vm)
    : Traits(vm, AS3::fl_events::ScreenMouseEventCI)
    {
//##protect##"ClassTraits::ScreenMouseEvent::ScreenMouseEvent()"
//##protect##"ClassTraits::ScreenMouseEvent::ScreenMouseEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::MouseEvent(vm, AS3::fl_events::ScreenMouseEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> ScreenMouseEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ScreenMouseEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo ScreenMouseEventTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "ScreenMouseEvent", "flash.events", &fl_events::MouseEventTI,
        TypeInfo::None
    };

    const ClassInfo ScreenMouseEventCI = {
        &ScreenMouseEventTI,
        ClassTraits::fl_events::ScreenMouseEvent::MakeClassTraits,
        0,
        0,
        4,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_events::ScreenMouseEvent_ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

