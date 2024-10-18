//##protect##"disclaimer"
/**********************************************************************

Filename    :   AS3_Obj_Display_Shader.cpp
Content     :   
Created     :   Sep, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_Shader.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class ShaderData;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_display
{
    const ThunkInfo Shader_ti[5] = {
        {ThunkInfo::EmptyFunc, NULL, "byteCode", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_display::ShaderDataTI, "data", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "data", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "precisionHint", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "precisionHint", NULL, Abc::NS_Public, CT_Set, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_display
{
    Shader::Shader(VM& vm)
    : Traits(vm, AS3::fl_display::ShaderCI)
    {
//##protect##"ClassTraits::Shader::Shader()"
//##protect##"ClassTraits::Shader::Shader()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_display::ShaderCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> Shader::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Shader(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_display
{
    const TypeInfo ShaderTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "Shader", "flash.display", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo ShaderCI = {
        &ShaderTI,
        ClassTraits::fl_display::Shader::MakeClassTraits,
        0,
        0,
        5,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_display::Shader_ti,
        NULL,
    };
}; // namespace fl_display


}}} // namespace Scaleform { namespace GFx { namespace AS3

