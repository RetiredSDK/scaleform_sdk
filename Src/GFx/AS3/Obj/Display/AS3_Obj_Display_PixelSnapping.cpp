//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_PixelSnapping.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_PixelSnapping.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_display
{
    PixelSnapping::PixelSnapping(ClassTraits::Traits& t)
    : Class(t)
    , ALWAYS("always")
    , AUTO("auto")
    , NEVER("never")
    {
//##protect##"class_::PixelSnapping::PixelSnapping()"
//##protect##"class_::PixelSnapping::PixelSnapping()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_display
{
    const MemberInfo PixelSnapping::mi[PixelSnapping::MemberInfoNum] = {
        {"ALWAYS", NULL, OFFSETOF(Classes::fl_display::PixelSnapping, ALWAYS), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"AUTO", NULL, OFFSETOF(Classes::fl_display::PixelSnapping, AUTO), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"NEVER", NULL, OFFSETOF(Classes::fl_display::PixelSnapping, NEVER), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    PixelSnapping::PixelSnapping(VM& vm)
    : Traits(vm, AS3::fl_display::PixelSnappingCI)
    {
//##protect##"ClassTraits::PixelSnapping::PixelSnapping()"
//##protect##"ClassTraits::PixelSnapping::PixelSnapping()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_display::PixelSnappingCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_display::PixelSnapping(*this));

    }

    Pickable<Traits> PixelSnapping::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) PixelSnapping(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_display
{
    const TypeInfo PixelSnappingTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "PixelSnapping", "flash.display", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo PixelSnappingCI = {
        &PixelSnappingTI,
        ClassTraits::fl_display::PixelSnapping::MakeClassTraits,
        0,
        ClassTraits::fl_display::PixelSnapping::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_display::PixelSnapping::mi,
        NULL,
        NULL,
    };
}; // namespace fl_display


}}} // namespace Scaleform { namespace GFx { namespace AS3

