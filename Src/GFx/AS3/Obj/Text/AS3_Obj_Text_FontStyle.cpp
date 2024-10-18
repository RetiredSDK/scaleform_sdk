//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_FontStyle.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_FontStyle.h"
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
    FontStyle::FontStyle(ClassTraits::Traits& t)
    : Class(t)
    , BOLD("bold")
    , BOLD_ITALIC("boldItalic")
    , ITALIC("italic")
    , REGULAR("regular")
    {
//##protect##"class_::FontStyle::FontStyle()"
//##protect##"class_::FontStyle::FontStyle()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_text
{
    const MemberInfo FontStyle::mi[FontStyle::MemberInfoNum] = {
        {"BOLD", NULL, OFFSETOF(Classes::fl_text::FontStyle, BOLD), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"BOLD_ITALIC", NULL, OFFSETOF(Classes::fl_text::FontStyle, BOLD_ITALIC), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"ITALIC", NULL, OFFSETOF(Classes::fl_text::FontStyle, ITALIC), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"REGULAR", NULL, OFFSETOF(Classes::fl_text::FontStyle, REGULAR), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    FontStyle::FontStyle(VM& vm)
    : Traits(vm, AS3::fl_text::FontStyleCI)
    {
//##protect##"ClassTraits::FontStyle::FontStyle()"
//##protect##"ClassTraits::FontStyle::FontStyle()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_text::FontStyleCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_text::FontStyle(*this));

    }

    Pickable<Traits> FontStyle::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FontStyle(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_text
{
    const TypeInfo FontStyleTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "FontStyle", "flash.text", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo FontStyleCI = {
        &FontStyleTI,
        ClassTraits::fl_text::FontStyle::MakeClassTraits,
        0,
        ClassTraits::fl_text::FontStyle::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_text::FontStyle::mi,
        NULL,
        NULL,
    };
}; // namespace fl_text


}}} // namespace Scaleform { namespace GFx { namespace AS3

