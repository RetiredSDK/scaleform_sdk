//##protect##"disclaimer"
/**********************************************************************

Filename    :   .cpp
Content     :   
Created     :   Aug, 2012
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2012 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_ShaderFilter.h"
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

namespace InstanceTraits { namespace fl_filters
{
    const ThunkInfo ShaderFilter_ti[10] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "bottomExtension", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bottomExtension", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "leftExtension", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "leftExtension", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "rightExtension", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "rightExtension", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_display::ShaderTI, "shader", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "shader", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "topExtension", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "topExtension", NULL, Abc::NS_Public, CT_Set, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_filters
{
    ShaderFilter::ShaderFilter(VM& vm)
    : Traits(vm, AS3::fl_filters::ShaderFilterCI)
    {
//##protect##"ClassTraits::ShaderFilter::ShaderFilter()"
//##protect##"ClassTraits::ShaderFilter::ShaderFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_filters::BitmapFilter(vm, AS3::fl_filters::ShaderFilterCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> ShaderFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ShaderFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_filters
{
    const TypeInfo ShaderFilterTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "ShaderFilter", "flash.filters", &fl_filters::BitmapFilterTI,
        TypeInfo::None
    };

    const ClassInfo ShaderFilterCI = {
        &ShaderFilterTI,
        ClassTraits::fl_filters::ShaderFilter::MakeClassTraits,
        0,
        0,
        10,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_filters::ShaderFilter_ti,
        NULL,
    };
}; // namespace fl_filters


}}} // namespace Scaleform { namespace GFx { namespace AS3

