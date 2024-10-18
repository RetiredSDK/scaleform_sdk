//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_Icon.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_Icon.h"
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

namespace InstanceTraits { namespace fl_desktop
{
    const ThunkInfo Icon_ti[2] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "bitmaps", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bitmaps", NULL, Abc::NS_Public, CT_Set, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_desktop
{
    Icon::Icon(VM& vm)
    : Traits(vm, AS3::fl_desktop::IconCI)
    {
//##protect##"ClassTraits::Icon::Icon()"
//##protect##"ClassTraits::Icon::Icon()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_desktop::IconCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> Icon::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Icon(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_desktop
{
    const TypeInfo IconTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "Icon", "flash.desktop", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo IconCI = {
        &IconTI,
        ClassTraits::fl_desktop::Icon::MakeClassTraits,
        0,
        0,
        2,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_desktop::Icon_ti,
        NULL,
    };
}; // namespace fl_desktop


}}} // namespace Scaleform { namespace GFx { namespace AS3

