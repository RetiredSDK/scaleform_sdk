//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_KeyboardEventEx.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_KeyboardEventEx.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../../AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace Instances { namespace fl_gfx
{
    KeyboardEventEx::KeyboardEventEx(InstanceTraits::Traits& t)
    : Instances::fl_events::KeyboardEvent(t)
    , controllerIdx()
//##protect##"instance::KeyboardEventEx::KeyboardEventEx()$data"
//##protect##"instance::KeyboardEventEx::KeyboardEventEx()$data"
    {
//##protect##"instance::KeyboardEventEx::KeyboardEventEx()$code"
//##protect##"instance::KeyboardEventEx::KeyboardEventEx()$code"
    }


//##protect##"instance$methods"
    AS3::Object* KeyboardEventEx::GetEventClass() const 
    { 
        return static_cast<ASVM&>(GetVM()).KeyboardEventExClass; 
    }

    SPtr<Instances::fl_events::Event> KeyboardEventEx::Clone() const
    {
        SPtr<Instances::fl_events::Event> p = Event::Clone();
        KeyboardEventEx* pe   = static_cast<KeyboardEventEx*>(p.GetPtr());
        pe->EvtId           = EvtId;
        pe->KeyLocation     = KeyLocation;
        pe->controllerIdx   = controllerIdx;
        return p;
    }
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_gfx
{
    const MemberInfo KeyboardEventEx::mi[KeyboardEventEx::MemberInfoNum] = {
        {"controllerIdx", NULL, OFFSETOF(Instances::fl_gfx::KeyboardEventEx, controllerIdx), Abc::NS_Public, SlotInfo::BT_UInt, 0},
    };


    KeyboardEventEx::KeyboardEventEx(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::KeyboardEventEx::KeyboardEventEx()"
//##protect##"InstanceTraits::KeyboardEventEx::KeyboardEventEx()"
        SetMemSize(sizeof(Instances::fl_gfx::KeyboardEventEx));

    }

    void KeyboardEventEx::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<KeyboardEventEx&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_gfx
{
    KeyboardEventEx::KeyboardEventEx(VM& vm)
    : Traits(vm, AS3::fl_gfx::KeyboardEventExCI)
    {
//##protect##"ClassTraits::KeyboardEventEx::KeyboardEventEx()"
//##protect##"ClassTraits::KeyboardEventEx::KeyboardEventEx()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_gfx::KeyboardEventEx(vm, AS3::fl_gfx::KeyboardEventExCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> KeyboardEventEx::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) KeyboardEventEx(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_gfx
{
    const TypeInfo KeyboardEventExTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "KeyboardEventEx", "scaleform.gfx", &fl_events::KeyboardEventTI,
        TypeInfo::None
    };

    const ClassInfo KeyboardEventExCI = {
        &KeyboardEventExTI,
        ClassTraits::fl_gfx::KeyboardEventEx::MakeClassTraits,
        0,
        0,
        0,
        InstanceTraits::fl_gfx::KeyboardEventEx::MemberInfoNum,
        NULL,
        NULL,
        NULL,
        InstanceTraits::fl_gfx::KeyboardEventEx::mi,
    };
}; // namespace fl_gfx


}}} // namespace Scaleform { namespace GFx { namespace AS3

