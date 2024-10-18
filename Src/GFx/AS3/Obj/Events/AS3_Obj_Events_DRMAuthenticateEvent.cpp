//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_DRMAuthenticateEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_DRMAuthenticateEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class NetStream;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_events
{
    const ThunkInfo DRMAuthenticateEvent_ti[7] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "authenticationType", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "header", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "passwordPrompt", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "urlPrompt", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "usernamePrompt", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_events::EventTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_events
{
    DRMAuthenticateEvent::DRMAuthenticateEvent(ClassTraits::Traits& t)
    : Class(t)
    , AUTHENTICATION_TYPE_DRM("drm")
    , AUTHENTICATION_TYPE_PROXY("proxy")
    , DRM_AUTHENTICATE("drmAuthenticate")
    {
//##protect##"class_::DRMAuthenticateEvent::DRMAuthenticateEvent()"
//##protect##"class_::DRMAuthenticateEvent::DRMAuthenticateEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo DRMAuthenticateEvent::mi[DRMAuthenticateEvent::MemberInfoNum] = {
        {"AUTHENTICATION_TYPE_DRM", NULL, OFFSETOF(Classes::fl_events::DRMAuthenticateEvent, AUTHENTICATION_TYPE_DRM), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"AUTHENTICATION_TYPE_PROXY", NULL, OFFSETOF(Classes::fl_events::DRMAuthenticateEvent, AUTHENTICATION_TYPE_PROXY), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"DRM_AUTHENTICATE", NULL, OFFSETOF(Classes::fl_events::DRMAuthenticateEvent, DRM_AUTHENTICATE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    DRMAuthenticateEvent::DRMAuthenticateEvent(VM& vm)
    : Traits(vm, AS3::fl_events::DRMAuthenticateEventCI)
    {
//##protect##"ClassTraits::DRMAuthenticateEvent::DRMAuthenticateEvent()"
//##protect##"ClassTraits::DRMAuthenticateEvent::DRMAuthenticateEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::Event(vm, AS3::fl_events::DRMAuthenticateEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::DRMAuthenticateEvent(*this));

    }

    Pickable<Traits> DRMAuthenticateEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DRMAuthenticateEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo DRMAuthenticateEventTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "DRMAuthenticateEvent", "flash.events", &fl_events::EventTI,
        TypeInfo::None
    };

    const ClassInfo DRMAuthenticateEventCI = {
        &DRMAuthenticateEventTI,
        ClassTraits::fl_events::DRMAuthenticateEvent::MakeClassTraits,
        0,
        ClassTraits::fl_events::DRMAuthenticateEvent::MemberInfoNum,
        7,
        0,
        NULL,
        ClassTraits::fl_events::DRMAuthenticateEvent::mi,
        InstanceTraits::fl_events::DRMAuthenticateEvent_ti,
        NULL,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

