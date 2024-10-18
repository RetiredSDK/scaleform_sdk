//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_Proxy.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Utils_Proxy.h"
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

namespace InstanceTraits { namespace fl_utils
{
    const ThunkInfo Proxy_ti[10] = {
        {ThunkInfo::EmptyFunc, NULL, "callProperty", NS_flash_proxy, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "deleteProperty", NS_flash_proxy, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "getDescendants", NS_flash_proxy, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "getProperty", NS_flash_proxy, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "hasProperty", NS_flash_proxy, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "isAttribute", NS_flash_proxy, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "nextName", NS_flash_proxy, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "nextNameIndex", NS_flash_proxy, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "nextValue", NS_flash_proxy, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "setProperty", NS_flash_proxy, Abc::NS_Public, CT_Method, 2, 2},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_utils
{
    Proxy::Proxy(VM& vm)
    : Traits(vm, AS3::fl_utils::ProxyCI)
    {
//##protect##"ClassTraits::Proxy::Proxy()"
//##protect##"ClassTraits::Proxy::Proxy()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_utils::ProxyCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> Proxy::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Proxy(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_utils
{
    const TypeInfo ProxyTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "Proxy", "flash.utils", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo ProxyCI = {
        &ProxyTI,
        ClassTraits::fl_utils::Proxy::MakeClassTraits,
        0,
        0,
        10,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_utils::Proxy_ti,
        NULL,
    };
}; // namespace fl_utils


}}} // namespace Scaleform { namespace GFx { namespace AS3

