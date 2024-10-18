//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_ContextMenuItem.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Ui_ContextMenuItem.h"
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

namespace InstanceTraits { namespace fl_ui
{
    const ThunkInfo ContextMenuItem_ti[7] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "caption", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "caption", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "separatorBefore", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "separatorBefore", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "visible", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "visible", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_ui::ContextMenuItemTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_ui
{
    ContextMenuItem::ContextMenuItem(VM& vm)
    : Traits(vm, AS3::fl_ui::ContextMenuItemCI)
    {
//##protect##"ClassTraits::ContextMenuItem::ContextMenuItem()"
//##protect##"ClassTraits::ContextMenuItem::ContextMenuItem()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_ui::ContextMenuItemCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> ContextMenuItem::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ContextMenuItem(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_ui
{
    const TypeInfo ContextMenuItemTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "ContextMenuItem", "flash.ui", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo ContextMenuItemCI = {
        &ContextMenuItemTI,
        ClassTraits::fl_ui::ContextMenuItem::MakeClassTraits,
        0,
        0,
        7,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_ui::ContextMenuItem_ti,
        NULL,
    };
}; // namespace fl_ui


}}} // namespace Scaleform { namespace GFx { namespace AS3

