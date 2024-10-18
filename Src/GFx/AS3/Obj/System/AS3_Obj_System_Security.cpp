//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_Security.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_System_Security.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_system
{
    const ThunkInfo Security_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "exactSettings", NULL, Abc::NS_Public, CT_Set, 1, 1},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_system
{
    Security::Security(ClassTraits::Traits& t)
    : Class(t)
    , APPLICATION("application")
    , LOCAL_TRUSTED("localTrusted")
    , LOCAL_WITH_FILE("localWithFile")
    , LOCAL_WITH_NETWORK("localWithNetwork")
    , REMOTE("remote")
    {
//##protect##"class_::Security::Security()"
//##protect##"class_::Security::Security()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_system
{
    const MemberInfo Security::mi[Security::MemberInfoNum] = {
        {"APPLICATION", NULL, OFFSETOF(Classes::fl_system::Security, APPLICATION), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"LOCAL_TRUSTED", NULL, OFFSETOF(Classes::fl_system::Security, LOCAL_TRUSTED), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"LOCAL_WITH_FILE", NULL, OFFSETOF(Classes::fl_system::Security, LOCAL_WITH_FILE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"LOCAL_WITH_NETWORK", NULL, OFFSETOF(Classes::fl_system::Security, LOCAL_WITH_NETWORK), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"REMOTE", NULL, OFFSETOF(Classes::fl_system::Security, REMOTE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    const ThunkInfo Security::ti[Security::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, NULL, "allowDomain", NULL, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {ThunkInfo::EmptyFunc, NULL, "allowInsecureDomain", NULL, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {ThunkInfo::EmptyFunc, NULL, "loadPolicyFile", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "showSettings", NULL, Abc::NS_Public, CT_Method, 0, 1},
    };
    Security::Security(VM& vm)
    : Traits(vm, AS3::fl_system::SecurityCI)
    {
//##protect##"ClassTraits::Security::Security()"
//##protect##"ClassTraits::Security::Security()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_system::SecurityCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_system::Security(*this));

    }

    Pickable<Traits> Security::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Security(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_system
{
    const TypeInfo SecurityTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "Security", "flash.system", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo SecurityCI = {
        &SecurityTI,
        ClassTraits::fl_system::Security::MakeClassTraits,
        ClassTraits::fl_system::Security::ThunkInfoNum,
        ClassTraits::fl_system::Security::MemberInfoNum,
        1,
        0,
        ClassTraits::fl_system::Security::ti,
        ClassTraits::fl_system::Security::mi,
        InstanceTraits::fl_system::Security_ti,
        NULL,
    };
}; // namespace fl_system


}}} // namespace Scaleform { namespace GFx { namespace AS3

