//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_BitmapFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_BitmapFilter.h"
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
typedef ThunkFunc0<Instances::fl_filters::BitmapFilter, Instances::fl_filters::BitmapFilter::mid_clone, SPtr<Instances::fl_filters::BitmapFilter> > TFunc_Instances_BitmapFilter_clone;

template <> const TFunc_Instances_BitmapFilter_clone::TMethod TFunc_Instances_BitmapFilter_clone::Method = &Instances::fl_filters::BitmapFilter::clone;

namespace Instances { namespace fl_filters
{
    BitmapFilter::BitmapFilter(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
//##protect##"instance::BitmapFilter::BitmapFilter()$data"
      , FilterData(0)
//##protect##"instance::BitmapFilter::BitmapFilter()$data"
    {
//##protect##"instance::BitmapFilter::BitmapFilter()$code"
//##protect##"instance::BitmapFilter::BitmapFilter()$code"
    }

    void BitmapFilter::clone(SPtr<Instances::fl_filters::BitmapFilter>& result)
    {
//##protect##"instance::BitmapFilter::clone()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::BitmapFilter::clone()");
//##protect##"instance::BitmapFilter::clone()"
    }

//##protect##"instance$methods"
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_filters
{
    const ThunkInfo BitmapFilter::ti[BitmapFilter::ThunkInfoNum] = {
        {TFunc_Instances_BitmapFilter_clone::Func, &AS3::fl_filters::BitmapFilterTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

    BitmapFilter::BitmapFilter(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::BitmapFilter::BitmapFilter()"
//##protect##"InstanceTraits::BitmapFilter::BitmapFilter()"
        SetMemSize(sizeof(Instances::fl_filters::BitmapFilter));

    }

    void BitmapFilter::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<BitmapFilter&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_filters
{
    BitmapFilter::BitmapFilter(VM& vm)
    : Traits(vm, AS3::fl_filters::BitmapFilterCI)
    {
//##protect##"ClassTraits::BitmapFilter::BitmapFilter()"
//##protect##"ClassTraits::BitmapFilter::BitmapFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_filters::BitmapFilter(vm, AS3::fl_filters::BitmapFilterCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> BitmapFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) BitmapFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_filters
{
    const TypeInfo BitmapFilterTI = {
        TypeInfo::CompileTime,
        "BitmapFilter", "flash.filters", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo BitmapFilterCI = {
        &BitmapFilterTI,
        ClassTraits::fl_filters::BitmapFilter::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_filters::BitmapFilter::ThunkInfoNum,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_filters::BitmapFilter::ti,
        NULL,
    };
}; // namespace fl_filters


}}} // namespace Scaleform { namespace GFx { namespace AS3

