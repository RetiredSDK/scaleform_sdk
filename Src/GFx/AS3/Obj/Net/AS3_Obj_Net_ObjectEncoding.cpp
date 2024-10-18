//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_ObjectEncoding.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_ObjectEncoding.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Net_IDynamicPropertyWriter.h"
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
    const ThunkInfo ObjectEncoding_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "dynamicPropertyWriter", NULL, Abc::NS_Public, CT_Set, 1, 1},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_net
{
    ObjectEncoding::ObjectEncoding(ClassTraits::Traits& t)
    : Class(t)
    , AMF0(0)
    , AMF3(3)
    , DEFAULT(3)
    {
//##protect##"class_::ObjectEncoding::ObjectEncoding()"
//##protect##"class_::ObjectEncoding::ObjectEncoding()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_net
{
    const MemberInfo ObjectEncoding::mi[ObjectEncoding::MemberInfoNum] = {
        {"AMF0", NULL, OFFSETOF(Classes::fl_net::ObjectEncoding, AMF0), Abc::NS_Public, SlotInfo::BT_UInt, 1},
        {"AMF3", NULL, OFFSETOF(Classes::fl_net::ObjectEncoding, AMF3), Abc::NS_Public, SlotInfo::BT_UInt, 1},
        {"DEFAULT", NULL, OFFSETOF(Classes::fl_net::ObjectEncoding, DEFAULT), Abc::NS_Public, SlotInfo::BT_UInt, 1},
    };

    ObjectEncoding::ObjectEncoding(VM& vm)
    : Traits(vm, AS3::fl_net::ObjectEncodingCI)
    {
//##protect##"ClassTraits::ObjectEncoding::ObjectEncoding()"
//##protect##"ClassTraits::ObjectEncoding::ObjectEncoding()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_net::ObjectEncodingCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_net::ObjectEncoding(*this));

    }

    Pickable<Traits> ObjectEncoding::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ObjectEncoding(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_net
{
    const TypeInfo ObjectEncodingTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "ObjectEncoding", "flash.net", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo ObjectEncodingCI = {
        &ObjectEncodingTI,
        ClassTraits::fl_net::ObjectEncoding::MakeClassTraits,
        0,
        ClassTraits::fl_net::ObjectEncoding::MemberInfoNum,
        1,
        0,
        NULL,
        ClassTraits::fl_net::ObjectEncoding::mi,
        InstanceTraits::fl_net::ObjectEncoding_ti,
        NULL,
    };
}; // namespace fl_net


}}} // namespace Scaleform { namespace GFx { namespace AS3

