//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_JointStyle.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_JointStyle.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_display
{
    JointStyle::JointStyle(ClassTraits::Traits& t)
    : Class(t)
    , BEVEL("bevel")
    , MITER("miter")
    , ROUND("round")
    {
//##protect##"class_::JointStyle::JointStyle()"
//##protect##"class_::JointStyle::JointStyle()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_display
{
    const MemberInfo JointStyle::mi[JointStyle::MemberInfoNum] = {
        {"BEVEL", NULL, OFFSETOF(Classes::fl_display::JointStyle, BEVEL), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"MITER", NULL, OFFSETOF(Classes::fl_display::JointStyle, MITER), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"ROUND", NULL, OFFSETOF(Classes::fl_display::JointStyle, ROUND), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    JointStyle::JointStyle(VM& vm)
    : Traits(vm, AS3::fl_display::JointStyleCI)
    {
//##protect##"ClassTraits::JointStyle::JointStyle()"
//##protect##"ClassTraits::JointStyle::JointStyle()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_display::JointStyleCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_display::JointStyle(*this));

    }

    Pickable<Traits> JointStyle::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) JointStyle(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_display
{
    const TypeInfo JointStyleTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "JointStyle", "flash.display", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo JointStyleCI = {
        &JointStyleTI,
        ClassTraits::fl_display::JointStyle::MakeClassTraits,
        0,
        ClassTraits::fl_display::JointStyle::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_display::JointStyle::mi,
        NULL,
        NULL,
    };
}; // namespace fl_display


}}} // namespace Scaleform { namespace GFx { namespace AS3

