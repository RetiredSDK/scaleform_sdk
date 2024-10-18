//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_Timer.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Utils_Timer.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "GFx/AS3/AS3_IntervalTimer.h"
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
typedef ThunkFunc0<Instances::fl_utils::Timer, Instances::fl_utils::Timer::mid_currentCountGet, SInt32> TFunc_Instances_Timer_currentCountGet;
typedef ThunkFunc0<Instances::fl_utils::Timer, Instances::fl_utils::Timer::mid_delayGet, Value::Number> TFunc_Instances_Timer_delayGet;
typedef ThunkFunc1<Instances::fl_utils::Timer, Instances::fl_utils::Timer::mid_delaySet, const Value, Value::Number> TFunc_Instances_Timer_delaySet;
typedef ThunkFunc0<Instances::fl_utils::Timer, Instances::fl_utils::Timer::mid_repeatCountGet, SInt32> TFunc_Instances_Timer_repeatCountGet;
typedef ThunkFunc1<Instances::fl_utils::Timer, Instances::fl_utils::Timer::mid_repeatCountSet, const Value, SInt32> TFunc_Instances_Timer_repeatCountSet;
typedef ThunkFunc0<Instances::fl_utils::Timer, Instances::fl_utils::Timer::mid_runningGet, bool> TFunc_Instances_Timer_runningGet;
typedef ThunkFunc0<Instances::fl_utils::Timer, Instances::fl_utils::Timer::mid_reset, const Value> TFunc_Instances_Timer_reset;
typedef ThunkFunc0<Instances::fl_utils::Timer, Instances::fl_utils::Timer::mid_start, const Value> TFunc_Instances_Timer_start;
typedef ThunkFunc0<Instances::fl_utils::Timer, Instances::fl_utils::Timer::mid_stop, const Value> TFunc_Instances_Timer_stop;

template <> const TFunc_Instances_Timer_currentCountGet::TMethod TFunc_Instances_Timer_currentCountGet::Method = &Instances::fl_utils::Timer::currentCountGet;
template <> const TFunc_Instances_Timer_delayGet::TMethod TFunc_Instances_Timer_delayGet::Method = &Instances::fl_utils::Timer::delayGet;
template <> const TFunc_Instances_Timer_delaySet::TMethod TFunc_Instances_Timer_delaySet::Method = &Instances::fl_utils::Timer::delaySet;
template <> const TFunc_Instances_Timer_repeatCountGet::TMethod TFunc_Instances_Timer_repeatCountGet::Method = &Instances::fl_utils::Timer::repeatCountGet;
template <> const TFunc_Instances_Timer_repeatCountSet::TMethod TFunc_Instances_Timer_repeatCountSet::Method = &Instances::fl_utils::Timer::repeatCountSet;
template <> const TFunc_Instances_Timer_runningGet::TMethod TFunc_Instances_Timer_runningGet::Method = &Instances::fl_utils::Timer::runningGet;
template <> const TFunc_Instances_Timer_reset::TMethod TFunc_Instances_Timer_reset::Method = &Instances::fl_utils::Timer::reset;
template <> const TFunc_Instances_Timer_start::TMethod TFunc_Instances_Timer_start::Method = &Instances::fl_utils::Timer::start;
template <> const TFunc_Instances_Timer_stop::TMethod TFunc_Instances_Timer_stop::Method = &Instances::fl_utils::Timer::stop;

namespace Instances { namespace fl_utils
{
    Timer::Timer(InstanceTraits::Traits& t)
    : Instances::fl_events::EventDispatcher(t)
//##protect##"instance::Timer::Timer()$data"
    , RepeatCount(0), CurrentCount(0), Delay(0), pCoreTimer(NULL)
//##protect##"instance::Timer::Timer()$data"
    {
//##protect##"instance::Timer::Timer()$code"
//##protect##"instance::Timer::Timer()$code"
    }

    void Timer::currentCountGet(SInt32& result)
    {
//##protect##"instance::Timer::currentCountGet()"
        SF_UNUSED1(result);
        if (pCoreTimer)
            result = pCoreTimer->GetCurrentCount();
        else
            result = CurrentCount;
//##protect##"instance::Timer::currentCountGet()"
    }
    void Timer::delayGet(Value::Number& result)
    {
//##protect##"instance::Timer::delayGet()"
        SF_UNUSED1(result);
        result = Delay;
//##protect##"instance::Timer::delayGet()"
    }
    void Timer::delaySet(const Value& result, Value::Number value)
    {
//##protect##"instance::Timer::delaySet()"
        SF_UNUSED2(result, value);
        Delay = value;
//##protect##"instance::Timer::delaySet()"
    }
    void Timer::repeatCountGet(SInt32& result)
    {
//##protect##"instance::Timer::repeatCountGet()"
        SF_UNUSED1(result);
        result = RepeatCount;
//##protect##"instance::Timer::repeatCountGet()"
    }
    void Timer::repeatCountSet(const Value& result, SInt32 value)
    {
//##protect##"instance::Timer::repeatCountSet()"
        SF_UNUSED2(result, value);
        RepeatCount = value;
//##protect##"instance::Timer::repeatCountSet()"
    }
    void Timer::runningGet(bool& result)
    {
//##protect##"instance::Timer::runningGet()"
        SF_UNUSED1(result);
        if (pCoreTimer && pCoreTimer->IsActive())
            result = true;
        else
            result = false;
//##protect##"instance::Timer::runningGet()"
    }
    void Timer::reset(const Value& result)
    {
//##protect##"instance::Timer::reset()"
        stop(result);
        CurrentCount = 0;
//##protect##"instance::Timer::reset()"
    }
    void Timer::start(const Value& result)
    {
//##protect##"instance::Timer::start()"
        SF_UNUSED1(result);

        MovieImpl* proot = static_cast<const ASVM&>(GetVM()).GetMovieImpl();
        if (pCoreTimer)
        {
            if (pCoreTimer->IsActive())
                return; // already active? do nothing!
            CurrentCount = (SInt32)pCoreTimer->GetCurrentCount();
            pCoreTimer = NULL;
        }
        pCoreTimer = *SF_HEAP_NEW(GetVM().GetMemoryHeap()) 
            IntervalTimer(this, (unsigned)Delay, CurrentCount, RepeatCount);

        proot->AddIntervalTimer(pCoreTimer);
        pCoreTimer->Start(proot);

//##protect##"instance::Timer::start()"
    }
    void Timer::stop(const Value& result)
    {
//##protect##"instance::Timer::stop()"
        SF_UNUSED1(result);
        if (pCoreTimer && pCoreTimer->IsActive())
        {
            MovieImpl* proot = static_cast<const ASVM&>(GetVM()).GetMovieImpl();
            proot->ClearIntervalTimer(int(pCoreTimer->GetId()));
        }
        pCoreTimer = NULL;
//##protect##"instance::Timer::stop()"
    }

//##protect##"instance$methods"
    void Timer::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc < 1)
        {
            return GetVM().ThrowArgumentError(VM::Error(VM::eWrongArgumentCountError, GetVM() SF_DEBUG_ARG("Timer::AS3Constructor") SF_DEBUG_ARG(1) SF_DEBUG_ARG(1) SF_DEBUG_ARG(argc)));
        }
        argv[0].Convert2Number(Delay).DoNotCheck();
        if (argc >= 2)
        {
            argv[1].Convert2Int32(RepeatCount).DoNotCheck();
        }
    }

    void Timer::ExecuteEvent()
    {
        SF_ASSERT(pCoreTimer);

        CurrentCount = (SInt32)pCoreTimer->GetCurrentCount();

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        SPtr<fl_events::TimerEvent> efe = CreateTimerEventObject(asvm.GetBuiltin(AS3Builtin_timer));
        efe->Target  = this;
        DispatchSingleEvent(efe, false);

        //!AB consider efe->IsDefaultPrevented() ?

        if (CurrentCount >= RepeatCount)
        {
            // dispatch TIMER_COMPLETE
            SPtr<fl_events::TimerEvent> efe = CreateTimerEventObject(asvm.GetBuiltin(AS3Builtin_timerComplete));
            efe->Target  = this;
            DispatchSingleEvent(efe, false);
        }
    }

    SPtr<Instances::fl_events::TimerEvent> Timer::CreateTimerEventObject(const ASString& type)
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        SPtr<Instances::fl_events::TimerEvent> evt;
        Value params[] = { Value(type), Value(false), Value(false) };
        asvm.ConstructInstance(evt, asvm.TimerEventClass, 3, params);
        SF_ASSERT(evt);
        return evt;
    }

//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_utils
{
    const ThunkInfo Timer::ti[Timer::ThunkInfoNum] = {
        {TFunc_Instances_Timer_currentCountGet::Func, &AS3::fl::int_TI, "currentCount", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Timer_delayGet::Func, &AS3::fl::NumberTI, "delay", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Timer_delaySet::Func, NULL, "delay", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_Timer_repeatCountGet::Func, &AS3::fl::int_TI, "repeatCount", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Timer_repeatCountSet::Func, NULL, "repeatCount", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_Timer_runningGet::Func, &AS3::fl::BooleanTI, "running", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Timer_reset::Func, NULL, "reset", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Timer_start::Func, NULL, "start", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Timer_stop::Func, NULL, "stop", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

    Timer::Timer(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::Timer::Timer()"
//##protect##"InstanceTraits::Timer::Timer()"
        SetMemSize(sizeof(Instances::fl_utils::Timer));

    }

    void Timer::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<Timer&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_utils
{
    Timer::Timer(VM& vm)
    : Traits(vm, AS3::fl_utils::TimerCI)
    {
//##protect##"ClassTraits::Timer::Timer()"
//##protect##"ClassTraits::Timer::Timer()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_utils::Timer(vm, AS3::fl_utils::TimerCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> Timer::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Timer(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_utils
{
    const TypeInfo TimerTI = {
        TypeInfo::CompileTime,
        "Timer", "flash.utils", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo TimerCI = {
        &TimerTI,
        ClassTraits::fl_utils::Timer::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_utils::Timer::ThunkInfoNum,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_utils::Timer::ti,
        NULL,
    };
}; // namespace fl_utils


}}} // namespace Scaleform { namespace GFx { namespace AS3

