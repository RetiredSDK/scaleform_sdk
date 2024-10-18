//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_BevelFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_BevelFilter.h"
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
typedef ThunkFunc0<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_angleGet, Value::Number> TFunc_Instances_BevelFilter_angleGet;
typedef ThunkFunc1<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_angleSet, const Value, Value::Number> TFunc_Instances_BevelFilter_angleSet;
typedef ThunkFunc0<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_blurXGet, Value::Number> TFunc_Instances_BevelFilter_blurXGet;
typedef ThunkFunc1<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_blurXSet, const Value, Value::Number> TFunc_Instances_BevelFilter_blurXSet;
typedef ThunkFunc0<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_blurYGet, Value::Number> TFunc_Instances_BevelFilter_blurYGet;
typedef ThunkFunc1<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_blurYSet, const Value, Value::Number> TFunc_Instances_BevelFilter_blurYSet;
typedef ThunkFunc0<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_distanceGet, Value::Number> TFunc_Instances_BevelFilter_distanceGet;
typedef ThunkFunc1<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_distanceSet, const Value, Value::Number> TFunc_Instances_BevelFilter_distanceSet;
typedef ThunkFunc0<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_highlightAlphaGet, Value::Number> TFunc_Instances_BevelFilter_highlightAlphaGet;
typedef ThunkFunc1<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_highlightAlphaSet, const Value, Value::Number> TFunc_Instances_BevelFilter_highlightAlphaSet;
typedef ThunkFunc0<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_highlightColorGet, UInt32> TFunc_Instances_BevelFilter_highlightColorGet;
typedef ThunkFunc1<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_highlightColorSet, const Value, UInt32> TFunc_Instances_BevelFilter_highlightColorSet;
typedef ThunkFunc0<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_knockoutGet, bool> TFunc_Instances_BevelFilter_knockoutGet;
typedef ThunkFunc1<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_knockoutSet, const Value, bool> TFunc_Instances_BevelFilter_knockoutSet;
typedef ThunkFunc0<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_qualityGet, SInt32> TFunc_Instances_BevelFilter_qualityGet;
typedef ThunkFunc1<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_qualitySet, const Value, SInt32> TFunc_Instances_BevelFilter_qualitySet;
typedef ThunkFunc0<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_shadowAlphaGet, Value::Number> TFunc_Instances_BevelFilter_shadowAlphaGet;
typedef ThunkFunc1<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_shadowAlphaSet, const Value, Value::Number> TFunc_Instances_BevelFilter_shadowAlphaSet;
typedef ThunkFunc0<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_shadowColorGet, UInt32> TFunc_Instances_BevelFilter_shadowColorGet;
typedef ThunkFunc1<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_shadowColorSet, const Value, UInt32> TFunc_Instances_BevelFilter_shadowColorSet;
typedef ThunkFunc0<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_strengthGet, Value::Number> TFunc_Instances_BevelFilter_strengthGet;
typedef ThunkFunc1<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_strengthSet, const Value, Value::Number> TFunc_Instances_BevelFilter_strengthSet;
typedef ThunkFunc0<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_typeGet, ASString> TFunc_Instances_BevelFilter_typeGet;
typedef ThunkFunc1<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_typeSet, const Value, const ASString&> TFunc_Instances_BevelFilter_typeSet;
typedef ThunkFunc0<Instances::fl_filters::BevelFilter, Instances::fl_filters::BevelFilter::mid_clone, SPtr<Instances::fl_filters::BitmapFilter> > TFunc_Instances_BevelFilter_clone;

template <> const TFunc_Instances_BevelFilter_angleGet::TMethod TFunc_Instances_BevelFilter_angleGet::Method = &Instances::fl_filters::BevelFilter::angleGet;
template <> const TFunc_Instances_BevelFilter_angleSet::TMethod TFunc_Instances_BevelFilter_angleSet::Method = &Instances::fl_filters::BevelFilter::angleSet;
template <> const TFunc_Instances_BevelFilter_blurXGet::TMethod TFunc_Instances_BevelFilter_blurXGet::Method = &Instances::fl_filters::BevelFilter::blurXGet;
template <> const TFunc_Instances_BevelFilter_blurXSet::TMethod TFunc_Instances_BevelFilter_blurXSet::Method = &Instances::fl_filters::BevelFilter::blurXSet;
template <> const TFunc_Instances_BevelFilter_blurYGet::TMethod TFunc_Instances_BevelFilter_blurYGet::Method = &Instances::fl_filters::BevelFilter::blurYGet;
template <> const TFunc_Instances_BevelFilter_blurYSet::TMethod TFunc_Instances_BevelFilter_blurYSet::Method = &Instances::fl_filters::BevelFilter::blurYSet;
template <> const TFunc_Instances_BevelFilter_distanceGet::TMethod TFunc_Instances_BevelFilter_distanceGet::Method = &Instances::fl_filters::BevelFilter::distanceGet;
template <> const TFunc_Instances_BevelFilter_distanceSet::TMethod TFunc_Instances_BevelFilter_distanceSet::Method = &Instances::fl_filters::BevelFilter::distanceSet;
template <> const TFunc_Instances_BevelFilter_highlightAlphaGet::TMethod TFunc_Instances_BevelFilter_highlightAlphaGet::Method = &Instances::fl_filters::BevelFilter::highlightAlphaGet;
template <> const TFunc_Instances_BevelFilter_highlightAlphaSet::TMethod TFunc_Instances_BevelFilter_highlightAlphaSet::Method = &Instances::fl_filters::BevelFilter::highlightAlphaSet;
template <> const TFunc_Instances_BevelFilter_highlightColorGet::TMethod TFunc_Instances_BevelFilter_highlightColorGet::Method = &Instances::fl_filters::BevelFilter::highlightColorGet;
template <> const TFunc_Instances_BevelFilter_highlightColorSet::TMethod TFunc_Instances_BevelFilter_highlightColorSet::Method = &Instances::fl_filters::BevelFilter::highlightColorSet;
template <> const TFunc_Instances_BevelFilter_knockoutGet::TMethod TFunc_Instances_BevelFilter_knockoutGet::Method = &Instances::fl_filters::BevelFilter::knockoutGet;
template <> const TFunc_Instances_BevelFilter_knockoutSet::TMethod TFunc_Instances_BevelFilter_knockoutSet::Method = &Instances::fl_filters::BevelFilter::knockoutSet;
template <> const TFunc_Instances_BevelFilter_qualityGet::TMethod TFunc_Instances_BevelFilter_qualityGet::Method = &Instances::fl_filters::BevelFilter::qualityGet;
template <> const TFunc_Instances_BevelFilter_qualitySet::TMethod TFunc_Instances_BevelFilter_qualitySet::Method = &Instances::fl_filters::BevelFilter::qualitySet;
template <> const TFunc_Instances_BevelFilter_shadowAlphaGet::TMethod TFunc_Instances_BevelFilter_shadowAlphaGet::Method = &Instances::fl_filters::BevelFilter::shadowAlphaGet;
template <> const TFunc_Instances_BevelFilter_shadowAlphaSet::TMethod TFunc_Instances_BevelFilter_shadowAlphaSet::Method = &Instances::fl_filters::BevelFilter::shadowAlphaSet;
template <> const TFunc_Instances_BevelFilter_shadowColorGet::TMethod TFunc_Instances_BevelFilter_shadowColorGet::Method = &Instances::fl_filters::BevelFilter::shadowColorGet;
template <> const TFunc_Instances_BevelFilter_shadowColorSet::TMethod TFunc_Instances_BevelFilter_shadowColorSet::Method = &Instances::fl_filters::BevelFilter::shadowColorSet;
template <> const TFunc_Instances_BevelFilter_strengthGet::TMethod TFunc_Instances_BevelFilter_strengthGet::Method = &Instances::fl_filters::BevelFilter::strengthGet;
template <> const TFunc_Instances_BevelFilter_strengthSet::TMethod TFunc_Instances_BevelFilter_strengthSet::Method = &Instances::fl_filters::BevelFilter::strengthSet;
template <> const TFunc_Instances_BevelFilter_typeGet::TMethod TFunc_Instances_BevelFilter_typeGet::Method = &Instances::fl_filters::BevelFilter::typeGet;
template <> const TFunc_Instances_BevelFilter_typeSet::TMethod TFunc_Instances_BevelFilter_typeSet::Method = &Instances::fl_filters::BevelFilter::typeSet;
template <> const TFunc_Instances_BevelFilter_clone::TMethod TFunc_Instances_BevelFilter_clone::Method = &Instances::fl_filters::BevelFilter::clone;

namespace Instances { namespace fl_filters
{
    BevelFilter::BevelFilter(InstanceTraits::Traits& t)
    : Instances::fl_filters::BitmapFilter(t)
//##protect##"instance::BevelFilter::BevelFilter()$data"
//##protect##"instance::BevelFilter::BevelFilter()$data"
    {
//##protect##"instance::BevelFilter::BevelFilter()$code"
        FilterData = *SF_NEW Render::BevelFilter();
//##protect##"instance::BevelFilter::BevelFilter()$code"
    }

    void BevelFilter::angleGet(Value::Number& result)
    {
//##protect##"instance::BevelFilter::angleGet()"
        result = SF_RADTODEG(GetBevelFilterData()->GetAngle());
//##protect##"instance::BevelFilter::angleGet()"
    }
    void BevelFilter::angleSet(const Value& result, Value::Number value)
    {
//##protect##"instance::BevelFilter::angleSet()"
        SF_UNUSED(result);
        GetBevelFilterData()->SetAngleDistance((float)SF_DEGTORAD((float)value), GetBevelFilterData()->GetDistance());
//##protect##"instance::BevelFilter::angleSet()"
    }
    void BevelFilter::blurXGet(Value::Number& result)
    {
//##protect##"instance::BevelFilter::blurXGet()"
        result = TwipsToPixels(GetBevelFilterData()->GetParams().BlurX);
//##protect##"instance::BevelFilter::blurXGet()"
    }
    void BevelFilter::blurXSet(const Value& result, Value::Number value)
    {
//##protect##"instance::BevelFilter::blurXSet()"
        SF_UNUSED(result);
        GetBevelFilterData()->GetParams().BlurX = PixelsToTwips((float)value);
//##protect##"instance::BevelFilter::blurXSet()"
    }
    void BevelFilter::blurYGet(Value::Number& result)
    {
//##protect##"instance::BevelFilter::blurYGet()"
        result = TwipsToPixels(GetBevelFilterData()->GetParams().BlurY);
//##protect##"instance::BevelFilter::blurYGet()"
    }
    void BevelFilter::blurYSet(const Value& result, Value::Number value)
    {
//##protect##"instance::BevelFilter::blurYSet()"
        SF_UNUSED(result);
        GetBevelFilterData()->GetParams().BlurY = PixelsToTwips((float)value);
//##protect##"instance::BevelFilter::blurYSet()"
    }
    void BevelFilter::distanceGet(Value::Number& result)
    {
//##protect##"instance::BevelFilter::distanceGet()"
        result = TwipsToPixels(GetBevelFilterData()->GetDistance());
//##protect##"instance::BevelFilter::distanceGet()"
    }
    void BevelFilter::distanceSet(const Value& result, Value::Number value)
    {
//##protect##"instance::BevelFilter::distanceSet()"
        SF_UNUSED(result);
        GetBevelFilterData()->SetAngleDistance( GetBevelFilterData()->GetAngle(), PixelsToTwips((float)value));
//##protect##"instance::BevelFilter::distanceSet()"
    }
    void BevelFilter::highlightAlphaGet(Value::Number& result)
    {
//##protect##"instance::BevelFilter::highlightAlphaGet()"
        result = GetBevelFilterData()->GetParams().Colors[1].GetAlpha() / 255.0;
//##protect##"instance::BevelFilter::highlightAlphaGet()"
    }
    void BevelFilter::highlightAlphaSet(const Value& result, Value::Number value)
    {
//##protect##"instance::BevelFilter::highlightAlphaSet()"
        SF_UNUSED(result);
        GetBevelFilterData()->GetParams().Colors[1].SetAlpha((UByte)(value * 255));
//##protect##"instance::BevelFilter::highlightAlphaSet()"
    }
    void BevelFilter::highlightColorGet(UInt32& result)
    {
//##protect##"instance::BevelFilter::highlightColorGet()"
        Render::Color& c = GetBevelFilterData()->GetParams().Colors[1];
        result = c.GetColorRGB().Raw;
//##protect##"instance::BevelFilter::highlightColorGet()"
    }
    void BevelFilter::highlightColorSet(const Value& result, UInt32 value)
    {
//##protect##"instance::BevelFilter::highlightColorSet()"
        SF_UNUSED(result);
        Render::Color& c = GetBevelFilterData()->GetParams().Colors[1];
        c.SetColor(value, c.GetAlpha());
//##protect##"instance::BevelFilter::highlightColorSet()"
    }
    void BevelFilter::knockoutGet(bool& result)
    {
//##protect##"instance::BevelFilter::knockoutGet()"
        result = (GetBevelFilterData()->GetParams().Mode & Render::BlurFilterParams::Mode_Knockout) != 0;
//##protect##"instance::BevelFilter::knockoutGet()"
    }
    void BevelFilter::knockoutSet(const Value& result, bool value)
    {
//##protect##"instance::BevelFilter::knockoutSet()"
        SF_UNUSED(result);
        GetBevelFilterData()->GetParams().Mode |= (value ? Render::BlurFilterParams::Mode_Knockout : 0);
//##protect##"instance::BevelFilter::knockoutSet()"
    }
    void BevelFilter::qualityGet(SInt32& result)
    {
//##protect##"instance::BevelFilter::qualityGet()"
        result = (GetBevelFilterData()->GetParams().Passes);
//##protect##"instance::BevelFilter::qualityGet()"
    }
    void BevelFilter::qualitySet(const Value& result, SInt32 value)
    {
//##protect##"instance::BevelFilter::qualitySet()"
        SF_UNUSED(result);
        GetBevelFilterData()->GetParams().Passes = Alg::Clamp<unsigned>(value, 0, 15);
//##protect##"instance::BevelFilter::qualitySet()"
    }
    void BevelFilter::shadowAlphaGet(Value::Number& result)
    {
//##protect##"instance::BevelFilter::shadowAlphaGet()"
        result = GetBevelFilterData()->GetParams().Colors[0].GetAlpha() / 255.0;
//##protect##"instance::BevelFilter::shadowAlphaGet()"
    }
    void BevelFilter::shadowAlphaSet(const Value& result, Value::Number value)
    {
//##protect##"instance::BevelFilter::shadowAlphaSet()"
        SF_UNUSED(result);
        GetBevelFilterData()->GetParams().Colors[0].SetAlpha((UByte)(value * 255));
//##protect##"instance::BevelFilter::shadowAlphaSet()"
    }
    void BevelFilter::shadowColorGet(UInt32& result)
    {
//##protect##"instance::BevelFilter::shadowColorGet()"
        Render::Color& c = GetBevelFilterData()->GetParams().Colors[0];
        result = c.GetColorRGB().Raw;
//##protect##"instance::BevelFilter::shadowColorGet()"
    }
    void BevelFilter::shadowColorSet(const Value& result, UInt32 value)
    {
//##protect##"instance::BevelFilter::shadowColorSet()"
        SF_UNUSED(result);
        Render::Color& c = GetBevelFilterData()->GetParams().Colors[0];
        c.SetColor(value, c.GetAlpha());
//##protect##"instance::BevelFilter::shadowColorSet()"
    }
    void BevelFilter::strengthGet(Value::Number& result)
    {
//##protect##"instance::BevelFilter::strengthGet()"
        result = GetBevelFilterData()->GetParams().Strength;
//##protect##"instance::BevelFilter::strengthGet()"
    }
    void BevelFilter::strengthSet(const Value& result, Value::Number value)
    {
//##protect##"instance::BevelFilter::strengthSet()"
        SF_UNUSED(result);
        GetBevelFilterData()->GetParams().Strength = (float)value;
//##protect##"instance::BevelFilter::strengthSet()"
    }
    void BevelFilter::typeGet(ASString& result)
    {
//##protect##"instance::BevelFilter::typeGet()"
        if ( GetBevelFilterData()->GetParams().Mode & Render::BlurFilterParams::Mode_Inner )
            result = "inner";
        else
            result = "outer";
//##protect##"instance::BevelFilter::typeGet()"
    }
    void BevelFilter::typeSet(const Value& result, const ASString& value)
    {
//##protect##"instance::BevelFilter::typeSet()"
        SF_UNUSED(result);
        if ( value == "inner" )
        {
            GetBevelFilterData()->GetParams().Mode |= Render::BlurFilterParams::Mode_Inner;
        }
        else if ( value == "outer" )
        {
            GetBevelFilterData()->GetParams().Mode &= ~Render::BlurFilterParams::Mode_Inner;
        }
        else if ( value == "full" )
        {
            WARN_NOT_IMPLEMENTED("instance::BevelFilter::typeSet() - full");
        }
//##protect##"instance::BevelFilter::typeSet()"
    }
    void BevelFilter::clone(SPtr<Instances::fl_filters::BitmapFilter>& result)
    {
//##protect##"instance::BevelFilter::clone()"
        InstanceTraits::fl_filters::BevelFilter& itr = static_cast<InstanceTraits::fl_filters::BevelFilter&>(GetTraits());
        Pickable<BevelFilter> r = itr.MakeInstance(itr);

        Value::Number dist, angl;
        UInt32 highC;
        Value::Number highA;
        UInt32 shadowC;
        Value::Number shadowA, blurX, blurY, stren;
        SInt32 qual;
        ASString type = GetVM().GetStringManager().CreateEmptyString();
        bool knock;
        distanceGet(dist);
        angleGet(angl);
        highlightColorGet(highC);
        highlightAlphaGet(highA);
        shadowColorGet(shadowC);
        shadowAlphaGet(shadowA);
        blurXGet(blurX);
        blurYGet(blurY);
        strengthGet(stren);
        qualityGet(qual);
        typeGet(type);
        knockoutGet(knock);

        Value tempResult;
        r->distanceSet(tempResult, dist);
        r->angleSet(tempResult, angl);
        r->highlightColorSet(tempResult, highC);
        r->highlightAlphaSet(tempResult, highA);
        r->shadowColorSet(tempResult, shadowC);
        r->shadowAlphaSet(tempResult, shadowA);
        r->blurXSet(tempResult, blurX);
        r->blurYSet(tempResult, blurY);
        r->strengthSet(tempResult, stren);
        r->qualitySet(tempResult, qual);
        r->typeSet(tempResult, type);
        r->knockoutSet(tempResult, knock);

        result = r;
//##protect##"instance::BevelFilter::clone()"
    }

    SPtr<Instances::fl_filters::BitmapFilter> BevelFilter::clone()
    {
        SPtr<Instances::fl_filters::BitmapFilter> result;
        clone(result);
        return result;
    }
//##protect##"instance$methods"
    void BevelFilter::AS3Constructor(unsigned argc, const Value* argv)
    {
        Value::Number dist(4), angl(45);
        UInt32 highC(0xFFFFFF);
        Value::Number highA(1);
        UInt32 shadowC(0);
        Value::Number shadowA(1), blurX(4), blurY(4), stren(1);
        SInt32 qual(1);
        StringManager& sm = GetVM().GetStringManager();
        ASString type = sm.CreateConstString("inner");
        bool knock(false);

        if ( argc >= 1 && !argv[0].Convert2Number(dist)) return;
        if ( argc >= 2 && !argv[1].Convert2Number(angl)) return;
        if ( argc >= 3 && !argv[2].Convert2UInt32(highC)) return;
        if ( argc >= 4 && !argv[3].Convert2Number(highA)) return;
        if ( argc >= 5 && !argv[4].Convert2UInt32(shadowC)) return;
        if ( argc >= 6 && !argv[5].Convert2Number(shadowA)) return;
        if ( argc >= 7 && !argv[6].Convert2Number(blurX)) return;
        if ( argc >= 8 && !argv[7].Convert2Number(blurY)) return;
        if ( argc >= 9 && !argv[8].Convert2Number(stren)) return;
        if ( argc >= 10&& !argv[9].Convert2Int32(qual)) return;
        if ( argc >= 11&& !argv[10].Convert2String(type)) return;
        if ( argc >= 12) knock = argv[11].Convert2Boolean();

        Value result;
        distanceSet(result, dist);
        angleSet(result, angl);
        highlightColorSet(result, highC);
        highlightAlphaSet(result, highA);
        shadowColorSet(result, shadowC);
        shadowAlphaSet(result, shadowA);
        blurXSet(result, blurX);
        blurYSet(result, blurY);
        strengthSet(result, stren);
        qualitySet(result, qual);
        typeSet(result, type);
        knockoutSet(result, knock);
    }
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_filters
{
    const ThunkInfo BevelFilter::ti[BevelFilter::ThunkInfoNum] = {
        {TFunc_Instances_BevelFilter_angleGet::Func, &AS3::fl::NumberTI, "angle", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_BevelFilter_angleSet::Func, NULL, "angle", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_BevelFilter_blurXGet::Func, &AS3::fl::NumberTI, "blurX", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_BevelFilter_blurXSet::Func, NULL, "blurX", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_BevelFilter_blurYGet::Func, &AS3::fl::NumberTI, "blurY", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_BevelFilter_blurYSet::Func, NULL, "blurY", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_BevelFilter_distanceGet::Func, &AS3::fl::NumberTI, "distance", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_BevelFilter_distanceSet::Func, NULL, "distance", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_BevelFilter_highlightAlphaGet::Func, &AS3::fl::NumberTI, "highlightAlpha", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_BevelFilter_highlightAlphaSet::Func, NULL, "highlightAlpha", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_BevelFilter_highlightColorGet::Func, &AS3::fl::uintTI, "highlightColor", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_BevelFilter_highlightColorSet::Func, NULL, "highlightColor", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_BevelFilter_knockoutGet::Func, &AS3::fl::BooleanTI, "knockout", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_BevelFilter_knockoutSet::Func, NULL, "knockout", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_BevelFilter_qualityGet::Func, &AS3::fl::int_TI, "quality", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_BevelFilter_qualitySet::Func, NULL, "quality", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_BevelFilter_shadowAlphaGet::Func, &AS3::fl::NumberTI, "shadowAlpha", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_BevelFilter_shadowAlphaSet::Func, NULL, "shadowAlpha", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_BevelFilter_shadowColorGet::Func, &AS3::fl::uintTI, "shadowColor", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_BevelFilter_shadowColorSet::Func, NULL, "shadowColor", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_BevelFilter_strengthGet::Func, &AS3::fl::NumberTI, "strength", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_BevelFilter_strengthSet::Func, NULL, "strength", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_BevelFilter_typeGet::Func, &AS3::fl::StringTI, "type", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_BevelFilter_typeSet::Func, NULL, "type", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_BevelFilter_clone::Func, &AS3::fl_filters::BitmapFilterTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

    BevelFilter::BevelFilter(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::BevelFilter::BevelFilter()"
//##protect##"InstanceTraits::BevelFilter::BevelFilter()"
        SetMemSize(sizeof(Instances::fl_filters::BevelFilter));

    }

    void BevelFilter::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<BevelFilter&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_filters
{
    BevelFilter::BevelFilter(VM& vm)
    : Traits(vm, AS3::fl_filters::BevelFilterCI)
    {
//##protect##"ClassTraits::BevelFilter::BevelFilter()"
//##protect##"ClassTraits::BevelFilter::BevelFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_filters::BevelFilter(vm, AS3::fl_filters::BevelFilterCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> BevelFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) BevelFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_filters
{
    const TypeInfo BevelFilterTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "BevelFilter", "flash.filters", &fl_filters::BitmapFilterTI,
        TypeInfo::None
    };

    const ClassInfo BevelFilterCI = {
        &BevelFilterTI,
        ClassTraits::fl_filters::BevelFilter::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_filters::BevelFilter::ThunkInfoNum,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_filters::BevelFilter::ti,
        NULL,
    };
}; // namespace fl_filters


}}} // namespace Scaleform { namespace GFx { namespace AS3

