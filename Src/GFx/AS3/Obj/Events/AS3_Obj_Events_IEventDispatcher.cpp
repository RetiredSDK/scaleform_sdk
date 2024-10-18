//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_IEventDispatcher.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_IEventDispatcher.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Events_Event.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_events
{
    const ThunkInfo IEventDispatcher_ti[5] = {
        {ThunkInfo::EmptyFunc, NULL, "addEventListener", "flash.events:IEventDispatcher", Abc::NS_Public, CT_Method, 2, 5},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "dispatchEvent", "flash.events:IEventDispatcher", Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "hasEventListener", "flash.events:IEventDispatcher", Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "removeEventListener", "flash.events:IEventDispatcher", Abc::NS_Public, CT_Method, 2, 3},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "willTrigger", "flash.events:IEventDispatcher", Abc::NS_Public, CT_Method, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_events
{
    IEventDispatcher::IEventDispatcher(VM& vm)
    : Traits(vm, AS3::fl_events::IEventDispatcherCI)
    {
//##protect##"ClassTraits::IEventDispatcher::IEventDispatcher()"
//##protect##"ClassTraits::IEventDispatcher::IEventDispatcher()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Interface(vm, AS3::fl_events::IEventDispatcherCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> IEventDispatcher::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IEventDispatcher(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo IEventDispatcherTI = {
        TypeInfo::CompileTime | TypeInfo::TypeInterface,
        "IEventDispatcher", "flash.events", NULL,
        TypeInfo::None
    };

    const ClassInfo IEventDispatcherCI = {
        &IEventDispatcherTI,
        ClassTraits::fl_events::IEventDispatcher::MakeClassTraits,
        0,
        0,
        5,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_events::IEventDispatcher_ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

