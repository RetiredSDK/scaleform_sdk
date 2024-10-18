//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_Updater.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_Updater.h"
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
    const ThunkInfo Updater_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "update", NULL, Abc::NS_Public, CT_Method, 2, 2},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_desktop
{
    Updater::Updater(VM& vm)
    : Traits(vm, AS3::fl_desktop::UpdaterCI)
    {
//##protect##"ClassTraits::Updater::Updater()"
//##protect##"ClassTraits::Updater::Updater()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_desktop::UpdaterCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> Updater::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Updater(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_desktop
{
    const TypeInfo UpdaterTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "Updater", "flash.desktop", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo UpdaterCI = {
        &UpdaterTI,
        ClassTraits::fl_desktop::Updater::MakeClassTraits,
        0,
        0,
        1,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_desktop::Updater_ti,
        NULL,
    };
}; // namespace fl_desktop


}}} // namespace Scaleform { namespace GFx { namespace AS3

