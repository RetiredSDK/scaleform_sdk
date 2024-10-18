//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeMenu.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_NativeMenu.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class NativeMenuItem;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_display
{
    const ThunkInfo NativeMenu_ti[14] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "items", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "numItems", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_display::NativeMenuItemTI, "addItem", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_display::NativeMenuItemTI, "addItemAt", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, &AS3::fl_display::NativeMenuItemTI, "addSubmenu", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, &AS3::fl_display::NativeMenuItemTI, "addSubmenuAt", NULL, Abc::NS_Public, CT_Method, 3, 3},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "containsItem", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "display", NULL, Abc::NS_Public, CT_Method, 3, 3},
        {ThunkInfo::EmptyFunc, &AS3::fl_display::NativeMenuItemTI, "getItemAt", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_display::NativeMenuItemTI, "getItemByName", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "getItemIndex", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_display::NativeMenuItemTI, "removeItem", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_display::NativeMenuItemTI, "removeItemAt", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "setItemIndex", NULL, Abc::NS_Public, CT_Method, 2, 2},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_display
{
    NativeMenu::NativeMenu(VM& vm)
    : Traits(vm, AS3::fl_display::NativeMenuCI)
    {
//##protect##"ClassTraits::NativeMenu::NativeMenu()"
//##protect##"ClassTraits::NativeMenu::NativeMenu()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_display::NativeMenuCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> NativeMenu::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeMenu(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_display
{
    const TypeInfo NativeMenuTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "NativeMenu", "flash.display", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo NativeMenuCI = {
        &NativeMenuTI,
        ClassTraits::fl_display::NativeMenu::MakeClassTraits,
        0,
        0,
        14,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_display::NativeMenu_ti,
        NULL,
    };
}; // namespace fl_display


}}} // namespace Scaleform { namespace GFx { namespace AS3

