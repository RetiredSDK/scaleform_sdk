//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_NativeDragActions.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_NativeDragActions.h"
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
    NativeDragActions::NativeDragActions(ClassTraits::Traits& t)
    : Class(t)
    , COPY("copy")
    , LINK("link")
    , MOVE("move")
    , NONE("none")
    {
//##protect##"class_::NativeDragActions::NativeDragActions()"
//##protect##"class_::NativeDragActions::NativeDragActions()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_desktop
{
    const MemberInfo NativeDragActions::mi[NativeDragActions::MemberInfoNum] = {
        {"COPY", NULL, OFFSETOF(Classes::fl_desktop::NativeDragActions, COPY), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"LINK", NULL, OFFSETOF(Classes::fl_desktop::NativeDragActions, LINK), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"MOVE", NULL, OFFSETOF(Classes::fl_desktop::NativeDragActions, MOVE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"NONE", NULL, OFFSETOF(Classes::fl_desktop::NativeDragActions, NONE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    NativeDragActions::NativeDragActions(VM& vm)
    : Traits(vm, AS3::fl_desktop::NativeDragActionsCI)
    {
//##protect##"ClassTraits::NativeDragActions::NativeDragActions()"
//##protect##"ClassTraits::NativeDragActions::NativeDragActions()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_desktop::NativeDragActionsCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_desktop::NativeDragActions(*this));

    }

    Pickable<Traits> NativeDragActions::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeDragActions(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_desktop
{
    const TypeInfo NativeDragActionsTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "NativeDragActions", "flash.desktop", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo NativeDragActionsCI = {
        &NativeDragActionsTI,
        ClassTraits::fl_desktop::NativeDragActions::MakeClassTraits,
        0,
        ClassTraits::fl_desktop::NativeDragActions::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_desktop::NativeDragActions::mi,
        NULL,
        NULL,
    };
}; // namespace fl_desktop


}}} // namespace Scaleform { namespace GFx { namespace AS3

