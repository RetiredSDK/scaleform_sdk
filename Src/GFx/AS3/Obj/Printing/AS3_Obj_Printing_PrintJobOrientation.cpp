//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Printing_PrintJobOrientation.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Printing_PrintJobOrientation.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_printing
{
    PrintJobOrientation::PrintJobOrientation(ClassTraits::Traits& t)
    : Class(t)
    , LANDSCAPE("landscape")
    , PORTRAIT("portrait")
    {
//##protect##"class_::PrintJobOrientation::PrintJobOrientation()"
//##protect##"class_::PrintJobOrientation::PrintJobOrientation()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_printing
{
    const MemberInfo PrintJobOrientation::mi[PrintJobOrientation::MemberInfoNum] = {
        {"LANDSCAPE", NULL, OFFSETOF(Classes::fl_printing::PrintJobOrientation, LANDSCAPE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"PORTRAIT", NULL, OFFSETOF(Classes::fl_printing::PrintJobOrientation, PORTRAIT), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    PrintJobOrientation::PrintJobOrientation(VM& vm)
    : Traits(vm, AS3::fl_printing::PrintJobOrientationCI)
    {
//##protect##"ClassTraits::PrintJobOrientation::PrintJobOrientation()"
//##protect##"ClassTraits::PrintJobOrientation::PrintJobOrientation()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_printing::PrintJobOrientationCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_printing::PrintJobOrientation(*this));

    }

    Pickable<Traits> PrintJobOrientation::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) PrintJobOrientation(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_printing
{
    const TypeInfo PrintJobOrientationTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "PrintJobOrientation", "flash.printing", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo PrintJobOrientationCI = {
        &PrintJobOrientationTI,
        ClassTraits::fl_printing::PrintJobOrientation::MakeClassTraits,
        0,
        ClassTraits::fl_printing::PrintJobOrientation::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_printing::PrintJobOrientation::mi,
        NULL,
        NULL,
    };
}; // namespace fl_printing


}}} // namespace Scaleform { namespace GFx { namespace AS3

