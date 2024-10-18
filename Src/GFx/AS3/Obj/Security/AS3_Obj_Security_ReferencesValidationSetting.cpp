//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Security_ReferencesValidationSetting.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Security_ReferencesValidationSetting.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../../AS3_GC.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_security
{
    ReferencesValidationSetting::ReferencesValidationSetting(ClassTraits::Traits& t)
    : Class(t)
    , NEVER("never")
    , VALID_IDENTITY("validIdentity")
    , VALID_OR_UNKNOWN_IDENTITY("validOrUnknownIdentity")
    {
//##protect##"class_::ReferencesValidationSetting::ReferencesValidationSetting()"
//##protect##"class_::ReferencesValidationSetting::ReferencesValidationSetting()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_security
{
    const MemberInfo ReferencesValidationSetting::mi[ReferencesValidationSetting::MemberInfoNum] = {
        {"NEVER", NULL, OFFSETOF(Classes::fl_security::ReferencesValidationSetting, NEVER), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"VALID_IDENTITY", NULL, OFFSETOF(Classes::fl_security::ReferencesValidationSetting, VALID_IDENTITY), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"VALID_OR_UNKNOWN_IDENTITY", NULL, OFFSETOF(Classes::fl_security::ReferencesValidationSetting, VALID_OR_UNKNOWN_IDENTITY), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    ReferencesValidationSetting::ReferencesValidationSetting(VM& vm)
    : Traits(vm, AS3::fl_security::ReferencesValidationSettingCI)
    {
//##protect##"ClassTraits::ReferencesValidationSetting::ReferencesValidationSetting()"
//##protect##"ClassTraits::ReferencesValidationSetting::ReferencesValidationSetting()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_security::ReferencesValidationSettingCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_security::ReferencesValidationSetting(*this));

    }

    Pickable<Traits> ReferencesValidationSetting::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ReferencesValidationSetting(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_security
{
    const TypeInfo ReferencesValidationSettingTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "ReferencesValidationSetting", "flash.security", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo ReferencesValidationSettingCI = {
        &ReferencesValidationSettingTI,
        ClassTraits::fl_security::ReferencesValidationSetting::MakeClassTraits,
        0,
        ClassTraits::fl_security::ReferencesValidationSetting::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_security::ReferencesValidationSetting::mi,
        NULL,
        NULL,
    };
}; // namespace fl_security


}}} // namespace Scaleform { namespace GFx { namespace AS3

