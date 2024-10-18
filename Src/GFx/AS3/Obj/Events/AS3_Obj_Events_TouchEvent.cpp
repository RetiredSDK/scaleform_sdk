//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_TouchEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_TouchEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Display/AS3_Obj_Display_InteractiveObject.h"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_altKeyGet, bool> TFunc_Instances_TouchEvent_altKeyGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_altKeySet, const Value, bool> TFunc_Instances_TouchEvent_altKeySet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_commandKeyGet, bool> TFunc_Instances_TouchEvent_commandKeyGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_commandKeySet, const Value, bool> TFunc_Instances_TouchEvent_commandKeySet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_controlKeyGet, bool> TFunc_Instances_TouchEvent_controlKeyGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_controlKeySet, const Value, bool> TFunc_Instances_TouchEvent_controlKeySet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_ctrlKeyGet, bool> TFunc_Instances_TouchEvent_ctrlKeyGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_ctrlKeySet, const Value, bool> TFunc_Instances_TouchEvent_ctrlKeySet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_isPrimaryTouchPointGet, bool> TFunc_Instances_TouchEvent_isPrimaryTouchPointGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_isPrimaryTouchPointSet, const Value, bool> TFunc_Instances_TouchEvent_isPrimaryTouchPointSet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_isRelatedObjectInaccessibleGet, bool> TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_isRelatedObjectInaccessibleSet, const Value, bool> TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleSet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_localXGet, Value::Number> TFunc_Instances_TouchEvent_localXGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_localXSet, const Value, Value::Number> TFunc_Instances_TouchEvent_localXSet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_localYGet, Value::Number> TFunc_Instances_TouchEvent_localYGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_localYSet, const Value, Value::Number> TFunc_Instances_TouchEvent_localYSet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_pressureGet, Value::Number> TFunc_Instances_TouchEvent_pressureGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_pressureSet, const Value, Value::Number> TFunc_Instances_TouchEvent_pressureSet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_relatedObjectGet, SPtr<Instances::fl_display::InteractiveObject> > TFunc_Instances_TouchEvent_relatedObjectGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_relatedObjectSet, const Value, Instances::fl_display::InteractiveObject*> TFunc_Instances_TouchEvent_relatedObjectSet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_shiftKeyGet, bool> TFunc_Instances_TouchEvent_shiftKeyGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_shiftKeySet, const Value, bool> TFunc_Instances_TouchEvent_shiftKeySet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_sizeXGet, Value::Number> TFunc_Instances_TouchEvent_sizeXGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_sizeXSet, const Value, Value::Number> TFunc_Instances_TouchEvent_sizeXSet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_sizeYGet, Value::Number> TFunc_Instances_TouchEvent_sizeYGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_sizeYSet, const Value, Value::Number> TFunc_Instances_TouchEvent_sizeYSet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_stageXGet, Value::Number> TFunc_Instances_TouchEvent_stageXGet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_stageYGet, Value::Number> TFunc_Instances_TouchEvent_stageYGet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_touchPointIDGet, SInt32> TFunc_Instances_TouchEvent_touchPointIDGet;
typedef ThunkFunc1<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_touchPointIDSet, const Value, SInt32> TFunc_Instances_TouchEvent_touchPointIDSet;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_clone, SPtr<Instances::fl_events::Event> > TFunc_Instances_TouchEvent_clone;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_toString, ASString> TFunc_Instances_TouchEvent_toString;
typedef ThunkFunc0<Instances::fl_events::TouchEvent, Instances::fl_events::TouchEvent::mid_updateAfterEvent, const Value> TFunc_Instances_TouchEvent_updateAfterEvent;

template <> const TFunc_Instances_TouchEvent_altKeyGet::TMethod TFunc_Instances_TouchEvent_altKeyGet::Method = &Instances::fl_events::TouchEvent::altKeyGet;
template <> const TFunc_Instances_TouchEvent_altKeySet::TMethod TFunc_Instances_TouchEvent_altKeySet::Method = &Instances::fl_events::TouchEvent::altKeySet;
template <> const TFunc_Instances_TouchEvent_commandKeyGet::TMethod TFunc_Instances_TouchEvent_commandKeyGet::Method = &Instances::fl_events::TouchEvent::commandKeyGet;
template <> const TFunc_Instances_TouchEvent_commandKeySet::TMethod TFunc_Instances_TouchEvent_commandKeySet::Method = &Instances::fl_events::TouchEvent::commandKeySet;
template <> const TFunc_Instances_TouchEvent_controlKeyGet::TMethod TFunc_Instances_TouchEvent_controlKeyGet::Method = &Instances::fl_events::TouchEvent::controlKeyGet;
template <> const TFunc_Instances_TouchEvent_controlKeySet::TMethod TFunc_Instances_TouchEvent_controlKeySet::Method = &Instances::fl_events::TouchEvent::controlKeySet;
template <> const TFunc_Instances_TouchEvent_ctrlKeyGet::TMethod TFunc_Instances_TouchEvent_ctrlKeyGet::Method = &Instances::fl_events::TouchEvent::ctrlKeyGet;
template <> const TFunc_Instances_TouchEvent_ctrlKeySet::TMethod TFunc_Instances_TouchEvent_ctrlKeySet::Method = &Instances::fl_events::TouchEvent::ctrlKeySet;
template <> const TFunc_Instances_TouchEvent_isPrimaryTouchPointGet::TMethod TFunc_Instances_TouchEvent_isPrimaryTouchPointGet::Method = &Instances::fl_events::TouchEvent::isPrimaryTouchPointGet;
template <> const TFunc_Instances_TouchEvent_isPrimaryTouchPointSet::TMethod TFunc_Instances_TouchEvent_isPrimaryTouchPointSet::Method = &Instances::fl_events::TouchEvent::isPrimaryTouchPointSet;
template <> const TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleGet::TMethod TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleGet::Method = &Instances::fl_events::TouchEvent::isRelatedObjectInaccessibleGet;
template <> const TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleSet::TMethod TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleSet::Method = &Instances::fl_events::TouchEvent::isRelatedObjectInaccessibleSet;
template <> const TFunc_Instances_TouchEvent_localXGet::TMethod TFunc_Instances_TouchEvent_localXGet::Method = &Instances::fl_events::TouchEvent::localXGet;
template <> const TFunc_Instances_TouchEvent_localXSet::TMethod TFunc_Instances_TouchEvent_localXSet::Method = &Instances::fl_events::TouchEvent::localXSet;
template <> const TFunc_Instances_TouchEvent_localYGet::TMethod TFunc_Instances_TouchEvent_localYGet::Method = &Instances::fl_events::TouchEvent::localYGet;
template <> const TFunc_Instances_TouchEvent_localYSet::TMethod TFunc_Instances_TouchEvent_localYSet::Method = &Instances::fl_events::TouchEvent::localYSet;
template <> const TFunc_Instances_TouchEvent_pressureGet::TMethod TFunc_Instances_TouchEvent_pressureGet::Method = &Instances::fl_events::TouchEvent::pressureGet;
template <> const TFunc_Instances_TouchEvent_pressureSet::TMethod TFunc_Instances_TouchEvent_pressureSet::Method = &Instances::fl_events::TouchEvent::pressureSet;
template <> const TFunc_Instances_TouchEvent_relatedObjectGet::TMethod TFunc_Instances_TouchEvent_relatedObjectGet::Method = &Instances::fl_events::TouchEvent::relatedObjectGet;
template <> const TFunc_Instances_TouchEvent_relatedObjectSet::TMethod TFunc_Instances_TouchEvent_relatedObjectSet::Method = &Instances::fl_events::TouchEvent::relatedObjectSet;
template <> const TFunc_Instances_TouchEvent_shiftKeyGet::TMethod TFunc_Instances_TouchEvent_shiftKeyGet::Method = &Instances::fl_events::TouchEvent::shiftKeyGet;
template <> const TFunc_Instances_TouchEvent_shiftKeySet::TMethod TFunc_Instances_TouchEvent_shiftKeySet::Method = &Instances::fl_events::TouchEvent::shiftKeySet;
template <> const TFunc_Instances_TouchEvent_sizeXGet::TMethod TFunc_Instances_TouchEvent_sizeXGet::Method = &Instances::fl_events::TouchEvent::sizeXGet;
template <> const TFunc_Instances_TouchEvent_sizeXSet::TMethod TFunc_Instances_TouchEvent_sizeXSet::Method = &Instances::fl_events::TouchEvent::sizeXSet;
template <> const TFunc_Instances_TouchEvent_sizeYGet::TMethod TFunc_Instances_TouchEvent_sizeYGet::Method = &Instances::fl_events::TouchEvent::sizeYGet;
template <> const TFunc_Instances_TouchEvent_sizeYSet::TMethod TFunc_Instances_TouchEvent_sizeYSet::Method = &Instances::fl_events::TouchEvent::sizeYSet;
template <> const TFunc_Instances_TouchEvent_stageXGet::TMethod TFunc_Instances_TouchEvent_stageXGet::Method = &Instances::fl_events::TouchEvent::stageXGet;
template <> const TFunc_Instances_TouchEvent_stageYGet::TMethod TFunc_Instances_TouchEvent_stageYGet::Method = &Instances::fl_events::TouchEvent::stageYGet;
template <> const TFunc_Instances_TouchEvent_touchPointIDGet::TMethod TFunc_Instances_TouchEvent_touchPointIDGet::Method = &Instances::fl_events::TouchEvent::touchPointIDGet;
template <> const TFunc_Instances_TouchEvent_touchPointIDSet::TMethod TFunc_Instances_TouchEvent_touchPointIDSet::Method = &Instances::fl_events::TouchEvent::touchPointIDSet;
template <> const TFunc_Instances_TouchEvent_clone::TMethod TFunc_Instances_TouchEvent_clone::Method = &Instances::fl_events::TouchEvent::clone;
template <> const TFunc_Instances_TouchEvent_toString::TMethod TFunc_Instances_TouchEvent_toString::Method = &Instances::fl_events::TouchEvent::toString;
template <> const TFunc_Instances_TouchEvent_updateAfterEvent::TMethod TFunc_Instances_TouchEvent_updateAfterEvent::Method = &Instances::fl_events::TouchEvent::updateAfterEvent;

namespace Instances { namespace fl_events
{
    TouchEvent::TouchEvent(InstanceTraits::Traits& t)
    : Instances::fl_events::Event(t)
//##protect##"instance::TouchEvent::TouchEvent()$data"
//##protect##"instance::TouchEvent::TouchEvent()$data"
    {
//##protect##"instance::TouchEvent::TouchEvent()$code"
        AltKey = CtrlKey    = ShiftKey = CommandKey = ControlKey = false;
        SizeX = SizeY       = 0;
        LocalX = LocalY     = 0;
        StageX = StageY     = 0;
        Pressure            = 1.0;
        TouchPointID        = 0;
        PrimaryPoint        = false;
        LocalInitialized    = false;
//##protect##"instance::TouchEvent::TouchEvent()$code"
    }

    void TouchEvent::altKeyGet(bool& result)
    {
//##protect##"instance::TouchEvent::altKeyGet()"
        SF_UNUSED1(result);
        result = AltKey;
//##protect##"instance::TouchEvent::altKeyGet()"
    }
    void TouchEvent::altKeySet(const Value& result, bool value)
    {
//##protect##"instance::TouchEvent::altKeySet()"
        SF_UNUSED2(result, value);
        AltKey = value;
//##protect##"instance::TouchEvent::altKeySet()"
    }
    void TouchEvent::commandKeyGet(bool& result)
    {
//##protect##"instance::TouchEvent::commandKeyGet()"
        SF_UNUSED1(result);
        result = CommandKey;
//##protect##"instance::TouchEvent::commandKeyGet()"
    }
    void TouchEvent::commandKeySet(const Value& result, bool value)
    {
//##protect##"instance::TouchEvent::commandKeySet()"
        SF_UNUSED2(result, value);
        CommandKey = value;
//##protect##"instance::TouchEvent::commandKeySet()"
    }
    void TouchEvent::controlKeyGet(bool& result)
    {
//##protect##"instance::TouchEvent::controlKeyGet()"
        SF_UNUSED1(result);
        result = ControlKey;
//##protect##"instance::TouchEvent::controlKeyGet()"
    }
    void TouchEvent::controlKeySet(const Value& result, bool value)
    {
//##protect##"instance::TouchEvent::controlKeySet()"
        SF_UNUSED2(result, value);
        ControlKey = value;
//##protect##"instance::TouchEvent::controlKeySet()"
    }
    void TouchEvent::ctrlKeyGet(bool& result)
    {
//##protect##"instance::TouchEvent::ctrlKeyGet()"
        SF_UNUSED1(result);
        result = CtrlKey;
//##protect##"instance::TouchEvent::ctrlKeyGet()"
    }
    void TouchEvent::ctrlKeySet(const Value& result, bool value)
    {
//##protect##"instance::TouchEvent::ctrlKeySet()"
        SF_UNUSED2(result, value);
        CtrlKey = value;
//##protect##"instance::TouchEvent::ctrlKeySet()"
    }
    void TouchEvent::isPrimaryTouchPointGet(bool& result)
    {
//##protect##"instance::TouchEvent::isPrimaryTouchPointGet()"
        SF_UNUSED1(result);
        result = PrimaryPoint;
//##protect##"instance::TouchEvent::isPrimaryTouchPointGet()"
    }
    void TouchEvent::isPrimaryTouchPointSet(const Value& result, bool value)
    {
//##protect##"instance::TouchEvent::isPrimaryTouchPointSet()"
        SF_UNUSED2(result, value);
        PrimaryPoint = value;
//##protect##"instance::TouchEvent::isPrimaryTouchPointSet()"
    }
    void TouchEvent::isRelatedObjectInaccessibleGet(bool& result)
    {
//##protect##"instance::TouchEvent::isRelatedObjectInaccessibleGet()"
        SF_UNUSED1(result);
        result = false;
//##protect##"instance::TouchEvent::isRelatedObjectInaccessibleGet()"
    }
    void TouchEvent::isRelatedObjectInaccessibleSet(const Value& result, bool value)
    {
//##protect##"instance::TouchEvent::isRelatedObjectInaccessibleSet()"
        SF_UNUSED2(result, value);
        //WARN_NOT_IMPLEMENTED("instance::TouchEvent::isRelatedObjectInaccessibleSet()");
//##protect##"instance::TouchEvent::isRelatedObjectInaccessibleSet()"
    }
    void TouchEvent::localXGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::localXGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(LocalX);
//##protect##"instance::TouchEvent::localXGet()"
    }
    void TouchEvent::localXSet(const Value& result, Value::Number value)
    {
//##protect##"instance::TouchEvent::localXSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        LocalX = PixelsToTwips(value);
//##protect##"instance::TouchEvent::localXSet()"
    }
    void TouchEvent::localYGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::localYGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(LocalY);
//##protect##"instance::TouchEvent::localYGet()"
    }
    void TouchEvent::localYSet(const Value& result, Value::Number value)
    {
//##protect##"instance::TouchEvent::localYSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        LocalY = PixelsToTwips(value);
//##protect##"instance::TouchEvent::localYSet()"
    }
    void TouchEvent::pressureGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::pressureGet()"
        SF_UNUSED1(result);
        result = Pressure;
//##protect##"instance::TouchEvent::pressureGet()"
    }
    void TouchEvent::pressureSet(const Value& result, Value::Number value)
    {
//##protect##"instance::TouchEvent::pressureSet()"
        SF_UNUSED2(result, value);
        Pressure = value;
//##protect##"instance::TouchEvent::pressureSet()"
    }
    void TouchEvent::relatedObjectGet(SPtr<Instances::fl_display::InteractiveObject>& result)
    {
//##protect##"instance::TouchEvent::relatedObjectGet()"
        SF_UNUSED1(result);
        result = RelatedObj;
//##protect##"instance::TouchEvent::relatedObjectGet()"
    }
    void TouchEvent::relatedObjectSet(const Value& result, Instances::fl_display::InteractiveObject* value)
    {
//##protect##"instance::TouchEvent::relatedObjectSet()"
        SF_UNUSED2(result, value);
        RelatedObj = value;
//##protect##"instance::TouchEvent::relatedObjectSet()"
    }
    void TouchEvent::shiftKeyGet(bool& result)
    {
//##protect##"instance::TouchEvent::shiftKeyGet()"
        SF_UNUSED1(result);
        result = ShiftKey;
//##protect##"instance::TouchEvent::shiftKeyGet()"
    }
    void TouchEvent::shiftKeySet(const Value& result, bool value)
    {
//##protect##"instance::TouchEvent::shiftKeySet()"
        SF_UNUSED2(result, value);
        ShiftKey = value;
//##protect##"instance::TouchEvent::shiftKeySet()"
    }
    void TouchEvent::sizeXGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::sizeXGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(SizeX);
//##protect##"instance::TouchEvent::sizeXGet()"
    }
    void TouchEvent::sizeXSet(const Value& result, Value::Number value)
    {
//##protect##"instance::TouchEvent::sizeXSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        SizeX = PixelsToTwips(value);
//##protect##"instance::TouchEvent::sizeXSet()"
    }
    void TouchEvent::sizeYGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::sizeYGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(SizeY);
//##protect##"instance::TouchEvent::sizeYGet()"
    }
    void TouchEvent::sizeYSet(const Value& result, Value::Number value)
    {
//##protect##"instance::TouchEvent::sizeYSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        SizeY = PixelsToTwips(value);
//##protect##"instance::TouchEvent::sizeYSet()"
    }
    void TouchEvent::stageXGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::stageXGet()"
        SF_UNUSED1(result);
        result = TwipsToPixels(StageX);
//##protect##"instance::TouchEvent::stageXGet()"
    }
    void TouchEvent::stageYGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::stageYGet()"
        SF_UNUSED1(result);
        result = TwipsToPixels(StageY);
//##protect##"instance::TouchEvent::stageYGet()"
    }
    void TouchEvent::touchPointIDGet(SInt32& result)
    {
//##protect##"instance::TouchEvent::touchPointIDGet()"
        SF_UNUSED1(result);
        result = TouchPointID;
//##protect##"instance::TouchEvent::touchPointIDGet()"
    }
    void TouchEvent::touchPointIDSet(const Value& result, SInt32 value)
    {
//##protect##"instance::TouchEvent::touchPointIDSet()"
        SF_UNUSED2(result, value);
        TouchPointID = value;
//##protect##"instance::TouchEvent::touchPointIDSet()"
    }
    void TouchEvent::clone(SPtr<Instances::fl_events::Event>& result)
    {
//##protect##"instance::TouchEvent::clone()"
        SF_UNUSED1(result);
        result = Clone().GetPtr();
//##protect##"instance::TouchEvent::clone()"
    }
    void TouchEvent::toString(ASString& result)
    {
//##protect##"instance::TouchEvent::toString()"
        SF_UNUSED1(result);
        //example: [TouchEvent type="touchTap" bubbles=true cancelable=false eventPhase=2 touchPointID=2 isPrimaryTouchPoint=true 
        // localX=149.25 localY=188.85 stageX=157.25 stageY=198.85 sizeX=1.4600000381469727 sizeY=0.8199999928474426 pressure=1 
        // relatedObject=null ctrlKey=false altKey=false shiftKey=false commandKey=false controlKey=false]
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("TouchEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("eventPhase"),
            vm.GetStringManager().CreateConstString("touchPointID"),
            vm.GetStringManager().CreateConstString("isPrimaryTouchPoint"),
            vm.GetStringManager().CreateConstString("localX"),
            vm.GetStringManager().CreateConstString("localY"),
            vm.GetStringManager().CreateConstString("stageX"),
            vm.GetStringManager().CreateConstString("stageY"),
            vm.GetStringManager().CreateConstString("sizeX"),
            vm.GetStringManager().CreateConstString("sizeY"),
            vm.GetStringManager().CreateConstString("relatedObject"),
            vm.GetStringManager().CreateConstString("ctrlKey"),
            vm.GetStringManager().CreateConstString("altKey"),
            vm.GetStringManager().CreateConstString("shiftKey"),
            vm.GetStringManager().CreateConstString("commandKey"),
            vm.GetStringManager().CreateConstString("controlKey")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
//##protect##"instance::TouchEvent::toString()"
    }
    void TouchEvent::updateAfterEvent(const Value& result)
    {
//##protect##"instance::TouchEvent::updateAfterEvent()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::TouchEvent::updateAfterEvent()");
//##protect##"instance::TouchEvent::updateAfterEvent()"
    }

    SPtr<Instances::fl_display::InteractiveObject> TouchEvent::relatedObjectGet()
    {
        SPtr<Instances::fl_display::InteractiveObject> result;
        relatedObjectGet(result);
        return result;
    }
    SPtr<Instances::fl_events::Event> TouchEvent::clone()
    {
        SPtr<Instances::fl_events::Event> result;
        clone(result);
        return result;
    }
//##protect##"instance$methods"
    void TouchEvent::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::fl_events::Event::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<fl_display::InteractiveObject, Mem_Stat>(prcc, RelatedObj, op SF_DEBUG_ARG(*this));
    }
    void TouchEvent::AS3Constructor(unsigned argc, const Value* argv)
    {
        Event::AS3Constructor(argc, argv);
        if (argc >= 4)
        {
            argv[3].Convert2Int32(TouchPointID).DoNotCheck();
        }
        if (argc >= 5)
        {
            PrimaryPoint = argv[4].Convert2Boolean();
        }
        if (argc >= 6)
        {
            Value::Number v;
            argv[5].Convert2Number(v).DoNotCheck();
            LocalX = PixelsToTwips(v);
            LocalInitialized = true;
        }
        if (argc >= 7)
        {
            Value::Number v;
            argv[6].Convert2Number(v).DoNotCheck();
            LocalY = PixelsToTwips(v);
            LocalInitialized = true;
        }
        if (argc >= 8)
        {
            Value::Number v;
            argv[7].Convert2Number(v).DoNotCheck();
            SizeX = PixelsToTwips(v);
            LocalInitialized = true;
        }
        if (argc >= 9)
        {
            Value::Number v;
            argv[8].Convert2Number(v).DoNotCheck();
            SizeY = PixelsToTwips(v);
            LocalInitialized = true;
        }
        if (argc >= 10)
        {
            argv[9].Convert2Number(Pressure).DoNotCheck();
        }
        if (argc >= 11)
        {
            RelatedObj = NULL;
            AS3::Object* ptr = argv[5].GetObject();
            if (ptr)
            {
                if (GetVM().IsOfType(argv[10], "flash.display.InteractiveObject", GetVM().GetCurrentAppDomain()))
                {
                    RelatedObj = static_cast<fl_display::InteractiveObject*>(ptr);
                }
            }
        }
        if (argc >= 12)
        {
            CtrlKey = argv[11].Convert2Boolean();
        }
        if (argc >= 13)
        {
            AltKey = argv[12].Convert2Boolean();
        }
        if (argc >= 14)
        {
            ShiftKey = argv[13].Convert2Boolean();
        }
        if (argc >= 15)
        {
            CommandKey = argv[14].Convert2Boolean();
        }
        if (argc >= 16)
        {
            ControlKey = argv[15].Convert2Boolean();
        }
    }
    AS3::Object* TouchEvent::GetEventClass() const 
    { 
#if defined(GFX_MULTITOUCH_SUPPORT_ENABLE)
		return static_cast<ASVM&>(GetVM()).TouchEventClass; 
#else
		return NULL;
#endif
    }

    SPtr<Instances::fl_events::Event> TouchEvent::Clone() const
    {
        SPtr<Instances::fl_events::Event> p = Event::Clone();
        TouchEvent* pe = static_cast<TouchEvent*>(p.GetPtr());
        pe->AltKey          = AltKey;
        pe->CtrlKey         = CtrlKey;
        pe->ShiftKey        = ShiftKey;
        pe->CommandKey      = CommandKey;
        pe->ControlKey      = ControlKey;
        pe->Pressure        = Pressure;
        pe->RelatedObj      = RelatedObj;
        pe->LocalX          = LocalX;
        pe->LocalY          = LocalY;
        pe->StageX          = StageX;
        pe->StageY          = StageY;
        pe->SizeX           = SizeX;
        pe->SizeY           = SizeY;
        pe->TouchPointID    = TouchPointID;
        pe->PrimaryPoint    = PrimaryPoint;
        pe->LocalInitialized= LocalInitialized;
        return p;
    }

    void TouchEvent::InitLocalCoords()
    {
        if (!LocalInitialized)
        {
            if (Target && GetVM().IsOfType(Value(Target), "flash.display.DisplayObject", GetVM().GetCurrentAppDomain()))
            {
                Instances::fl_display::DisplayObject* dobj = static_cast<Instances::fl_display::DisplayObject*>(Target.GetPtr());
                SF_ASSERT(dobj->pDispObj);
                Matrix2F m = dobj->pDispObj->GetWorldMatrix();

                PointF p((float)StageX, (float)StageY);
                p = m.TransformByInverse(p);
                LocalX = p.x;
                LocalY = p.y;

                PointF p1((float)SizeX, (float)SizeY);
                p1 = m.TransformByInverse(p1);
                SizeX = p1.x;
                SizeY = p1.y;
            }
            else
            {
                LocalX = LocalY = SizeX = SizeY = 0;
            }
            LocalInitialized = true;
        }
    }
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_events
{
    const ThunkInfo TouchEvent::ti[TouchEvent::ThunkInfoNum] = {
        {TFunc_Instances_TouchEvent_altKeyGet::Func, &AS3::fl::BooleanTI, "altKey", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_altKeySet::Func, NULL, "altKey", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_commandKeyGet::Func, &AS3::fl::BooleanTI, "commandKey", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_commandKeySet::Func, NULL, "commandKey", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_controlKeyGet::Func, &AS3::fl::BooleanTI, "controlKey", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_controlKeySet::Func, NULL, "controlKey", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_ctrlKeyGet::Func, &AS3::fl::BooleanTI, "ctrlKey", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_ctrlKeySet::Func, NULL, "ctrlKey", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_isPrimaryTouchPointGet::Func, &AS3::fl::BooleanTI, "isPrimaryTouchPoint", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_isPrimaryTouchPointSet::Func, NULL, "isPrimaryTouchPoint", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleGet::Func, &AS3::fl::BooleanTI, "isRelatedObjectInaccessible", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleSet::Func, NULL, "isRelatedObjectInaccessible", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_localXGet::Func, &AS3::fl::NumberTI, "localX", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_localXSet::Func, NULL, "localX", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_localYGet::Func, &AS3::fl::NumberTI, "localY", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_localYSet::Func, NULL, "localY", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_pressureGet::Func, &AS3::fl::NumberTI, "pressure", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_pressureSet::Func, NULL, "pressure", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_relatedObjectGet::Func, &AS3::fl_display::InteractiveObjectTI, "relatedObject", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_relatedObjectSet::Func, NULL, "relatedObject", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_shiftKeyGet::Func, &AS3::fl::BooleanTI, "shiftKey", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_shiftKeySet::Func, NULL, "shiftKey", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_sizeXGet::Func, &AS3::fl::NumberTI, "sizeX", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_sizeXSet::Func, NULL, "sizeX", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_sizeYGet::Func, &AS3::fl::NumberTI, "sizeY", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_sizeYSet::Func, NULL, "sizeY", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_stageXGet::Func, &AS3::fl::NumberTI, "stageX", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_stageYGet::Func, &AS3::fl::NumberTI, "stageY", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_touchPointIDGet::Func, &AS3::fl::int_TI, "touchPointID", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_touchPointIDSet::Func, NULL, "touchPointID", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_clone::Func, &AS3::fl_events::EventTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_TouchEvent_toString::Func, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_TouchEvent_updateAfterEvent::Func, NULL, "updateAfterEvent", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

    TouchEvent::TouchEvent(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::TouchEvent::TouchEvent()"
//##protect##"InstanceTraits::TouchEvent::TouchEvent()"
        SetMemSize(sizeof(Instances::fl_events::TouchEvent));

    }

    void TouchEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<TouchEvent&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits

namespace Classes { namespace fl_events
{
    TouchEvent::TouchEvent(ClassTraits::Traits& t)
    : Class(t)
    , TOUCH_BEGIN("touchBegin")
    , TOUCH_END("touchEnd")
    , TOUCH_MOVE("touchMove")
    , TOUCH_OUT("touchOut")
    , TOUCH_OVER("touchOver")
    , TOUCH_ROLL_OUT("touchRollOut")
    , TOUCH_ROLL_OVER("touchRollOver")
    , TOUCH_TAP("touchTap")
    {
//##protect##"class_::TouchEvent::TouchEvent()"
//##protect##"class_::TouchEvent::TouchEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo TouchEvent::mi[TouchEvent::MemberInfoNum] = {
        {"TOUCH_BEGIN", NULL, OFFSETOF(Classes::fl_events::TouchEvent, TOUCH_BEGIN), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"TOUCH_END", NULL, OFFSETOF(Classes::fl_events::TouchEvent, TOUCH_END), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"TOUCH_MOVE", NULL, OFFSETOF(Classes::fl_events::TouchEvent, TOUCH_MOVE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"TOUCH_OUT", NULL, OFFSETOF(Classes::fl_events::TouchEvent, TOUCH_OUT), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"TOUCH_OVER", NULL, OFFSETOF(Classes::fl_events::TouchEvent, TOUCH_OVER), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"TOUCH_ROLL_OUT", NULL, OFFSETOF(Classes::fl_events::TouchEvent, TOUCH_ROLL_OUT), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"TOUCH_ROLL_OVER", NULL, OFFSETOF(Classes::fl_events::TouchEvent, TOUCH_ROLL_OVER), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"TOUCH_TAP", NULL, OFFSETOF(Classes::fl_events::TouchEvent, TOUCH_TAP), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    TouchEvent::TouchEvent(VM& vm)
    : Traits(vm, AS3::fl_events::TouchEventCI)
    {
//##protect##"ClassTraits::TouchEvent::TouchEvent()"
//##protect##"ClassTraits::TouchEvent::TouchEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::TouchEvent(vm, AS3::fl_events::TouchEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::TouchEvent(*this));

    }

    Pickable<Traits> TouchEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TouchEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo TouchEventTI = {
        TypeInfo::CompileTime,
        "TouchEvent", "flash.events", &fl_events::EventTI,
        TypeInfo::None
    };

    const ClassInfo TouchEventCI = {
        &TouchEventTI,
        ClassTraits::fl_events::TouchEvent::MakeClassTraits,
        0,
        ClassTraits::fl_events::TouchEvent::MemberInfoNum,
        InstanceTraits::fl_events::TouchEvent::ThunkInfoNum,
        0,
        NULL,
        ClassTraits::fl_events::TouchEvent::mi,
        InstanceTraits::fl_events::TouchEvent::ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

