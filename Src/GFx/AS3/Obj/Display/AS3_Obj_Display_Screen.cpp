//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Screen.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_Screen.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class Rectangle;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_display
{
    const ThunkInfo Screen_ti[3] = {
        {ThunkInfo::EmptyFunc, &AS3::fl_geom::RectangleTI, "bounds", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "colorDepth", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_geom::RectangleTI, "visibleBounds", NULL, Abc::NS_Public, CT_Get, 0, 0},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_display
{
    Screen::Screen(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Screen::Screen()"
//##protect##"class_::Screen::Screen()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_display
{
    const ThunkInfo Screen_ti[1] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "getScreensForRectangle", NULL, Abc::NS_Public, CT_Method, 1, 1},
    };
    Screen::Screen(VM& vm)
    : Traits(vm, AS3::fl_display::ScreenCI)
    {
//##protect##"ClassTraits::Screen::Screen()"
//##protect##"ClassTraits::Screen::Screen()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_display::ScreenCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_display::Screen(*this));

    }

    Pickable<Traits> Screen::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Screen(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_display
{
    const TypeInfo ScreenTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "Screen", "flash.display", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo ScreenCI = {
        &ScreenTI,
        ClassTraits::fl_display::Screen::MakeClassTraits,
        1,
        0,
        3,
        0,
        ClassTraits::fl_display::Screen_ti,
        NULL,
        InstanceTraits::fl_display::Screen_ti,
        NULL,
    };
}; // namespace fl_display


}}} // namespace Scaleform { namespace GFx { namespace AS3

