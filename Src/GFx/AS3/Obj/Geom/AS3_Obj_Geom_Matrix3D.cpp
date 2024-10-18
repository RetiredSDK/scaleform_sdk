//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_Matrix3D.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Geom_Matrix3D.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Geom_Vector3D.h"
#include "../Vec/AS3_Obj_Vec_Vector_double.h"
#include "../Vec/AS3_Obj_Vec_Vector_object.h"
#include "../../AS3_MovieRoot.h"
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
    ASString GetMethodDefArg<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_decompose, 0, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("eulerAngles");
    }

    template <>
    SF_INLINE
    ASString GetMethodDefArg<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_recompose, 1, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("eulerAngles");
    }

} // namespace Impl
typedef ThunkFunc0<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_determinantGet, Value::Number> TFunc_Instances_Matrix3D_determinantGet;
typedef ThunkFunc0<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_positionGet, SPtr<Instances::fl_geom::Vector3D> > TFunc_Instances_Matrix3D_positionGet;
typedef ThunkFunc1<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_positionSet, const Value, Instances::fl_geom::Vector3D*> TFunc_Instances_Matrix3D_positionSet;
typedef ThunkFunc0<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_rawDataGet, SPtr<Instances::fl_vec::Vector_double> > TFunc_Instances_Matrix3D_rawDataGet;
typedef ThunkFunc1<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_rawDataSet, const Value, Instances::fl_vec::Vector_double*> TFunc_Instances_Matrix3D_rawDataSet;
typedef ThunkFunc1<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_append, const Value, Instances::fl_geom::Matrix3D*> TFunc_Instances_Matrix3D_append;
typedef ThunkFunc3<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_appendRotation, const Value, Value::Number, Instances::fl_geom::Vector3D*, Instances::fl_geom::Vector3D*> TFunc_Instances_Matrix3D_appendRotation;
typedef ThunkFunc3<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_appendScale, const Value, Value::Number, Value::Number, Value::Number> TFunc_Instances_Matrix3D_appendScale;
typedef ThunkFunc3<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_appendTranslation, const Value, Value::Number, Value::Number, Value::Number> TFunc_Instances_Matrix3D_appendTranslation;
typedef ThunkFunc0<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_clone, SPtr<Instances::fl_geom::Matrix3D> > TFunc_Instances_Matrix3D_clone;
typedef ThunkFunc1<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_decompose, SPtr<Instances::fl_vec::Vector_object>, const ASString&> TFunc_Instances_Matrix3D_decompose;
typedef ThunkFunc1<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_deltaTransformVector, SPtr<Instances::fl_geom::Vector3D>, Instances::fl_geom::Vector3D*> TFunc_Instances_Matrix3D_deltaTransformVector;
typedef ThunkFunc0<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_identity, const Value> TFunc_Instances_Matrix3D_identity;
typedef ThunkFunc3<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_interpolate, SPtr<Instances::fl_geom::Matrix3D>, Instances::fl_geom::Matrix3D*, Instances::fl_geom::Matrix3D*, Value::Number> TFunc_Instances_Matrix3D_interpolate;
typedef ThunkFunc2<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_interpolateTo, const Value, Instances::fl_geom::Matrix3D*, Value::Number> TFunc_Instances_Matrix3D_interpolateTo;
typedef ThunkFunc0<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_invert, bool> TFunc_Instances_Matrix3D_invert;
typedef ThunkFunc3<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_pointAt, const Value, Instances::fl_geom::Vector3D*, Instances::fl_geom::Vector3D*, Instances::fl_geom::Vector3D*> TFunc_Instances_Matrix3D_pointAt;
typedef ThunkFunc1<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_prepend, const Value, Instances::fl_geom::Matrix3D*> TFunc_Instances_Matrix3D_prepend;
typedef ThunkFunc3<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_prependRotation, const Value, Value::Number, Instances::fl_geom::Vector3D*, Instances::fl_geom::Vector3D*> TFunc_Instances_Matrix3D_prependRotation;
typedef ThunkFunc3<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_prependScale, const Value, Value::Number, Value::Number, Value::Number> TFunc_Instances_Matrix3D_prependScale;
typedef ThunkFunc3<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_prependTranslation, const Value, Value::Number, Value::Number, Value::Number> TFunc_Instances_Matrix3D_prependTranslation;
typedef ThunkFunc2<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_recompose, bool, Instances::fl_vec::Vector_object*, const ASString&> TFunc_Instances_Matrix3D_recompose;
typedef ThunkFunc1<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_transformVector, SPtr<Instances::fl_geom::Vector3D>, Instances::fl_geom::Vector3D*> TFunc_Instances_Matrix3D_transformVector;
typedef ThunkFunc2<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_transformVectors, const Value, Instances::fl_vec::Vector_double*, Instances::fl_vec::Vector_double*> TFunc_Instances_Matrix3D_transformVectors;
typedef ThunkFunc0<Instances::fl_geom::Matrix3D, Instances::fl_geom::Matrix3D::mid_transpose, const Value> TFunc_Instances_Matrix3D_transpose;

template <> const TFunc_Instances_Matrix3D_determinantGet::TMethod TFunc_Instances_Matrix3D_determinantGet::Method = &Instances::fl_geom::Matrix3D::determinantGet;
template <> const TFunc_Instances_Matrix3D_positionGet::TMethod TFunc_Instances_Matrix3D_positionGet::Method = &Instances::fl_geom::Matrix3D::positionGet;
template <> const TFunc_Instances_Matrix3D_positionSet::TMethod TFunc_Instances_Matrix3D_positionSet::Method = &Instances::fl_geom::Matrix3D::positionSet;
template <> const TFunc_Instances_Matrix3D_rawDataGet::TMethod TFunc_Instances_Matrix3D_rawDataGet::Method = &Instances::fl_geom::Matrix3D::rawDataGet;
template <> const TFunc_Instances_Matrix3D_rawDataSet::TMethod TFunc_Instances_Matrix3D_rawDataSet::Method = &Instances::fl_geom::Matrix3D::rawDataSet;
template <> const TFunc_Instances_Matrix3D_append::TMethod TFunc_Instances_Matrix3D_append::Method = &Instances::fl_geom::Matrix3D::append;
template <> const TFunc_Instances_Matrix3D_appendRotation::TMethod TFunc_Instances_Matrix3D_appendRotation::Method = &Instances::fl_geom::Matrix3D::appendRotation;
template <> const TFunc_Instances_Matrix3D_appendScale::TMethod TFunc_Instances_Matrix3D_appendScale::Method = &Instances::fl_geom::Matrix3D::appendScale;
template <> const TFunc_Instances_Matrix3D_appendTranslation::TMethod TFunc_Instances_Matrix3D_appendTranslation::Method = &Instances::fl_geom::Matrix3D::appendTranslation;
template <> const TFunc_Instances_Matrix3D_clone::TMethod TFunc_Instances_Matrix3D_clone::Method = &Instances::fl_geom::Matrix3D::clone;
template <> const TFunc_Instances_Matrix3D_decompose::TMethod TFunc_Instances_Matrix3D_decompose::Method = &Instances::fl_geom::Matrix3D::decompose;
template <> const TFunc_Instances_Matrix3D_deltaTransformVector::TMethod TFunc_Instances_Matrix3D_deltaTransformVector::Method = &Instances::fl_geom::Matrix3D::deltaTransformVector;
template <> const TFunc_Instances_Matrix3D_identity::TMethod TFunc_Instances_Matrix3D_identity::Method = &Instances::fl_geom::Matrix3D::identity;
template <> const TFunc_Instances_Matrix3D_interpolate::TMethod TFunc_Instances_Matrix3D_interpolate::Method = &Instances::fl_geom::Matrix3D::interpolate;
template <> const TFunc_Instances_Matrix3D_interpolateTo::TMethod TFunc_Instances_Matrix3D_interpolateTo::Method = &Instances::fl_geom::Matrix3D::interpolateTo;
template <> const TFunc_Instances_Matrix3D_invert::TMethod TFunc_Instances_Matrix3D_invert::Method = &Instances::fl_geom::Matrix3D::invert;
template <> const TFunc_Instances_Matrix3D_pointAt::TMethod TFunc_Instances_Matrix3D_pointAt::Method = &Instances::fl_geom::Matrix3D::pointAt;
template <> const TFunc_Instances_Matrix3D_prepend::TMethod TFunc_Instances_Matrix3D_prepend::Method = &Instances::fl_geom::Matrix3D::prepend;
template <> const TFunc_Instances_Matrix3D_prependRotation::TMethod TFunc_Instances_Matrix3D_prependRotation::Method = &Instances::fl_geom::Matrix3D::prependRotation;
template <> const TFunc_Instances_Matrix3D_prependScale::TMethod TFunc_Instances_Matrix3D_prependScale::Method = &Instances::fl_geom::Matrix3D::prependScale;
template <> const TFunc_Instances_Matrix3D_prependTranslation::TMethod TFunc_Instances_Matrix3D_prependTranslation::Method = &Instances::fl_geom::Matrix3D::prependTranslation;
template <> const TFunc_Instances_Matrix3D_recompose::TMethod TFunc_Instances_Matrix3D_recompose::Method = &Instances::fl_geom::Matrix3D::recompose;
template <> const TFunc_Instances_Matrix3D_transformVector::TMethod TFunc_Instances_Matrix3D_transformVector::Method = &Instances::fl_geom::Matrix3D::transformVector;
template <> const TFunc_Instances_Matrix3D_transformVectors::TMethod TFunc_Instances_Matrix3D_transformVectors::Method = &Instances::fl_geom::Matrix3D::transformVectors;
template <> const TFunc_Instances_Matrix3D_transpose::TMethod TFunc_Instances_Matrix3D_transpose::Method = &Instances::fl_geom::Matrix3D::transpose;

namespace Instances { namespace fl_geom
{
    Matrix3D::Matrix3D(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
//##protect##"instance::Matrix3D::Matrix3D()$data"
        ,pDispObj(NULL)
//##protect##"instance::Matrix3D::Matrix3D()$data"
    {
//##protect##"instance::Matrix3D::Matrix3D()$code"
//##protect##"instance::Matrix3D::Matrix3D()$code"
    }

    void Matrix3D::determinantGet(Value::Number& result)
    {
//##protect##"instance::Matrix3D::determinantGet()"
        result = GetMatrix3D().GetDeterminant();
//##protect##"instance::Matrix3D::determinantGet()"
    }
    void Matrix3D::positionGet(SPtr<Instances::fl_geom::Vector3D>& result)
    {
//##protect##"instance::Matrix3D::positionGet()"
        const Matrix4DDouble &m4d = GetMatrix3D();

        Value params[] = { Value(TwipsToPixels(m4d.Tx())), Value(TwipsToPixels(m4d.Ty())), Value(TwipsToPixels(m4d.Tz())), Value(0.) };
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        asvm.ConstructInstance(result, asvm.GetClass("flash.geom.Vector3D", asvm.GetCurrentAppDomain()), 4, params);
//##protect##"instance::Matrix3D::positionGet()"
    }
    void Matrix3D::positionSet(const Value& result, Instances::fl_geom::Vector3D* value)
    {
//##protect##"instance::Matrix3D::positionSet()"
        Value::Number v;
        
        value->xGet(v);
        mat4.Tx() = PixelsToTwips(v);
        
        value->yGet(v);
        mat4.Ty() = PixelsToTwips(v);

        value->zGet(v);
        mat4.Tz() = PixelsToTwips(v);

        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }

        SF_UNUSED(result);
//##protect##"instance::Matrix3D::positionSet()"
    }
    void Matrix3D::rawDataGet(SPtr<Instances::fl_vec::Vector_double>& result)
    {
//##protect##"instance::Matrix3D::rawDataGet()"
        Matrix4DDouble m4d = GetMatrix3D();
        
        // Flash wants pixels, we keep twips
        m4d.Tx() = TwipsToPixels(m4d.Tx());
        m4d.Ty() = TwipsToPixels(m4d.Ty());
        m4d.Tz() = TwipsToPixels(m4d.Tz());

        m4d.Transpose();    // Flash wants it transposed

        Value params[] = { Value(0.) };
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        asvm.ConstructInstance(result, &asvm.GetClassVectorNumber(), 1, params);

        int i;
        for(i=0;i<16;i++)
        {
            Value v(m4d[i]);
            if (!result->Set(i, v, result->GetEnclosedClassTraits()))
                break;
        }
//##protect##"instance::Matrix3D::rawDataGet()"
    }
    void Matrix3D::rawDataSet(const Value& result, Instances::fl_vec::Vector_double* value)
    {
//##protect##"instance::Matrix3D::rawDataSet()"
        if (!value)
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));

        int i;
        for(i=0;i<16;i++)
        {
            Value v;
            value->Get(i, v);
            mat4.Data()[i] = v.AsNumber();
        }

        mat4.Transpose();    // Flash transposes it

        // Flash uses pixels, we use twips
        mat4.Tx() = PixelsToTwips(mat4.Tx());
        mat4.Ty() = PixelsToTwips(mat4.Ty());
        mat4.Tz() = PixelsToTwips(mat4.Tz());

        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }

        SF_UNUSED(result);
//##protect##"instance::Matrix3D::rawDataSet()"
    }
    void Matrix3D::append(const Value& result, Instances::fl_geom::Matrix3D* lhs)
    {
//##protect##"instance::Matrix3D::append()"
        if (!lhs)
        {
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
        }
        mat4.Append(lhs->GetMatrix3D());

        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }

        SF_UNUSED(result);
//##protect##"instance::Matrix3D::append()"
    }
    void Matrix3D::appendRotation(const Value& result, Value::Number degrees, Instances::fl_geom::Vector3D* axis, Instances::fl_geom::Vector3D* pivotPoint)
    {
//##protect##"instance::Matrix3D::appendRotation()"
        Point3<Double> sfaxis;
        sfaxis = axis ? Point3<Double>(axis->x, axis->y, axis->z) : Point3<Double>(0,0,0);

        Point3<Double> sfpivot;
        sfpivot = pivotPoint ? Point3<Double>(pivotPoint->x, pivotPoint->y, pivotPoint->z) : Point3<Double>(0,0,0);

        mat4.Append(Matrix4DDouble::Rotation(SF_DEGTORAD(degrees), sfaxis, sfpivot)); 

        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }
        SF_UNUSED(result);
//##protect##"instance::Matrix3D::appendRotation()"
    }
    void Matrix3D::appendScale(const Value& result, Value::Number xScale, Value::Number yScale, Value::Number zScale)
    {
//##protect##"instance::Matrix3D::appendScale()"
        mat4.Append(Matrix4DDouble::Scaling(xScale, yScale, zScale));

        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }
        SF_UNUSED(result);
//##protect##"instance::Matrix3D::appendScale()"
    }
    void Matrix3D::appendTranslation(const Value& result, Value::Number x, Value::Number y, Value::Number z)
    {
//##protect##"instance::Matrix3D::appendTranslation()"
        mat4.Append(Matrix4DDouble::Translation(x, y, z));

        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }

        SF_UNUSED(result);
//##protect##"instance::Matrix3D::appendTranslation()"
    }
    void Matrix3D::clone(SPtr<Instances::fl_geom::Matrix3D>& result)
    {
//##protect##"instance::Matrix3D::clone()"
        Value args[16];
        int i;
        for(i=0;i<16;i++)
            args[i].SetNumber(mat4[i]);
        GetVM().ConstructBuiltinObject(result, "flash.geom.Matrix3D", 16, args).DoNotCheck();
//##protect##"instance::Matrix3D::clone()"
    }
    void Matrix3D::decompose(SPtr<Instances::fl_vec::Vector_object>& result, const ASString& orientationStyle)
    {
//##protect##"instance::Matrix3D::decompose()"
        SF_UNUSED2(result, orientationStyle);
        NOT_IMPLEMENTED("instance::Matrix3D::decompose() is not implemented yet");
//##protect##"instance::Matrix3D::decompose()"
    }
    void Matrix3D::deltaTransformVector(SPtr<Instances::fl_geom::Vector3D>& result, Instances::fl_geom::Vector3D* v)
    {
//##protect##"instance::Matrix3D::deltaTransformVector()"
        if (!v)
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));

        Point3<Double> pdIn(v->x, v->y, v->z);
        Matrix4DDouble mat4NoTrans = mat4;
        mat4NoTrans.Tx() = 0;
        mat4NoTrans.Ty() = 0;
        mat4NoTrans.Tz() = 0;
        Point3<Double> pdOut = mat4NoTrans.Transform(pdIn);

        InstanceTraits::fl_geom::Vector3D& itr = static_cast<InstanceTraits::fl_geom::Vector3D&>(v->GetInstanceTraits());
        Pickable<Instances::fl_geom::Vector3D> r = itr.MakeInstance(itr);

        r->x = pdOut.x;
        r->y = pdOut.y;
        r->z = pdOut.z;

        result = r;
//##protect##"instance::Matrix3D::deltaTransformVector()"
    }
    void Matrix3D::identity(const Value& result)
    {
//##protect##"instance::Matrix3D::identity()"
        mat4.SetIdentity();

        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }

        SF_UNUSED(result);
//##protect##"instance::Matrix3D::identity()"
    }
    void Matrix3D::interpolate(SPtr<Instances::fl_geom::Matrix3D>& result, Instances::fl_geom::Matrix3D* thisMat, Instances::fl_geom::Matrix3D* toMat, Value::Number percent)
    {
//##protect##"instance::Matrix3D::interpolate()"
        SF_UNUSED4(result, thisMat, toMat, percent);
        NOT_IMPLEMENTED("instance::Matrix3D::interpolate() is not implemented yet");
//##protect##"instance::Matrix3D::interpolate()"
    }
    void Matrix3D::interpolateTo(const Value& result, Instances::fl_geom::Matrix3D* toMat, Value::Number percent)
    {
//##protect##"instance::Matrix3D::interpolateTo()"
        SF_UNUSED3(result, toMat, percent);
        NOT_IMPLEMENTED("instance::Matrix3D::interpolateTo() is not implemented yet");
//##protect##"instance::Matrix3D::interpolateTo()"
    }
    void Matrix3D::invert(bool& result)
    {
//##protect##"instance::Matrix3D::invert()"
        mat4.Invert();
        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }

        result = true;
//##protect##"instance::Matrix3D::invert()"
    }
    void Matrix3D::pointAt(const Value& result, Instances::fl_geom::Vector3D* pos, Instances::fl_geom::Vector3D* at, Instances::fl_geom::Vector3D* up)
    {
//##protect##"instance::Matrix3D::pointAt()"
        if (!pos)
        {
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
        }

        Point3<Double> posd(pos->x, pos->y, pos->z);
        Point3<Double> atd = at ? Point3<Double>(at->x, at->y, at->z) : Point3<Double>(0,1,0);
        Point3<Double> upd = up ? Point3<Double>(up->x, up->y, up->z) : Point3<Double>(0,0,1);

        mat4.ViewRH(posd, atd, upd);
        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }
        SF_UNUSED(result);            
//##protect##"instance::Matrix3D::pointAt()"
    }
    void Matrix3D::prepend(const Value& result, Instances::fl_geom::Matrix3D* rhs)
    {
//##protect##"instance::Matrix3D::prepend()"
        if (!rhs)
        {
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
        }
        mat4.Prepend(rhs->GetMatrix3D());

        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }

        SF_UNUSED(result);
//##protect##"instance::Matrix3D::prepend()"
    }
    void Matrix3D::prependRotation(const Value& result, Value::Number degrees, Instances::fl_geom::Vector3D* axis, Instances::fl_geom::Vector3D* pivotPoint)
    {
//##protect##"instance::Matrix3D::prependRotation()"
        Point3<Double> sfaxis;
        sfaxis = axis ? Point3<Double>(axis->x, axis->y, axis->z) : Point3<Double>(0,0,0);

        Point3<Double> sfpivot;
        sfpivot = pivotPoint ? Point3<Double>(pivotPoint->x, pivotPoint->y, pivotPoint->z) : Point3<Double>(0,0,0);

        mat4.Prepend(Matrix4DDouble::Rotation(SF_DEGTORAD(degrees), sfaxis, sfpivot)); 

        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }
        SF_UNUSED(result);
//##protect##"instance::Matrix3D::prependRotation()"
    }
    void Matrix3D::prependScale(const Value& result, Value::Number xScale, Value::Number yScale, Value::Number zScale)
    {
//##protect##"instance::Matrix3D::prependScale()"
        mat4.Prepend(Matrix4DDouble::Scaling(xScale, yScale, zScale));

        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }

        SF_UNUSED(result);
//##protect##"instance::Matrix3D::prependScale()"
    }
    void Matrix3D::prependTranslation(const Value& result, Value::Number x, Value::Number y, Value::Number z)
    {
//##protect##"instance::Matrix3D::prependTranslation()"
        mat4.Prepend(Matrix4DDouble::Translation(x, y, z));

        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }

        SF_UNUSED(result);
//##protect##"instance::Matrix3D::prependTranslation()"
    }
    void Matrix3D::recompose(bool& result, Instances::fl_vec::Vector_object* components, const ASString& orientationStyle)
    {
//##protect##"instance::Matrix3D::recompose()"
        SF_UNUSED3(result, components, orientationStyle);
        NOT_IMPLEMENTED("instance::Matrix3D::recompose() is not implemented yet");
//##protect##"instance::Matrix3D::recompose()"
    }
    void Matrix3D::transformVector(SPtr<Instances::fl_geom::Vector3D>& result, Instances::fl_geom::Vector3D* v)
    {
//##protect##"instance::Matrix3D::transformVector()"

        if (!v)
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));

        Point3<Double> pdIn(v->x, v->y, v->z);
        Point3<Double> pdOut = mat4.Transform(pdIn);

        InstanceTraits::fl_geom::Vector3D& itr = static_cast<InstanceTraits::fl_geom::Vector3D&>(v->GetInstanceTraits());
        Pickable<Instances::fl_geom::Vector3D> r = itr.MakeInstance(itr);

        r->x = pdOut.x;
        r->y = pdOut.y;
        r->z = pdOut.z;

        result = r;
//##protect##"instance::Matrix3D::transformVector()"
    }
    void Matrix3D::transformVectors(const Value& result, Instances::fl_vec::Vector_double* vin, Instances::fl_vec::Vector_double* vout)
    {
//##protect##"instance::Matrix3D::transformVectors()"
        int i;
        Value v1, v2, v3;
        UInt32 sz;
        vin->lengthGet(sz);
        Value::Number n1, n2, n3;
        const ClassTraits::Traits &tr = vout->GetEnclosedClassTraits();
        for(i=0;i<(int)sz; i+=3)
        {
            vin->Get(i, v1);
            if (!v1.Convert2Number(n1))
                n1 = 0;

            vin->Get(i+1, v2);
            if (!v2.Convert2Number(n2))
                n2 = 0;

            vin->Get(i+2, v3);
            if (!v3.Convert2Number(n3))
                n3 = 0;

            Point3<Double> pdIn(n1, n2, n3);
            Point3<Double> pdOut = mat4.Transform(pdIn);

            vout->Set(i, Value(pdOut.x), tr).DoNotCheck();
            vout->Set(i+1, Value(pdOut.y), tr).DoNotCheck();
            vout->Set(i+2, Value(pdOut.z), tr).DoNotCheck();
        }
        SF_UNUSED(result);
//##protect##"instance::Matrix3D::transformVectors()"
    }
    void Matrix3D::transpose(const Value& result)
    {
//##protect##"instance::Matrix3D::transpose()"
        mat4.Transpose();

        if (pDispObj)
        {
            Matrix3F m(mat4);
            pDispObj->SetMatrix3D(m);
        }

        SF_UNUSED(result);
//##protect##"instance::Matrix3D::transpose()"
    }

    SPtr<Instances::fl_geom::Vector3D> Matrix3D::positionGet()
    {
        SPtr<Instances::fl_geom::Vector3D> result;
        positionGet(result);
        return result;
    }
    SPtr<Instances::fl_vec::Vector_double> Matrix3D::rawDataGet()
    {
        SPtr<Instances::fl_vec::Vector_double> result;
        rawDataGet(result);
        return result;
    }
    SPtr<Instances::fl_vec::Vector_object> Matrix3D::decompose(const ASString& orientationStyle)
    {
        SPtr<Instances::fl_vec::Vector_object> result;
        decompose(result, orientationStyle);
        return result;
    }
    SPtr<Instances::fl_geom::Vector3D> Matrix3D::deltaTransformVector(Instances::fl_geom::Vector3D* v)
    {
        SPtr<Instances::fl_geom::Vector3D> result;
        deltaTransformVector(result, v);
        return result;
    }
    SPtr<Instances::fl_geom::Vector3D> Matrix3D::transformVector(Instances::fl_geom::Vector3D* v)
    {
        SPtr<Instances::fl_geom::Vector3D> result;
        transformVector(result, v);
        return result;
    }
//##protect##"instance$methods"

    Matrix4F Matrix3D::GetMatrix3DF() const
    {
        Matrix4F m;
        int i;
        for(i=0;i<16;i++)
            m.Data()[i] = (float)mat4[i];
        return m;
    }

    void Matrix3D::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc == 16)
        {
            int i;
            for(i=0;i<16;i++)
                mat4.Data()[i] = argv[i];        // data should already be in GFx format
        }
        else
        if (argc == 1)
        {
            if (!argv[0].IsObject() || !(argv[0].GetObject()->GetName() == "Vector$double"))
                return;
            Instances::fl_vec::Vector_double* vec = static_cast<Instances::fl_vec::Vector_double*>(argv[0].GetObject());

            int i;
            for(i=0;i<16;i++)
            {
                Value v;
                vec->Get(i, v);
                mat4.Data()[i] = v;
            }
            mat4.Transpose();    // store the matrix in GFx format

            if (pDispObj)
            {
                Matrix3F m(mat4);
                pDispObj->SetMatrix3D(m);
            }

        }

    }
    //##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_geom
{
    const ThunkInfo Matrix3D::ti[Matrix3D::ThunkInfoNum] = {
        {TFunc_Instances_Matrix3D_determinantGet::Func, &AS3::fl::NumberTI, "determinant", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Matrix3D_positionGet::Func, &AS3::fl_geom::Vector3DTI, "position", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Matrix3D_positionSet::Func, NULL, "position", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_Matrix3D_rawDataGet::Func, NULL, "rawData", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Matrix3D_rawDataSet::Func, NULL, "rawData", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_Matrix3D_append::Func, NULL, "append", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_Matrix3D_appendRotation::Func, NULL, "appendRotation", NULL, Abc::NS_Public, CT_Method, 2, 3},
        {TFunc_Instances_Matrix3D_appendScale::Func, NULL, "appendScale", NULL, Abc::NS_Public, CT_Method, 3, 3},
        {TFunc_Instances_Matrix3D_appendTranslation::Func, NULL, "appendTranslation", NULL, Abc::NS_Public, CT_Method, 3, 3},
        {TFunc_Instances_Matrix3D_clone::Func, &AS3::fl_geom::Matrix3DTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Matrix3D_decompose::Func, NULL, "decompose", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {TFunc_Instances_Matrix3D_deltaTransformVector::Func, &AS3::fl_geom::Vector3DTI, "deltaTransformVector", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_Matrix3D_identity::Func, NULL, "identity", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Matrix3D_interpolate::Func, &AS3::fl_geom::Matrix3DTI, "interpolate", NULL, Abc::NS_Public, CT_Method, 3, 3},
        {TFunc_Instances_Matrix3D_interpolateTo::Func, NULL, "interpolateTo", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Instances_Matrix3D_invert::Func, &AS3::fl::BooleanTI, "invert", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Matrix3D_pointAt::Func, NULL, "pointAt", NULL, Abc::NS_Public, CT_Method, 1, 3},
        {TFunc_Instances_Matrix3D_prepend::Func, NULL, "prepend", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_Matrix3D_prependRotation::Func, NULL, "prependRotation", NULL, Abc::NS_Public, CT_Method, 2, 3},
        {TFunc_Instances_Matrix3D_prependScale::Func, NULL, "prependScale", NULL, Abc::NS_Public, CT_Method, 3, 3},
        {TFunc_Instances_Matrix3D_prependTranslation::Func, NULL, "prependTranslation", NULL, Abc::NS_Public, CT_Method, 3, 3},
        {TFunc_Instances_Matrix3D_recompose::Func, &AS3::fl::BooleanTI, "recompose", NULL, Abc::NS_Public, CT_Method, 1, 2},
        {TFunc_Instances_Matrix3D_transformVector::Func, &AS3::fl_geom::Vector3DTI, "transformVector", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_Matrix3D_transformVectors::Func, NULL, "transformVectors", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Instances_Matrix3D_transpose::Func, NULL, "transpose", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

    Matrix3D::Matrix3D(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::Matrix3D::Matrix3D()"
//##protect##"InstanceTraits::Matrix3D::Matrix3D()"
        SetMemSize(sizeof(Instances::fl_geom::Matrix3D));

    }

    void Matrix3D::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<Matrix3D&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_geom
{
    Matrix3D::Matrix3D(VM& vm)
    : Traits(vm, AS3::fl_geom::Matrix3DCI)
    {
//##protect##"ClassTraits::Matrix3D::Matrix3D()"
//##protect##"ClassTraits::Matrix3D::Matrix3D()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_geom::Matrix3D(vm, AS3::fl_geom::Matrix3DCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> Matrix3D::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Matrix3D(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_geom
{
    const TypeInfo Matrix3DTI = {
        TypeInfo::CompileTime,
        "Matrix3D", "flash.geom", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo Matrix3DCI = {
        &Matrix3DTI,
        ClassTraits::fl_geom::Matrix3D::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_geom::Matrix3D::ThunkInfoNum,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_geom::Matrix3D::ti,
        NULL,
    };
}; // namespace fl_geom


}}} // namespace Scaleform { namespace GFx { namespace AS3

