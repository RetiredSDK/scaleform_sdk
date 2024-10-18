//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_DockIcon.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_DockIcon.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class NativeMenu;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_desktop
{
    const ThunkInfo DockIcon_ti[6] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "bitmaps", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bitmaps", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "height", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "menu", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "width", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bounce", NULL, Abc::NS_Public, CT_Method, 0, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_desktop
{
    DockIcon::DockIcon(VM& vm)
    : Traits(vm, AS3::fl_desktop::DockIconCI)
    {
//##protect##"ClassTraits::DockIcon::DockIcon()"
//##protect##"ClassTraits::DockIcon::DockIcon()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_desktop::DockIconCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> DockIcon::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DockIcon(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_desktop
{
    const TypeInfo DockIconTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "DockIcon", "flash.desktop", &fl_desktop::InteractiveIconTI,
        TypeInfo::None
    };

    const ClassInfo DockIconCI = {
        &DockIconTI,
        ClassTraits::fl_desktop::DockIcon::MakeClassTraits,
        0,
        0,
        6,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_desktop::DockIcon_ti,
        NULL,
    };
}; // namespace fl_desktop


}}} // namespace Scaleform { namespace GFx { namespace AS3

