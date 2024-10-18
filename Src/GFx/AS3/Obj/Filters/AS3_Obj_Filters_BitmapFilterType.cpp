//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_BitmapFilterType.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_BitmapFilterType.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_filters
{
    BitmapFilterType::BitmapFilterType(ClassTraits::Traits& t)
    : Class(t)
    , FULL("full")
    , INNER("inner")
    , OUTER("outer")
    {
//##protect##"class_::BitmapFilterType::BitmapFilterType()"
//##protect##"class_::BitmapFilterType::BitmapFilterType()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_filters
{
    const MemberInfo BitmapFilterType::mi[BitmapFilterType::MemberInfoNum] = {
        {"FULL", NULL, OFFSETOF(Classes::fl_filters::BitmapFilterType, FULL), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"INNER", NULL, OFFSETOF(Classes::fl_filters::BitmapFilterType, INNER), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"OUTER", NULL, OFFSETOF(Classes::fl_filters::BitmapFilterType, OUTER), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    BitmapFilterType::BitmapFilterType(VM& vm)
    : Traits(vm, AS3::fl_filters::BitmapFilterTypeCI)
    {
//##protect##"ClassTraits::BitmapFilterType::BitmapFilterType()"
//##protect##"ClassTraits::BitmapFilterType::BitmapFilterType()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_filters::BitmapFilterTypeCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_filters::BitmapFilterType(*this));

    }

    Pickable<Traits> BitmapFilterType::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) BitmapFilterType(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_filters
{
    const TypeInfo BitmapFilterTypeTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "BitmapFilterType", "flash.filters", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo BitmapFilterTypeCI = {
        &BitmapFilterTypeTI,
        ClassTraits::fl_filters::BitmapFilterType::MakeClassTraits,
        0,
        ClassTraits::fl_filters::BitmapFilterType::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_filters::BitmapFilterType::mi,
        NULL,
        NULL,
    };
}; // namespace fl_filters


}}} // namespace Scaleform { namespace GFx { namespace AS3

