//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Accessibility_ISimpleTextSelection.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Accessibility_ISimpleTextSelection.h"
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

namespace InstanceTraits { namespace fl_accessibility
{
    const ThunkInfo ISimpleTextSelection_ti[2] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "selectionActiveIndex", "flash.accessibility:ISimpleTextSelection", Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "selectionAnchorIndex", "flash.accessibility:ISimpleTextSelection", Abc::NS_Public, CT_Get, 0, 0},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_accessibility
{
    ISimpleTextSelection::ISimpleTextSelection(VM& vm)
    : Traits(vm, AS3::fl_accessibility::ISimpleTextSelectionCI)
    {
//##protect##"ClassTraits::ISimpleTextSelection::ISimpleTextSelection()"
//##protect##"ClassTraits::ISimpleTextSelection::ISimpleTextSelection()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Interface(vm, AS3::fl_accessibility::ISimpleTextSelectionCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> ISimpleTextSelection::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ISimpleTextSelection(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_accessibility
{
    const TypeInfo ISimpleTextSelectionTI = {
        TypeInfo::CompileTime | TypeInfo::TypeInterface,
        "ISimpleTextSelection", "flash.accessibility", NULL,
        TypeInfo::None
    };

    const ClassInfo ISimpleTextSelectionCI = {
        &ISimpleTextSelectionTI,
        ClassTraits::fl_accessibility::ISimpleTextSelection::MakeClassTraits,
        0,
        0,
        2,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_accessibility::ISimpleTextSelection_ti,
        NULL,
    };
}; // namespace fl_accessibility


}}} // namespace Scaleform { namespace GFx { namespace AS3

