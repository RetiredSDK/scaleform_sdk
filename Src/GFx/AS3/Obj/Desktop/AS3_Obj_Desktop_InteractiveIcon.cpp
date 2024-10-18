//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_InteractiveIcon.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_InteractiveIcon.h"
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
    const ThunkInfo InteractiveIcon_ti[4] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "bitmaps", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bitmaps", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "height", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "width", NULL, Abc::NS_Public, CT_Get, 0, 0},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_desktop
{
    InteractiveIcon::InteractiveIcon(VM& vm)
    : Traits(vm, AS3::fl_desktop::InteractiveIconCI)
    {
//##protect##"ClassTraits::InteractiveIcon::InteractiveIcon()"
//##protect##"ClassTraits::InteractiveIcon::InteractiveIcon()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_desktop::InteractiveIconCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> InteractiveIcon::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) InteractiveIcon(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_desktop
{
    const TypeInfo InteractiveIconTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "InteractiveIcon", "flash.desktop", &fl_desktop::IconTI,
        TypeInfo::None
    };

    const ClassInfo InteractiveIconCI = {
        &InteractiveIconTI,
        ClassTraits::fl_desktop::InteractiveIcon::MakeClassTraits,
        0,
        0,
        4,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_desktop::InteractiveIcon_ti,
        NULL,
    };
}; // namespace fl_desktop


}}} // namespace Scaleform { namespace GFx { namespace AS3

