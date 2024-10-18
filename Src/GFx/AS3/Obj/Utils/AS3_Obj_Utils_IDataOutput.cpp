//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_IDataOutput.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Utils_IDataOutput.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Utils_ByteArray.h"
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
    const ThunkInfo IDataOutput_ti[16] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "endian", "flash.utils:IDataOutput", Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "endian", "flash.utils:IDataOutput", Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "objectEncoding", "flash.utils:IDataOutput", Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "objectEncoding", "flash.utils:IDataOutput", Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeBoolean", "flash.utils:IDataOutput", Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeByte", "flash.utils:IDataOutput", Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeBytes", "flash.utils:IDataOutput", Abc::NS_Public, CT_Method, 1, 3},
        {ThunkInfo::EmptyFunc, NULL, "writeDouble", "flash.utils:IDataOutput", Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeFloat", "flash.utils:IDataOutput", Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeInt", "flash.utils:IDataOutput", Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeMultiByte", "flash.utils:IDataOutput", Abc::NS_Public, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "writeObject", "flash.utils:IDataOutput", Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeShort", "flash.utils:IDataOutput", Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeUnsignedInt", "flash.utils:IDataOutput", Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeUTF", "flash.utils:IDataOutput", Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeUTFBytes", "flash.utils:IDataOutput", Abc::NS_Public, CT_Method, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_utils
{
    IDataOutput::IDataOutput(VM& vm)
    : Traits(vm, AS3::fl_utils::IDataOutputCI)
    {
//##protect##"ClassTraits::IDataOutput::IDataOutput()"
//##protect##"ClassTraits::IDataOutput::IDataOutput()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Interface(vm, AS3::fl_utils::IDataOutputCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> IDataOutput::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IDataOutput(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_utils
{
    const TypeInfo IDataOutputTI = {
        TypeInfo::CompileTime | TypeInfo::TypeInterface,
        "IDataOutput", "flash.utils", NULL,
        TypeInfo::None
    };

    const ClassInfo IDataOutputCI = {
        &IDataOutputTI,
        ClassTraits::fl_utils::IDataOutput::MakeClassTraits,
        0,
        0,
        16,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_utils::IDataOutput_ti,
        NULL,
    };
}; // namespace fl_utils


}}} // namespace Scaleform { namespace GFx { namespace AS3

