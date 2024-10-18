//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_IDynamicPropertyWriter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_IDynamicPropertyWriter.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Net_IDynamicPropertyOutput.h"
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
    const ThunkInfo IDynamicPropertyWriter_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "writeDynamicProperties", "flash.net:IDynamicPropertyWriter", Abc::NS_Public, CT_Method, 2, 2},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_net
{
    IDynamicPropertyWriter::IDynamicPropertyWriter(VM& vm)
    : Traits(vm, AS3::fl_net::IDynamicPropertyWriterCI)
    {
//##protect##"ClassTraits::IDynamicPropertyWriter::IDynamicPropertyWriter()"
//##protect##"ClassTraits::IDynamicPropertyWriter::IDynamicPropertyWriter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Interface(vm, AS3::fl_net::IDynamicPropertyWriterCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> IDynamicPropertyWriter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IDynamicPropertyWriter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_net
{
    const TypeInfo IDynamicPropertyWriterTI = {
        TypeInfo::CompileTime | TypeInfo::TypeInterface,
        "IDynamicPropertyWriter", "flash.net", NULL,
        TypeInfo::None
    };

    const ClassInfo IDynamicPropertyWriterCI = {
        &IDynamicPropertyWriterTI,
        ClassTraits::fl_net::IDynamicPropertyWriter::MakeClassTraits,
        0,
        0,
        1,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_net::IDynamicPropertyWriter_ti,
        NULL,
    };
}; // namespace fl_net


}}} // namespace Scaleform { namespace GFx { namespace AS3

