//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeWindowInitOptions.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_NativeWindowInitOptions.h"
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

namespace InstanceTraits { namespace fl_display
{
    const ThunkInfo NativeWindowInitOptions_ti[12] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "maximizable", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "maximizable", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "minimizable", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "minimizable", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "resizable", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "resizable", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "systemChrome", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "systemChrome", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "transparent", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "transparent", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "type", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "type", NULL, Abc::NS_Public, CT_Set, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_display
{
    NativeWindowInitOptions::NativeWindowInitOptions(VM& vm)
    : Traits(vm, AS3::fl_display::NativeWindowInitOptionsCI)
    {
//##protect##"ClassTraits::NativeWindowInitOptions::NativeWindowInitOptions()"
//##protect##"ClassTraits::NativeWindowInitOptions::NativeWindowInitOptions()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_display::NativeWindowInitOptionsCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> NativeWindowInitOptions::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeWindowInitOptions(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_display
{
    const TypeInfo NativeWindowInitOptionsTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "NativeWindowInitOptions", "flash.display", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo NativeWindowInitOptionsCI = {
        &NativeWindowInitOptionsTI,
        ClassTraits::fl_display::NativeWindowInitOptions::MakeClassTraits,
        0,
        0,
        12,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_display::NativeWindowInitOptions_ti,
        NULL,
    };
}; // namespace fl_display


}}} // namespace Scaleform { namespace GFx { namespace AS3

