//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_MultitouchInputMode.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Ui_MultitouchInputMode.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_ui
{
    MultitouchInputMode::MultitouchInputMode(ClassTraits::Traits& t)
    : Class(t)
    , GESTURE("gesture")
    , NONE("none")
    , TOUCH_POINT("touchPoint")
    {
//##protect##"class_::MultitouchInputMode::MultitouchInputMode()"
//##protect##"class_::MultitouchInputMode::MultitouchInputMode()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_ui
{
    const MemberInfo MultitouchInputMode::mi[MultitouchInputMode::MemberInfoNum] = {
        {"GESTURE", NULL, OFFSETOF(Classes::fl_ui::MultitouchInputMode, GESTURE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"NONE", NULL, OFFSETOF(Classes::fl_ui::MultitouchInputMode, NONE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"TOUCH_POINT", NULL, OFFSETOF(Classes::fl_ui::MultitouchInputMode, TOUCH_POINT), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    MultitouchInputMode::MultitouchInputMode(VM& vm)
    : Traits(vm, AS3::fl_ui::MultitouchInputModeCI)
    {
//##protect##"ClassTraits::MultitouchInputMode::MultitouchInputMode()"
//##protect##"ClassTraits::MultitouchInputMode::MultitouchInputMode()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_ui::MultitouchInputModeCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_ui::MultitouchInputMode(*this));

    }

    Pickable<Traits> MultitouchInputMode::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) MultitouchInputMode(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_ui
{
    const TypeInfo MultitouchInputModeTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "MultitouchInputMode", "flash.ui", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo MultitouchInputModeCI = {
        &MultitouchInputModeTI,
        ClassTraits::fl_ui::MultitouchInputMode::MakeClassTraits,
        0,
        ClassTraits::fl_ui::MultitouchInputMode::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_ui::MultitouchInputMode::mi,
        NULL,
        NULL,
    };
}; // namespace fl_ui


}}} // namespace Scaleform { namespace GFx { namespace AS3

