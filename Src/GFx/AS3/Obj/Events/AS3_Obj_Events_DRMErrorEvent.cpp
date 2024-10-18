//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_DRMErrorEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_DRMErrorEvent.h"
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
    const ThunkInfo DRMErrorEvent_ti[3] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "subErrorID", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_events::EventTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_events
{
    DRMErrorEvent::DRMErrorEvent(ClassTraits::Traits& t)
    : Class(t)
    , DRM_ERROR("drmError")
    {
//##protect##"class_::DRMErrorEvent::DRMErrorEvent()"
//##protect##"class_::DRMErrorEvent::DRMErrorEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo DRMErrorEvent::mi[DRMErrorEvent::MemberInfoNum] = {
        {"DRM_ERROR", NULL, OFFSETOF(Classes::fl_events::DRMErrorEvent, DRM_ERROR), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    DRMErrorEvent::DRMErrorEvent(VM& vm)
    : Traits(vm, AS3::fl_events::DRMErrorEventCI)
    {
//##protect##"ClassTraits::DRMErrorEvent::DRMErrorEvent()"
//##protect##"ClassTraits::DRMErrorEvent::DRMErrorEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::ErrorEvent(vm, AS3::fl_events::DRMErrorEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::DRMErrorEvent(*this));

    }

    Pickable<Traits> DRMErrorEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DRMErrorEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo DRMErrorEventTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "DRMErrorEvent", "flash.events", &fl_events::ErrorEventTI,
        TypeInfo::None
    };

    const ClassInfo DRMErrorEventCI = {
        &DRMErrorEventTI,
        ClassTraits::fl_events::DRMErrorEvent::MakeClassTraits,
        0,
        ClassTraits::fl_events::DRMErrorEvent::MemberInfoNum,
        3,
        0,
        NULL,
        ClassTraits::fl_events::DRMErrorEvent::mi,
        InstanceTraits::fl_events::DRMErrorEvent_ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

