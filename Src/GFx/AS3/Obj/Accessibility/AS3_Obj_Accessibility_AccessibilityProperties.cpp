//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Accessibility_AccessibilityProperties.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Accessibility_AccessibilityProperties.h"
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

namespace Instances { namespace fl_accessibility
{
    AccessibilityProperties::AccessibilityProperties(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
    , description(AS3::DefaultValue<ASString>(GetStringManager()))
    , forceSimple()
    , name(AS3::DefaultValue<ASString>(GetStringManager()))
    , noAutoLabeling()
    , shortcut(AS3::DefaultValue<ASString>(GetStringManager()))
    , silent()
//##protect##"instance::AccessibilityProperties::AccessibilityProperties()$data"
//##protect##"instance::AccessibilityProperties::AccessibilityProperties()$data"
    {
//##protect##"instance::AccessibilityProperties::AccessibilityProperties()$code"
//##protect##"instance::AccessibilityProperties::AccessibilityProperties()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_accessibility
{
    const MemberInfo AccessibilityProperties::mi[AccessibilityProperties::MemberInfoNum] = {
        {"description", NULL, OFFSETOF(Instances::fl_accessibility::AccessibilityProperties, description), Abc::NS_Public, SlotInfo::BT_String, 0},
        {"forceSimple", NULL, OFFSETOF(Instances::fl_accessibility::AccessibilityProperties, forceSimple), Abc::NS_Public, SlotInfo::BT_Boolean, 0},
        {"name", NULL, OFFSETOF(Instances::fl_accessibility::AccessibilityProperties, name), Abc::NS_Public, SlotInfo::BT_String, 0},
        {"noAutoLabeling", NULL, OFFSETOF(Instances::fl_accessibility::AccessibilityProperties, noAutoLabeling), Abc::NS_Public, SlotInfo::BT_Boolean, 0},
        {"shortcut", NULL, OFFSETOF(Instances::fl_accessibility::AccessibilityProperties, shortcut), Abc::NS_Public, SlotInfo::BT_String, 0},
        {"silent", NULL, OFFSETOF(Instances::fl_accessibility::AccessibilityProperties, silent), Abc::NS_Public, SlotInfo::BT_Boolean, 0},
    };


    AccessibilityProperties::AccessibilityProperties(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::AccessibilityProperties::AccessibilityProperties()"
//##protect##"InstanceTraits::AccessibilityProperties::AccessibilityProperties()"
        SetMemSize(sizeof(Instances::fl_accessibility::AccessibilityProperties));

    }

    void AccessibilityProperties::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<AccessibilityProperties&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_accessibility
{
    AccessibilityProperties::AccessibilityProperties(VM& vm)
    : Traits(vm, AS3::fl_accessibility::AccessibilityPropertiesCI)
    {
//##protect##"ClassTraits::AccessibilityProperties::AccessibilityProperties()"
//##protect##"ClassTraits::AccessibilityProperties::AccessibilityProperties()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_accessibility::AccessibilityProperties(vm, AS3::fl_accessibility::AccessibilityPropertiesCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> AccessibilityProperties::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) AccessibilityProperties(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_accessibility
{
    const TypeInfo AccessibilityPropertiesTI = {
        TypeInfo::CompileTime,
        "AccessibilityProperties", "flash.accessibility", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo AccessibilityPropertiesCI = {
        &AccessibilityPropertiesTI,
        ClassTraits::fl_accessibility::AccessibilityProperties::MakeClassTraits,
        0,
        0,
        0,
        InstanceTraits::fl_accessibility::AccessibilityProperties::MemberInfoNum,
        NULL,
        NULL,
        NULL,
        InstanceTraits::fl_accessibility::AccessibilityProperties::mi,
    };
}; // namespace fl_accessibility


}}} // namespace Scaleform { namespace GFx { namespace AS3

