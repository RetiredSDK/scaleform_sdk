//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_FileReference.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_FileReference.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Net_URLRequest.h"
#include "../AS3_Obj_Date.h"
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

namespace InstanceTraits { namespace fl_net
{
    const ThunkInfo FileReference_ti[12] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::DateTI, "creationDate", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "creator", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "extension", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::DateTI, "modificationDate", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "name", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "size", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "type", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "browse", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, NULL, "cancel", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "download", NULL, Abc::NS_Public, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "upload", NULL, Abc::NS_Public, CT_Method, 1, 3},
        {ThunkInfo::EmptyFunc, NULL, "uploadUnencoded", NULL, Abc::NS_Public, CT_Method, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_net
{
    FileReference::FileReference(VM& vm)
    : Traits(vm, AS3::fl_net::FileReferenceCI)
    {
//##protect##"ClassTraits::FileReference::FileReference()"
//##protect##"ClassTraits::FileReference::FileReference()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_net::FileReferenceCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> FileReference::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FileReference(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_net
{
    const TypeInfo FileReferenceTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "FileReference", "flash.net", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo FileReferenceCI = {
        &FileReferenceTI,
        ClassTraits::fl_net::FileReference::MakeClassTraits,
        0,
        0,
        12,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_net::FileReference_ti,
        NULL,
    };
}; // namespace fl_net


}}} // namespace Scaleform { namespace GFx { namespace AS3

