//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_SharedObjectFlushStatus.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_SharedObjectFlushStatus.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_net
{
    SharedObjectFlushStatus::SharedObjectFlushStatus(ClassTraits::Traits& t)
    : Class(t)
    , FLUSHED("flushed")
    , PENDING("pending")
    {
//##protect##"class_::SharedObjectFlushStatus::SharedObjectFlushStatus()"
//##protect##"class_::SharedObjectFlushStatus::SharedObjectFlushStatus()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_net
{
    const MemberInfo SharedObjectFlushStatus::mi[SharedObjectFlushStatus::MemberInfoNum] = {
        {"FLUSHED", NULL, OFFSETOF(Classes::fl_net::SharedObjectFlushStatus, FLUSHED), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"PENDING", NULL, OFFSETOF(Classes::fl_net::SharedObjectFlushStatus, PENDING), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    SharedObjectFlushStatus::SharedObjectFlushStatus(VM& vm)
    : Traits(vm, AS3::fl_net::SharedObjectFlushStatusCI)
    {
//##protect##"ClassTraits::SharedObjectFlushStatus::SharedObjectFlushStatus()"
//##protect##"ClassTraits::SharedObjectFlushStatus::SharedObjectFlushStatus()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_net::SharedObjectFlushStatusCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_net::SharedObjectFlushStatus(*this));

    }

    Pickable<Traits> SharedObjectFlushStatus::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SharedObjectFlushStatus(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_net
{
    const TypeInfo SharedObjectFlushStatusTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "SharedObjectFlushStatus", "flash.net", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo SharedObjectFlushStatusCI = {
        &SharedObjectFlushStatusTI,
        ClassTraits::fl_net::SharedObjectFlushStatus::MakeClassTraits,
        0,
        ClassTraits::fl_net::SharedObjectFlushStatus::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_net::SharedObjectFlushStatus::mi,
        NULL,
        NULL,
    };
}; // namespace fl_net


}}} // namespace Scaleform { namespace GFx { namespace AS3

