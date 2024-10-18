//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Xml_XMLDocument.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Xml_XMLDocument.h"
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

namespace Instances { namespace fl_xml
{
    XMLDocument::XMLDocument(InstanceTraits::Traits& t)
    : Instances::fl_xml::XMLNode(t)
    , docTypeDecl()
    , idMap()
    , ignoreWhite(false)
    , xmlDecl()
//##protect##"instance::XMLDocument::XMLDocument()$data"
//##protect##"instance::XMLDocument::XMLDocument()$data"
    {
//##protect##"instance::XMLDocument::XMLDocument()$code"
//##protect##"instance::XMLDocument::XMLDocument()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_xml
{
    const ThunkInfo XMLDocument::ti[XMLDocument::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, &AS3::fl_xml::XMLNodeTI, "createElement", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_xml::XMLNodeTI, "createTextNode", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "parseXML", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };
    const MemberInfo XMLDocument::mi[XMLDocument::MemberInfoNum] = {
        {"docTypeDecl", NULL, OFFSETOF(Instances::fl_xml::XMLDocument, docTypeDecl), Abc::NS_Public, SlotInfo::BT_ObjectCpp, 0},
        {"idMap", NULL, OFFSETOF(Instances::fl_xml::XMLDocument, idMap), Abc::NS_Public, SlotInfo::BT_ObjectCpp, 0},
        {"ignoreWhite", NULL, OFFSETOF(Instances::fl_xml::XMLDocument, ignoreWhite), Abc::NS_Public, SlotInfo::BT_Boolean, 0},
        {"xmlDecl", NULL, OFFSETOF(Instances::fl_xml::XMLDocument, xmlDecl), Abc::NS_Public, SlotInfo::BT_ObjectCpp, 0},
    };


    XMLDocument::XMLDocument(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::XMLDocument::XMLDocument()"
//##protect##"InstanceTraits::XMLDocument::XMLDocument()"
        SetMemSize(sizeof(Instances::fl_xml::XMLDocument));

    }

    void XMLDocument::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<XMLDocument&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_xml
{
    XMLDocument::XMLDocument(VM& vm)
    : Traits(vm, AS3::fl_xml::XMLDocumentCI)
    {
//##protect##"ClassTraits::XMLDocument::XMLDocument()"
//##protect##"ClassTraits::XMLDocument::XMLDocument()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_xml::XMLDocument(vm, AS3::fl_xml::XMLDocumentCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> XMLDocument::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) XMLDocument(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_xml
{
    const TypeInfo XMLDocumentTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "XMLDocument", "flash.xml", &fl_xml::XMLNodeTI,
        TypeInfo::None
    };

    const ClassInfo XMLDocumentCI = {
        &XMLDocumentTI,
        ClassTraits::fl_xml::XMLDocument::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_xml::XMLDocument::ThunkInfoNum,
        InstanceTraits::fl_xml::XMLDocument::MemberInfoNum,
        NULL,
        NULL,
        InstanceTraits::fl_xml::XMLDocument::ti,
        InstanceTraits::fl_xml::XMLDocument::mi,
    };
}; // namespace fl_xml


}}} // namespace Scaleform { namespace GFx { namespace AS3

