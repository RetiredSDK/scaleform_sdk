//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeWindow.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_NativeWindow.h"
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
    class Point;
    class NativeMenu;
    class Stage;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_display
{
    const ThunkInfo NativeWindow_ti[44] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "active", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "alwaysInFront", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "alwaysInFront", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_geom::RectangleTI, "bounds", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bounds", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "closed", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "displayState", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "height", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "height", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "maximizable", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_geom::PointTI, "maxSize", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "maxSize", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "menu", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "minimizable", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_geom::PointTI, "minSize", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "minSize", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "resizable", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_display::StageTI, "stage", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "systemChrome", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "title", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "title", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "transparent", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "type", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "visible", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "visible", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "width", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "width", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "x", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "x", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "y", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "y", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "activate", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "close", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_geom::PointTI, "globalToScreen", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "maximize", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "minimize", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "notifyUser", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "orderInBackOf", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "orderInFrontOf", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "orderToBack", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "orderToFront", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "restore", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "startMove", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "startResize", NULL, Abc::NS_Public, CT_Method, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_display
{
    NativeWindow::NativeWindow(VM& vm)
    : Traits(vm, AS3::fl_display::NativeWindowCI)
    {
//##protect##"ClassTraits::NativeWindow::NativeWindow()"
//##protect##"ClassTraits::NativeWindow::NativeWindow()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_display::NativeWindowCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> NativeWindow::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeWindow(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_display
{
    const TypeInfo NativeWindowTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "NativeWindow", "flash.display", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo NativeWindowCI = {
        &NativeWindowTI,
        ClassTraits::fl_display::NativeWindow::MakeClassTraits,
        0,
        0,
        44,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_display::NativeWindow_ti,
        NULL,
    };
}; // namespace fl_display


}}} // namespace Scaleform { namespace GFx { namespace AS3

