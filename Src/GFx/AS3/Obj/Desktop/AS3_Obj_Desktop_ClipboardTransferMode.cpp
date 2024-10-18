//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_ClipboardTransferMode.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_ClipboardTransferMode.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_desktop
{
    ClipboardTransferMode::ClipboardTransferMode(ClassTraits::Traits& t)
    : Class(t)
    , CLONE_ONLY("cloneOnly")
    , CLONE_PREFERRED("clonePreferred")
    , ORIGINAL_ONLY("originalOnly")
    , ORIGINAL_PREFERRED("originalPreferred")
    {
//##protect##"class_::ClipboardTransferMode::ClipboardTransferMode()"
//##protect##"class_::ClipboardTransferMode::ClipboardTransferMode()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_desktop
{
    const MemberInfo ClipboardTransferMode::mi[ClipboardTransferMode::MemberInfoNum] = {
        {"CLONE_ONLY", NULL, OFFSETOF(Classes::fl_desktop::ClipboardTransferMode, CLONE_ONLY), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"CLONE_PREFERRED", NULL, OFFSETOF(Classes::fl_desktop::ClipboardTransferMode, CLONE_PREFERRED), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"ORIGINAL_ONLY", NULL, OFFSETOF(Classes::fl_desktop::ClipboardTransferMode, ORIGINAL_ONLY), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"ORIGINAL_PREFERRED", NULL, OFFSETOF(Classes::fl_desktop::ClipboardTransferMode, ORIGINAL_PREFERRED), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    ClipboardTransferMode::ClipboardTransferMode(VM& vm)
    : Traits(vm, AS3::fl_desktop::ClipboardTransferModeCI)
    {
//##protect##"ClassTraits::ClipboardTransferMode::ClipboardTransferMode()"
//##protect##"ClassTraits::ClipboardTransferMode::ClipboardTransferMode()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_desktop::ClipboardTransferModeCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_desktop::ClipboardTransferMode(*this));

    }

    Pickable<Traits> ClipboardTransferMode::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClipboardTransferMode(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_desktop
{
    const TypeInfo ClipboardTransferModeTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "ClipboardTransferMode", "flash.desktop", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo ClipboardTransferModeCI = {
        &ClipboardTransferModeTI,
        ClassTraits::fl_desktop::ClipboardTransferMode::MakeClassTraits,
        0,
        ClassTraits::fl_desktop::ClipboardTransferMode::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_desktop::ClipboardTransferMode::mi,
        NULL,
        NULL,
    };
}; // namespace fl_desktop


}}} // namespace Scaleform { namespace GFx { namespace AS3

