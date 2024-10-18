//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_GridFitType.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_GridFitType.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_text
{
    GridFitType::GridFitType(ClassTraits::Traits& t)
    : Class(t)
    , NONE("none")
    , PIXEL("pixel")
    , SUBPIXEL("subpixel")
    {
//##protect##"class_::GridFitType::GridFitType()"
//##protect##"class_::GridFitType::GridFitType()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_text
{
    const MemberInfo GridFitType::mi[GridFitType::MemberInfoNum] = {
        {"NONE", NULL, OFFSETOF(Classes::fl_text::GridFitType, NONE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"PIXEL", NULL, OFFSETOF(Classes::fl_text::GridFitType, PIXEL), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"SUBPIXEL", NULL, OFFSETOF(Classes::fl_text::GridFitType, SUBPIXEL), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    GridFitType::GridFitType(VM& vm)
    : Traits(vm, AS3::fl_text::GridFitTypeCI)
    {
//##protect##"ClassTraits::GridFitType::GridFitType()"
//##protect##"ClassTraits::GridFitType::GridFitType()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_text::GridFitTypeCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_text::GridFitType(*this));

    }

    Pickable<Traits> GridFitType::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) GridFitType(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_text
{
    const TypeInfo GridFitTypeTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "GridFitType", "flash.text", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo GridFitTypeCI = {
        &GridFitTypeTI,
        ClassTraits::fl_text::GridFitType::MakeClassTraits,
        0,
        ClassTraits::fl_text::GridFitType::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_text::GridFitType::mi,
        NULL,
        NULL,
    };
}; // namespace fl_text


}}} // namespace Scaleform { namespace GFx { namespace AS3

