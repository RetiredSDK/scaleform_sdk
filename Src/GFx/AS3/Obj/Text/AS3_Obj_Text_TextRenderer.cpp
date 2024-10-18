//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextRenderer.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_TextRenderer.h"
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

namespace InstanceTraits { namespace fl_text
{
    const ThunkInfo TextRenderer_ti[2] = {
        {ThunkInfo::EmptyFunc, NULL, "displayMode", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "maxLevel", NULL, Abc::NS_Public, CT_Set, 1, 1},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_text
{
    TextRenderer::TextRenderer(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::TextRenderer::TextRenderer()"
//##protect##"class_::TextRenderer::TextRenderer()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_text
{
    const ThunkInfo TextRenderer_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "setAdvancedAntiAliasingTable", NULL, Abc::NS_Public, CT_Method, 4, 4},
    };
    TextRenderer::TextRenderer(VM& vm)
    : Traits(vm, AS3::fl_text::TextRendererCI)
    {
//##protect##"ClassTraits::TextRenderer::TextRenderer()"
//##protect##"ClassTraits::TextRenderer::TextRenderer()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_text::TextRendererCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_text::TextRenderer(*this));

    }

    Pickable<Traits> TextRenderer::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextRenderer(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_text
{
    const TypeInfo TextRendererTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "TextRenderer", "flash.text", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo TextRendererCI = {
        &TextRendererTI,
        ClassTraits::fl_text::TextRenderer::MakeClassTraits,
        1,
        0,
        2,
        0,
        ClassTraits::fl_text::TextRenderer_ti,
        NULL,
        InstanceTraits::fl_text::TextRenderer_ti,
        NULL,
    };
}; // namespace fl_text


}}} // namespace Scaleform { namespace GFx { namespace AS3

