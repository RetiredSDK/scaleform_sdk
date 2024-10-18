//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_ConvolutionFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_ConvolutionFilter.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
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
    const ThunkInfo ConvolutionFilter_ti[19] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "alpha", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "alpha", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "bias", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bias", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "clamp", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "clamp", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "color", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "color", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "divisor", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "divisor", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "matrix", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "matrix", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "matrixX", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "matrixX", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "matrixY", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "matrixY", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "preserveAlpha", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "preserveAlpha", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_filters::BitmapFilterTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_filters
{
    ConvolutionFilter::ConvolutionFilter(VM& vm)
    : Traits(vm, AS3::fl_filters::ConvolutionFilterCI)
    {
//##protect##"ClassTraits::ConvolutionFilter::ConvolutionFilter()"
//##protect##"ClassTraits::ConvolutionFilter::ConvolutionFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_filters::BitmapFilter(vm, AS3::fl_filters::ConvolutionFilterCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> ConvolutionFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ConvolutionFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_filters
{
    const TypeInfo ConvolutionFilterTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "ConvolutionFilter", "flash.filters", &fl_filters::BitmapFilterTI,
        TypeInfo::None
    };

    const ClassInfo ConvolutionFilterCI = {
        &ConvolutionFilterTI,
        ClassTraits::fl_filters::ConvolutionFilter::MakeClassTraits,
        0,
        0,
        19,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_filters::ConvolutionFilter_ti,
        NULL,
    };
}; // namespace fl_filters


}}} // namespace Scaleform { namespace GFx { namespace AS3

