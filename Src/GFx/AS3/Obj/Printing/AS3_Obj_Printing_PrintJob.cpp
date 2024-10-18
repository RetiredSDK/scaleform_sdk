//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Printing_PrintJob.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Printing_PrintJob.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Geom/AS3_Obj_Geom_Rectangle.h"
#include "../Display/AS3_Obj_Display_Sprite.h"
#include "AS3_Obj_Printing_PrintJobOptions.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_printing
{
    const ThunkInfo PrintJob_ti[8] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "orientation", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "pageHeight", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "pageWidth", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "paperHeight", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "paperWidth", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "addPage", NULL, Abc::NS_Public, CT_Method, 1, 4},
        {ThunkInfo::EmptyFunc, NULL, "send", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "start", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_printing
{
    PrintJob::PrintJob(VM& vm)
    : Traits(vm, AS3::fl_printing::PrintJobCI)
    {
//##protect##"ClassTraits::PrintJob::PrintJob()"
//##protect##"ClassTraits::PrintJob::PrintJob()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_printing::PrintJobCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> PrintJob::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) PrintJob(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_printing
{
    const TypeInfo PrintJobTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "PrintJob", "flash.printing", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo PrintJobCI = {
        &PrintJobTI,
        ClassTraits::fl_printing::PrintJob::MakeClassTraits,
        0,
        0,
        8,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_printing::PrintJob_ti,
        NULL,
    };
}; // namespace fl_printing


}}} // namespace Scaleform { namespace GFx { namespace AS3

