//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextFieldType.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_TextFieldType.h"
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
    TextFieldType::TextFieldType(ClassTraits::Traits& t)
    : Class(t)
    , DYNAMIC("dynamic")
    , INPUT("input")
    {
//##protect##"class_::TextFieldType::TextFieldType()"
//##protect##"class_::TextFieldType::TextFieldType()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_text
{
    const MemberInfo TextFieldType::mi[TextFieldType::MemberInfoNum] = {
        {"DYNAMIC", NULL, OFFSETOF(Classes::fl_text::TextFieldType, DYNAMIC), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"INPUT", NULL, OFFSETOF(Classes::fl_text::TextFieldType, INPUT), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    TextFieldType::TextFieldType(VM& vm)
    : Traits(vm, AS3::fl_text::TextFieldTypeCI)
    {
//##protect##"ClassTraits::TextFieldType::TextFieldType()"
//##protect##"ClassTraits::TextFieldType::TextFieldType()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_text::TextFieldTypeCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_text::TextFieldType(*this));

    }

    Pickable<Traits> TextFieldType::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextFieldType(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_text
{
    const TypeInfo TextFieldTypeTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "TextFieldType", "flash.text", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo TextFieldTypeCI = {
        &TextFieldTypeTI,
        ClassTraits::fl_text::TextFieldType::MakeClassTraits,
        0,
        ClassTraits::fl_text::TextFieldType::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_text::TextFieldType::mi,
        NULL,
        NULL,
    };
}; // namespace fl_text


}}} // namespace Scaleform { namespace GFx { namespace AS3

