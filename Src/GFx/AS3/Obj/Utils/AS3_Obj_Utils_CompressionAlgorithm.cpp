//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_CompressionAlgorithm.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Utils_CompressionAlgorithm.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_utils
{
    CompressionAlgorithm::CompressionAlgorithm(ClassTraits::Traits& t)
    : Class(t)
    , DEFLATE("deflate")
    , ZLIB("zlib")
    {
//##protect##"class_::CompressionAlgorithm::CompressionAlgorithm()"
//##protect##"class_::CompressionAlgorithm::CompressionAlgorithm()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_utils
{
    const MemberInfo CompressionAlgorithm::mi[CompressionAlgorithm::MemberInfoNum] = {
        {"DEFLATE", NULL, OFFSETOF(Classes::fl_utils::CompressionAlgorithm, DEFLATE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"ZLIB", NULL, OFFSETOF(Classes::fl_utils::CompressionAlgorithm, ZLIB), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    CompressionAlgorithm::CompressionAlgorithm(VM& vm)
    : Traits(vm, AS3::fl_utils::CompressionAlgorithmCI)
    {
//##protect##"ClassTraits::CompressionAlgorithm::CompressionAlgorithm()"
//##protect##"ClassTraits::CompressionAlgorithm::CompressionAlgorithm()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_utils::CompressionAlgorithmCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_utils::CompressionAlgorithm(*this));

    }

    Pickable<Traits> CompressionAlgorithm::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) CompressionAlgorithm(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_utils
{
    const TypeInfo CompressionAlgorithmTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "CompressionAlgorithm", "flash.utils", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo CompressionAlgorithmCI = {
        &CompressionAlgorithmTI,
        ClassTraits::fl_utils::CompressionAlgorithm::MakeClassTraits,
        0,
        ClassTraits::fl_utils::CompressionAlgorithm::MemberInfoNum,
        0,
        0,
        NULL,
        ClassTraits::fl_utils::CompressionAlgorithm::mi,
        NULL,
        NULL,
    };
}; // namespace fl_utils


}}} // namespace Scaleform { namespace GFx { namespace AS3

