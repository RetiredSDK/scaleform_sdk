//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Security_SignatureStatus.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Security_SignatureStatus.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_security
{
    SignatureStatus::SignatureStatus(ClassTraits::Traits& t)
    : Class(t)
    , INVALID("invalid")
    , UNKNOWN("")
    , VALID("valid")
    {
//##protect##"class_::SignatureStatus::SignatureStatus()"
//##protect##"class_::SignatureStatus::SignatureStatus()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_security
{
    const MemberInfo SignatureStatus::mi[SignatureStatus::MemberInfoNum] = {
        {"INVALID", NULL, OFFSETOF(Classes::fl_security::SignatureStatus, INVALID), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"UNKNOWN", NULL, OFFSETOF(Classes::fl_security::SignatureStatus, UNKNOWN), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"VALID", NULL, OFFSETOF(Classes::fl_security::SignatureStatus, VALID), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    SignatureStatus::SignatureStatus(VM& vm)
    : Traits(vm, AS3::fl_security::SignatureStatusCI)
    {
//##protect##"ClassTraits::SignatureStatus::SignatureStatus()"
//##protect##"ClassTraits::SignatureStatus::SignatureStatus()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_security::SignatureStatusCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_security::SignatureStatus(*this));

    }

    Pickable<Traits> SignatureStatus::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SignatureStatus(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_security
{
    const TypeInfo SignatureStatusTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "SignatureStatus", "flash.security", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo SignatureStatusCI = {
        &SignatureStatusTI,
        ClassTraits::fl_security::SignatureStatus::MakeClassTraits,
        0,
        ClassTraits::fl_security::SignatureStatus::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_security::SignatureStatus::mi,
        NULL,
        NULL,
    };
}; // namespace fl_security


}}} // namespace Scaleform { namespace GFx { namespace AS3

