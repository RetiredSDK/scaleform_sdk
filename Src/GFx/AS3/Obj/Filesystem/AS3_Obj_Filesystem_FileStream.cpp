//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filesystem_FileStream.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filesystem_FileStream.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Filesystem_File.h"
#include "../Utils/AS3_Obj_Utils_ByteArray.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_filesystem
{
    const ThunkInfo FileStream_ti[39] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "bytesAvailable", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "endian", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "endian", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "objectEncoding", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "objectEncoding", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "position", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "position", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "readAhead", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "readAhead", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "close", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "open", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "openAsync", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "readBoolean", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "readByte", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "readBytes", NULL, Abc::NS_Public, CT_Method, 1, 3},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "readDouble", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "readFloat", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "readInt", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "readMultiByte", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "readObject", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "readShort", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "readUnsignedByte", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "readUnsignedInt", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "readUnsignedShort", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "readUTF", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "readUTFBytes", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "truncate", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "writeBoolean", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeByte", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeBytes", NULL, Abc::NS_Public, CT_Method, 1, 3},
        {ThunkInfo::EmptyFunc, NULL, "writeDouble", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeFloat", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeInt", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeMultiByte", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "writeObject", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeShort", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeUnsignedInt", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeUTF", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeUTFBytes", NULL, Abc::NS_Public, CT_Method, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_filesystem
{
    FileStream::FileStream(VM& vm)
    : Traits(vm, AS3::fl_filesystem::FileStreamCI)
    {
//##protect##"ClassTraits::FileStream::FileStream()"
//##protect##"ClassTraits::FileStream::FileStream()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_filesystem::FileStreamCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> FileStream::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FileStream(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_filesystem
{
    const TypeInfo* FileStreamImplements[] = {
        &fl_utils::IDataInputTI,
        &fl_utils::IDataOutputTI,
        NULL
    };

    const TypeInfo FileStreamTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "FileStream", "flash.filesystem", &fl_events::EventDispatcherTI,
        FileStreamImplements
    };

    const ClassInfo FileStreamCI = {
        &FileStreamTI,
        ClassTraits::fl_filesystem::FileStream::MakeClassTraits,
        0,
        0,
        39,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_filesystem::FileStream_ti,
        NULL,
    };
}; // namespace fl_filesystem


}}} // namespace Scaleform { namespace GFx { namespace AS3

