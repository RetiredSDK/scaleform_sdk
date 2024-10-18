//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_uint.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_uint.h"
#include "../AS3_VM.h"
#include "../AS3_Marshalling.h"
//##protect##"includes"
#include "Kernel/SF_MsgFormat.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace InstanceTraits { namespace fl
{
    const ThunkInfo uint::ti[uint::ThunkInfoNum] = {
        {&InstanceTraits::fl::uint::AS3toExponential, &AS3::fl::StringTI, "toExponential", NS_AS3, Abc::NS_Public, CT_Method, 0, 1},
        {&InstanceTraits::fl::uint::AS3toFixed, &AS3::fl::StringTI, "toFixed", NS_AS3, Abc::NS_Public, CT_Method, 0, 1},
        {&InstanceTraits::fl::uint::AS3toPrecision, &AS3::fl::StringTI, "toPrecision", NS_AS3, Abc::NS_Public, CT_Method, 0, 1},
        {&InstanceTraits::fl::uint::AS3toString, &AS3::fl::StringTI, "toString", NS_AS3, Abc::NS_Public, CT_Method, 0, 1},
        {&InstanceTraits::fl::uint::AS3valueOf, &AS3::fl::uintTI, "valueOf", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
    };

    uint::uint(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::uint::uint()"
        SetTraitsType(Traits_UInt);
//##protect##"InstanceTraits::uint::uint()"

    }

    void uint::MakeObject(Value& result, Traits& t)
    {
        SF_UNUSED2(result, t); SF_ASSERT(false);
    }

    void uint::AS3toExponential(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toExponential()"
        SF_UNUSED1(ti);

        UInt32 fractionDigits = 0;

        if (argc > 0)
            if (!argv[0].Convert2UInt32(fractionDigits))
                // Exception
                return;

        if (fractionDigits > 20)
            return vm.ThrowRangeError(VM::Error(VM::eInvalidPrecisionError, vm));

        DoubleFormatter f(static_cast<Double>(_this.AsUInt()));
        f.SetType(DoubleFormatter::FmtScientific).SetPrecision(fractionDigits).Convert();
        result = vm.GetStringManager().CreateString(f.GetResult().ToCStr(), f.GetSize());
//##protect##"InstanceTraits::AS3toExponential()"
    }
    void uint::AS3toFixed(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toFixed()"
        SF_UNUSED1(ti);

        UInt32 fractionDigits = 0;

        if (argc > 0)
            if (!argv[0].Convert2UInt32(fractionDigits))
                // Exception
                return;

        if (fractionDigits > 20)
            return vm.ThrowRangeError(VM::Error(VM::eInvalidPrecisionError, vm));

        DoubleFormatter f(static_cast<Double>(_this.AsUInt()));
        f.SetType(DoubleFormatter::FmtDecimal).SetPrecision(fractionDigits).Convert();
        result = vm.GetStringManager().CreateString(f.GetResult().ToCStr(), f.GetSize());
//##protect##"InstanceTraits::AS3toFixed()"
    }
    void uint::AS3toPrecision(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toPrecision()"
        SF_UNUSED1(ti);

        UInt32 precision = 0;

        if (argc > 0)
            if (!argv[0].Convert2UInt32(precision))
                // Exception
                return;

        if (precision == 0 || precision > 21)
            return vm.ThrowRangeError(VM::Error(VM::eInvalidPrecisionError, vm));

        DoubleFormatter f(static_cast<Double>(_this.AsUInt()));
        f.SetType(DoubleFormatter::FmtSignificant).SetPrecision(precision).Convert();
        result = vm.GetStringManager().CreateString(f.GetResult().ToCStr(), f.GetSize());
//##protect##"InstanceTraits::AS3toPrecision()"
    }
    void uint::AS3toString(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toString()"
        SF_UNUSED1(ti);

        // This method is not generic.
        if (!_this.IsUInt())
            return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));

        // If radix is the number 10 or undefined ...
        // Save undefined.
        UInt32 radix = 10;
        if (argc > 0 && !argv[0].IsUndefined())
            if (!argv[0].Convert2UInt32(radix))
                // Exception
                return;

        if (radix < 2 || radix > 16)
            return vm.ThrowRangeError(VM::Error(VM::eInvalidRadixError, vm SF_DEBUG_ARG(radix)));

        LongFormatter f(_this.AsUInt());
        f.SetBase(radix).SetBigLetters(false).Convert();
        StringDataPtr r = f.GetResult();

        result = vm.GetStringManager().CreateString(r.ToCStr(), r.GetSize());
//##protect##"InstanceTraits::AS3toString()"
    }
    void uint::AS3valueOf(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3valueOf()"
        SF_UNUSED3(ti, argc, argv);

        // This method is not generic.
        if (!_this.IsUInt())
            return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));

        result.SetUInt32(_this.AsUInt());
//##protect##"InstanceTraits::AS3valueOf()"
    }
    void uint::toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::toStringProto()"
        if (_this.IsObject() && _this.GetObject() == &vm.GetClassUInt().GetPrototype())
            // This method is called on a prototype object.
            result = vm.GetStringManager().GetBuiltin(AS3Builtin_zero);
        else
            AS3toString(ti, vm, _this, result, argc, argv);
//##protect##"InstanceTraits::toStringProto()"
    }
    void uint::toLocaleStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::toLocaleStringProto()"
        toStringProto(ti, vm, _this, result, argc, argv);
//##protect##"InstanceTraits::toLocaleStringProto()"
    }
    void uint::valueOfProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::valueOfProto()"
        if (_this.IsObject() && _this.GetObject() == &vm.GetClassUInt().GetPrototype())
            // This method is called on a prototype object.
            result.SetUInt32(0);
        else
            AS3valueOf(ti, vm, _this, result, argc, argv);
//##protect##"InstanceTraits::valueOfProto()"
    }
    void uint::toExponentialProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::toExponentialProto()"
        Value coerced_this;

        if (!vm.GetClassTraitsUInt().CoerceValue(_this, coerced_this))
        {
            return vm.ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, vm
                SF_DEBUG_ARG(vm.GetValueTraits(_this).GetName().ToCStr())
                SF_DEBUG_ARG(vm.GetClassTraitsUInt().GetName().ToCStr())
                ));
        }

        AS3toExponential(ti, vm, coerced_this, result, argc, argv);
//##protect##"InstanceTraits::toExponentialProto()"
    }
    void uint::toFixedProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::toFixedProto()"
        Value coerced_this;

        if (!vm.GetClassTraitsUInt().CoerceValue(_this, coerced_this))
        {
            return vm.ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, vm
                SF_DEBUG_ARG(vm.GetValueTraits(_this).GetName().ToCStr())
                SF_DEBUG_ARG(vm.GetClassTraitsUInt().GetName().ToCStr())
                ));
        }

        AS3toFixed(ti, vm, coerced_this, result, argc, argv);
//##protect##"InstanceTraits::toFixedProto()"
    }
    void uint::toPrecisionProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::toPrecisionProto()"
        Value coerced_this;

        if (!vm.GetClassTraitsUInt().CoerceValue(_this, coerced_this))
        {
            return vm.ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, vm
                SF_DEBUG_ARG(vm.GetValueTraits(_this).GetName().ToCStr())
                SF_DEBUG_ARG(vm.GetClassTraitsUInt().GetName().ToCStr())
                ));
        }

        AS3toPrecision(ti, vm, coerced_this, result, argc, argv);
//##protect##"InstanceTraits::toPrecisionProto()"
    }
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits

namespace Classes { namespace fl
{
    const ThunkInfo uint::ti[uint::ThunkInfoNum] = {
        {&InstanceTraits::fl::uint::toStringProto, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {&InstanceTraits::fl::uint::toLocaleStringProto, &AS3::fl::StringTI, "toLocaleString", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {&InstanceTraits::fl::uint::valueOfProto, &AS3::fl::uintTI, "valueOf", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {&InstanceTraits::fl::uint::toExponentialProto, &AS3::fl::StringTI, "toExponential", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {&InstanceTraits::fl::uint::toFixedProto, &AS3::fl::StringTI, "toFixed", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {&InstanceTraits::fl::uint::toPrecisionProto, &AS3::fl::StringTI, "toPrecision", NULL, Abc::NS_Public, CT_Method, 0, 1},
    };

    uint::uint(ClassTraits::Traits& t)
    : Class(t)
    , MIN_VALUE(0)
    , MAX_VALUE(0xffffffff)
    {
//##protect##"class_::uint::uint()"
//##protect##"class_::uint::uint()"
    }

    void uint::InitPrototype(AS3::Object& obj) const
    {
        if (GetParentClass())
            GetParentClass()->InitPrototype(obj);

        for (unsigned i = 0; i < NUMBEROF(ti); ++i)
            AddDynamicFunc(obj, ti[i]);
        AddConstructor(obj);
    }
//##protect##"class_$methods"
    void uint::Call(const Value& /*_this*/, Value& result, unsigned argc, const Value* const argv)
    {
        // The same logic as in Construct.
        Construct(result, argc, argv);
    }

    void uint::Construct(Value& result, unsigned argc, const Value* argv, bool /*extCall*/)
    {
        if (argc > 0)
        {
            UInt32 v;
            if (argv[0].Convert2UInt32(v))
                result.SetUInt32(v);
        }
        else
            result.SetUInt32(0);
    }
    
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl
{
    const MemberInfo uint::mi[uint::MemberInfoNum] = {
        {"MIN_VALUE", NULL, OFFSETOF(Classes::fl::uint, MIN_VALUE), Abc::NS_Public, SlotInfo::BT_UInt, 1},
        {"MAX_VALUE", NULL, OFFSETOF(Classes::fl::uint, MAX_VALUE), Abc::NS_Public, SlotInfo::BT_UInt, 1},
    };

    uint::uint(VM& vm)
    : Traits(vm, AS3::fl::uintCI)
    {
//##protect##"ClassTraits::uint::uint()"
        SetTraitsType(Traits_UInt);
//##protect##"ClassTraits::uint::uint()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::uint(vm, AS3::fl::uintCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl::uint(*this));

    }

    Pickable<Traits> uint::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) uint(vm));
    }
//##protect##"ClassTraits$methods"
    bool uint::Coerce(const Value& value, Value& result) const
    {
        return CoerceValue(value, result);
    }
    bool uint::CoerceValue(const Value& value, Value& result) const
    {
        UInt32 r;

        if (value.Convert2UInt32(r))
        {
            result.SetUInt32(r);
            return true;
        }

        return false;
    }
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl
{
    const TypeInfo uintTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "uint", "", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo uintCI = {
        &uintTI,
        ClassTraits::fl::uint::MakeClassTraits,
        0,
        ClassTraits::fl::uint::MemberInfoNum,
        InstanceTraits::fl::uint::ThunkInfoNum,
        0,
        NULL,
        ClassTraits::fl::uint::mi,
        InstanceTraits::fl::uint::ti,
        NULL,
    };
}; // namespace fl


}}} // namespace Scaleform { namespace GFx { namespace AS3

