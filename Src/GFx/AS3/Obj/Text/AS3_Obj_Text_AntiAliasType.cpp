//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_AntiAliasType.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_AntiAliasType.h"
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
    AntiAliasType::AntiAliasType(ClassTraits::Traits& t)
    : Class(t)
    , ADVANCED("advanced")
    , NORMAL("normal")
    {
//##protect##"class_::AntiAliasType::AntiAliasType()"
//##protect##"class_::AntiAliasType::AntiAliasType()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_text
{
    const MemberInfo AntiAliasType::mi[AntiAliasType::MemberInfoNum] = {
        {"ADVANCED", NULL, OFFSETOF(Classes::fl_text::AntiAliasType, ADVANCED), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"NORMAL", NULL, OFFSETOF(Classes::fl_text::AntiAliasType, NORMAL), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    AntiAliasType::AntiAliasType(VM& vm)
    : Traits(vm, AS3::fl_text::AntiAliasTypeCI)
    {
//##protect##"ClassTraits::AntiAliasType::AntiAliasType()"
//##protect##"ClassTraits::AntiAliasType::AntiAliasType()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_text::AntiAliasTypeCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_text::AntiAliasType(*this));

    }

    Pickable<Traits> AntiAliasType::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) AntiAliasType(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_text
{
    const TypeInfo AntiAliasTypeTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "AntiAliasType", "flash.text", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo AntiAliasTypeCI = {
        &AntiAliasTypeTI,
        ClassTraits::fl_text::AntiAliasType::MakeClassTraits,
        0,
        ClassTraits::fl_text::AntiAliasType::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_text::AntiAliasType::mi,
        NULL,
        NULL,
    };
}; // namespace fl_text


}}} // namespace Scaleform { namespace GFx { namespace AS3

