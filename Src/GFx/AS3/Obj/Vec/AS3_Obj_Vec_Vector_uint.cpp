//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Vec_Vector_uint.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Vec_Vector_uint.h"
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

    template <>
    SF_INLINE
    ASString GetMethodDefArg<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3join, 0, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString(",");
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3every, 1, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3forEach, 1, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3map, 1, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3some, 1, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3filter, 1, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    SInt32 GetMethodDefArg<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3lastIndexOf, 1, SInt32>(AS3::StringManager&)
    {
        return 0x7fffffff;
    }

} // namespace Impl
typedef ThunkFunc0<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_lengthGet, UInt32> TFunc_Instances_Vector_uint_lengthGet;
typedef ThunkFunc1<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_lengthSet, const Value, UInt32> TFunc_Instances_Vector_uint_lengthSet;
typedef ThunkFunc1<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_fixedSet, const Value, bool> TFunc_Instances_Vector_uint_fixedSet;
typedef ThunkFunc0<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_fixedGet, bool> TFunc_Instances_Vector_uint_fixedGet;
typedef ThunkFunc0<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3toString, ASString> TFunc_Instances_Vector_uint_AS3toString;
typedef ThunkFunc0<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3toLocaleString, ASString> TFunc_Instances_Vector_uint_AS3toLocaleString;
typedef ThunkFunc1<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3join, ASString, const ASString&> TFunc_Instances_Vector_uint_AS3join;
typedef ThunkFunc2<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3every, bool, const Value&, const Value&> TFunc_Instances_Vector_uint_AS3every;
typedef ThunkFunc2<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3forEach, const Value, const Value&, const Value&> TFunc_Instances_Vector_uint_AS3forEach;
typedef ThunkFunc2<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3map, SPtr<Instances::fl_vec::Vector_uint>, const Value&, const Value&> TFunc_Instances_Vector_uint_AS3map;
typedef ThunkFunc2<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3push, Value, unsigned, const Value*> TFunc_Instances_Vector_uint_AS3push;
typedef ThunkFunc2<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3some, bool, const Value&, const Value&> TFunc_Instances_Vector_uint_AS3some;
typedef ThunkFunc2<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3unshift, Value, unsigned, const Value*> TFunc_Instances_Vector_uint_AS3unshift;
typedef ThunkFunc2<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3concat, Value, unsigned, const Value*> TFunc_Instances_Vector_uint_AS3concat;
typedef ThunkFunc2<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3filter, SPtr<Instances::fl_vec::Vector_uint>, const Value&, const Value&> TFunc_Instances_Vector_uint_AS3filter;
typedef ThunkFunc0<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3pop, UInt32> TFunc_Instances_Vector_uint_AS3pop;
typedef ThunkFunc0<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3reverse, SPtr<Instances::fl_vec::Vector_uint> > TFunc_Instances_Vector_uint_AS3reverse;
typedef ThunkFunc0<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3shift, UInt32> TFunc_Instances_Vector_uint_AS3shift;
typedef ThunkFunc2<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3slice, Value, unsigned, const Value*> TFunc_Instances_Vector_uint_AS3slice;
typedef ThunkFunc2<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3sort, Value, unsigned, const Value*> TFunc_Instances_Vector_uint_AS3sort;
typedef ThunkFunc2<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3splice, Value, unsigned, const Value*> TFunc_Instances_Vector_uint_AS3splice;
typedef ThunkFunc2<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3indexOf, SInt32, UInt32, SInt32> TFunc_Instances_Vector_uint_AS3indexOf;
typedef ThunkFunc2<Instances::fl_vec::Vector_uint, Instances::fl_vec::Vector_uint::mid_AS3lastIndexOf, SInt32, UInt32, SInt32> TFunc_Instances_Vector_uint_AS3lastIndexOf;

template <> const TFunc_Instances_Vector_uint_lengthGet::TMethod TFunc_Instances_Vector_uint_lengthGet::Method = &Instances::fl_vec::Vector_uint::lengthGet;
template <> const TFunc_Instances_Vector_uint_lengthSet::TMethod TFunc_Instances_Vector_uint_lengthSet::Method = &Instances::fl_vec::Vector_uint::lengthSet;
template <> const TFunc_Instances_Vector_uint_fixedSet::TMethod TFunc_Instances_Vector_uint_fixedSet::Method = &Instances::fl_vec::Vector_uint::fixedSet;
template <> const TFunc_Instances_Vector_uint_fixedGet::TMethod TFunc_Instances_Vector_uint_fixedGet::Method = &Instances::fl_vec::Vector_uint::fixedGet;
template <> const TFunc_Instances_Vector_uint_AS3toString::TMethod TFunc_Instances_Vector_uint_AS3toString::Method = &Instances::fl_vec::Vector_uint::AS3toString;
template <> const TFunc_Instances_Vector_uint_AS3toLocaleString::TMethod TFunc_Instances_Vector_uint_AS3toLocaleString::Method = &Instances::fl_vec::Vector_uint::AS3toLocaleString;
template <> const TFunc_Instances_Vector_uint_AS3join::TMethod TFunc_Instances_Vector_uint_AS3join::Method = &Instances::fl_vec::Vector_uint::AS3join;
template <> const TFunc_Instances_Vector_uint_AS3every::TMethod TFunc_Instances_Vector_uint_AS3every::Method = &Instances::fl_vec::Vector_uint::AS3every;
template <> const TFunc_Instances_Vector_uint_AS3forEach::TMethod TFunc_Instances_Vector_uint_AS3forEach::Method = &Instances::fl_vec::Vector_uint::AS3forEach;
template <> const TFunc_Instances_Vector_uint_AS3map::TMethod TFunc_Instances_Vector_uint_AS3map::Method = &Instances::fl_vec::Vector_uint::AS3map;
template <> const TFunc_Instances_Vector_uint_AS3push::TMethod TFunc_Instances_Vector_uint_AS3push::Method = &Instances::fl_vec::Vector_uint::AS3push;
template <> const TFunc_Instances_Vector_uint_AS3some::TMethod TFunc_Instances_Vector_uint_AS3some::Method = &Instances::fl_vec::Vector_uint::AS3some;
template <> const TFunc_Instances_Vector_uint_AS3unshift::TMethod TFunc_Instances_Vector_uint_AS3unshift::Method = &Instances::fl_vec::Vector_uint::AS3unshift;
template <> const TFunc_Instances_Vector_uint_AS3concat::TMethod TFunc_Instances_Vector_uint_AS3concat::Method = &Instances::fl_vec::Vector_uint::AS3concat;
template <> const TFunc_Instances_Vector_uint_AS3filter::TMethod TFunc_Instances_Vector_uint_AS3filter::Method = &Instances::fl_vec::Vector_uint::AS3filter;
template <> const TFunc_Instances_Vector_uint_AS3pop::TMethod TFunc_Instances_Vector_uint_AS3pop::Method = &Instances::fl_vec::Vector_uint::AS3pop;
template <> const TFunc_Instances_Vector_uint_AS3reverse::TMethod TFunc_Instances_Vector_uint_AS3reverse::Method = &Instances::fl_vec::Vector_uint::AS3reverse;
template <> const TFunc_Instances_Vector_uint_AS3shift::TMethod TFunc_Instances_Vector_uint_AS3shift::Method = &Instances::fl_vec::Vector_uint::AS3shift;
template <> const TFunc_Instances_Vector_uint_AS3slice::TMethod TFunc_Instances_Vector_uint_AS3slice::Method = &Instances::fl_vec::Vector_uint::AS3slice;
template <> const TFunc_Instances_Vector_uint_AS3sort::TMethod TFunc_Instances_Vector_uint_AS3sort::Method = &Instances::fl_vec::Vector_uint::AS3sort;
template <> const TFunc_Instances_Vector_uint_AS3splice::TMethod TFunc_Instances_Vector_uint_AS3splice::Method = &Instances::fl_vec::Vector_uint::AS3splice;
template <> const TFunc_Instances_Vector_uint_AS3indexOf::TMethod TFunc_Instances_Vector_uint_AS3indexOf::Method = &Instances::fl_vec::Vector_uint::AS3indexOf;
template <> const TFunc_Instances_Vector_uint_AS3lastIndexOf::TMethod TFunc_Instances_Vector_uint_AS3lastIndexOf::Method = &Instances::fl_vec::Vector_uint::AS3lastIndexOf;

namespace Instances { namespace fl_vec
{
    Vector_uint::Vector_uint(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
//##protect##"instance::Vector_uint::Vector_uint()$data"
    , V(t.GetVM().GetMemoryHeap(), t.GetVM())
//##protect##"instance::Vector_uint::Vector_uint()$data"
    {
//##protect##"instance::Vector_uint::Vector_uint()$code"
//##protect##"instance::Vector_uint::Vector_uint()$code"
    }

    void Vector_uint::lengthGet(UInt32& result)
    {
//##protect##"instance::Vector_uint::lengthGet()"
        result = static_cast<UInt32>(V.GetSize());
//##protect##"instance::Vector_uint::lengthGet()"
    }
    void Vector_uint::lengthSet(const Value& result, UInt32 value)
    {
//##protect##"instance::Vector_uint::lengthSet()"
        SF_UNUSED1(result);
        V.Resize(value).DoNotCheck();
//##protect##"instance::Vector_uint::lengthSet()"
    }
    void Vector_uint::fixedSet(const Value& result, bool f)
    {
//##protect##"instance::Vector_uint::fixedSet()"
        SF_UNUSED1(result);
        V.SetFixed(f);
//##protect##"instance::Vector_uint::fixedSet()"
    }
    void Vector_uint::fixedGet(bool& result)
    {
//##protect##"instance::Vector_uint::fixedGet()"
        result = V.GetFixed();
//##protect##"instance::Vector_uint::fixedGet()"
    }
    void Vector_uint::AS3toString(ASString& result)
    {
//##protect##"instance::Vector_uint::AS3toString()"
        result = V.ToString(GetVM().GetStringManager().GetBuiltin(AS3Builtin_comma));
//##protect##"instance::Vector_uint::AS3toString()"
    }
    void Vector_uint::AS3toLocaleString(ASString& result)
    {
//##protect##"instance::Vector_uint::AS3toLocaleString()"
        AS3toString(result);
//##protect##"instance::Vector_uint::AS3toLocaleString()"
    }
    void Vector_uint::AS3join(ASString& result, const ASString& separator)
    {
//##protect##"instance::Vector_uint::AS3join()"
        result = V.ToString(separator);
//##protect##"instance::Vector_uint::AS3join()"
    }
    void Vector_uint::AS3every(bool& result, const Value& checker, const Value& thisObj)
    {
//##protect##"instance::Vector_uint::AS3every()"
        result = V.Every(checker, thisObj, *this);
//##protect##"instance::Vector_uint::AS3every()"
    }
    void Vector_uint::AS3forEach(const Value& result, const Value& eacher, const Value& thisObj)
    {
//##protect##"instance::Vector_uint::AS3forEach()"
        SF_UNUSED1(result);
        V.ForEach(eacher, thisObj, *this);
//##protect##"instance::Vector_uint::AS3forEach()"
    }
    void Vector_uint::AS3map(SPtr<Instances::fl_vec::Vector_uint>& result, const Value& mapper, const Value& thisObj)
    {
//##protect##"instance::Vector_uint::AS3map()"
        V.Map(result, mapper, thisObj, this);
//##protect##"instance::Vector_uint::AS3map()"
    }
    void Vector_uint::AS3push(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::Vector_uint::AS3push()"
        V.PushBack(argc, argv, GetEnclosedClassTraits());
        result.SetUInt32(static_cast<UInt32>(V.GetSize()));
//##protect##"instance::Vector_uint::AS3push()"
    }
    void Vector_uint::AS3some(bool& result, const Value& checker, const Value& thisObj)
    {
//##protect##"instance::Vector_uint::AS3some()"
        result = V.Some(checker, thisObj, *this);
//##protect##"instance::Vector_uint::AS3some()"
    }
    void Vector_uint::AS3unshift(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::Vector_uint::AS3unshift()"
        V.Unshift(argc, argv, GetEnclosedClassTraits());
        result.SetUInt32(static_cast<UInt32>(V.GetSize()));
//##protect##"instance::Vector_uint::AS3unshift()"
    }
    void Vector_uint::AS3concat(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::Vector_uint::AS3concat()"
        V.Concat(result, argc, argv, *this);
//##protect##"instance::Vector_uint::AS3concat()"
    }
    void Vector_uint::AS3filter(SPtr<Instances::fl_vec::Vector_uint>& result, const Value& checker, const Value& thisObj)
    {
//##protect##"instance::Vector_uint::AS3filter()"
        V.Filter(result, checker, thisObj, *this);
//##protect##"instance::Vector_uint::AS3filter()"
    }
    void Vector_uint::AS3pop(UInt32& result)
    {
//##protect##"instance::Vector_uint::AS3pop()"
        V.Pop(result);
//##protect##"instance::Vector_uint::AS3pop()"
    }
    void Vector_uint::AS3reverse(SPtr<Instances::fl_vec::Vector_uint>& result)
    {
//##protect##"instance::Vector_uint::AS3reverse()"
        V.Reverse();
        result = this;
//##protect##"instance::Vector_uint::AS3reverse()"
    }
    void Vector_uint::AS3shift(UInt32& result)
    {
//##protect##"instance::Vector_uint::AS3shift()"
        V.Shift(result);
//##protect##"instance::Vector_uint::AS3shift()"
    }
    void Vector_uint::AS3slice(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::Vector_uint::AS3slice()"
        V.Slice(result, argc, argv, *this);
//##protect##"instance::Vector_uint::AS3slice()"
    }
    void Vector_uint::AS3sort(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::Vector_uint::AS3sort()"
        if (argc < 1 || argv[0].IsNullOrUndefined() || !argv[0].IsCallable())
        {
            VM& vm = GetVM();
            return vm.ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, vm 
                SF_DEBUG_ARG((argc > 0) ? vm.GetValueTraits(argv[0]).GetName().ToCStr() : "undefined")
                SF_DEBUG_ARG(this->GetEnclosedClassTraits().GetName().ToCStr())
                ));
        }

        V.Sort(result, argc, argv, *this);
//##protect##"instance::Vector_uint::AS3sort()"
    }
    void Vector_uint::AS3splice(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::Vector_uint::AS3splice()"
        V.Splice(result, argc, argv, *this);
//##protect##"instance::Vector_uint::AS3splice()"
    }
    void Vector_uint::AS3indexOf(SInt32& result, UInt32 value, SInt32 from)
    {
//##protect##"instance::Vector_uint::AS3indexOf()"
        V.IndexOf(result, value, from);
//##protect##"instance::Vector_uint::AS3indexOf()"
    }
    void Vector_uint::AS3lastIndexOf(SInt32& result, UInt32 value, SInt32 from)
    {
//##protect##"instance::Vector_uint::AS3lastIndexOf()"
        V.LastIndexOf(result, value, from);
//##protect##"instance::Vector_uint::AS3lastIndexOf()"
    }

//##protect##"instance$methods"
    void Vector_uint::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc > 0)
        {
            UInt32 length;
            if (!argv[0].Convert2UInt32(length))
                return;

            if (!V.Resize(length))
                return;
        }

        if (argc > 1)
        {
            V.SetFixed(argv[1].Convert2Boolean());
        }
    }

    void Vector_uint::GetNextPropertyName(Value& name, GlobalSlotIndex ind) const
    {
        if (!ind.IsValid())
            return name.SetUndefined();

        name.SetUInt32(static_cast<UInt32>(AbsoluteIndex(ind).Get()));
    }

    GlobalSlotIndex Vector_uint::GetNextDynPropIndex(GlobalSlotIndex ind) const
    {
        GlobalSlotIndex gind(0);
        const AbsoluteIndex aind = GetNextArrayIndex(AbsoluteIndex(ind));

        if (aind.IsValid())
            gind = GlobalSlotIndex(aind);

        return gind;
    }

    CheckResult Vector_uint::SetProperty(const Multiname& prop_name, const Value& value)
    {
        UInt32 ind;
        if (GetVectorInd(prop_name, ind))
            return Set(ind, value, GetEnclosedClassTraits());

        // Not an Array index. Let us treat it as a regular object.
        return Instances::fl::Object::SetProperty(prop_name, value);
    }

    CheckResult Vector_uint::GetProperty(const Multiname& prop_name, Value& value)
    {
        UInt32 ind;
        if (GetVectorInd(prop_name, ind))
        {
            if (ind < V.GetSize())
            {
                Get(ind, value);
                return true;
            }

            VM& vm = GetVM();
            vm.ThrowRangeError(VM::Error(VM::eOutOfRangeError, vm
                SF_DEBUG_ARG(ind)
                SF_DEBUG_ARG(V.GetSize())
                ));

            return false;
        }

        // Not an Array index. Let us treat it as a regular object.
        return Instances::fl::Object::GetProperty(prop_name, value);
    }

    void Vector_uint::GetDynamicProperty(AbsoluteIndex ind, Value& value)
    {
        V.GetValue(ind.Get(), value);
    }

    CheckResult Vector_uint::DeleteProperty(const Multiname& prop_name)
    {
        UInt32 ind;
        if (GetVectorInd(prop_name, ind))
            return RemoveAt(ind);

        // Not an Array index. Let us treat it as a regular object.
        return Instances::fl::Object::DeleteProperty(prop_name);
    }
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_vec
{
    const ThunkInfo Vector_uint::ti[Vector_uint::ThunkInfoNum] = {
        {TFunc_Instances_Vector_uint_lengthGet::Func, &AS3::fl::uintTI, "length", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Vector_uint_lengthSet::Func, NULL, "length", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_Vector_uint_fixedSet::Func, NULL, "fixed", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_Vector_uint_fixedGet::Func, &AS3::fl::BooleanTI, "fixed", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Vector_uint_AS3toString::Func, &AS3::fl::StringTI, "toString", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Vector_uint_AS3toLocaleString::Func, &AS3::fl::StringTI, "toLocaleString", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Vector_uint_AS3join::Func, &AS3::fl::StringTI, "join", NS_AS3, Abc::NS_Public, CT_Method, 0, 1},
        {TFunc_Instances_Vector_uint_AS3every::Func, &AS3::fl::BooleanTI, "every", NS_AS3, Abc::NS_Public, CT_Method, 1, 2},
        {TFunc_Instances_Vector_uint_AS3forEach::Func, NULL, "forEach", NS_AS3, Abc::NS_Public, CT_Method, 1, 2},
        {TFunc_Instances_Vector_uint_AS3map::Func, NULL, "map", NS_AS3, Abc::NS_Public, CT_Method, 1, 2},
        {TFunc_Instances_Vector_uint_AS3push::Func, &AS3::fl::uintTI, "push", NS_AS3, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {TFunc_Instances_Vector_uint_AS3some::Func, &AS3::fl::BooleanTI, "some", NS_AS3, Abc::NS_Public, CT_Method, 1, 2},
        {TFunc_Instances_Vector_uint_AS3unshift::Func, &AS3::fl::uintTI, "unshift", NS_AS3, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {TFunc_Instances_Vector_uint_AS3concat::Func, NULL, "concat", NS_AS3, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {TFunc_Instances_Vector_uint_AS3filter::Func, NULL, "filter", NS_AS3, Abc::NS_Public, CT_Method, 1, 2},
        {TFunc_Instances_Vector_uint_AS3pop::Func, &AS3::fl::uintTI, "pop", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Vector_uint_AS3reverse::Func, NULL, "reverse", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Vector_uint_AS3shift::Func, &AS3::fl::uintTI, "shift", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Vector_uint_AS3slice::Func, NULL, "slice", NS_AS3, Abc::NS_Public, CT_Method, 0, 2},
        {TFunc_Instances_Vector_uint_AS3sort::Func, NULL, "sort", NS_AS3, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {TFunc_Instances_Vector_uint_AS3splice::Func, NULL, "splice", NS_AS3, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {TFunc_Instances_Vector_uint_AS3indexOf::Func, &AS3::fl::int_TI, "indexOf", NS_AS3, Abc::NS_Public, CT_Method, 1, 2},
        {TFunc_Instances_Vector_uint_AS3lastIndexOf::Func, &AS3::fl::int_TI, "lastIndexOf", NS_AS3, Abc::NS_Public, CT_Method, 1, 2},
    };

    Vector_uint::Vector_uint(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::Vector_uint::Vector_uint()"
        SetArrayLike();
//##protect##"InstanceTraits::Vector_uint::Vector_uint()"
        SetMemSize(sizeof(Instances::fl_vec::Vector_uint));

    }

    void Vector_uint::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<Vector_uint&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits

namespace Classes { namespace fl_vec
{
    Vector_uint::Vector_uint(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Vector_uint::Vector_uint()"
//##protect##"class_::Vector_uint::Vector_uint()"
    }
//##protect##"class_$methods"
    void Vector_uint::Call(const Value& /*_this*/, Value& result, unsigned argc, const Value* const argv)
    {
        if (argc == 1)
        {
            const Value& value = argv[0];

            if (value.IsNullOrUndefined())
            {
                result = value;
                return;
            }

            InstanceTraits::fl_vec::Vector_uint& itr = static_cast<InstanceTraits::fl_vec::Vector_uint&>(GetClassTraits().GetInstanceTraits());
            const Traits& value_tr = GetVM().GetValueTraits(value);

            // Class Vector.<X> is final. 
            if (&value_tr == &itr)
            {
                result = value;
                return;
            }

            SPtr<Instances::fl_vec::Vector_uint> vstr(itr.MakeInstance(itr));

            if (vstr->AppendCoerce(value))
                result = vstr;
            else
                GetVM().ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, GetVM()
                SF_DEBUG_ARG(value)
                SF_DEBUG_ARG(itr.GetName().ToCStr())
                ));
        }
        else
            return GetVM().ThrowRangeError(VM::Error(VM::eCoerceArgumentCountError, GetVM() SF_DEBUG_ARG(argc)));
    }
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_vec
{
    Vector_uint::Vector_uint(VM& vm)
    : Traits(vm, AS3::fl_vec::Vector_uintCI)
    {
//##protect##"ClassTraits::Vector_uint::Vector_uint()"
//##protect##"ClassTraits::Vector_uint::Vector_uint()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_vec::Vector_uint(vm, AS3::fl_vec::Vector_uintCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_vec::Vector_uint(*this));

    }

    Pickable<Traits> Vector_uint::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Vector_uint(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_vec
{
    const TypeInfo Vector_uintTI = {
        TypeInfo::CompileTime | TypeInfo::DynamicObject | TypeInfo::Final,
        "Vector$uint", "__AS3__.vec", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo Vector_uintCI = {
        &Vector_uintTI,
        ClassTraits::fl_vec::Vector_uint::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_vec::Vector_uint::ThunkInfoNum,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_vec::Vector_uint::ti,
        NULL,
    };
}; // namespace fl_vec


}}} // namespace Scaleform { namespace GFx { namespace AS3

