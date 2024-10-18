//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_XMLSocket.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_XMLSocket.h"
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
    const ThunkInfo XMLSocket_ti[4] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "connected", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "close", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "connect", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "send", NULL, Abc::NS_Public, CT_Method, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_net
{
    XMLSocket::XMLSocket(VM& vm)
    : Traits(vm, AS3::fl_net::XMLSocketCI)
    {
//##protect##"ClassTraits::XMLSocket::XMLSocket()"
//##protect##"ClassTraits::XMLSocket::XMLSocket()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_net::XMLSocketCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> XMLSocket::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) XMLSocket(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_net
{
    const TypeInfo XMLSocketTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "XMLSocket", "flash.net", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo XMLSocketCI = {
        &XMLSocketTI,
        ClassTraits::fl_net::XMLSocket::MakeClassTraits,
        0,
        0,
        4,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_net::XMLSocket_ti,
        NULL,
    };
}; // namespace fl_net


}}} // namespace Scaleform { namespace GFx { namespace AS3

