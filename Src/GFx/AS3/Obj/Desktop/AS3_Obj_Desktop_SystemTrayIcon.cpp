//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_SystemTrayIcon.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_SystemTrayIcon.h"
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
    const ThunkInfo SystemTrayIcon_ti[7] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "bitmaps", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bitmaps", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "height", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "menu", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "tooltip", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "tooltip", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "width", NULL, Abc::NS_Public, CT_Get, 0, 0},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_desktop
{
    SystemTrayIcon::SystemTrayIcon(ClassTraits::Traits& t)
    : Class(t)
    , MAX_TIP_LENGTH(63)
    {
//##protect##"class_::SystemTrayIcon::SystemTrayIcon()"
//##protect##"class_::SystemTrayIcon::SystemTrayIcon()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_desktop
{
    const MemberInfo SystemTrayIcon::mi[SystemTrayIcon::MemberInfoNum] = {
        {"MAX_TIP_LENGTH", NULL, OFFSETOF(Classes::fl_desktop::SystemTrayIcon, MAX_TIP_LENGTH), Abc::NS_Public, SlotInfo::BT_Number, 1},
    };

    SystemTrayIcon::SystemTrayIcon(VM& vm)
    : Traits(vm, AS3::fl_desktop::SystemTrayIconCI)
    {
//##protect##"ClassTraits::SystemTrayIcon::SystemTrayIcon()"
//##protect##"ClassTraits::SystemTrayIcon::SystemTrayIcon()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_desktop::SystemTrayIconCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_desktop::SystemTrayIcon(*this));

    }

    Pickable<Traits> SystemTrayIcon::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SystemTrayIcon(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_desktop
{
    const TypeInfo SystemTrayIconTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "SystemTrayIcon", "flash.desktop", &fl_desktop::InteractiveIconTI,
        TypeInfo::None
    };

    const ClassInfo SystemTrayIconCI = {
        &SystemTrayIconTI,
        ClassTraits::fl_desktop::SystemTrayIcon::MakeClassTraits,
        0,
        ClassTraits::fl_desktop::SystemTrayIcon::MemberInfoNum,
        7,
        0,
        NULL,
        ClassTraits::fl_desktop::SystemTrayIcon::mi,
        InstanceTraits::fl_desktop::SystemTrayIcon_ti,
        NULL,
    };
}; // namespace fl_desktop


}}} // namespace Scaleform { namespace GFx { namespace AS3

