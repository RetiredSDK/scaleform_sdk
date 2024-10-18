//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Accessibility_Accessibility.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Accessibility_Accessibility.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_accessibility
{
    Accessibility::Accessibility(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Accessibility::Accessibility()"
//##protect##"class_::Accessibility::Accessibility()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_accessibility
{
    const ThunkInfo Accessibility_ti[2] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "active", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "updateProperties", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };
    Accessibility::Accessibility(VM& vm)
    : Traits(vm, AS3::fl_accessibility::AccessibilityCI)
    {
//##protect##"ClassTraits::Accessibility::Accessibility()"
//##protect##"ClassTraits::Accessibility::Accessibility()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_accessibility::AccessibilityCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_accessibility::Accessibility(*this));

    }

    Pickable<Traits> Accessibility::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Accessibility(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_accessibility
{
    const TypeInfo AccessibilityTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "Accessibility", "flash.accessibility", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo AccessibilityCI = {
        &AccessibilityTI,
        ClassTraits::fl_accessibility::Accessibility::MakeClassTraits,
        2,
        0,
        0,
        0,
        ClassTraits::fl_accessibility::Accessibility_ti,
        NULL,
        NULL,
        NULL,
    };
}; // namespace fl_accessibility


}}} // namespace Scaleform { namespace GFx { namespace AS3

