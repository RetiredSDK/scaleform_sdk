//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_PerspectiveProjection.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Geom_PerspectiveProjection.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Geom_Point.h"
#include "AS3_Obj_Geom_Matrix3D.h"
#include "GFx/GFx_PlayerImpl.h"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class Matrix3D;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::fl_geom::PerspectiveProjection, Instances::fl_geom::PerspectiveProjection::mid_projectionCenterGet, SPtr<Instances::fl_geom::Point> > TFunc_Instances_PerspectiveProjection_projectionCenterGet;
typedef ThunkFunc1<Instances::fl_geom::PerspectiveProjection, Instances::fl_geom::PerspectiveProjection::mid_projectionCenterSet, const Value, Instances::fl_geom::Point*> TFunc_Instances_PerspectiveProjection_projectionCenterSet;
typedef ThunkFunc0<Instances::fl_geom::PerspectiveProjection, Instances::fl_geom::PerspectiveProjection::mid_focalLengthGet, Value::Number> TFunc_Instances_PerspectiveProjection_focalLengthGet;
typedef ThunkFunc1<Instances::fl_geom::PerspectiveProjection, Instances::fl_geom::PerspectiveProjection::mid_focalLengthSet, const Value, Value::Number> TFunc_Instances_PerspectiveProjection_focalLengthSet;
typedef ThunkFunc0<Instances::fl_geom::PerspectiveProjection, Instances::fl_geom::PerspectiveProjection::mid_fieldOfViewGet, Value::Number> TFunc_Instances_PerspectiveProjection_fieldOfViewGet;
typedef ThunkFunc1<Instances::fl_geom::PerspectiveProjection, Instances::fl_geom::PerspectiveProjection::mid_fieldOfViewSet, const Value, Value::Number> TFunc_Instances_PerspectiveProjection_fieldOfViewSet;
typedef ThunkFunc0<Instances::fl_geom::PerspectiveProjection, Instances::fl_geom::PerspectiveProjection::mid_toMatrix3D, SPtr<Instances::fl_geom::Matrix3D> > TFunc_Instances_PerspectiveProjection_toMatrix3D;

template <> const TFunc_Instances_PerspectiveProjection_projectionCenterGet::TMethod TFunc_Instances_PerspectiveProjection_projectionCenterGet::Method = &Instances::fl_geom::PerspectiveProjection::projectionCenterGet;
template <> const TFunc_Instances_PerspectiveProjection_projectionCenterSet::TMethod TFunc_Instances_PerspectiveProjection_projectionCenterSet::Method = &Instances::fl_geom::PerspectiveProjection::projectionCenterSet;
template <> const TFunc_Instances_PerspectiveProjection_focalLengthGet::TMethod TFunc_Instances_PerspectiveProjection_focalLengthGet::Method = &Instances::fl_geom::PerspectiveProjection::focalLengthGet;
template <> const TFunc_Instances_PerspectiveProjection_focalLengthSet::TMethod TFunc_Instances_PerspectiveProjection_focalLengthSet::Method = &Instances::fl_geom::PerspectiveProjection::focalLengthSet;
template <> const TFunc_Instances_PerspectiveProjection_fieldOfViewGet::TMethod TFunc_Instances_PerspectiveProjection_fieldOfViewGet::Method = &Instances::fl_geom::PerspectiveProjection::fieldOfViewGet;
template <> const TFunc_Instances_PerspectiveProjection_fieldOfViewSet::TMethod TFunc_Instances_PerspectiveProjection_fieldOfViewSet::Method = &Instances::fl_geom::PerspectiveProjection::fieldOfViewSet;
template <> const TFunc_Instances_PerspectiveProjection_toMatrix3D::TMethod TFunc_Instances_PerspectiveProjection_toMatrix3D::Method = &Instances::fl_geom::PerspectiveProjection::toMatrix3D;

namespace Instances { namespace fl_geom
{
    PerspectiveProjection::PerspectiveProjection(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
//##protect##"instance::PerspectiveProjection::PerspectiveProjection()$data"
    , focalLength(0)
    , fieldOfView(0)
    , pDispObj(NULL)
//##protect##"instance::PerspectiveProjection::PerspectiveProjection()$data"
    {
//##protect##"instance::PerspectiveProjection::PerspectiveProjection()$code"
        
        // set AS3 defaults
        projectionCenter.x = DEFAULT_STAGE_WIDTH/2.f;
        projectionCenter.y = DEFAULT_STAGE_WIDTH/2.f;

        fieldOfView = DEFAULT_FLASH_FOV;
        focalLength = CalculateFocalLength(DEFAULT_STAGE_WIDTH);
//##protect##"instance::PerspectiveProjection::PerspectiveProjection()$code"
    }

    void PerspectiveProjection::projectionCenterGet(SPtr<Instances::fl_geom::Point>& result)
    {
//##protect##"instance::PerspectiveProjection::projectionCenterGet()"
        Value params[] = { Value(projectionCenter.x), Value(projectionCenter.y) };
        Value r;
        static_cast<ASVM&>(GetVM()).PointClass->Construct(r, 2, params, true);
        result = static_cast<Instances::fl_geom::Point*>(r.GetObject());
//##protect##"instance::PerspectiveProjection::projectionCenterGet()"
    }
    void PerspectiveProjection::projectionCenterSet(const Value& result, Instances::fl_geom::Point* value)
    {
//##protect##"instance::PerspectiveProjection::projectionCenterSet()"
        SF_UNUSED1(result);
        projectionCenter.x = (float)value->x;
        projectionCenter.y = (float)value->y;
        if (pDispObj)
            pDispObj->SetProjectionCenter(PixelsToTwips(projectionCenter));
//##protect##"instance::PerspectiveProjection::projectionCenterSet()"
    }
    void PerspectiveProjection::focalLengthGet(Value::Number& result)
    {
//##protect##"instance::PerspectiveProjection::focalLengthGet()"
        result = focalLength;
//##protect##"instance::PerspectiveProjection::focalLengthGet()"
    }
    void PerspectiveProjection::focalLengthSet(const Value& result, Value::Number value)
    {
//##protect##"instance::PerspectiveProjection::focalLengthSet()"
        SF_UNUSED1(result);
        focalLength = (float)value;

        // Must recompute the field of view, as it is linked to the focal length.
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        // always use actual stage width for focalLength calc (whether root or stage not)
        float stageWidth = asvm.GetMovieImpl()->GetVisibleFrameRect().Width();
        fieldOfView = CalculateFOV(stageWidth);
        if (pDispObj)
        {
            pDispObj->SetFOV(fieldOfView);
            pDispObj->SetFocalLength(PixelsToTwips(focalLength));
        }
//##protect##"instance::PerspectiveProjection::focalLengthSet()"
    }
    void PerspectiveProjection::fieldOfViewGet(Value::Number& result)
    {
//##protect##"instance::PerspectiveProjection::fieldOfViewGet()"
        result = fieldOfView;
//##protect##"instance::PerspectiveProjection::fieldOfViewGet()"
    }
    void PerspectiveProjection::fieldOfViewSet(const Value& result, Value::Number value)
    {
//##protect##"instance::PerspectiveProjection::fieldOfViewSet()"
        SF_UNUSED1(result);
        fieldOfView = (float)value;

        // Must recompute the focal length, as it is linked to the field of view.
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        // always use actual stage width for focalLength calc (whether root or stage not)
        float stageWidth = asvm.GetMovieImpl()->GetVisibleFrameRect().Width();
        focalLength = CalculateFocalLength(stageWidth);

        if (pDispObj)
        {
            pDispObj->SetFOV(fieldOfView);
            pDispObj->SetFocalLength(PixelsToTwips(focalLength));
        }
//##protect##"instance::PerspectiveProjection::fieldOfViewSet()"
    }
    void PerspectiveProjection::toMatrix3D(SPtr<Instances::fl_geom::Matrix3D>& result)
    {
//##protect##"instance::PerspectiveProjection::toMatrix3D()"
        Matrix4F mat4;
        float displayWidth;
        if (pDispObj)
        {
            const RectF &vfr = pDispObj->GetMovieImpl()->GetVisibleFrameRectInTwips();
            displayWidth = TwipsToPixels(fabsf(vfr.Width()));     
        }
        else
            // default Flash stage size
            displayWidth = 500;

        float fovYAngle = (float)SF_DEGTORAD(fieldOfView);
        float pixelPerUnitRatio = displayWidth*.5f;    
        float eyeZ = (focalLength == 0) ? (pixelPerUnitRatio/tanf(fovYAngle/2.f)) : (float)focalLength;

        // build transposed simple persp matrix that Flash prints out
        mat4 = Matrix4F::Scaling(eyeZ, eyeZ, 1);
        mat4.M[3][2] = 1;
        mat4.M[3][3] = 0;
        Value args[16];
        int i;
        for(i=0;i<16;i++)
            args[i].SetNumber(mat4[i]);
        GetVM().ConstructBuiltinObject(result, "flash.geom.Matrix3D", 16, args).DoNotCheck();
//##protect##"instance::PerspectiveProjection::toMatrix3D()"
    }

    SPtr<Instances::fl_geom::Point> PerspectiveProjection::projectionCenterGet()
    {
        SPtr<Instances::fl_geom::Point> result;
        projectionCenterGet(result);
        return result;
    }
    SPtr<Instances::fl_geom::Matrix3D> PerspectiveProjection::toMatrix3D()
    {
        SPtr<Instances::fl_geom::Matrix3D> result;
        toMatrix3D(result);
        return result;
    }
//##protect##"instance$methods"

    Double PerspectiveProjection::CalculateFocalLength(float stageWidth)
    {
        return (stageWidth/2.f) / tan(SF_DEGTORAD(fieldOfView/2.f));     // == 250/tan((Pi/180)*(55/2)) = 480.25
    }

    Double PerspectiveProjection::CalculateFOV(float stageWidth)
    {
        return  (2.0f * SF_RADTODEG(1.0f)) * atan(stageWidth/(2.f * focalLength));
    }

	void PerspectiveProjection::AS3Constructor(unsigned argc, const Value* argv) 
    {
        // fov, focalLength, projCtrX, projCtrY
        if (argc > 0)
        {
            Value::Number tmp;
            if (!argv[0].Convert2Number(tmp))
                return;
            if (tmp != 0)
                fieldOfView = tmp;
            if (argc > 1)
            {
                if (!argv[1].Convert2Number(tmp))
                    return;
                if (tmp != 0)
                    focalLength = tmp;
                if (argc > 2)
                {
                    Value::Number x, y;
                    if (!argv[2].Convert2Number(x))
                        return;
                    if (!argv[3].Convert2Number(y))
                        return;
                    if (x != 0 && y != 0)
                    {
                        projectionCenter.x = (float)x;
                        projectionCenter.y = (float)y;
                    }
                }
            }
        }
    }

//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_geom
{
    const ThunkInfo PerspectiveProjection::ti[PerspectiveProjection::ThunkInfoNum] = {
        {TFunc_Instances_PerspectiveProjection_projectionCenterGet::Func, &AS3::fl_geom::PointTI, "projectionCenter", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_PerspectiveProjection_projectionCenterSet::Func, NULL, "projectionCenter", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_PerspectiveProjection_focalLengthGet::Func, &AS3::fl::NumberTI, "focalLength", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_PerspectiveProjection_focalLengthSet::Func, NULL, "focalLength", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_PerspectiveProjection_fieldOfViewGet::Func, &AS3::fl::NumberTI, "fieldOfView", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_PerspectiveProjection_fieldOfViewSet::Func, NULL, "fieldOfView", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_PerspectiveProjection_toMatrix3D::Func, &AS3::fl_geom::Matrix3DTI, "toMatrix3D", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

    PerspectiveProjection::PerspectiveProjection(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::PerspectiveProjection::PerspectiveProjection()"
//##protect##"InstanceTraits::PerspectiveProjection::PerspectiveProjection()"
        SetMemSize(sizeof(Instances::fl_geom::PerspectiveProjection));

    }

    void PerspectiveProjection::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<PerspectiveProjection&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_geom
{
    PerspectiveProjection::PerspectiveProjection(VM& vm)
    : Traits(vm, AS3::fl_geom::PerspectiveProjectionCI)
    {
//##protect##"ClassTraits::PerspectiveProjection::PerspectiveProjection()"
//##protect##"ClassTraits::PerspectiveProjection::PerspectiveProjection()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_geom::PerspectiveProjection(vm, AS3::fl_geom::PerspectiveProjectionCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> PerspectiveProjection::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) PerspectiveProjection(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_geom
{
    const TypeInfo PerspectiveProjectionTI = {
        TypeInfo::CompileTime,
        "PerspectiveProjection", "flash.geom", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo PerspectiveProjectionCI = {
        &PerspectiveProjectionTI,
        ClassTraits::fl_geom::PerspectiveProjection::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_geom::PerspectiveProjection::ThunkInfoNum,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_geom::PerspectiveProjection::ti,
        NULL,
    };
}; // namespace fl_geom


}}} // namespace Scaleform { namespace GFx { namespace AS3

