//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_DRMStatusEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_DRMStatusEvent.h"
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
    const ThunkInfo DRMStatusEvent_ti[8] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "detail", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "isAnonymous", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "isAvailableOffline", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "offlineLeasePeriod", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::ObjectTI, "policies", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::DateTI, "voucherEndDate", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_events::EventTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_events
{
    DRMStatusEvent::DRMStatusEvent(ClassTraits::Traits& t)
    : Class(t)
    , DRM_STATUS("drmStatus")
    {
//##protect##"class_::DRMStatusEvent::DRMStatusEvent()"
//##protect##"class_::DRMStatusEvent::DRMStatusEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo DRMStatusEvent::mi[DRMStatusEvent::MemberInfoNum] = {
        {"DRM_STATUS", NULL, OFFSETOF(Classes::fl_events::DRMStatusEvent, DRM_STATUS), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    DRMStatusEvent::DRMStatusEvent(VM& vm)
    : Traits(vm, AS3::fl_events::DRMStatusEventCI)
    {
//##protect##"ClassTraits::DRMStatusEvent::DRMStatusEvent()"
//##protect##"ClassTraits::DRMStatusEvent::DRMStatusEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::Event(vm, AS3::fl_events::DRMStatusEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::DRMStatusEvent(*this));

    }

    Pickable<Traits> DRMStatusEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DRMStatusEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo DRMStatusEventTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "DRMStatusEvent", "flash.events", &fl_events::EventTI,
        TypeInfo::None
    };

    const ClassInfo DRMStatusEventCI = {
        &DRMStatusEventTI,
        ClassTraits::fl_events::DRMStatusEvent::MakeClassTraits,
        0,
        ClassTraits::fl_events::DRMStatusEvent::MemberInfoNum,
        8,
        0,
        NULL,
        ClassTraits::fl_events::DRMStatusEvent::mi,
        InstanceTraits::fl_events::DRMStatusEvent_ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

