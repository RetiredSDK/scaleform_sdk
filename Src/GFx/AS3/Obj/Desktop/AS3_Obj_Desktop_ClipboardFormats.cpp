//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_ClipboardFormats.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_ClipboardFormats.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_desktop
{
    ClipboardFormats::ClipboardFormats(ClassTraits::Traits& t)
    : Class(t)
    , HTML_FORMAT("air:html")
    , TEXT_FORMAT("air:text")
    {
//##protect##"class_::ClipboardFormats::ClipboardFormats()"
//##protect##"class_::ClipboardFormats::ClipboardFormats()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_desktop
{
    const MemberInfo ClipboardFormats::mi[ClipboardFormats::MemberInfoNum] = {
        {"HTML_FORMAT", NULL, OFFSETOF(Classes::fl_desktop::ClipboardFormats, HTML_FORMAT), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"TEXT_FORMAT", NULL, OFFSETOF(Classes::fl_desktop::ClipboardFormats, TEXT_FORMAT), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    ClipboardFormats::ClipboardFormats(VM& vm)
    : Traits(vm, AS3::fl_desktop::ClipboardFormatsCI)
    {
//##protect##"ClassTraits::ClipboardFormats::ClipboardFormats()"
//##protect##"ClassTraits::ClipboardFormats::ClipboardFormats()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_desktop::ClipboardFormatsCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_desktop::ClipboardFormats(*this));

    }

    Pickable<Traits> ClipboardFormats::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClipboardFormats(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_desktop
{
    const TypeInfo ClipboardFormatsTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "ClipboardFormats", "flash.desktop", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo ClipboardFormatsCI = {
        &ClipboardFormatsTI,
        ClassTraits::fl_desktop::ClipboardFormats::MakeClassTraits,
        0,
        ClassTraits::fl_desktop::ClipboardFormats::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_desktop::ClipboardFormats::mi,
        NULL,
        NULL,
    };
}; // namespace fl_desktop


}}} // namespace Scaleform { namespace GFx { namespace AS3

