//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_TextEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_TextEvent.h"
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
typedef ThunkFunc0<Instances::fl_events::TextEvent, Instances::fl_events::TextEvent::mid_textGet, ASString> TFunc_Instances_TextEvent_textGet;
typedef ThunkFunc1<Instances::fl_events::TextEvent, Instances::fl_events::TextEvent::mid_textSet, const Value, const ASString&> TFunc_Instances_TextEvent_textSet;
typedef ThunkFunc0<Instances::fl_events::TextEvent, Instances::fl_events::TextEvent::mid_clone, SPtr<Instances::fl_events::Event> > TFunc_Instances_TextEvent_clone;
typedef ThunkFunc0<Instances::fl_events::TextEvent, Instances::fl_events::TextEvent::mid_toString, ASString> TFunc_Instances_TextEvent_toString;

template <> const TFunc_Instances_TextEvent_textGet::TMethod TFunc_Instances_TextEvent_textGet::Method = &Instances::fl_events::TextEvent::textGet;
template <> const TFunc_Instances_TextEvent_textSet::TMethod TFunc_Instances_TextEvent_textSet::Method = &Instances::fl_events::TextEvent::textSet;
template <> const TFunc_Instances_TextEvent_clone::TMethod TFunc_Instances_TextEvent_clone::Method = &Instances::fl_events::TextEvent::clone;
template <> const TFunc_Instances_TextEvent_toString::TMethod TFunc_Instances_TextEvent_toString::Method = &Instances::fl_events::TextEvent::toString;

namespace Instances { namespace fl_events
{
    TextEvent::TextEvent(InstanceTraits::Traits& t)
    : Instances::fl_events::Event(t)
//##protect##"instance::TextEvent::TextEvent()$data"
    , Text(GetVM().GetStringManager().CreateEmptyString())
//##protect##"instance::TextEvent::TextEvent()$data"
    {
//##protect##"instance::TextEvent::TextEvent()$code"
//##protect##"instance::TextEvent::TextEvent()$code"
    }

    void TextEvent::textGet(ASString& result)
    {
//##protect##"instance::TextEvent::textGet()"
        SF_UNUSED1(result);
        result = Text;
//##protect##"instance::TextEvent::textGet()"
    }
    void TextEvent::textSet(const Value& result, const ASString& value)
    {
//##protect##"instance::TextEvent::textSet()"
        SF_UNUSED2(result, value);
        Text = value;
//##protect##"instance::TextEvent::textSet()"
    }
    void TextEvent::clone(SPtr<Instances::fl_events::Event>& result)
    {
//##protect##"instance::TextEvent::clone()"
        SF_UNUSED1(result);
        result = Clone().GetPtr();
//##protect##"instance::TextEvent::clone()"
    }
    void TextEvent::toString(ASString& result)
    {
//##protect##"instance::TextEvent::toString()"
        SF_UNUSED1(result);
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("TextEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("eventPhase"),
            vm.GetStringManager().CreateConstString("text")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
//##protect##"instance::TextEvent::toString()"
    }

    SPtr<Instances::fl_events::Event> TextEvent::clone()
    {
        SPtr<Instances::fl_events::Event> result;
        clone(result);
        return result;
    }
//##protect##"instance$methods"
    AS3::Object* TextEvent::GetEventClass() const 
    { 
        return static_cast<ASVM&>(GetVM()).TextEventClass; 
    }

    SPtr<Instances::fl_events::Event> TextEvent::Clone() const
    {
        SPtr<Instances::fl_events::Event> p = Event::Clone();
        TextEvent* pe = static_cast<TextEvent*>(p.GetPtr());
        pe->Text = Text;
        return p;
    }
    void TextEvent::SetText(wchar_t ch)
    {
        Text = GetVM().GetStringManager().CreateString(&ch, 1);
    }
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_events
{
    const ThunkInfo TextEvent::ti[TextEvent::ThunkInfoNum] = {
        {TFunc_Instances_TextEvent_textGet::Func, &AS3::fl::StringTI, "text", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TextEvent_textSet::Func, NULL, "text", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TextEvent_clone::Func, &AS3::fl_events::EventTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_TextEvent_toString::Func, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

    TextEvent::TextEvent(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::TextEvent::TextEvent()"
//##protect##"InstanceTraits::TextEvent::TextEvent()"
        SetMemSize(sizeof(Instances::fl_events::TextEvent));

    }

    void TextEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<TextEvent&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits

namespace Classes { namespace fl_events
{
    TextEvent::TextEvent(ClassTraits::Traits& t)
    : Class(t)
    , LINK("link")
    , TEXT_INPUT("textInput")
    {
//##protect##"class_::TextEvent::TextEvent()"
//##protect##"class_::TextEvent::TextEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo TextEvent::mi[TextEvent::MemberInfoNum] = {
        {"LINK", NULL, OFFSETOF(Classes::fl_events::TextEvent, LINK), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"TEXT_INPUT", NULL, OFFSETOF(Classes::fl_events::TextEvent, TEXT_INPUT), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    TextEvent::TextEvent(VM& vm)
    : Traits(vm, AS3::fl_events::TextEventCI)
    {
//##protect##"ClassTraits::TextEvent::TextEvent()"
//##protect##"ClassTraits::TextEvent::TextEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::TextEvent(vm, AS3::fl_events::TextEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::TextEvent(*this));

    }

    Pickable<Traits> TextEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo TextEventTI = {
        TypeInfo::CompileTime,
        "TextEvent", "flash.events", &fl_events::EventTI,
        TypeInfo::None
    };

    const ClassInfo TextEventCI = {
        &TextEventTI,
        ClassTraits::fl_events::TextEvent::MakeClassTraits,
        0,
        ClassTraits::fl_events::TextEvent::MemberInfoNum,
        InstanceTraits::fl_events::TextEvent::ThunkInfoNum,
        0,
        NULL,
        ClassTraits::fl_events::TextEvent::mi,
        InstanceTraits::fl_events::TextEvent::ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

