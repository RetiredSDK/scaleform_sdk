//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_IExternalizable.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Utils_IExternalizable.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Utils_IDataOutput.h"
#include "AS3_Obj_Utils_IDataInput.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_utils
{
    const ThunkInfo IExternalizable_ti[2] = {
        {ThunkInfo::EmptyFunc, NULL, "readExternal", "flash.utils:IExternalizable", Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeExternal", "flash.utils:IExternalizable", Abc::NS_Public, CT_Method, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_utils
{
    IExternalizable::IExternalizable(VM& vm)
    : Traits(vm, AS3::fl_utils::IExternalizableCI)
    {
//##protect##"ClassTraits::IExternalizable::IExternalizable()"
//##protect##"ClassTraits::IExternalizable::IExternalizable()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Interface(vm, AS3::fl_utils::IExternalizableCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> IExternalizable::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IExternalizable(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_utils
{
    const TypeInfo IExternalizableTI = {
        TypeInfo::CompileTime | TypeInfo::TypeInterface,
        "IExternalizable", "flash.utils", NULL,
        TypeInfo::None
    };

    const ClassInfo IExternalizableCI = {
        &IExternalizableTI,
        ClassTraits::fl_utils::IExternalizable::MakeClassTraits,
        0,
        0,
        2,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_utils::IExternalizable_ti,
        NULL,
    };
}; // namespace fl_utils


}}} // namespace Scaleform { namespace GFx { namespace AS3

