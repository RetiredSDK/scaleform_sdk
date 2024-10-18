//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_IDynamicPropertyOutput.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_IDynamicPropertyOutput.h"
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

namespace InstanceTraits { namespace fl_net
{
    const ThunkInfo IDynamicPropertyOutput_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "writeDynamicProperty", "flash.net:IDynamicPropertyOutput", Abc::NS_Public, CT_Method, 2, 2},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_net
{
    IDynamicPropertyOutput::IDynamicPropertyOutput(VM& vm)
    : Traits(vm, AS3::fl_net::IDynamicPropertyOutputCI)
    {
//##protect##"ClassTraits::IDynamicPropertyOutput::IDynamicPropertyOutput()"
//##protect##"ClassTraits::IDynamicPropertyOutput::IDynamicPropertyOutput()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Interface(vm, AS3::fl_net::IDynamicPropertyOutputCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> IDynamicPropertyOutput::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IDynamicPropertyOutput(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_net
{
    const TypeInfo IDynamicPropertyOutputTI = {
        TypeInfo::CompileTime | TypeInfo::TypeInterface,
        "IDynamicPropertyOutput", "flash.net", NULL,
        TypeInfo::None
    };

    const ClassInfo IDynamicPropertyOutputCI = {
        &IDynamicPropertyOutputTI,
        ClassTraits::fl_net::IDynamicPropertyOutput::MakeClassTraits,
        0,
        0,
        1,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_net::IDynamicPropertyOutput_ti,
        NULL,
    };
}; // namespace fl_net


}}} // namespace Scaleform { namespace GFx { namespace AS3

