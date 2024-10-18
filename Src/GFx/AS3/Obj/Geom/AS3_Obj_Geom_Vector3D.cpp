//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_Vector3D.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Geom_Vector3D.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
	bool compareTol(Value::Number a, Value::Number b, Value::Number tol)
	{
		Value::Number diff = a-b;
		if (diff<0)
			diff = -diff;
		return (diff<tol);
	}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_lengthGet, Value::Number> TFunc_Instances_Vector3D_lengthGet;
typedef ThunkFunc0<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_lengthSquaredGet, Value::Number> TFunc_Instances_Vector3D_lengthSquaredGet;
typedef ThunkFunc1<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_xSet, const Value, Value::Number> TFunc_Instances_Vector3D_xSet;
typedef ThunkFunc0<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_xGet, Value::Number> TFunc_Instances_Vector3D_xGet;
typedef ThunkFunc1<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_ySet, const Value, Value::Number> TFunc_Instances_Vector3D_ySet;
typedef ThunkFunc0<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_yGet, Value::Number> TFunc_Instances_Vector3D_yGet;
typedef ThunkFunc1<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_zSet, const Value, Value::Number> TFunc_Instances_Vector3D_zSet;
typedef ThunkFunc0<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_zGet, Value::Number> TFunc_Instances_Vector3D_zGet;
typedef ThunkFunc1<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_wSet, const Value, Value::Number> TFunc_Instances_Vector3D_wSet;
typedef ThunkFunc0<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_wGet, Value::Number> TFunc_Instances_Vector3D_wGet;
typedef ThunkFunc1<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_add, SPtr<Instances::fl_geom::Vector3D>, Instances::fl_geom::Vector3D*> TFunc_Instances_Vector3D_add;
typedef ThunkFunc0<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_clone, SPtr<Instances::fl_geom::Vector3D> > TFunc_Instances_Vector3D_clone;
typedef ThunkFunc1<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_crossProduct, SPtr<Instances::fl_geom::Vector3D>, Instances::fl_geom::Vector3D*> TFunc_Instances_Vector3D_crossProduct;
typedef ThunkFunc1<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_decrementBy, const Value, Instances::fl_geom::Vector3D*> TFunc_Instances_Vector3D_decrementBy;
typedef ThunkFunc1<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_dotProduct, Value::Number, Instances::fl_geom::Vector3D*> TFunc_Instances_Vector3D_dotProduct;
typedef ThunkFunc2<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_equals, bool, Instances::fl_geom::Vector3D*, bool> TFunc_Instances_Vector3D_equals;
typedef ThunkFunc1<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_incrementBy, const Value, Instances::fl_geom::Vector3D*> TFunc_Instances_Vector3D_incrementBy;
typedef ThunkFunc3<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_nearEquals, bool, Instances::fl_geom::Vector3D*, Value::Number, bool> TFunc_Instances_Vector3D_nearEquals;
typedef ThunkFunc0<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_negate, const Value> TFunc_Instances_Vector3D_negate;
typedef ThunkFunc0<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_normalize, Value::Number> TFunc_Instances_Vector3D_normalize;
typedef ThunkFunc0<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_project, const Value> TFunc_Instances_Vector3D_project;
typedef ThunkFunc1<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_scaleBy, const Value, Value::Number> TFunc_Instances_Vector3D_scaleBy;
typedef ThunkFunc1<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_subtract, SPtr<Instances::fl_geom::Vector3D>, Instances::fl_geom::Vector3D*> TFunc_Instances_Vector3D_subtract;
typedef ThunkFunc0<Instances::fl_geom::Vector3D, Instances::fl_geom::Vector3D::mid_toString, ASString> TFunc_Instances_Vector3D_toString;

template <> const TFunc_Instances_Vector3D_lengthGet::TMethod TFunc_Instances_Vector3D_lengthGet::Method = &Instances::fl_geom::Vector3D::lengthGet;
template <> const TFunc_Instances_Vector3D_lengthSquaredGet::TMethod TFunc_Instances_Vector3D_lengthSquaredGet::Method = &Instances::fl_geom::Vector3D::lengthSquaredGet;
template <> const TFunc_Instances_Vector3D_xSet::TMethod TFunc_Instances_Vector3D_xSet::Method = &Instances::fl_geom::Vector3D::xSet;
template <> const TFunc_Instances_Vector3D_xGet::TMethod TFunc_Instances_Vector3D_xGet::Method = &Instances::fl_geom::Vector3D::xGet;
template <> const TFunc_Instances_Vector3D_ySet::TMethod TFunc_Instances_Vector3D_ySet::Method = &Instances::fl_geom::Vector3D::ySet;
template <> const TFunc_Instances_Vector3D_yGet::TMethod TFunc_Instances_Vector3D_yGet::Method = &Instances::fl_geom::Vector3D::yGet;
template <> const TFunc_Instances_Vector3D_zSet::TMethod TFunc_Instances_Vector3D_zSet::Method = &Instances::fl_geom::Vector3D::zSet;
template <> const TFunc_Instances_Vector3D_zGet::TMethod TFunc_Instances_Vector3D_zGet::Method = &Instances::fl_geom::Vector3D::zGet;
template <> const TFunc_Instances_Vector3D_wSet::TMethod TFunc_Instances_Vector3D_wSet::Method = &Instances::fl_geom::Vector3D::wSet;
template <> const TFunc_Instances_Vector3D_wGet::TMethod TFunc_Instances_Vector3D_wGet::Method = &Instances::fl_geom::Vector3D::wGet;
template <> const TFunc_Instances_Vector3D_add::TMethod TFunc_Instances_Vector3D_add::Method = &Instances::fl_geom::Vector3D::add;
template <> const TFunc_Instances_Vector3D_clone::TMethod TFunc_Instances_Vector3D_clone::Method = &Instances::fl_geom::Vector3D::clone;
template <> const TFunc_Instances_Vector3D_crossProduct::TMethod TFunc_Instances_Vector3D_crossProduct::Method = &Instances::fl_geom::Vector3D::crossProduct;
template <> const TFunc_Instances_Vector3D_decrementBy::TMethod TFunc_Instances_Vector3D_decrementBy::Method = &Instances::fl_geom::Vector3D::decrementBy;
template <> const TFunc_Instances_Vector3D_dotProduct::TMethod TFunc_Instances_Vector3D_dotProduct::Method = &Instances::fl_geom::Vector3D::dotProduct;
template <> const TFunc_Instances_Vector3D_equals::TMethod TFunc_Instances_Vector3D_equals::Method = &Instances::fl_geom::Vector3D::equals;
template <> const TFunc_Instances_Vector3D_incrementBy::TMethod TFunc_Instances_Vector3D_incrementBy::Method = &Instances::fl_geom::Vector3D::incrementBy;
template <> const TFunc_Instances_Vector3D_nearEquals::TMethod TFunc_Instances_Vector3D_nearEquals::Method = &Instances::fl_geom::Vector3D::nearEquals;
template <> const TFunc_Instances_Vector3D_negate::TMethod TFunc_Instances_Vector3D_negate::Method = &Instances::fl_geom::Vector3D::negate;
template <> const TFunc_Instances_Vector3D_normalize::TMethod TFunc_Instances_Vector3D_normalize::Method = &Instances::fl_geom::Vector3D::normalize;
template <> const TFunc_Instances_Vector3D_project::TMethod TFunc_Instances_Vector3D_project::Method = &Instances::fl_geom::Vector3D::project;
template <> const TFunc_Instances_Vector3D_scaleBy::TMethod TFunc_Instances_Vector3D_scaleBy::Method = &Instances::fl_geom::Vector3D::scaleBy;
template <> const TFunc_Instances_Vector3D_subtract::TMethod TFunc_Instances_Vector3D_subtract::Method = &Instances::fl_geom::Vector3D::subtract;
template <> const TFunc_Instances_Vector3D_toString::TMethod TFunc_Instances_Vector3D_toString::Method = &Instances::fl_geom::Vector3D::toString;

namespace Instances { namespace fl_geom
{
    Vector3D::Vector3D(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
//##protect##"instance::Vector3D::Vector3D()$data"
    , x()
    , y()
    , z()
    , w()
//##protect##"instance::Vector3D::Vector3D()$data"
    {
//##protect##"instance::Vector3D::Vector3D()$code"
//##protect##"instance::Vector3D::Vector3D()$code"
    }

    void Vector3D::lengthGet(Value::Number& result)
    {
//##protect##"instance::Vector3D::lengthGet()"
        result = sqrt(x*x + y*y + z*z);
//##protect##"instance::Vector3D::lengthGet()"
    }
    void Vector3D::lengthSquaredGet(Value::Number& result)
    {
//##protect##"instance::Vector3D::lengthSquaredGet()"
        result = (x*x + y*y + z*z);
//##protect##"instance::Vector3D::lengthSquaredGet()"
    }
    void Vector3D::xSet(const Value& result, Value::Number value)
    {
//##protect##"instance::Vector3D::xSet()"
        SF_UNUSED1(result);
        x = value;
//##protect##"instance::Vector3D::xSet()"
    }
    void Vector3D::xGet(Value::Number& result)
    {
//##protect##"instance::Vector3D::xGet()"
        result = x;
//##protect##"instance::Vector3D::xGet()"
    }
    void Vector3D::ySet(const Value& result, Value::Number value)
    {
//##protect##"instance::Vector3D::ySet()"
        SF_UNUSED1(result);
        y = value;
//##protect##"instance::Vector3D::ySet()"
    }
    void Vector3D::yGet(Value::Number& result)
    {
//##protect##"instance::Vector3D::yGet()"
        result = y;
//##protect##"instance::Vector3D::yGet()"
    }
    void Vector3D::zSet(const Value& result, Value::Number value)
    {
//##protect##"instance::Vector3D::zSet()"
        SF_UNUSED1(result);
        z = value;
//##protect##"instance::Vector3D::zSet()"
    }
    void Vector3D::zGet(Value::Number& result)
    {
//##protect##"instance::Vector3D::zGet()"
        result = z;
//##protect##"instance::Vector3D::zGet()"
    }
    void Vector3D::wSet(const Value& result, Value::Number value)
    {
//##protect##"instance::Vector3D::wSet()"
        SF_UNUSED1(result);
        w = value;
//##protect##"instance::Vector3D::wSet()"
    }
    void Vector3D::wGet(Value::Number& result)
    {
//##protect##"instance::Vector3D::wGet()"
		result = w;
//##protect##"instance::Vector3D::wGet()"
    }
    void Vector3D::add(SPtr<Instances::fl_geom::Vector3D>& result, Instances::fl_geom::Vector3D* v)
    {
//##protect##"instance::Vector3D::add()"
		if (!v)
			return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));

        InstanceTraits::fl_geom::Vector3D& itr = static_cast<InstanceTraits::fl_geom::Vector3D&>(GetInstanceTraits());
        Pickable<Instances::fl_geom::Vector3D> r = itr.MakeInstance(itr);

        r->x = x + v->x;
        r->y = y + v->y;
        r->z = z + v->z;

        result = r;
//##protect##"instance::Vector3D::add()"
    }
    void Vector3D::clone(SPtr<Instances::fl_geom::Vector3D>& result)
    {
//##protect##"instance::Vector3D::clone()"
		Value args[] = {Value(x), Value(y), Value(z), Value(w)};
		GetVM().ConstructBuiltinObject(result, "flash.geom.Vector3D", 4, args).DoNotCheck();
//##protect##"instance::Vector3D::clone()"
    }
    void Vector3D::crossProduct(SPtr<Instances::fl_geom::Vector3D>& result, Instances::fl_geom::Vector3D* v)
    {
//##protect##"instance::Vector3D::crossProduct()"
		if (!v)
		{
			return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}

#if 0
        Value::Number tx = (y*v->z - z*v->y);
        Value::Number ty = (z*v->x - x*v->z);
        Value::Number tz = (x*v->y - y*v->x);		

		Value args[] = {Value(tx), Value(ty), Value(tz)};
		// ConstructBuiltinValue is not compared to anything. Safe since this is the last 
		// line in the code.  by calling DoNotCheck, we avoid throwing an exception if the return value of 
		GetVM().ConstructBuiltinValue(result, "flash.geom.Vector3D", 3, args).DoNotCheck();
#else
        InstanceTraits::fl_geom::Vector3D& itr = static_cast<InstanceTraits::fl_geom::Vector3D&>(GetInstanceTraits());
        Pickable<Instances::fl_geom::Vector3D> r = itr.MakeInstance(itr);

        Value::Number tx = (y*v->z - z*v->y);
        Value::Number ty = (z*v->x - x*v->z);
        Value::Number tz = (x*v->y - y*v->x);		

        r->x = tx;
        r->y = ty;
        r->z = tz;

        result = r;
#endif
//##protect##"instance::Vector3D::crossProduct()"
    }
    void Vector3D::decrementBy(const Value& result, Instances::fl_geom::Vector3D* v)
    {
//##protect##"instance::Vector3D::decrementBy()"
        SF_UNUSED1(result);

		if (!v)
		{
			return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}

		x -= v->x;
		y -= v->y;
		z -= v->z;
//##protect##"instance::Vector3D::decrementBy()"
    }
    void Vector3D::dotProduct(Value::Number& result, Instances::fl_geom::Vector3D* a)
    {
//##protect##"instance::Vector3D::dotProduct()"
		if (!a)
		{
			return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}

		result = x*a->x + y*a->y + z*a->z;
//##protect##"instance::Vector3D::dotProduct()"
    }
    void Vector3D::equals(bool& result, Instances::fl_geom::Vector3D* toCompare, bool allFour)
    {
//##protect##"instance::Vector3D::equals()"
		if (!toCompare)
		{
			return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
		result  = (x==toCompare->x && y==toCompare->y && z==toCompare->z);
		if (allFour)
			result = result && (w==toCompare->w);
//##protect##"instance::Vector3D::equals()"
    }
    void Vector3D::incrementBy(const Value& result, Instances::fl_geom::Vector3D* v)
    {
//##protect##"instance::Vector3D::incrementBy()"
        SF_UNUSED1(result);
		if (!v)
		{
			return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}

		x += v->x;
		y += v->y;
		z += v->z;
//##protect##"instance::Vector3D::incrementBy()"
    }
    void Vector3D::nearEquals(bool& result, Instances::fl_geom::Vector3D* toCompare, Value::Number tolerance, bool allFour)
    {
//##protect##"instance::Vector3D::nearEquals()"
		if (!toCompare)
		{
			return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}

		result  = ( compareTol(x, toCompare->x, tolerance) && compareTol(y, toCompare->y, tolerance) && compareTol(z, toCompare->z, tolerance) );
		if (allFour)
			result = result && (compareTol(w, toCompare->w, tolerance));
//##protect##"instance::Vector3D::nearEquals()"
    }
    void Vector3D::negate(const Value& result)
    {
//##protect##"instance::Vector3D::negate()"
        SF_UNUSED1(result);
		x = -x;
		y = -y;
		z = -z;
//##protect##"instance::Vector3D::negate()"
    }
    void Vector3D::normalize(Value::Number& result)
    {
//##protect##"instance::Vector3D::normalize()"
		lengthGet(result);
		x /= result;
		y /= result;
		z /= result;
//##protect##"instance::Vector3D::normalize()"
    }
    void Vector3D::project(const Value& result)
    {
//##protect##"instance::Vector3D::project()"
        SF_UNUSED1(result);
		x/=w;
		y/=w;
		z/=w;
//##protect##"instance::Vector3D::project()"
    }
    void Vector3D::scaleBy(const Value& result, Value::Number s)
    {
//##protect##"instance::Vector3D::scaleBy()"
        SF_UNUSED1(result);
		x *= s;
		y *= s;
		z *= s;
//##protect##"instance::Vector3D::scaleBy()"
    }
    void Vector3D::subtract(SPtr<Instances::fl_geom::Vector3D>& result, Instances::fl_geom::Vector3D* v)
    {
//##protect##"instance::Vector3D::subtract()"
		if (!v)
		{
			return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}

#if 0
		Value args[] = {Value(x - v->x), Value(y - v->y), Value(z - v->z)};
		// ConstructBuiltinValue is not compared to anything. Safe since this is the last 
		// line in the code.  by calling DoNotCheck, we avoid throwing an exception if the return value of 
		GetVM().ConstructBuiltinValue(result, "flash.geom.Vector3D", 3, args).DoNotCheck();
#else
        InstanceTraits::fl_geom::Vector3D& itr = static_cast<InstanceTraits::fl_geom::Vector3D&>(GetInstanceTraits());
        Pickable<Instances::fl_geom::Vector3D> r = itr.MakeInstance(itr);

        r->x = x - v->x;
        r->y = y - v->y;
        r->z = z - v->z;

        result = r;
#endif
//##protect##"instance::Vector3D::subtract()"
    }
    void Vector3D::toString(ASString& result)
    {
//##protect##"instance::Vector3D::toString()"
        VM& vm = GetVM();

		result += "(x=" + vm.AsString(Value(x)) + 
			", y=" + 
			vm.AsString(Value(y)) +
			", z=" + 
			vm.AsString(Value(z)) +
			")";
//##protect##"instance::Vector3D::toString()"
    }

//##protect##"instance$methods"
	void Vector3D::AS3Constructor(unsigned argc, const Value* argv)
	{

		if (argc > 0)
		{
			// According to doc, x will not be modified if there is an exception
			if (!argv[0].Convert2Number(x))
			{
				return;
			}
			if (argc > 1)
			{
				if (!argv[1].Convert2Number(y))
				{
					return;
				}
				if (argc > 2)
				{
					if (!argv[2].Convert2Number(z))
					{
						return;
					}
					if (argc > 3)
					{
						if (!argv[3].Convert2Number(w))
						{
							return;
						}
					}
				}
			}
		}
	}

//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_geom
{
    const ThunkInfo Vector3D::ti[Vector3D::ThunkInfoNum] = {
        {TFunc_Instances_Vector3D_lengthGet::Func, &AS3::fl::NumberTI, "length", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Vector3D_lengthSquaredGet::Func, &AS3::fl::NumberTI, "lengthSquared", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Vector3D_xSet::Func, NULL, "x", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_Vector3D_xGet::Func, &AS3::fl::NumberTI, "x", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Vector3D_ySet::Func, NULL, "y", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_Vector3D_yGet::Func, &AS3::fl::NumberTI, "y", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Vector3D_zSet::Func, NULL, "z", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_Vector3D_zGet::Func, &AS3::fl::NumberTI, "z", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Vector3D_wSet::Func, NULL, "w", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_Vector3D_wGet::Func, &AS3::fl::NumberTI, "w", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Vector3D_add::Func, &AS3::fl_geom::Vector3DTI, "add", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_Vector3D_clone::Func, &AS3::fl_geom::Vector3DTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Vector3D_crossProduct::Func, &AS3::fl_geom::Vector3DTI, "crossProduct", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_Vector3D_decrementBy::Func, NULL, "decrementBy", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_Vector3D_dotProduct::Func, &AS3::fl::NumberTI, "dotProduct", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_Vector3D_equals::Func, &AS3::fl::BooleanTI, "equals", NULL, Abc::NS_Public, CT_Method, 1, 2},
        {TFunc_Instances_Vector3D_incrementBy::Func, NULL, "incrementBy", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_Vector3D_nearEquals::Func, &AS3::fl::BooleanTI, "nearEquals", NULL, Abc::NS_Public, CT_Method, 2, 3},
        {TFunc_Instances_Vector3D_negate::Func, NULL, "negate", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Vector3D_normalize::Func, &AS3::fl::NumberTI, "normalize", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Vector3D_project::Func, NULL, "project", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Vector3D_scaleBy::Func, NULL, "scaleBy", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_Vector3D_subtract::Func, &AS3::fl_geom::Vector3DTI, "subtract", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_Vector3D_toString::Func, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

    Vector3D::Vector3D(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::Vector3D::Vector3D()"
//##protect##"InstanceTraits::Vector3D::Vector3D()"
        SetMemSize(sizeof(Instances::fl_geom::Vector3D));

    }

    void Vector3D::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<Vector3D&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits

namespace Classes { namespace fl_geom
{
    Vector3D::Vector3D(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Vector3D::Vector3D()"
        InstanceTraits::fl_geom::Vector3D& itr = static_cast<InstanceTraits::fl_geom::Vector3D&>(GetClassTraits().GetInstanceTraits());

        X_AXIS = itr.MakeInstance(itr);
        Y_AXIS = itr.MakeInstance(itr);
        Z_AXIS = itr.MakeInstance(itr);

        X_AXIS->x = 1.0;
        Y_AXIS->y = 1.0;
        Z_AXIS->z = 1.0;
//##protect##"class_::Vector3D::Vector3D()"
    }
    void Vector3D::angleBetween(Value::Number& result, Instances::fl_geom::Vector3D* a, Instances::fl_geom::Vector3D* b)
    {
//##protect##"class_::Vector3D::angleBetween()"
		Value::Number dot = a->x*b->x + a->y*b->y + a->z*b->z;
		Value::Number aLen = sqrt(a->x*a->x + a->y*a->y + a->z*a->z);
		Value::Number bLen = sqrt(b->x*b->x + b->y*b->y + b->z*b->z);
		result = MakeValueNumber(acos(dot/(aLen*bLen)));
//##protect##"class_::Vector3D::angleBetween()"
    }
    void Vector3D::distance(Value::Number& result, Instances::fl_geom::Vector3D* pt1, Instances::fl_geom::Vector3D* pt2)
    {
//##protect##"class_::Vector3D::distance()"
		result = MakeValueNumber(sqrt(
			(pt1->GetX() - pt2->GetX())*(pt1->GetX() - pt2->GetX()) + 
			(pt1->GetY() - pt2->GetY())*(pt1->GetY() - pt2->GetY()) + 
			(pt1->GetZ() - pt2->GetZ())*(pt1->GetZ() - pt2->GetZ())
			));
//##protect##"class_::Vector3D::distance()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes

typedef ThunkFunc2<Classes::fl_geom::Vector3D, Classes::fl_geom::Vector3D::mid_angleBetween, Value::Number, Instances::fl_geom::Vector3D*, Instances::fl_geom::Vector3D*> TFunc_Classes_Vector3D_angleBetween;
typedef ThunkFunc2<Classes::fl_geom::Vector3D, Classes::fl_geom::Vector3D::mid_distance, Value::Number, Instances::fl_geom::Vector3D*, Instances::fl_geom::Vector3D*> TFunc_Classes_Vector3D_distance;

template <> const TFunc_Classes_Vector3D_angleBetween::TMethod TFunc_Classes_Vector3D_angleBetween::Method = &Classes::fl_geom::Vector3D::angleBetween;
template <> const TFunc_Classes_Vector3D_distance::TMethod TFunc_Classes_Vector3D_distance::Method = &Classes::fl_geom::Vector3D::distance;

namespace ClassTraits { namespace fl_geom
{
    const MemberInfo Vector3D::mi[Vector3D::MemberInfoNum] = {
        {"X_AXIS", NULL, OFFSETOF(Classes::fl_geom::Vector3D, X_AXIS), Abc::NS_Public, SlotInfo::BT_ObjectCpp, 1},
        {"Y_AXIS", NULL, OFFSETOF(Classes::fl_geom::Vector3D, Y_AXIS), Abc::NS_Public, SlotInfo::BT_ObjectCpp, 1},
        {"Z_AXIS", NULL, OFFSETOF(Classes::fl_geom::Vector3D, Z_AXIS), Abc::NS_Public, SlotInfo::BT_ObjectCpp, 1},
    };

    const ThunkInfo Vector3D::ti[Vector3D::ThunkInfoNum] = {
        {TFunc_Classes_Vector3D_angleBetween::Func, &AS3::fl::NumberTI, "angleBetween", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Classes_Vector3D_distance::Func, &AS3::fl::NumberTI, "distance", NULL, Abc::NS_Public, CT_Method, 2, 2},
    };
    Vector3D::Vector3D(VM& vm)
    : Traits(vm, AS3::fl_geom::Vector3DCI)
    {
//##protect##"ClassTraits::Vector3D::Vector3D()"
//##protect##"ClassTraits::Vector3D::Vector3D()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_geom::Vector3D(vm, AS3::fl_geom::Vector3DCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_geom::Vector3D(*this));

    }

    Pickable<Traits> Vector3D::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Vector3D(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_geom
{
    const TypeInfo Vector3DTI = {
        TypeInfo::CompileTime,
        "Vector3D", "flash.geom", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo Vector3DCI = {
        &Vector3DTI,
        ClassTraits::fl_geom::Vector3D::MakeClassTraits,
        ClassTraits::fl_geom::Vector3D::ThunkInfoNum,
        ClassTraits::fl_geom::Vector3D::MemberInfoNum,
        InstanceTraits::fl_geom::Vector3D::ThunkInfoNum,
        0,
        ClassTraits::fl_geom::Vector3D::ti,
        ClassTraits::fl_geom::Vector3D::mi,
        InstanceTraits::fl_geom::Vector3D::ti,
        NULL,
    };
}; // namespace fl_geom


}}} // namespace Scaleform { namespace GFx { namespace AS3

