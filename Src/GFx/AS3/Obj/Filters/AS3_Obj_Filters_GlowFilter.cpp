//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_GlowFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_GlowFilter.h"
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

} // namespace Impl
typedef ThunkFunc0<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_alphaGet, Value::Number> TFunc_Instances_GlowFilter_alphaGet;
typedef ThunkFunc1<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_alphaSet, const Value, Value::Number> TFunc_Instances_GlowFilter_alphaSet;
typedef ThunkFunc0<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_blurXGet, Value::Number> TFunc_Instances_GlowFilter_blurXGet;
typedef ThunkFunc1<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_blurXSet, const Value, Value::Number> TFunc_Instances_GlowFilter_blurXSet;
typedef ThunkFunc0<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_blurYGet, Value::Number> TFunc_Instances_GlowFilter_blurYGet;
typedef ThunkFunc1<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_blurYSet, const Value, Value::Number> TFunc_Instances_GlowFilter_blurYSet;
typedef ThunkFunc0<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_colorGet, UInt32> TFunc_Instances_GlowFilter_colorGet;
typedef ThunkFunc1<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_colorSet, const Value, UInt32> TFunc_Instances_GlowFilter_colorSet;
typedef ThunkFunc0<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_innerGet, bool> TFunc_Instances_GlowFilter_innerGet;
typedef ThunkFunc1<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_innerSet, const Value, bool> TFunc_Instances_GlowFilter_innerSet;
typedef ThunkFunc0<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_knockoutGet, bool> TFunc_Instances_GlowFilter_knockoutGet;
typedef ThunkFunc1<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_knockoutSet, const Value, bool> TFunc_Instances_GlowFilter_knockoutSet;
typedef ThunkFunc0<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_qualityGet, SInt32> TFunc_Instances_GlowFilter_qualityGet;
typedef ThunkFunc1<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_qualitySet, const Value, SInt32> TFunc_Instances_GlowFilter_qualitySet;
typedef ThunkFunc0<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_strengthGet, Value::Number> TFunc_Instances_GlowFilter_strengthGet;
typedef ThunkFunc1<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_strengthSet, const Value, Value::Number> TFunc_Instances_GlowFilter_strengthSet;
typedef ThunkFunc0<Instances::fl_filters::GlowFilter, Instances::fl_filters::GlowFilter::mid_clone, SPtr<Instances::fl_filters::BitmapFilter> > TFunc_Instances_GlowFilter_clone;

template <> const TFunc_Instances_GlowFilter_alphaGet::TMethod TFunc_Instances_GlowFilter_alphaGet::Method = &Instances::fl_filters::GlowFilter::alphaGet;
template <> const TFunc_Instances_GlowFilter_alphaSet::TMethod TFunc_Instances_GlowFilter_alphaSet::Method = &Instances::fl_filters::GlowFilter::alphaSet;
template <> const TFunc_Instances_GlowFilter_blurXGet::TMethod TFunc_Instances_GlowFilter_blurXGet::Method = &Instances::fl_filters::GlowFilter::blurXGet;
template <> const TFunc_Instances_GlowFilter_blurXSet::TMethod TFunc_Instances_GlowFilter_blurXSet::Method = &Instances::fl_filters::GlowFilter::blurXSet;
template <> const TFunc_Instances_GlowFilter_blurYGet::TMethod TFunc_Instances_GlowFilter_blurYGet::Method = &Instances::fl_filters::GlowFilter::blurYGet;
template <> const TFunc_Instances_GlowFilter_blurYSet::TMethod TFunc_Instances_GlowFilter_blurYSet::Method = &Instances::fl_filters::GlowFilter::blurYSet;
template <> const TFunc_Instances_GlowFilter_colorGet::TMethod TFunc_Instances_GlowFilter_colorGet::Method = &Instances::fl_filters::GlowFilter::colorGet;
template <> const TFunc_Instances_GlowFilter_colorSet::TMethod TFunc_Instances_GlowFilter_colorSet::Method = &Instances::fl_filters::GlowFilter::colorSet;
template <> const TFunc_Instances_GlowFilter_innerGet::TMethod TFunc_Instances_GlowFilter_innerGet::Method = &Instances::fl_filters::GlowFilter::innerGet;
template <> const TFunc_Instances_GlowFilter_innerSet::TMethod TFunc_Instances_GlowFilter_innerSet::Method = &Instances::fl_filters::GlowFilter::innerSet;
template <> const TFunc_Instances_GlowFilter_knockoutGet::TMethod TFunc_Instances_GlowFilter_knockoutGet::Method = &Instances::fl_filters::GlowFilter::knockoutGet;
template <> const TFunc_Instances_GlowFilter_knockoutSet::TMethod TFunc_Instances_GlowFilter_knockoutSet::Method = &Instances::fl_filters::GlowFilter::knockoutSet;
template <> const TFunc_Instances_GlowFilter_qualityGet::TMethod TFunc_Instances_GlowFilter_qualityGet::Method = &Instances::fl_filters::GlowFilter::qualityGet;
template <> const TFunc_Instances_GlowFilter_qualitySet::TMethod TFunc_Instances_GlowFilter_qualitySet::Method = &Instances::fl_filters::GlowFilter::qualitySet;
template <> const TFunc_Instances_GlowFilter_strengthGet::TMethod TFunc_Instances_GlowFilter_strengthGet::Method = &Instances::fl_filters::GlowFilter::strengthGet;
template <> const TFunc_Instances_GlowFilter_strengthSet::TMethod TFunc_Instances_GlowFilter_strengthSet::Method = &Instances::fl_filters::GlowFilter::strengthSet;
template <> const TFunc_Instances_GlowFilter_clone::TMethod TFunc_Instances_GlowFilter_clone::Method = &Instances::fl_filters::GlowFilter::clone;

namespace Instances { namespace fl_filters
{
    GlowFilter::GlowFilter(InstanceTraits::Traits& t)
    : Instances::fl_filters::BitmapFilter(t)
//##protect##"instance::GlowFilter::GlowFilter()$data"
//##protect##"instance::GlowFilter::GlowFilter()$data"
    {
//##protect##"instance::GlowFilter::GlowFilter()$code"
        FilterData = *SF_NEW Render::GlowFilter();
//##protect##"instance::GlowFilter::GlowFilter()$code"
    }

    void GlowFilter::alphaGet(Value::Number& result)
    {
//##protect##"instance::GlowFilter::alphaGet()"
        result = GetGlowFilterData()->GetParams().Colors[0].GetAlpha() / 255.0;
//##protect##"instance::GlowFilter::alphaGet()"
    }
    void GlowFilter::alphaSet(const Value& result, Value::Number value)
    {
//##protect##"instance::GlowFilter::alphaSet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().Colors[0].SetAlpha((UByte)(value * 255));
//##protect##"instance::GlowFilter::alphaSet()"
    }
    void GlowFilter::blurXGet(Value::Number& result)
    {
//##protect##"instance::GlowFilter::blurXGet()"
        result = TwipsToPixels(GetGlowFilterData()->GetParams().BlurX);
//##protect##"instance::GlowFilter::blurXGet()"
    }
    void GlowFilter::blurXSet(const Value& result, Value::Number value)
    {
//##protect##"instance::GlowFilter::blurXSet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().BlurX = PixelsToTwips((float)value);
//##protect##"instance::GlowFilter::blurXSet()"
    }
    void GlowFilter::blurYGet(Value::Number& result)
    {
//##protect##"instance::GlowFilter::blurYGet()"
        result = TwipsToPixels(GetGlowFilterData()->GetParams().BlurY);
//##protect##"instance::GlowFilter::blurYGet()"
    }
    void GlowFilter::blurYSet(const Value& result, Value::Number value)
    {
//##protect##"instance::GlowFilter::blurYSet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().BlurY = PixelsToTwips((float)value);
//##protect##"instance::GlowFilter::blurYSet()"
    }
    void GlowFilter::colorGet(UInt32& result)
    {
//##protect##"instance::GlowFilter::colorGet()"
        Render::Color& c = GetGlowFilterData()->GetParams().Colors[0];
        result = c.GetColorRGB().Raw;
//##protect##"instance::GlowFilter::colorGet()"
    }
    void GlowFilter::colorSet(const Value& result, UInt32 value)
    {
//##protect##"instance::GlowFilter::colorSet()"
        SF_UNUSED(result);
        Render::Color& c = GetGlowFilterData()->GetParams().Colors[0];
        c.SetColor(value, c.GetAlpha());
//##protect##"instance::GlowFilter::colorSet()"
    }
    void GlowFilter::innerGet(bool& result)
    {
//##protect##"instance::GlowFilter::innerGet()"
        result = (GetGlowFilterData()->GetParams().Mode & Render::BlurFilterParams::Mode_Inner) != 0;
//##protect##"instance::GlowFilter::innerGet()"
    }
    void GlowFilter::innerSet(const Value& result, bool value)
    {
//##protect##"instance::GlowFilter::innerSet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().Mode |= (value ? Render::BlurFilterParams::Mode_Inner : 0);
//##protect##"instance::GlowFilter::innerSet()"
    }
    void GlowFilter::knockoutGet(bool& result)
    {
//##protect##"instance::GlowFilter::knockoutGet()"
        result = (GetGlowFilterData()->GetParams().Mode & Render::BlurFilterParams::Mode_Knockout) != 0;
//##protect##"instance::GlowFilter::knockoutGet()"
    }
    void GlowFilter::knockoutSet(const Value& result, bool value)
    {
//##protect##"instance::GlowFilter::knockoutSet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().Mode |= (value ? Render::BlurFilterParams::Mode_Knockout : 0);
//##protect##"instance::GlowFilter::knockoutSet()"
    }
    void GlowFilter::qualityGet(SInt32& result)
    {
//##protect##"instance::GlowFilter::qualityGet()"
        result = (GetGlowFilterData()->GetParams().Passes);
//##protect##"instance::GlowFilter::qualityGet()"
    }
    void GlowFilter::qualitySet(const Value& result, SInt32 value)
    {
//##protect##"instance::GlowFilter::qualitySet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().Passes = Alg::Clamp<unsigned>(value, 0, 15);
//##protect##"instance::GlowFilter::qualitySet()"
    }
    void GlowFilter::strengthGet(Value::Number& result)
    {
//##protect##"instance::GlowFilter::strengthGet()"
        result = GetGlowFilterData()->GetParams().Strength;
//##protect##"instance::GlowFilter::strengthGet()"
    }
    void GlowFilter::strengthSet(const Value& result, Value::Number value)
    {
//##protect##"instance::GlowFilter::strengthSet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().Strength = (float)value;
//##protect##"instance::GlowFilter::strengthSet()"
    }
    void GlowFilter::clone(SPtr<Instances::fl_filters::BitmapFilter>& result)
    {
//##protect##"instance::GlowFilter::clone()"
        InstanceTraits::fl_filters::GlowFilter& itr = static_cast<InstanceTraits::fl_filters::GlowFilter&>(GetTraits());
        Pickable<GlowFilter> r = itr.MakeInstance(itr);

        UInt32 color;
        Value::Number alpha, blurX, blurY, stren;
        SInt32 qual;
        bool inner, knock;
        colorGet(color);
        alphaGet(alpha);
        blurXGet(blurX);
        blurYGet(blurY);
        strengthGet(stren);
        qualityGet(qual);
        innerGet(inner);
        knockoutGet(knock);

        Value tempResult;
        r->colorSet(tempResult, color);
        r->alphaSet(tempResult, alpha);
        r->blurXSet(tempResult, blurX);
        r->blurYSet(tempResult, blurY);
        r->strengthSet(tempResult, stren);
        r->qualitySet(tempResult, qual);
        r->innerSet(tempResult, inner);
        r->knockoutSet(tempResult, knock);
        result = r;
//##protect##"instance::GlowFilter::clone()"
    }

    SPtr<Instances::fl_filters::BitmapFilter> GlowFilter::clone()
    {
        SPtr<Instances::fl_filters::BitmapFilter> result;
        clone(result);
        return result;
    }
//##protect##"instance$methods"
    void GlowFilter::AS3Constructor(unsigned argc, const Value* argv)
    {
        UInt32 color(0xFF0000);
        Value::Number alpha(1), blurX(6), blurY(6), stren(2);
        SInt32 qual(1);
        bool inner(false), knock(false);

        if ( argc >= 1 && !argv[0].Convert2UInt32(color)) return;
        if ( argc >= 2 && !argv[1].Convert2Number(alpha)) return;
        if ( argc >= 3 && !argv[2].Convert2Number(blurX)) return;
        if ( argc >= 4 && !argv[3].Convert2Number(blurY)) return;
        if ( argc >= 5 && !argv[4].Convert2Number(stren)) return;
        if ( argc >= 6 && !argv[5].Convert2Int32(qual)) return;
        if ( argc >= 7 ) inner = argv[6].Convert2Boolean();
        if ( argc >= 8 ) knock = argv[7].Convert2Boolean();

        Value result;
        colorSet(result, color);
        alphaSet(result, alpha);
        blurXSet(result, blurX);
        blurYSet(result, blurY);
        strengthSet(result, stren);
        qualitySet(result, qual);
        innerSet(result, inner);
        knockoutSet(result, knock);
    }
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_filters
{
    const ThunkInfo GlowFilter::ti[GlowFilter::ThunkInfoNum] = {
        {TFunc_Instances_GlowFilter_alphaGet::Func, &AS3::fl::NumberTI, "alpha", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_alphaSet::Func, NULL, "alpha", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_blurXGet::Func, &AS3::fl::NumberTI, "blurX", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_blurXSet::Func, NULL, "blurX", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_blurYGet::Func, &AS3::fl::NumberTI, "blurY", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_blurYSet::Func, NULL, "blurY", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_colorGet::Func, &AS3::fl::uintTI, "color", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_colorSet::Func, NULL, "color", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_innerGet::Func, &AS3::fl::BooleanTI, "inner", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_innerSet::Func, NULL, "inner", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_knockoutGet::Func, &AS3::fl::BooleanTI, "knockout", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_knockoutSet::Func, NULL, "knockout", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_qualityGet::Func, &AS3::fl::int_TI, "quality", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_qualitySet::Func, NULL, "quality", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_strengthGet::Func, &AS3::fl::NumberTI, "strength", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_strengthSet::Func, NULL, "strength", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_clone::Func, &AS3::fl_filters::BitmapFilterTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

    GlowFilter::GlowFilter(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::GlowFilter::GlowFilter()"
//##protect##"InstanceTraits::GlowFilter::GlowFilter()"
        SetMemSize(sizeof(Instances::fl_filters::GlowFilter));

    }

    void GlowFilter::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<GlowFilter&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_filters
{
    GlowFilter::GlowFilter(VM& vm)
    : Traits(vm, AS3::fl_filters::GlowFilterCI)
    {
//##protect##"ClassTraits::GlowFilter::GlowFilter()"
//##protect##"ClassTraits::GlowFilter::GlowFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_filters::GlowFilter(vm, AS3::fl_filters::GlowFilterCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> GlowFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) GlowFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_filters
{
    const TypeInfo GlowFilterTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "GlowFilter", "flash.filters", &fl_filters::BitmapFilterTI,
        TypeInfo::None
    };

    const ClassInfo GlowFilterCI = {
        &GlowFilterTI,
        ClassTraits::fl_filters::GlowFilter::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_filters::GlowFilter::ThunkInfoNum,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_filters::GlowFilter::ti,
        NULL,
    };
}; // namespace fl_filters


}}} // namespace Scaleform { namespace GFx { namespace AS3

