//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_NativeApplication.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_NativeApplication.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class NativeWindow;
    class InteractiveIcon;
    class NativeMenu;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_desktop
{
    const ThunkInfo NativeApplication_ti[29] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::XMLTI, "applicationDescriptor", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "applicationID", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "autoExit", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "autoExit", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_desktop::InteractiveIconTI, "icon", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "idleThreshold", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "idleThreshold", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "menu", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "openedWindows", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "publisherID", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "runtimePatchLevel", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "runtimeVersion", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "startAtLogin", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "startAtLogin", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "timeSinceLastUserInput", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "activate", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, NULL, "addEventListener", NULL, Abc::NS_Public, CT_Method, 2, 5},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "clear", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "copy", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "cut", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "dispatchEvent", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "exit", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "getDefaultApplication", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "isSetAsDefaultApplication", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "paste", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "removeAsDefaultApplication", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "removeEventListener", NULL, Abc::NS_Public, CT_Method, 2, 3},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "selectAll", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "setAsDefaultApplication", NULL, Abc::NS_Public, CT_Method, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_desktop
{
    NativeApplication::NativeApplication(VM& vm)
    : Traits(vm, AS3::fl_desktop::NativeApplicationCI)
    {
//##protect##"ClassTraits::NativeApplication::NativeApplication()"
//##protect##"ClassTraits::NativeApplication::NativeApplication()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_desktop::NativeApplicationCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> NativeApplication::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeApplication(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_desktop
{
    const TypeInfo NativeApplicationTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "NativeApplication", "flash.desktop", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo NativeApplicationCI = {
        &NativeApplicationTI,
        ClassTraits::fl_desktop::NativeApplication::MakeClassTraits,
        0,
        0,
        29,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_desktop::NativeApplication_ti,
        NULL,
    };
}; // namespace fl_desktop


}}} // namespace Scaleform { namespace GFx { namespace AS3

