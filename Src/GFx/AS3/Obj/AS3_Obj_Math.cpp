//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Math.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Math.h"
#include "../AS3_VM.h"
#include "../AS3_Marshalling.h"
//##protect##"includes"
#include "Kernel/SF_Alg.h"
#include "Kernel/SF_Random.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl
{
    Math::Math(ClassTraits::Traits& t)
    : Class(t)
    , LN10(2.302585092994046)
    , E(2.718281828459045)
    , LN2(0.6931471805599453)
    , LOG10E(0.4342944819032518)
    , LOG2E(1.442695040888963387)
    , PI(3.141592653589793)
    , SQRT1_2(0.7071067811865476)
    , SQRT2(1.4142135623730951)
    {
//##protect##"class_::Math::Math()"
//##protect##"class_::Math::Math()"
    }
    void Math::abs(Value::Number& result, Value::Number x)
    {
//##protect##"class_::Math::abs()"
        if (NumberUtil::IsNEGATIVE_ZERO(x))
            result = 0.0;
        else
            result = (x < 0.0) ? -x : x;
//##protect##"class_::Math::abs()"
    }
    void Math::acos(Value::Number& result, Value::Number x)
    {
//##protect##"class_::Math::acos()"
        result = ::acos(x);
//##protect##"class_::Math::acos()"
    }
    void Math::asin(Value::Number& result, Value::Number x)
    {
//##protect##"class_::Math::asin()"
        result = ::asin(x);
//##protect##"class_::Math::asin()"
    }
    void Math::atan(Value::Number& result, Value::Number x)
    {
//##protect##"class_::Math::atan()"
        result = ::atan(x);
//##protect##"class_::Math::atan()"
    }
    void Math::atan2(Value::Number& result, Value::Number y, Value::Number x)
    {
//##protect##"class_::Math::atan2()"
        if (NumberUtil::IsPOSITIVE_INFINITY(y))
        {
            if (NumberUtil::IsPOSITIVE_INFINITY(x))
                result = PI * 0.25;
            else if (NumberUtil::IsNEGATIVE_INFINITY(x))
                result = PI * 0.75;
            else
                result = PI * 0.5;
        }
        else if (NumberUtil::IsNEGATIVE_INFINITY(y))
        {
            if (NumberUtil::IsPOSITIVE_INFINITY(x))
                result = - PI * 0.25;
            else if (NumberUtil::IsNEGATIVE_INFINITY(x))
                result = - PI * 0.75;
            else
                result = - PI * 0.5;
        }
        else
            result = ::atan2(y, x);
//##protect##"class_::Math::atan2()"
    }
    void Math::ceil(Value::Number& result, Value::Number x)
    {
//##protect##"class_::Math::ceil()"
        result = ::ceil(x);
//##protect##"class_::Math::ceil()"
    }
    void Math::cos(Value::Number& result, Value::Number x)
    {
//##protect##"class_::Math::cos()"
        result = ::cos(x);
//##protect##"class_::Math::cos()"
    }
    void Math::exp(Value::Number& result, Value::Number x)
    {
//##protect##"class_::Math::exp()"
        result = ::exp(x);
//##protect##"class_::Math::exp()"
    }
    void Math::floor(Value::Number& result, Value::Number x)
    {
//##protect##"class_::Math::floor()"
        result = ::floor(x);
//##protect##"class_::Math::floor()"
    }
    void Math::log(Value::Number& result, Value::Number x)
    {
//##protect##"class_::Math::log()"
        result = ::log(x);
//##protect##"class_::Math::log()"
    }
    void Math::round(Value::Number& result, Value::Number x)
    {
//##protect##"class_::Math::round()"
        //This implementation produces Math.round(-0) = 0 to pass Tamarin tests,
        // but according to ECMA-262 Math.round(-0) = -0
        if (NumberUtil::IsNaNOrInfinity(x))
            result = x;
        else
            result = ::floor(x + 0.5);
//##protect##"class_::Math::round()"
    }
    void Math::sin(Value::Number& result, Value::Number x)
    {
//##protect##"class_::Math::sin()"
        result = ::sin(x);
//##protect##"class_::Math::sin()"
    }
    void Math::sqrt(Value::Number& result, Value::Number x)
    {
//##protect##"class_::Math::sqrt()"
        result = ::sqrt(x);
//##protect##"class_::Math::sqrt()"
    }
    void Math::tan(Value::Number& result, Value::Number x)
    {
//##protect##"class_::Math::tan()"
        result = ::tan(x);
//##protect##"class_::Math::tan()"
    }
    void Math::pow(Value::Number& result, Value::Number x, Value::Number y)
    {
//##protect##"class_::Math::pow()"
        if (y == 0)
            result = 1;
        else if ((x == 1 || x == -1) && NumberUtil::IsNaNOrInfinity(y))
            result = NumberUtil::NaN();
        else
            result = ::pow(x, y);
//##protect##"class_::Math::pow()"
    }
    void Math::max(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"class_::Math::max()"
        if (argc > 0)
        {
            Boolean3 lt;
            result = argv[0];

            for(unsigned  i = 1; i < argc; ++i)
            {
                const Value& v = argv[i];

                if (!AbstractLessThan(lt, v, result))
                    // Exception.
                    return;

                if (lt == undefined3)
                    return result.SetNumber(NumberUtil::NaN());
                else if (lt == false3)
                    result = v; 
            }

            result.ToNumberValue().DoNotCheck();
        }
        else
            result.SetNumber(NumberUtil::NEGATIVE_INFINITY());
//##protect##"class_::Math::max()"
    }
    void Math::min(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"class_::Math::min()"
        if (argc > 0)
        {
            Boolean3 lt;
            result = argv[0];

            for(unsigned i = 1; i < argc; ++i)
            {
                const Value& v = argv[i];

                if (!AbstractLessThan(lt, result, v))
                    // Exception.
                    return;

                if (lt == undefined3)
                    return result.SetNumber(NumberUtil::NaN());
                else if (lt == false3)
                    result = v; 
            }

            result.ToNumberValue().DoNotCheck();
        }
        else
            result.SetNumber(NumberUtil::POSITIVE_INFINITY());
//##protect##"class_::Math::min()"
    }
    void Math::random(Value::Number& result)
    {
//##protect##"class_::Math::random()"
        result = double(Alg::Random::NextRandom()) / double(~0u);
//##protect##"class_::Math::random()"
    }
//##protect##"class_$methods"
    void Math::Call(const Value& _this, Value& result, unsigned argc, const Value* const argv)
    {
        SF_UNUSED4(_this, argc, argv, result);
        return GetVM().ThrowTypeError(VM::Error(VM::eMathNotFunctionError, GetVM()));
    }
    void Math::Construct(Value& _this, unsigned argc, const Value* argv, bool extCall)
    {
        SF_UNUSED4(_this, argc, argv, extCall);
        return GetVM().ThrowTypeError(VM::Error(VM::eMathNotConstructorError, GetVM()));
    }
//##protect##"class_$methods"

}} // namespace Classes

typedef ThunkFunc1<Classes::fl::Math, Classes::fl::Math::mid_abs, Value::Number, Value::Number> TFunc_Classes_Math_abs;
typedef ThunkFunc1<Classes::fl::Math, Classes::fl::Math::mid_acos, Value::Number, Value::Number> TFunc_Classes_Math_acos;
typedef ThunkFunc1<Classes::fl::Math, Classes::fl::Math::mid_asin, Value::Number, Value::Number> TFunc_Classes_Math_asin;
typedef ThunkFunc1<Classes::fl::Math, Classes::fl::Math::mid_atan, Value::Number, Value::Number> TFunc_Classes_Math_atan;
typedef ThunkFunc2<Classes::fl::Math, Classes::fl::Math::mid_atan2, Value::Number, Value::Number, Value::Number> TFunc_Classes_Math_atan2;
typedef ThunkFunc1<Classes::fl::Math, Classes::fl::Math::mid_ceil, Value::Number, Value::Number> TFunc_Classes_Math_ceil;
typedef ThunkFunc1<Classes::fl::Math, Classes::fl::Math::mid_cos, Value::Number, Value::Number> TFunc_Classes_Math_cos;
typedef ThunkFunc1<Classes::fl::Math, Classes::fl::Math::mid_exp, Value::Number, Value::Number> TFunc_Classes_Math_exp;
typedef ThunkFunc1<Classes::fl::Math, Classes::fl::Math::mid_floor, Value::Number, Value::Number> TFunc_Classes_Math_floor;
typedef ThunkFunc1<Classes::fl::Math, Classes::fl::Math::mid_log, Value::Number, Value::Number> TFunc_Classes_Math_log;
typedef ThunkFunc1<Classes::fl::Math, Classes::fl::Math::mid_round, Value::Number, Value::Number> TFunc_Classes_Math_round;
typedef ThunkFunc1<Classes::fl::Math, Classes::fl::Math::mid_sin, Value::Number, Value::Number> TFunc_Classes_Math_sin;
typedef ThunkFunc1<Classes::fl::Math, Classes::fl::Math::mid_sqrt, Value::Number, Value::Number> TFunc_Classes_Math_sqrt;
typedef ThunkFunc1<Classes::fl::Math, Classes::fl::Math::mid_tan, Value::Number, Value::Number> TFunc_Classes_Math_tan;
typedef ThunkFunc2<Classes::fl::Math, Classes::fl::Math::mid_pow, Value::Number, Value::Number, Value::Number> TFunc_Classes_Math_pow;
typedef ThunkFunc2<Classes::fl::Math, Classes::fl::Math::mid_max, Value, unsigned, const Value*> TFunc_Classes_Math_max;
typedef ThunkFunc2<Classes::fl::Math, Classes::fl::Math::mid_min, Value, unsigned, const Value*> TFunc_Classes_Math_min;
typedef ThunkFunc0<Classes::fl::Math, Classes::fl::Math::mid_random, Value::Number> TFunc_Classes_Math_random;

template <> const TFunc_Classes_Math_abs::TMethod TFunc_Classes_Math_abs::Method = &Classes::fl::Math::abs;
template <> const TFunc_Classes_Math_acos::TMethod TFunc_Classes_Math_acos::Method = &Classes::fl::Math::acos;
template <> const TFunc_Classes_Math_asin::TMethod TFunc_Classes_Math_asin::Method = &Classes::fl::Math::asin;
template <> const TFunc_Classes_Math_atan::TMethod TFunc_Classes_Math_atan::Method = &Classes::fl::Math::atan;
template <> const TFunc_Classes_Math_atan2::TMethod TFunc_Classes_Math_atan2::Method = &Classes::fl::Math::atan2;
template <> const TFunc_Classes_Math_ceil::TMethod TFunc_Classes_Math_ceil::Method = &Classes::fl::Math::ceil;
template <> const TFunc_Classes_Math_cos::TMethod TFunc_Classes_Math_cos::Method = &Classes::fl::Math::cos;
template <> const TFunc_Classes_Math_exp::TMethod TFunc_Classes_Math_exp::Method = &Classes::fl::Math::exp;
template <> const TFunc_Classes_Math_floor::TMethod TFunc_Classes_Math_floor::Method = &Classes::fl::Math::floor;
template <> const TFunc_Classes_Math_log::TMethod TFunc_Classes_Math_log::Method = &Classes::fl::Math::log;
template <> const TFunc_Classes_Math_round::TMethod TFunc_Classes_Math_round::Method = &Classes::fl::Math::round;
template <> const TFunc_Classes_Math_sin::TMethod TFunc_Classes_Math_sin::Method = &Classes::fl::Math::sin;
template <> const TFunc_Classes_Math_sqrt::TMethod TFunc_Classes_Math_sqrt::Method = &Classes::fl::Math::sqrt;
template <> const TFunc_Classes_Math_tan::TMethod TFunc_Classes_Math_tan::Method = &Classes::fl::Math::tan;
template <> const TFunc_Classes_Math_pow::TMethod TFunc_Classes_Math_pow::Method = &Classes::fl::Math::pow;
template <> const TFunc_Classes_Math_max::TMethod TFunc_Classes_Math_max::Method = &Classes::fl::Math::max;
template <> const TFunc_Classes_Math_min::TMethod TFunc_Classes_Math_min::Method = &Classes::fl::Math::min;
template <> const TFunc_Classes_Math_random::TMethod TFunc_Classes_Math_random::Method = &Classes::fl::Math::random;

namespace ClassTraits { namespace fl
{
    const MemberInfo Math::mi[Math::MemberInfoNum] = {
        {"LN10", NULL, OFFSETOF(Classes::fl::Math, LN10), Abc::NS_Public, SlotInfo::BT_Number, 1},
        {"E", NULL, OFFSETOF(Classes::fl::Math, E), Abc::NS_Public, SlotInfo::BT_Number, 1},
        {"LN2", NULL, OFFSETOF(Classes::fl::Math, LN2), Abc::NS_Public, SlotInfo::BT_Number, 1},
        {"LOG10E", NULL, OFFSETOF(Classes::fl::Math, LOG10E), Abc::NS_Public, SlotInfo::BT_Number, 1},
        {"LOG2E", NULL, OFFSETOF(Classes::fl::Math, LOG2E), Abc::NS_Public, SlotInfo::BT_Number, 1},
        {"PI", NULL, OFFSETOF(Classes::fl::Math, PI), Abc::NS_Public, SlotInfo::BT_Number, 1},
        {"SQRT1_2", NULL, OFFSETOF(Classes::fl::Math, SQRT1_2), Abc::NS_Public, SlotInfo::BT_Number, 1},
        {"SQRT2", NULL, OFFSETOF(Classes::fl::Math, SQRT2), Abc::NS_Public, SlotInfo::BT_Number, 1},
    };

    const ThunkInfo Math::ti[Math::ThunkInfoNum] = {
        {TFunc_Classes_Math_abs::Func, &AS3::fl::NumberTI, "abs", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_Math_acos::Func, &AS3::fl::NumberTI, "acos", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_Math_asin::Func, &AS3::fl::NumberTI, "asin", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_Math_atan::Func, &AS3::fl::NumberTI, "atan", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_Math_atan2::Func, &AS3::fl::NumberTI, "atan2", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Classes_Math_ceil::Func, &AS3::fl::NumberTI, "ceil", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_Math_cos::Func, &AS3::fl::NumberTI, "cos", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_Math_exp::Func, &AS3::fl::NumberTI, "exp", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_Math_floor::Func, &AS3::fl::NumberTI, "floor", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_Math_log::Func, &AS3::fl::NumberTI, "log", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_Math_round::Func, &AS3::fl::NumberTI, "round", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_Math_sin::Func, &AS3::fl::NumberTI, "sin", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_Math_sqrt::Func, &AS3::fl::NumberTI, "sqrt", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_Math_tan::Func, &AS3::fl::NumberTI, "tan", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_Math_pow::Func, &AS3::fl::NumberTI, "pow", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Classes_Math_max::Func, &AS3::fl::NumberTI, "max", NULL, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {TFunc_Classes_Math_min::Func, &AS3::fl::NumberTI, "min", NULL, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {TFunc_Classes_Math_random::Func, &AS3::fl::NumberTI, "random", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };
    Math::Math(VM& vm)
    : Traits(vm, AS3::fl::MathCI)
    {
//##protect##"ClassTraits::Math::Math()"
//##protect##"ClassTraits::Math::Math()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl::MathCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl::Math(*this));

    }

    Pickable<Traits> Math::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Math(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl
{
    const TypeInfo MathTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "Math", "", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo MathCI = {
        &MathTI,
        ClassTraits::fl::Math::MakeClassTraits,
        ClassTraits::fl::Math::ThunkInfoNum,
        ClassTraits::fl::Math::MemberInfoNum,
        0,
        0,
        ClassTraits::fl::Math::ti,
        ClassTraits::fl::Math::mi,
        NULL,
        NULL,
    };
}; // namespace fl


}}} // namespace Scaleform { namespace GFx { namespace AS3

