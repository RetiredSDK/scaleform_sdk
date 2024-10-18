//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLStream.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_URLStream.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Net_URLRequest.h"
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

namespace InstanceTraits { namespace fl_net
{
    const ThunkInfo URLStream_ti[22] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "bytesAvailable", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "connected", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "endian", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "endian", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "objectEncoding", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "objectEncoding", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "close", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "load", NULL, Abc::NS_Public, CT_Method, 1, 1},
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
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_net
{
    URLStream::URLStream(VM& vm)
    : Traits(vm, AS3::fl_net::URLStreamCI)
    {
//##protect##"ClassTraits::URLStream::URLStream()"
//##protect##"ClassTraits::URLStream::URLStream()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_net::URLStreamCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> URLStream::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) URLStream(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_net
{
    const TypeInfo* URLStreamImplements[] = {
        &fl_utils::IDataInputTI,
        NULL
    };

    const TypeInfo URLStreamTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "URLStream", "flash.net", &fl_events::EventDispatcherTI,
        URLStreamImplements
    };

    const ClassInfo URLStreamCI = {
        &URLStreamTI,
        ClassTraits::fl_net::URLStream::MakeClassTraits,
        0,
        0,
        22,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_net::URLStream_ti,
        NULL,
    };
}; // namespace fl_net


}}} // namespace Scaleform { namespace GFx { namespace AS3

