//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_IDataInput.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Utils_IDataInput.h"
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
    const ThunkInfo IDataInput_ti[19] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "bytesAvailable", "flash.utils:IDataInput", Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "endian", "flash.utils:IDataInput", Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "endian", "flash.utils:IDataInput", Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "objectEncoding", "flash.utils:IDataInput", Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "objectEncoding", "flash.utils:IDataInput", Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "readBoolean", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "readByte", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "readBytes", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 1, 3},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "readDouble", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "readFloat", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "readInt", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "readMultiByte", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "readObject", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "readShort", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "readUnsignedByte", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "readUnsignedInt", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "readUnsignedShort", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "readUTF", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "readUTFBytes", "flash.utils:IDataInput", Abc::NS_Public, CT_Method, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_utils
{
    IDataInput::IDataInput(VM& vm)
    : Traits(vm, AS3::fl_utils::IDataInputCI)
    {
//##protect##"ClassTraits::IDataInput::IDataInput()"
//##protect##"ClassTraits::IDataInput::IDataInput()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Interface(vm, AS3::fl_utils::IDataInputCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> IDataInput::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IDataInput(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_utils
{
    const TypeInfo IDataInputTI = {
        TypeInfo::CompileTime | TypeInfo::TypeInterface,
        "IDataInput", "flash.utils", NULL,
        TypeInfo::None
    };

    const ClassInfo IDataInputCI = {
        &IDataInputTI,
        ClassTraits::fl_utils::IDataInput::MakeClassTraits,
        0,
        0,
        19,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_utils::IDataInput_ti,
        NULL,
    };
}; // namespace fl_utils


}}} // namespace Scaleform { namespace GFx { namespace AS3

