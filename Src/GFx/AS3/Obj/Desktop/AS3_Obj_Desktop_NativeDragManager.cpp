//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_NativeDragManager.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_NativeDragManager.h"
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
    const ThunkInfo NativeDragManager_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "dropAction", NULL, Abc::NS_Public, CT_Set, 1, 1},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_desktop
{
    NativeDragManager::NativeDragManager(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::NativeDragManager::NativeDragManager()"
//##protect##"class_::NativeDragManager::NativeDragManager()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_desktop
{
    const ThunkInfo NativeDragManager_ti[2] = {
        {ThunkInfo::EmptyFunc, NULL, "acceptDragDrop", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "doDrag", NULL, Abc::NS_Public, CT_Method, 2, 5},
    };
    NativeDragManager::NativeDragManager(VM& vm)
    : Traits(vm, AS3::fl_desktop::NativeDragManagerCI)
    {
//##protect##"ClassTraits::NativeDragManager::NativeDragManager()"
//##protect##"ClassTraits::NativeDragManager::NativeDragManager()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_desktop::NativeDragManagerCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_desktop::NativeDragManager(*this));

    }

    Pickable<Traits> NativeDragManager::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeDragManager(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_desktop
{
    const TypeInfo NativeDragManagerTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "NativeDragManager", "flash.desktop", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo NativeDragManagerCI = {
        &NativeDragManagerTI,
        ClassTraits::fl_desktop::NativeDragManager::MakeClassTraits,
        2,
        0,
        1,
        0,
        ClassTraits::fl_desktop::NativeDragManager_ti,
        NULL,
        InstanceTraits::fl_desktop::NativeDragManager_ti,
        NULL,
    };
}; // namespace fl_desktop


}}} // namespace Scaleform { namespace GFx { namespace AS3

