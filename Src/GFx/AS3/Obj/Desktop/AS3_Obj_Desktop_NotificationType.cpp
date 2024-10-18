//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_NotificationType.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_NotificationType.h"
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
    NotificationType::NotificationType(ClassTraits::Traits& t)
    : Class(t)
    , CRITICAL("critical")
    , INFORMATIONAL("informational")
    {
//##protect##"class_::NotificationType::NotificationType()"
//##protect##"class_::NotificationType::NotificationType()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_desktop
{
    const MemberInfo NotificationType::mi[NotificationType::MemberInfoNum] = {
        {"CRITICAL", NULL, OFFSETOF(Classes::fl_desktop::NotificationType, CRITICAL), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"INFORMATIONAL", NULL, OFFSETOF(Classes::fl_desktop::NotificationType, INFORMATIONAL), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    NotificationType::NotificationType(VM& vm)
    : Traits(vm, AS3::fl_desktop::NotificationTypeCI)
    {
//##protect##"ClassTraits::NotificationType::NotificationType()"
//##protect##"ClassTraits::NotificationType::NotificationType()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_desktop::NotificationTypeCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_desktop::NotificationType(*this));

    }

    Pickable<Traits> NotificationType::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NotificationType(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_desktop
{
    const TypeInfo NotificationTypeTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "NotificationType", "flash.desktop", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo NotificationTypeCI = {
        &NotificationTypeTI,
        ClassTraits::fl_desktop::NotificationType::MakeClassTraits,
        0,
        ClassTraits::fl_desktop::NotificationType::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_desktop::NotificationType::mi,
        NULL,
        NULL,
    };
}; // namespace fl_desktop


}}} // namespace Scaleform { namespace GFx { namespace AS3

