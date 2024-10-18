//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLRequestHeader.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_URLRequestHeader.h"
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

namespace Instances { namespace fl_net
{
    URLRequestHeader::URLRequestHeader(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
    , name(AS3::DefaultValue<ASString>(GetStringManager()))
    , value(AS3::DefaultValue<ASString>(GetStringManager()))
//##protect##"instance::URLRequestHeader::URLRequestHeader()$data"
//##protect##"instance::URLRequestHeader::URLRequestHeader()$data"
    {
//##protect##"instance::URLRequestHeader::URLRequestHeader()$code"
//##protect##"instance::URLRequestHeader::URLRequestHeader()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_net
{
    const MemberInfo URLRequestHeader::mi[URLRequestHeader::MemberInfoNum] = {
        {"name", NULL, OFFSETOF(Instances::fl_net::URLRequestHeader, name), Abc::NS_Public, SlotInfo::BT_String, 0},
        {"value", NULL, OFFSETOF(Instances::fl_net::URLRequestHeader, value), Abc::NS_Public, SlotInfo::BT_String, 0},
    };


    URLRequestHeader::URLRequestHeader(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::URLRequestHeader::URLRequestHeader()"
//##protect##"InstanceTraits::URLRequestHeader::URLRequestHeader()"
        SetMemSize(sizeof(Instances::fl_net::URLRequestHeader));

    }

    void URLRequestHeader::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<URLRequestHeader&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_net
{
    URLRequestHeader::URLRequestHeader(VM& vm)
    : Traits(vm, AS3::fl_net::URLRequestHeaderCI)
    {
//##protect##"ClassTraits::URLRequestHeader::URLRequestHeader()"
//##protect##"ClassTraits::URLRequestHeader::URLRequestHeader()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_net::URLRequestHeader(vm, AS3::fl_net::URLRequestHeaderCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> URLRequestHeader::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) URLRequestHeader(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_net
{
    const TypeInfo URLRequestHeaderTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "URLRequestHeader", "flash.net", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo URLRequestHeaderCI = {
        &URLRequestHeaderTI,
        ClassTraits::fl_net::URLRequestHeader::MakeClassTraits,
        0,
        0,
        0,
        InstanceTraits::fl_net::URLRequestHeader::MemberInfoNum,
        NULL,
        NULL,
        NULL,
        InstanceTraits::fl_net::URLRequestHeader::mi,
    };
}; // namespace fl_net


}}} // namespace Scaleform { namespace GFx { namespace AS3

