//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_DisplacementMapFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_DisplacementMapFilter.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Display/AS3_Obj_Display_BitmapData.h"
#include "../Geom/AS3_Obj_Geom_Point.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_filters
{
    const ThunkInfo DisplacementMapFilter_ti[19] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "alpha", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "alpha", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "color", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "color", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "componentX", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "componentX", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "componentY", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "componentY", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_display::BitmapDataTI, "mapBitmap", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "mapBitmap", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_geom::PointTI, "mapPoint", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "mapPoint", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "mode", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "mode", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "scaleX", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "scaleX", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "scaleY", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "scaleY", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_filters::BitmapFilterTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_filters
{
    DisplacementMapFilter::DisplacementMapFilter(VM& vm)
    : Traits(vm, AS3::fl_filters::DisplacementMapFilterCI)
    {
//##protect##"ClassTraits::DisplacementMapFilter::DisplacementMapFilter()"
//##protect##"ClassTraits::DisplacementMapFilter::DisplacementMapFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_filters::BitmapFilter(vm, AS3::fl_filters::DisplacementMapFilterCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> DisplacementMapFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DisplacementMapFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_filters
{
    const TypeInfo DisplacementMapFilterTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "DisplacementMapFilter", "flash.filters", &fl_filters::BitmapFilterTI,
        TypeInfo::None
    };

    const ClassInfo DisplacementMapFilterCI = {
        &DisplacementMapFilterTI,
        ClassTraits::fl_filters::DisplacementMapFilter::MakeClassTraits,
        0,
        0,
        19,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_filters::DisplacementMapFilter_ti,
        NULL,
    };
}; // namespace fl_filters


}}} // namespace Scaleform { namespace GFx { namespace AS3

