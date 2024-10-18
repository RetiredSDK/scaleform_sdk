//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_AVM1Movie.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_AVM1Movie.h"
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

namespace Instances { namespace fl_display
{
    AVM1Movie::AVM1Movie(InstanceTraits::Traits& t)
    : Instances::fl_display::DisplayObject(t)
//##protect##"instance::AVM1Movie::AVM1Movie()$data"
//##protect##"instance::AVM1Movie::AVM1Movie()$data"
    {
//##protect##"instance::AVM1Movie::AVM1Movie()$code"
//##protect##"instance::AVM1Movie::AVM1Movie()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_display
{

    AVM1Movie::AVM1Movie(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::AVM1Movie::AVM1Movie()"
        SetTraitsType(Traits_AVM1Movie);
//##protect##"InstanceTraits::AVM1Movie::AVM1Movie()"
        SetMemSize(sizeof(Instances::fl_display::AVM1Movie));

    }

    void AVM1Movie::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<AVM1Movie&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_display
{
    AVM1Movie::AVM1Movie(VM& vm)
    : Traits(vm, AS3::fl_display::AVM1MovieCI)
    {
//##protect##"ClassTraits::AVM1Movie::AVM1Movie()"
        SetTraitsType(Traits_AVM1Movie);
//##protect##"ClassTraits::AVM1Movie::AVM1Movie()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_display::AVM1Movie(vm, AS3::fl_display::AVM1MovieCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> AVM1Movie::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) AVM1Movie(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_display
{
    const TypeInfo AVM1MovieTI = {
        TypeInfo::CompileTime,
        "AVM1Movie", "flash.display", &fl_display::DisplayObjectTI,
        TypeInfo::None
    };

    const ClassInfo AVM1MovieCI = {
        &AVM1MovieTI,
        ClassTraits::fl_display::AVM1Movie::MakeClassTraits,
        0,
        0,
        0,
        0,
        NULL,
        NULL,
        NULL,
        NULL,
    };
}; // namespace fl_display


}}} // namespace Scaleform { namespace GFx { namespace AS3

