//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_FileListEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_FileListEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace Instances { namespace fl_events
{
    FileListEvent::FileListEvent(InstanceTraits::Traits& t)
    : Instances::fl_events::Event(t)
    , files()
//##protect##"instance::FileListEvent::FileListEvent()$data"
//##protect##"instance::FileListEvent::FileListEvent()$data"
    {
//##protect##"instance::FileListEvent::FileListEvent()$code"
//##protect##"instance::FileListEvent::FileListEvent()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_events
{
    const MemberInfo FileListEvent::mi[FileListEvent::MemberInfoNum] = {
        {"files", NULL, OFFSETOF(Instances::fl_events::FileListEvent, files), Abc::NS_Public, SlotInfo::BT_ObjectCpp, 0},
    };


    FileListEvent::FileListEvent(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::FileListEvent::FileListEvent()"
//##protect##"InstanceTraits::FileListEvent::FileListEvent()"
        SetMemSize(sizeof(Instances::fl_events::FileListEvent));

    }

    void FileListEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<FileListEvent&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits

namespace Classes { namespace fl_events
{
    FileListEvent::FileListEvent(ClassTraits::Traits& t)
    : Class(t)
    , DIRECTORY_LISTING("directoryListing")
    , SELECT_MULTIPLE("selectMultiple")
    {
//##protect##"class_::FileListEvent::FileListEvent()"
//##protect##"class_::FileListEvent::FileListEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_events
{
    const MemberInfo FileListEvent::mi[FileListEvent::MemberInfoNum] = {
        {"DIRECTORY_LISTING", NULL, OFFSETOF(Classes::fl_events::FileListEvent, DIRECTORY_LISTING), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"SELECT_MULTIPLE", NULL, OFFSETOF(Classes::fl_events::FileListEvent, SELECT_MULTIPLE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    FileListEvent::FileListEvent(VM& vm)
    : Traits(vm, AS3::fl_events::FileListEventCI)
    {
//##protect##"ClassTraits::FileListEvent::FileListEvent()"
//##protect##"ClassTraits::FileListEvent::FileListEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::FileListEvent(vm, AS3::fl_events::FileListEventCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_events::FileListEvent(*this));

    }

    Pickable<Traits> FileListEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FileListEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_events
{
    const TypeInfo FileListEventTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "FileListEvent", "flash.events", &fl_events::EventTI,
        TypeInfo::None
    };

    const ClassInfo FileListEventCI = {
        &FileListEventTI,
        ClassTraits::fl_events::FileListEvent::MakeClassTraits,
        0,
        ClassTraits::fl_events::FileListEvent::MemberInfoNum,
        0,
        InstanceTraits::fl_events::FileListEvent::MemberInfoNum,
        NULL,
        ClassTraits::fl_events::FileListEvent::mi,
        NULL,
        InstanceTraits::fl_events::FileListEvent::mi,
    };
}; // namespace fl_events


}}} // namespace Scaleform { namespace GFx { namespace AS3

