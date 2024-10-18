//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Accessibility_AccessibilityImplementation.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Accessibility_AccessibilityImplementation.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Geom/AS3_Obj_Geom_Rectangle.h"
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
    AccessibilityImplementation::AccessibilityImplementation(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
    , errno()
    , stub()
//##protect##"instance::AccessibilityImplementation::AccessibilityImplementation()$data"
//##protect##"instance::AccessibilityImplementation::AccessibilityImplementation()$data"
    {
//##protect##"instance::AccessibilityImplementation::AccessibilityImplementation()$code"
//##protect##"instance::AccessibilityImplementation::AccessibilityImplementation()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_accessibility
{
    const ThunkInfo AccessibilityImplementation::ti[AccessibilityImplementation::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, NULL, "accDoDefaultAction", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "accLocation", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "accSelect", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "get_accDefaultAction", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "get_accFocus", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "get_accName", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "get_accRole", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "get_accSelection", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::uintTI, "get_accState", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "get_accValue", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "getChildIDArray", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "isLabeledBy", NULL, Abc::NS_Public, CT_Method, 1, 1},
    };
    const MemberInfo AccessibilityImplementation::mi[AccessibilityImplementation::MemberInfoNum] = {
        {"errno", NULL, OFFSETOF(Instances::fl_accessibility::AccessibilityImplementation, errno), Abc::NS_Public, SlotInfo::BT_UInt, 0},
        {"stub", NULL, OFFSETOF(Instances::fl_accessibility::AccessibilityImplementation, stub), Abc::NS_Public, SlotInfo::BT_Boolean, 0},
    };


    AccessibilityImplementation::AccessibilityImplementation(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::AccessibilityImplementation::AccessibilityImplementation()"
//##protect##"InstanceTraits::AccessibilityImplementation::AccessibilityImplementation()"
        SetMemSize(sizeof(Instances::fl_accessibility::AccessibilityImplementation));

    }

    void AccessibilityImplementation::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<AccessibilityImplementation&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_accessibility
{
    AccessibilityImplementation::AccessibilityImplementation(VM& vm)
    : Traits(vm, AS3::fl_accessibility::AccessibilityImplementationCI)
    {
//##protect##"ClassTraits::AccessibilityImplementation::AccessibilityImplementation()"
//##protect##"ClassTraits::AccessibilityImplementation::AccessibilityImplementation()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_accessibility::AccessibilityImplementation(vm, AS3::fl_accessibility::AccessibilityImplementationCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> AccessibilityImplementation::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) AccessibilityImplementation(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_accessibility
{
    const TypeInfo AccessibilityImplementationTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "AccessibilityImplementation", "flash.accessibility", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo AccessibilityImplementationCI = {
        &AccessibilityImplementationTI,
        ClassTraits::fl_accessibility::AccessibilityImplementation::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_accessibility::AccessibilityImplementation::ThunkInfoNum,
        InstanceTraits::fl_accessibility::AccessibilityImplementation::MemberInfoNum,
        NULL,
        NULL,
        InstanceTraits::fl_accessibility::AccessibilityImplementation::ti,
        InstanceTraits::fl_accessibility::AccessibilityImplementation::mi,
    };
}; // namespace fl_accessibility


}}} // namespace Scaleform { namespace GFx { namespace AS3

