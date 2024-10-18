//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Html_HTMLHistoryItem.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Html_HTMLHistoryItem.h"
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

namespace InstanceTraits { namespace fl_html
{
    const ThunkInfo HTMLHistoryItem_ti[4] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "isPost", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "originalUrl", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "title", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "url", NULL, Abc::NS_Public, CT_Get, 0, 0},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_html
{
    HTMLHistoryItem::HTMLHistoryItem(VM& vm)
    : Traits(vm, AS3::fl_html::HTMLHistoryItemCI)
    {
//##protect##"ClassTraits::HTMLHistoryItem::HTMLHistoryItem()"
//##protect##"ClassTraits::HTMLHistoryItem::HTMLHistoryItem()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_html::HTMLHistoryItemCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> HTMLHistoryItem::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) HTMLHistoryItem(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_html
{
    const TypeInfo HTMLHistoryItemTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "HTMLHistoryItem", "flash.html", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo HTMLHistoryItemCI = {
        &HTMLHistoryItemTI,
        ClassTraits::fl_html::HTMLHistoryItem::MakeClassTraits,
        0,
        0,
        4,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_html::HTMLHistoryItem_ti,
        NULL,
    };
}; // namespace fl_html


}}} // namespace Scaleform { namespace GFx { namespace AS3

