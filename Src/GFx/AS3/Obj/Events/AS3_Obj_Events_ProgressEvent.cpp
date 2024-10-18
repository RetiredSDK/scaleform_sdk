//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_ProgressEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_ProgressEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../../AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::fl_events::ProgressEvent, Instances::fl_events::ProgressEvent::mid_bytesLoadedGet, Value::Number> TFunc_Instances_ProgressEvent_bytesLoadedGet;
typedef ThunkFunc1<Instances::fl_events::ProgressEvent, Instances::fl_events::ProgressEvent::mid_bytesLoadedSet, const Value, Value::Number> TFunc_Instances_ProgressEvent_bytesLoadedSet;
typedef ThunkFunc0<Instances::fl_events::ProgressEvent, Instances::fl_events::ProgressEvent::mid_bytesTotalGet, Value::Number> TFunc_Instances_ProgressEvent_bytesTotalGet;
typedef ThunkFunc1<Instances::fl_events::ProgressEvent, Instances::fl_events::ProgressEvent::mid_bytesTotalSet, const Value, Value::Number> TFunc_Instances_ProgressEvent_bytesTotalSet;
typedef ThunkFunc0<Instances::fl_events::ProgressEvent, Instances::fl_events::ProgressEvent::mid_clone, SPtr<Instances::fl_events::Event> > TFunc_Instances_ProgressEvent_clone;
typedef ThunkFunc0<Instances::fl_events::ProgressEvent, Instances::fl_events::ProgressEvent::mid_toString, ASString> TFunc_Instances_ProgressEvent_toString;

template <> const TFunc_Instances_ProgressEvent_bytesLoadedGet::TMethod TFunc_Instances_ProgressEvent_bytesLoadedGet::Method = &Instances::fl_events::ProgressEvent::bytesLoadedGet;
template <> const TFunc_Instances_ProgressEvent_bytesLoadedSet::TMethod TFunc_Instances_ProgressEvent_bytesLoadedSet::Method = &Instances::fl_events::ProgressEvent::bytesLoadedSet;
template <> const TFunc_Instances_ProgressEvent_bytesTotalGet::TMethod TFunc_Instances_ProgressEvent_bytesTotalGet::Method = &Instances::fl_events::ProgressEvent::bytesTotalGet;
template <> const TFunc_Instances_ProgressEvent_bytesTotalSet::TMethod TFunc_Instances_ProgressEvent_bytesTotalSet::Method = &Instances::fl_events::ProgressEvent::bytesTotalSet;
template <> const TFunc_Instances_ProgressEvent_clone::TMethod TFunc_Instances_ProgressEvent_clone::Method = &Instances::fl_events::ProgressEvent::clone;
template <> const TFunc_Instances_ProgressEvent_toString::TMethod TFunc_Instances_ProgressEvent_toString::Method = &Instances::fl_events::ProgressEvent::toString;

namespace Instances { namespace fl_events
{
    ProgressEvent::ProgressEvent(InstanceTraits::Traits& t)
    : Instances::fl_events::Event(t)
//##protect##"instance::ProgressEvent::ProgressEvent()$data"
//##protect##"instance::ProgressEvent::ProgressEvent()$data"
    {
//##protect##"instance::ProgressEvent::ProgressEvent()$code"
        BytesLoaded = BytesTotal = 0;
//##protect##"instance::ProgressEvent::ProgressEvent()$code"
    }

    void ProgressEvent::bytesLoadedGet(Value::Number& result)
    {
//##protect##"instance::ProgressEvent::bytesLoadedGet()"
        SF_UNUSED1(result);
        result = (Value::Number)BytesLoaded;
//##protect##"instance::ProgressEvent::bytesLoadedGet()"
    }
    void ProgressEvent::bytesLoadedSet(const Value& result, Value::Number value)
    {
//##protect##"instance::ProgressEvent::bytesLoadedSet()"
        SF_UNUSED2(result, value);
        BytesLoaded = (UPInt)value;
//##protect##"instance::ProgressEvent::bytesLoadedSet()"
    }
    void ProgressEvent::bytesTotalGet(Value::Number& result)
    {
//##protect##"instance::ProgressEvent::bytesTotalGet()"
        SF_UNUSED1(result);
        result = (Value::Number)BytesTotal;
//##protect##"instance::ProgressEvent::bytesTotalGet()"
    }
    void ProgressEvent::bytesTotalSet(const Value& result, Value::Number value)
    {
//##protect##"instance::ProgressEvent::bytesTotalSet()"
        SF_UNUSED2(result, value);
        BytesTotal = (UPInt)value;
//##protect##"instance::ProgressEvent::bytesTotalSet()"
    }
    void ProgressEvent::clone(SPtr<Instances::fl_events::Event>& result)
    {
//##protect##"instance::ProgressEvent::clone()"
        SF_UNUSED1(result);
        result = Clone().GetPtr();
//##protect##"instance::ProgressEvent::clone()"
    }
    void ProgressEvent::toString(ASString& result)
    {
//##protect##"instance::ProgressEvent::toString()"
        SF_UNUSED1(result);
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("ProgressEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("eventPhase"),
            vm.GetStringManager().CreateConstString("bytesLoaded"),
            vm.GetStringManager().CreateConstString("bytesTotal")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
//##protect##"instance::ProgressEvent::toString()"
    }

    SPtr<Instances::fl_events::Event> ProgressEvent::clone()
    {
        SPtr<Instances::fl_events::Event> result;
        clone(result);
        return result;
    }
//##protect##"instance$methods"
    AS3::Object* ProgressEvent::GetEventClass() const 
    { 
        return static_cast<ASVM&>(GetVM()).ProgressEventClass; 
    }

    SPtr<Instances::fl_events::Event> ProgressEvent::Clone() const
    {
        SPtr<Instances::fl_events::Event> p = Event::Clone();
        ProgressEvent* pe = static_cast<ProgressEvent*>(p.GetPtr());
        pe->BytesLoaded = BytesLoaded;
        pe->BytesTotal  = BytesTotal;
        return p;
    }
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_events
{
    const ThunkInfo ProgressEvent::ti[ProgressEvent::ThunkInfoNum] = {
        {TFunc_Instances_ProgressEvent_bytesLoadedGet::Func, &AS3::fl::NumberTI, "bytesLoaded", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_ProgressEvent_bytesLoadedSet::Func, NULL, "bytesLoaded", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_ProgressEvent_bytesTotalGet::Func, &AS3::fl::NumberTI, "bytesTotal", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_ProgressEvent_bytesTotalSet::Func, NULL, "bytesTotal", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_ProgressEvent_clone::Func, &AS3::fl_events::EventTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ProgressEvent_toString::Func, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

    ProgressEvent::ProgressEvent(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::ProgressEvent::ProgressEvent()"
//##protect##"InstanceTraits::ProgressEvent::ProgressEvent()"
        SetMemSize(sizeof(Instances::fl_events::ProgressEvent));

    }

    void ProgressEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<ProgressEvent&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits

namespace Classes { namespace fl_events
{
    ProgressEvent::ProgressEvent(ClassTraits::Traits& t)
    : Class(t)
    , PROGRESS("progress")
    , SOCKET_DATA("socketData")
    {
//##protect##"class_::ProgressEvent::ProgressEvent()"
//##protect##"class_::ProgressEvent::ProgressEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo ProgressEvent::mi[ProgressEvent::MemberInfoNum] = {
        {"PROGRESS", NULL, OFFSETOF(Classes::fl_events::ProgressEvent, PROGRESS), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"SOCKET_DATA", NULL, OFFSETOF(Classes::fl_events::ProgressEvent, SOCKET_DATA), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    ProgressEvent::ProgressEvent(VM& vm)
    : Traits(vm, AS3::fl_events::ProgressEventCI)
    {
//##protect##"ClassTraits::ProgressEvent::ProgressEvent()"
//##protect##"ClassTraits::ProgressEvent::ProgressEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::ProgressEvent(vm, AS3::fl_events::ProgressEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::ProgressEvent(*this));

    }

    Pickable<Traits> ProgressEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ProgressEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo ProgressEventTI = {
        TypeInfo::CompileTime,
        "ProgressEvent", "flash.events", &fl_events::EventTI,
        TypeInfo::None
    };

    const ClassInfo ProgressEventCI = {
        &ProgressEventTI,
        ClassTraits::fl_events::ProgressEvent::MakeClassTraits,
        0,
        ClassTraits::fl_events::ProgressEvent::MemberInfoNum,
        InstanceTraits::fl_events::ProgressEvent::ThunkInfoNum,
        0,
        NULL,
        ClassTraits::fl_events::ProgressEvent::mi,
        InstanceTraits::fl_events::ProgressEvent::ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

