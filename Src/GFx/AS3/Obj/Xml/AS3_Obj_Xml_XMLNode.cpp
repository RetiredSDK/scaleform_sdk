//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Xml_XMLNode.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Xml_XMLNode.h"
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
    XMLNode::XMLNode(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
    , firstChild()
    , lastChild()
    , nextSibling()
    , nodeName(AS3::DefaultValue<ASString>(GetStringManager()))
    , nodeType()
    , nodeValue(AS3::DefaultValue<ASString>(GetStringManager()))
    , parentNode()
    , previousSibling()
//##protect##"instance::XMLNode::XMLNode()$data"
//##protect##"instance::XMLNode::XMLNode()$data"
    {
//##protect##"instance::XMLNode::XMLNode()$code"
//##protect##"instance::XMLNode::XMLNode()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_xml
{
    const ThunkInfo XMLNode::ti[XMLNode::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::ObjectTI, "attributes", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "attributes", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "childNodes", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "localName", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "namespaceURI", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "prefix", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "appendChild", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_xml::XMLNodeTI, "cloneNode", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "getNamespaceForPrefix", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "getPrefixForNamespace", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "hasChildNodes", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "insertBefore", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "removeNode", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };
    const MemberInfo XMLNode::mi[XMLNode::MemberInfoNum] = {
        {"firstChild", NULL, OFFSETOF(Instances::fl_xml::XMLNode, firstChild), Abc::NS_Public, SlotInfo::BT_ObjectCpp, 0},
        {"lastChild", NULL, OFFSETOF(Instances::fl_xml::XMLNode, lastChild), Abc::NS_Public, SlotInfo::BT_ObjectCpp, 0},
        {"nextSibling", NULL, OFFSETOF(Instances::fl_xml::XMLNode, nextSibling), Abc::NS_Public, SlotInfo::BT_ObjectCpp, 0},
        {"nodeName", NULL, OFFSETOF(Instances::fl_xml::XMLNode, nodeName), Abc::NS_Public, SlotInfo::BT_String, 0},
        {"nodeType", NULL, OFFSETOF(Instances::fl_xml::XMLNode, nodeType), Abc::NS_Public, SlotInfo::BT_UInt, 0},
        {"nodeValue", NULL, OFFSETOF(Instances::fl_xml::XMLNode, nodeValue), Abc::NS_Public, SlotInfo::BT_String, 0},
        {"parentNode", NULL, OFFSETOF(Instances::fl_xml::XMLNode, parentNode), Abc::NS_Public, SlotInfo::BT_ObjectCpp, 0},
        {"previousSibling", NULL, OFFSETOF(Instances::fl_xml::XMLNode, previousSibling), Abc::NS_Public, SlotInfo::BT_ObjectCpp, 0},
    };


    XMLNode::XMLNode(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::XMLNode::XMLNode()"
//##protect##"InstanceTraits::XMLNode::XMLNode()"
        SetMemSize(sizeof(Instances::fl_xml::XMLNode));

    }

    void XMLNode::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<XMLNode&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_xml
{
    XMLNode::XMLNode(VM& vm)
    : Traits(vm, AS3::fl_xml::XMLNodeCI)
    {
//##protect##"ClassTraits::XMLNode::XMLNode()"
//##protect##"ClassTraits::XMLNode::XMLNode()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_xml::XMLNode(vm, AS3::fl_xml::XMLNodeCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> XMLNode::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) XMLNode(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_xml
{
    const TypeInfo XMLNodeTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "XMLNode", "flash.xml", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo XMLNodeCI = {
        &XMLNodeTI,
        ClassTraits::fl_xml::XMLNode::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_xml::XMLNode::ThunkInfoNum,
        InstanceTraits::fl_xml::XMLNode::MemberInfoNum,
        NULL,
        NULL,
        InstanceTraits::fl_xml::XMLNode::ti,
        InstanceTraits::fl_xml::XMLNode::mi,
    };
}; // namespace fl_xml


}}} // namespace Scaleform { namespace GFx { namespace AS3

