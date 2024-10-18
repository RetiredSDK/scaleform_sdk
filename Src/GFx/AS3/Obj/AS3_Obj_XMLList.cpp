//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_XMLList.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy, Alex Mantzaris

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_XMLList.h"
#include "../AS3_VM.h"
#include "../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Array.h"
#include "AS3_Obj_XML.h"
#include "AS3_Obj_QName.h"
#include "Kernel/SF_MsgFormat.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_prototypeGet, SPtr<Instances::fl::XMLList> > TFunc_Instances_XMLList_prototypeGet;
typedef ThunkFunc1<Instances::fl::XMLList, Instances::fl::XMLList::mid_prototypeSet, const Value, const Value&> TFunc_Instances_XMLList_prototypeSet;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3length, SInt32> TFunc_Instances_XMLList_AS3length;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3toString, ASString> TFunc_Instances_XMLList_AS3toString;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3valueOf, SPtr<Instances::fl::XMLList> > TFunc_Instances_XMLList_AS3valueOf;
typedef ThunkFunc2<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3propertyIsEnumerable, Value, unsigned, const Value*> TFunc_Instances_XMLList_AS3propertyIsEnumerable;
typedef ThunkFunc1<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3attribute, SPtr<Instances::fl::XMLList>, const Value&> TFunc_Instances_XMLList_AS3attribute;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3attributes, SPtr<Instances::fl::XMLList> > TFunc_Instances_XMLList_AS3attributes;
typedef ThunkFunc1<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3child, SPtr<Instances::fl::XMLList>, const Value&> TFunc_Instances_XMLList_AS3child;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3children, SPtr<Instances::fl::XMLList> > TFunc_Instances_XMLList_AS3children;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3comments, SPtr<Instances::fl::XMLList> > TFunc_Instances_XMLList_AS3comments;
typedef ThunkFunc1<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3contains, bool, const Value&> TFunc_Instances_XMLList_AS3contains;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3copy, SPtr<Instances::fl::XMLList> > TFunc_Instances_XMLList_AS3copy;
typedef ThunkFunc2<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3descendants, Value, unsigned, const Value*> TFunc_Instances_XMLList_AS3descendants;
typedef ThunkFunc2<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3elements, Value, unsigned, const Value*> TFunc_Instances_XMLList_AS3elements;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3hasComplexContent, bool> TFunc_Instances_XMLList_AS3hasComplexContent;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3hasSimpleContent, bool> TFunc_Instances_XMLList_AS3hasSimpleContent;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3name, SPtr<Instances::fl::QName> > TFunc_Instances_XMLList_AS3name;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3normalize, SPtr<Instances::fl::XMLList> > TFunc_Instances_XMLList_AS3normalize;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3parent, Value> TFunc_Instances_XMLList_AS3parent;
typedef ThunkFunc2<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3processingInstructions, Value, unsigned, const Value*> TFunc_Instances_XMLList_AS3processingInstructions;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3text, SPtr<Instances::fl::XMLList> > TFunc_Instances_XMLList_AS3text;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3toXMLString, ASString> TFunc_Instances_XMLList_AS3toXMLString;
typedef ThunkFunc1<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3addNamespace, SPtr<Instances::fl::XML>, const Value&> TFunc_Instances_XMLList_AS3addNamespace;
typedef ThunkFunc1<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3appendChild, SPtr<Instances::fl::XML>, const Value&> TFunc_Instances_XMLList_AS3appendChild;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3childIndex, SInt32> TFunc_Instances_XMLList_AS3childIndex;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3inScopeNamespaces, SPtr<Instances::fl::Array> > TFunc_Instances_XMLList_AS3inScopeNamespaces;
typedef ThunkFunc2<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3insertChildAfter, Value, const Value&, const Value&> TFunc_Instances_XMLList_AS3insertChildAfter;
typedef ThunkFunc2<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3insertChildBefore, Value, const Value&, const Value&> TFunc_Instances_XMLList_AS3insertChildBefore;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3nodeKind, ASString> TFunc_Instances_XMLList_AS3nodeKind;
typedef ThunkFunc2<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3namespace_, Value, unsigned, const Value*> TFunc_Instances_XMLList_AS3namespace_;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3localName, ASString> TFunc_Instances_XMLList_AS3localName;
typedef ThunkFunc0<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3namespaceDeclarations, SPtr<Instances::fl::Array> > TFunc_Instances_XMLList_AS3namespaceDeclarations;
typedef ThunkFunc1<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3prependChild, SPtr<Instances::fl::XML>, const Value&> TFunc_Instances_XMLList_AS3prependChild;
typedef ThunkFunc1<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3removeNamespace, SPtr<Instances::fl::XML>, const Value&> TFunc_Instances_XMLList_AS3removeNamespace;
typedef ThunkFunc2<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3replace, SPtr<Instances::fl::XML>, const Value&, const Value&> TFunc_Instances_XMLList_AS3replace;
typedef ThunkFunc1<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3setChildren, SPtr<Instances::fl::XML>, const Value&> TFunc_Instances_XMLList_AS3setChildren;
typedef ThunkFunc1<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3setLocalName, const Value, const Value&> TFunc_Instances_XMLList_AS3setLocalName;
typedef ThunkFunc1<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3setName, const Value, const Value&> TFunc_Instances_XMLList_AS3setName;
typedef ThunkFunc1<Instances::fl::XMLList, Instances::fl::XMLList::mid_AS3setNamespace, const Value, const Value&> TFunc_Instances_XMLList_AS3setNamespace;

template <> const TFunc_Instances_XMLList_prototypeGet::TMethod TFunc_Instances_XMLList_prototypeGet::Method = &Instances::fl::XMLList::prototypeGet;
template <> const TFunc_Instances_XMLList_prototypeSet::TMethod TFunc_Instances_XMLList_prototypeSet::Method = &Instances::fl::XMLList::prototypeSet;
template <> const TFunc_Instances_XMLList_AS3length::TMethod TFunc_Instances_XMLList_AS3length::Method = &Instances::fl::XMLList::AS3length;
template <> const TFunc_Instances_XMLList_AS3toString::TMethod TFunc_Instances_XMLList_AS3toString::Method = &Instances::fl::XMLList::AS3toString;
template <> const TFunc_Instances_XMLList_AS3valueOf::TMethod TFunc_Instances_XMLList_AS3valueOf::Method = &Instances::fl::XMLList::AS3valueOf;
template <> const TFunc_Instances_XMLList_AS3propertyIsEnumerable::TMethod TFunc_Instances_XMLList_AS3propertyIsEnumerable::Method = &Instances::fl::XMLList::AS3propertyIsEnumerable;
template <> const TFunc_Instances_XMLList_AS3attribute::TMethod TFunc_Instances_XMLList_AS3attribute::Method = &Instances::fl::XMLList::AS3attribute;
template <> const TFunc_Instances_XMLList_AS3attributes::TMethod TFunc_Instances_XMLList_AS3attributes::Method = &Instances::fl::XMLList::AS3attributes;
template <> const TFunc_Instances_XMLList_AS3child::TMethod TFunc_Instances_XMLList_AS3child::Method = &Instances::fl::XMLList::AS3child;
template <> const TFunc_Instances_XMLList_AS3children::TMethod TFunc_Instances_XMLList_AS3children::Method = &Instances::fl::XMLList::AS3children;
template <> const TFunc_Instances_XMLList_AS3comments::TMethod TFunc_Instances_XMLList_AS3comments::Method = &Instances::fl::XMLList::AS3comments;
template <> const TFunc_Instances_XMLList_AS3contains::TMethod TFunc_Instances_XMLList_AS3contains::Method = &Instances::fl::XMLList::AS3contains;
template <> const TFunc_Instances_XMLList_AS3copy::TMethod TFunc_Instances_XMLList_AS3copy::Method = &Instances::fl::XMLList::AS3copy;
template <> const TFunc_Instances_XMLList_AS3descendants::TMethod TFunc_Instances_XMLList_AS3descendants::Method = &Instances::fl::XMLList::AS3descendants;
template <> const TFunc_Instances_XMLList_AS3elements::TMethod TFunc_Instances_XMLList_AS3elements::Method = &Instances::fl::XMLList::AS3elements;
template <> const TFunc_Instances_XMLList_AS3hasComplexContent::TMethod TFunc_Instances_XMLList_AS3hasComplexContent::Method = &Instances::fl::XMLList::AS3hasComplexContent;
template <> const TFunc_Instances_XMLList_AS3hasSimpleContent::TMethod TFunc_Instances_XMLList_AS3hasSimpleContent::Method = &Instances::fl::XMLList::AS3hasSimpleContent;
template <> const TFunc_Instances_XMLList_AS3name::TMethod TFunc_Instances_XMLList_AS3name::Method = &Instances::fl::XMLList::AS3name;
template <> const TFunc_Instances_XMLList_AS3normalize::TMethod TFunc_Instances_XMLList_AS3normalize::Method = &Instances::fl::XMLList::AS3normalize;
template <> const TFunc_Instances_XMLList_AS3parent::TMethod TFunc_Instances_XMLList_AS3parent::Method = &Instances::fl::XMLList::AS3parent;
template <> const TFunc_Instances_XMLList_AS3processingInstructions::TMethod TFunc_Instances_XMLList_AS3processingInstructions::Method = &Instances::fl::XMLList::AS3processingInstructions;
template <> const TFunc_Instances_XMLList_AS3text::TMethod TFunc_Instances_XMLList_AS3text::Method = &Instances::fl::XMLList::AS3text;
template <> const TFunc_Instances_XMLList_AS3toXMLString::TMethod TFunc_Instances_XMLList_AS3toXMLString::Method = &Instances::fl::XMLList::AS3toXMLString;
template <> const TFunc_Instances_XMLList_AS3addNamespace::TMethod TFunc_Instances_XMLList_AS3addNamespace::Method = &Instances::fl::XMLList::AS3addNamespace;
template <> const TFunc_Instances_XMLList_AS3appendChild::TMethod TFunc_Instances_XMLList_AS3appendChild::Method = &Instances::fl::XMLList::AS3appendChild;
template <> const TFunc_Instances_XMLList_AS3childIndex::TMethod TFunc_Instances_XMLList_AS3childIndex::Method = &Instances::fl::XMLList::AS3childIndex;
template <> const TFunc_Instances_XMLList_AS3inScopeNamespaces::TMethod TFunc_Instances_XMLList_AS3inScopeNamespaces::Method = &Instances::fl::XMLList::AS3inScopeNamespaces;
template <> const TFunc_Instances_XMLList_AS3insertChildAfter::TMethod TFunc_Instances_XMLList_AS3insertChildAfter::Method = &Instances::fl::XMLList::AS3insertChildAfter;
template <> const TFunc_Instances_XMLList_AS3insertChildBefore::TMethod TFunc_Instances_XMLList_AS3insertChildBefore::Method = &Instances::fl::XMLList::AS3insertChildBefore;
template <> const TFunc_Instances_XMLList_AS3nodeKind::TMethod TFunc_Instances_XMLList_AS3nodeKind::Method = &Instances::fl::XMLList::AS3nodeKind;
template <> const TFunc_Instances_XMLList_AS3namespace_::TMethod TFunc_Instances_XMLList_AS3namespace_::Method = &Instances::fl::XMLList::AS3namespace_;
template <> const TFunc_Instances_XMLList_AS3localName::TMethod TFunc_Instances_XMLList_AS3localName::Method = &Instances::fl::XMLList::AS3localName;
template <> const TFunc_Instances_XMLList_AS3namespaceDeclarations::TMethod TFunc_Instances_XMLList_AS3namespaceDeclarations::Method = &Instances::fl::XMLList::AS3namespaceDeclarations;
template <> const TFunc_Instances_XMLList_AS3prependChild::TMethod TFunc_Instances_XMLList_AS3prependChild::Method = &Instances::fl::XMLList::AS3prependChild;
template <> const TFunc_Instances_XMLList_AS3removeNamespace::TMethod TFunc_Instances_XMLList_AS3removeNamespace::Method = &Instances::fl::XMLList::AS3removeNamespace;
template <> const TFunc_Instances_XMLList_AS3replace::TMethod TFunc_Instances_XMLList_AS3replace::Method = &Instances::fl::XMLList::AS3replace;
template <> const TFunc_Instances_XMLList_AS3setChildren::TMethod TFunc_Instances_XMLList_AS3setChildren::Method = &Instances::fl::XMLList::AS3setChildren;
template <> const TFunc_Instances_XMLList_AS3setLocalName::TMethod TFunc_Instances_XMLList_AS3setLocalName::Method = &Instances::fl::XMLList::AS3setLocalName;
template <> const TFunc_Instances_XMLList_AS3setName::TMethod TFunc_Instances_XMLList_AS3setName::Method = &Instances::fl::XMLList::AS3setName;
template <> const TFunc_Instances_XMLList_AS3setNamespace::TMethod TFunc_Instances_XMLList_AS3setNamespace::Method = &Instances::fl::XMLList::AS3setNamespace;

namespace Instances { namespace fl
{
    XMLList::XMLList(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
//##protect##"instance::XMLList::XMLList()$data"
    , TargetProperty(NULL)
//##protect##"instance::XMLList::XMLList()$data"
    {
//##protect##"instance::XMLList::XMLList()$code"
//##protect##"instance::XMLList::XMLList()$code"
    }

    void XMLList::prototypeGet(SPtr<Instances::fl::XMLList>& result)
    {
//##protect##"instance::XMLList::prototypeGet()"
        result = MakeInstance();
//##protect##"instance::XMLList::prototypeGet()"
    }
    void XMLList::prototypeSet(const Value& result, const Value& p)
    {
//##protect##"instance::XMLList::prototypeSet()"
        SF_UNUSED2(result, p);
//##protect##"instance::XMLList::prototypeSet()"
    }
    void XMLList::AS3length(SInt32& result)
    {
//##protect##"instance::XMLList::AS3length()"
        result = static_cast<SInt32>(List.GetSize());
//##protect##"instance::XMLList::AS3length()"
    }
    void XMLList::AS3toString(ASString& result)
    {
//##protect##"instance::XMLList::AS3toString()"
        bool simple;

        AS3hasSimpleContent(simple);
        if (simple)
        {
            VM& vm = GetVM();
            StringBuffer buf(vm.GetMemoryHeap());
            const UPInt size = List.GetSize();

            for (UPInt i = 0; i < size; ++i)
            {
                XML* xml = List[i];
                const XML::Kind k = xml->GetKind();

                if (k == XML::kInstruction || k == XML::kComment)
                    continue;

                xml->ToString(buf, 0);
            }

            result = vm.GetStringManager().CreateString(buf.ToCStr(), buf.GetSize());
        }
        else
            AS3toXMLString(result);
//##protect##"instance::XMLList::AS3toString()"
    }
    void XMLList::AS3valueOf(SPtr<Instances::fl::XMLList>& result)
    {
//##protect##"instance::XMLList::AS3valueOf()"
        result = this;
//##protect##"instance::XMLList::AS3valueOf()"
    }
    void XMLList::AS3hasOwnProperty(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"instance::XMLList::AS3hasOwnProperty()"
        // When the hasOwnProperty method of an XMLList object x is called with parameter P, the following step is taken:
        // 1. If the result of calling the [[HasProperty]] method of this object with argument P is true, return true
        // 2. If x has a property with name ToString(P), return true
        // 3. Return false

        if (argc > 0 && IsXMLListObject(_this))
        {
            XMLList* list = static_cast<XMLList*>(_this.GetObject());
            Multiname prop_name(vm, argv[0]);

            const bool rc = list->HasProperty(prop_name);

            if (rc)
            {
                result.SetBool(rc);
                return;
            }
        }

        Instances::fl::Object::AS3hasOwnProperty(ti, vm, _this, result, argc, argv);
//##protect##"instance::XMLList::AS3hasOwnProperty()"
    }
    void XMLList::AS3propertyIsEnumerable(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::XMLList::AS3propertyIsEnumerable()"
        if (argc > 0 && !argv[0].IsNullOrUndefined())
        {
            Multiname prop_name(GetVM(), argv[0]);
            UInt32 ind;

            if (GetVectorInd(prop_name, ind))
            {
                if (ind < GetSize())
                {
                    result.SetBool(true);
                    return;
                }
            }
        }

        result.SetBool(false);
//##protect##"instance::XMLList::AS3propertyIsEnumerable()"
    }
    void XMLList::AS3attribute(SPtr<Instances::fl::XMLList>& result, const Value& arg)
    {
//##protect##"instance::XMLList::AS3attribute()"
        VM& vm = GetVM();

        if (arg.IsNullOrUndefined())
            return vm.ThrowTypeError(VM::Error(VM::eInvalidArgumentError, vm SF_DEBUG_ARG("arg")));

        Multiname prop_name(vm, arg);
        prop_name.SetAttr();

        if (vm.IsException())
            return;

        // We have to return XMLList.
        result = MakeInstance(prop_name);

        const UPInt size = List.GetSize();
        for (UPInt i = 0; i < size; ++i)
        {
            XML* xml = List[i];

            if (!xml->GetProperty(prop_name, *result))
                // Exception.
                return;
        }
//##protect##"instance::XMLList::AS3attribute()"
    }
    void XMLList::AS3attributes(SPtr<Instances::fl::XMLList>& result)
    {
//##protect##"instance::XMLList::AS3attributes()"
        Pickable<Instances::fl::XMLList> list = MakeInstance();

        result = list;
        const UPInt size = List.GetSize();
        for (UPInt i = 0; i < size; ++i)
        {
            XML* xml = List[i];
            xml->GetAttributes(*list);
        }
//##protect##"instance::XMLList::AS3attributes()"
    }
    void XMLList::AS3child(SPtr<Instances::fl::XMLList>& result, const Value& propertyName)
    {
//##protect##"instance::XMLList::AS3child()"
        if (propertyName.IsNullOrUndefined())
            return GetVM().ThrowTypeError(VM::Error(VM::eInvalidArgumentError, GetVM() SF_DEBUG_ARG("propertyName")));

        Pickable<Instances::fl::XMLList> list = MakeInstance();
        result = list;

        Multiname mn(GetVM().GetPublicNamespace(), propertyName);
        const UPInt size = List.GetSize();
        for (UPInt i = 0; i < size; ++i)
        {
            XML* xml = List[i];
            xml->GetChildren(*list, mn);
        }
//##protect##"instance::XMLList::AS3child()"
    }
    void XMLList::AS3children(SPtr<Instances::fl::XMLList>& result)
    {
//##protect##"instance::XMLList::AS3children()"
        result = MakeInstance();

        VM& vm = GetVM();
        const Multiname prop_name(vm);

        GetProperty(prop_name, *result).DoNotCheck();
//##protect##"instance::XMLList::AS3children()"
    }
    void XMLList::AS3comments(SPtr<Instances::fl::XMLList>& result)
    {
//##protect##"instance::XMLList::AS3comments()"
        result = MakeInstance(*this, GetVM().GetStringManager().CreateNullString(), GetVM().GetPublicNamespace());

        const UPInt size = List.GetSize();
        for (UPInt i = 0; i < size; ++i)
        {
            XML* xml = List[i];
            if (xml->GetKind() == XML::kElement)
            {
                SPtr<XMLList> r = xml->AS3comments();
                UPInt eltSize = r->List.GetSize();
                if (eltSize > 0)
                {
                    result->List.Append(&r->List[0], eltSize);
                }
            }
        }
//##protect##"instance::XMLList::AS3comments()"
    }
    void XMLList::AS3contains(bool& result, const Value& value)
    {
//##protect##"instance::XMLList::AS3contains()"
        result = false;

        if (!IsXMLObject(value))
            return;

        Instances::fl::XML* other = static_cast<Instances::fl::XML*>(value.GetObject());
        const UPInt size = List.GetSize();
        for (UPInt i = 0; i < size && !result; ++i)
        {
            if (List[i]->Equals(*other))
                result = true;
        }
//##protect##"instance::XMLList::AS3contains()"
    }
    void XMLList::AS3copy(SPtr<Instances::fl::XMLList>& result)
    {
//##protect##"instance::XMLList::AS3copy()"
        result = DeepCopy(NULL);
//##protect##"instance::XMLList::AS3copy()"
    }
    void XMLList::AS3descendants(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::XMLList::AS3descendants()"
        Multiname mn(GetVM().GetPublicNamespace(), argc == 0 ? Value(GetVM().GetStringManager().CreateConstString("*")) : argv[0]);
        Pickable<XMLList> list = MakeInstance();
        result = list;

        GetDescendants(*list, mn);
//##protect##"instance::XMLList::AS3descendants()"
    }
    void XMLList::AS3elements(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::XMLList::AS3elements()"
        Pickable<XMLList> list = MakeInstance();
        result = list;

        Multiname mn(GetVM().GetPublicNamespace(), argc == 0 ? Value(GetVM().GetStringManager().CreateConstString("*")) : argv[0]);
        const UPInt size = List.GetSize();

        for (UPInt i = 0; i < size; ++i)
        {
            XML* xml = List[i];
            xml->GetChildren(*list, mn);
        }
//##protect##"instance::XMLList::AS3elements()"
    }
    void XMLList::AS3hasComplexContent(bool& result)
    {
//##protect##"instance::XMLList::AS3hasComplexContent()"
        AS3hasSimpleContent(result);
        result = !result;
//##protect##"instance::XMLList::AS3hasComplexContent()"
    }
    void XMLList::AS3hasSimpleContent(bool& result)
    {
//##protect##"instance::XMLList::AS3hasSimpleContent()"
        const UPInt size = List.GetSize();

        switch (size)
        {
        case 0:
            result = true;
            break;
        case 1:
            List[0]->AS3hasSimpleContent(result);
            break;
        default:
            result = true;
            for (UPInt i = 0; i < size; ++ i)
            {
                if (List[i]->GetKind() == Instances::fl::XML::kElement)
                {
                    result = false;
                    break;
                }
            }
        }
//##protect##"instance::XMLList::AS3hasSimpleContent()"
    }
    void XMLList::AS3name(SPtr<Instances::fl::QName>& result)
    {
//##protect##"instance::XMLList::AS3name()"
        if (HasOneItem(SF_DEBUG_CODE("name")))
            List[0]->AS3name(result);
//##protect##"instance::XMLList::AS3name()"
    }
    void XMLList::AS3normalize(SPtr<Instances::fl::XMLList>& result)
    {
//##protect##"instance::XMLList::AS3normalize()"
        result = this;
        const UPInt size = List.GetSize();
        for (UPInt i = 0; i < size; ++i)
        {
            XML* xml = List[i];
            xml->Normalize();
        }
//##protect##"instance::XMLList::AS3normalize()"
    }
    void XMLList::AS3parent(Value& result)
    {
//##protect##"instance::XMLList::AS3parent()"
        const UPInt size = List.GetSize();

        if (size == 0)
            return result.SetUndefined();

        XML* parent = List[0]->GetParent();
        for (UPInt i = 1; i < size; ++i)
        {
            XML* cur_parent = List[i]->GetParent();
            if (parent != cur_parent)
                return result.SetUndefined();
        }

        if (parent)
            result = parent;
        else
            result.SetUndefined();
//##protect##"instance::XMLList::AS3parent()"
    }
    void XMLList::AS3processingInstructions(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::XMLList::AS3processingInstructions()"
        Pickable<Instances::fl::XMLList> list = MakeInstance();
        result = list;

        if (argc == 0)
        {
            const UPInt size = List.GetSize();
            for (UPInt i = 0; i < size; ++i)
            {
                XML* xml = List[i];
                xml->GetChildren(*list, XML::kInstruction);
            }
        }
        else
        {
            VM& vm = GetVM();
            StringManager& sm = vm.GetStringManager();
            ASString name = sm.CreateEmptyString();

            if (argv[0].Convert2String(name))
            {
                const UPInt size = List.GetSize();
                for (UPInt i = 0; i < size; ++i)
                {
                    XML* xml = List[i];
                    xml->GetChildren(*list, XML::kInstruction, &name);
                }
            }
        }
//##protect##"instance::XMLList::AS3processingInstructions()"
    }
    void XMLList::AS3text(SPtr<Instances::fl::XMLList>& result)
    {
//##protect##"instance::XMLList::AS3text()"
        Pickable<Instances::fl::XMLList> list = MakeInstance();
        result = list;

        const UPInt size = List.GetSize();
        for (UPInt i = 0; i < size; ++i)
        {
            XML* xml = List[i];
            xml->GetChildren(*list, XML::kText);
        }
//##protect##"instance::XMLList::AS3text()"
    }
    void XMLList::AS3toXMLString(ASString& result)
    {
//##protect##"instance::XMLList::AS3toXMLString()"
        VM& vm = GetVM();
        const UPInt size = List.GetSize();

        // Collect referenced namespaces.
        NamespaceArray na(vm.GetMemoryHeap());
        if (size > 0)
        {
            Object* to = TargetObject;
            const Namespace& publicNS = vm.GetPublicNamespace();

            while (to)
            {
                if (IsXMLObject(to))
                {
                    for (XML* xml = static_cast<XML*>(to); xml; xml = xml->GetParent())
                    {
                        const XML::NamespaceH* nsh = xml->GetInScopeNamespaces();

                        if (nsh)
                        {
                            const UPInt size = nsh->GetSize();
                            for (UPInt i = 0; i < size; ++i)
                            {
                                Namespace& ns = *(*nsh)[i];

                                if (ns != publicNS)
                                    na.Add(ns);
                            }
                        }
                    }

                    // Stop iteration.
                    break;
                }
                else if (IsXMLListObject(to))
                {
                    XMLList* list = static_cast<XMLList*>(to);

                    const UPInt size = list->GetSize();
                    for (UPInt i = 0; i < size; ++i)
                    {
                        XML* xml = list->List[i];

                        const XML::NamespaceH* nsh = xml->GetInScopeNamespaces();

                        if (nsh)
                        {
                            const UPInt size = nsh->GetSize();
                            for (UPInt i = 0; i < size; ++i)
                            {
                                Namespace& ns = *(*nsh)[i];

                                if (ns != publicNS)
                                    na.Add(ns);
                            }
                        }
                    }

                    to = list->TargetObject;
                }
                else
                {
                    SF_ASSERT(false);
                }
            }
        }

        StringBuffer buf(vm.GetMemoryHeap());
        for (UPInt i = 0; i < size; ++i)
        {
            if (i > 0)
                buf.AppendChar('\n');

            List[i]->ToXMLString(buf, 0, NULL, &na);
        }

        result = vm.GetStringManager().CreateString(buf.ToCStr(), buf.GetSize());
//##protect##"instance::XMLList::AS3toXMLString()"
    }
    void XMLList::AS3addNamespace(SPtr<Instances::fl::XML>& result, const Value& ns)
    {
//##protect##"instance::XMLList::AS3addNamespace()"
        if (HasOneItem(SF_DEBUG_CODE("addNamespace")))
            List[0]->AS3addNamespace(result, ns);
//##protect##"instance::XMLList::AS3addNamespace()"
    }
    void XMLList::AS3appendChild(SPtr<Instances::fl::XML>& result, const Value& child)
    {
//##protect##"instance::XMLList::AS3appendChild()"
        if (HasOneItem(SF_DEBUG_CODE("appendChild")))
            List[0]->AS3appendChild(result, child);
//##protect##"instance::XMLList::AS3appendChild()"
    }
    void XMLList::AS3childIndex(SInt32& result)
    {
//##protect##"instance::XMLList::AS3childIndex()"
        if (HasOneItem(SF_DEBUG_CODE("childIndex")))
            List[0]->AS3childIndex(result);
//##protect##"instance::XMLList::AS3childIndex()"
    }
    void XMLList::AS3inScopeNamespaces(SPtr<Instances::fl::Array>& result)
    {
//##protect##"instance::XMLList::AS3inScopeNamespaces()"
        if (HasOneItem(SF_DEBUG_CODE("inScopeNamespaces")))
            List[0]->AS3inScopeNamespaces(result);
//##protect##"instance::XMLList::AS3inScopeNamespaces()"
    }
    void XMLList::AS3insertChildAfter(Value& result, const Value& child1, const Value& child2)
    {
//##protect##"instance::XMLList::AS3insertChildAfter()"
        if (HasOneItem(SF_DEBUG_CODE("insertChildAfter")))
            List[0]->AS3insertChildAfter(result, child1, child2);
//##protect##"instance::XMLList::AS3insertChildAfter()"
    }
    void XMLList::AS3insertChildBefore(Value& result, const Value& child1, const Value& child2)
    {
//##protect##"instance::XMLList::AS3insertChildBefore()"
        if (HasOneItem(SF_DEBUG_CODE("insertChildBefore")))
            List[0]->AS3insertChildBefore(result, child1, child2);
//##protect##"instance::XMLList::AS3insertChildBefore()"
    }
    void XMLList::AS3nodeKind(ASString& result)
    {
//##protect##"instance::XMLList::AS3nodeKind()"
        if (HasOneItem(SF_DEBUG_CODE("nodeKind")))
            List[0]->AS3nodeKind(result);
//##protect##"instance::XMLList::AS3nodeKind()"
    }
    void XMLList::AS3namespace_(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::XMLList::AS3namespace_()"
        if (HasOneItem(SF_DEBUG_CODE("namespace")))
            List[0]->AS3namespace_(result, argc, argv);
//##protect##"instance::XMLList::AS3namespace_()"
    }
    void XMLList::AS3localName(ASString& result)
    {
//##protect##"instance::XMLList::AS3localName()"
        if (HasOneItem(SF_DEBUG_CODE("localName")))
            List[0]->AS3localName(result);
//##protect##"instance::XMLList::AS3localName()"
    }
    void XMLList::AS3namespaceDeclarations(SPtr<Instances::fl::Array>& result)
    {
//##protect##"instance::XMLList::AS3namespaceDeclarations()"
        if (HasOneItem(SF_DEBUG_CODE("namespaceDeclarations")))
            List[0]->AS3namespaceDeclarations(result);
//##protect##"instance::XMLList::AS3namespaceDeclarations()"
    }
    void XMLList::AS3prependChild(SPtr<Instances::fl::XML>& result, const Value& value)
    {
//##protect##"instance::XMLList::AS3prependChild()"
        if (HasOneItem(SF_DEBUG_CODE("prependChild")))
            List[0]->AS3prependChild(result, value);
//##protect##"instance::XMLList::AS3prependChild()"
    }
    void XMLList::AS3removeNamespace(SPtr<Instances::fl::XML>& result, const Value& ns)
    {
//##protect##"instance::XMLList::AS3removeNamespace()"
        if (HasOneItem(SF_DEBUG_CODE("removeNamespace")))
            List[0]->AS3removeNamespace(result, ns);
//##protect##"instance::XMLList::AS3removeNamespace()"
    }
    void XMLList::AS3replace(SPtr<Instances::fl::XML>& result, const Value& propertyName, const Value& value)
    {
//##protect##"instance::XMLList::AS3replace()"
        if (HasOneItem(SF_DEBUG_CODE("replace")))
            List[0]->AS3replace(result, propertyName, value);
//##protect##"instance::XMLList::AS3replace()"
    }
    void XMLList::AS3setChildren(SPtr<Instances::fl::XML>& result, const Value& value)
    {
//##protect##"instance::XMLList::AS3setChildren()"
        if (HasOneItem(SF_DEBUG_CODE("setChildren")))
            List[0]->AS3setChildren(result, value);
//##protect##"instance::XMLList::AS3setChildren()"
    }
    void XMLList::AS3setLocalName(const Value& result, const Value& name)
    {
//##protect##"instance::XMLList::AS3setLocalName()"
        if (HasOneItem(SF_DEBUG_CODE("setLocalName")))
            List[0]->AS3setLocalName(result, name);
//##protect##"instance::XMLList::AS3setLocalName()"
    }
    void XMLList::AS3setName(const Value& result, const Value& name)
    {
//##protect##"instance::XMLList::AS3setName()"
        if (HasOneItem(SF_DEBUG_CODE("setName")))
            List[0]->AS3setName(result, name);
//##protect##"instance::XMLList::AS3setName()"
    }
    void XMLList::AS3setNamespace(const Value& result, const Value& ns)
    {
//##protect##"instance::XMLList::AS3setNamespace()"
        if (HasOneItem(SF_DEBUG_CODE("setNamespace")))
            List[0]->AS3setNamespace(result, ns);
//##protect##"instance::XMLList::AS3setNamespace()"
    }

    SPtr<Instances::fl::QName> XMLList::AS3name()
    {
        SPtr<Instances::fl::QName> result;
        AS3name(result);
        return result;
    }
    SPtr<Instances::fl::XML> XMLList::AS3addNamespace(const Value& ns)
    {
        SPtr<Instances::fl::XML> result;
        AS3addNamespace(result, ns);
        return result;
    }
    SPtr<Instances::fl::XML> XMLList::AS3appendChild(const Value& child)
    {
        SPtr<Instances::fl::XML> result;
        AS3appendChild(result, child);
        return result;
    }
    SPtr<Instances::fl::Array> XMLList::AS3inScopeNamespaces()
    {
        SPtr<Instances::fl::Array> result;
        AS3inScopeNamespaces(result);
        return result;
    }
    SPtr<Instances::fl::Array> XMLList::AS3namespaceDeclarations()
    {
        SPtr<Instances::fl::Array> result;
        AS3namespaceDeclarations(result);
        return result;
    }
    SPtr<Instances::fl::XML> XMLList::AS3prependChild(const Value& value)
    {
        SPtr<Instances::fl::XML> result;
        AS3prependChild(result, value);
        return result;
    }
    SPtr<Instances::fl::XML> XMLList::AS3removeNamespace(const Value& ns)
    {
        SPtr<Instances::fl::XML> result;
        AS3removeNamespace(result, ns);
        return result;
    }
    SPtr<Instances::fl::XML> XMLList::AS3replace(const Value& propertyName, const Value& value)
    {
        SPtr<Instances::fl::XML> result;
        AS3replace(result, propertyName, value);
        return result;
    }
    SPtr<Instances::fl::XML> XMLList::AS3setChildren(const Value& value)
    {
        SPtr<Instances::fl::XML> result;
        AS3setChildren(result, value);
        return result;
    }
//##protect##"instance$methods"
    XMLList::~XMLList()
    {
        if (TargetProperty)
            TargetProperty->Release();
    }

    void XMLList::GetDescendants(XMLList& list, const Multiname& prop_name)
    {
        const UPInt size = List.GetSize();
        for (UPInt i = 0; i < size; ++i)
        {
            XML* xml = List[i];
            xml->GetDescendants(list, prop_name);
        }
    }

    void XMLList::AS3Constructor(unsigned argc, const Value* argv)
    {
        VM& vm = GetVM();

        if (argc == 0 || argv[0].IsNullOrUndefined())
        {
#if 0
            // This should be correct.
            InstanceTraits::fl::XML& xml_itr = static_cast<InstanceTraits::fl::XML&>(vm.GetClassTraitsXML().GetInstanceTraits());
            SPtr<XML> xml = xml_itr.MakeInstance(xml_itr);

            List.PushBack(xml);
#endif
        }
        else if (argc == 1)
        {
            const Value& arg = argv[0];

            if (IsXMLObject(arg))
            {
                // Temporary solution.
                Instances::fl::XML* xml = static_cast<Instances::fl::XML*>(arg.GetObject());

                List.PushBack(xml);
            } else
            {
                InstanceTraits::fl::XML& itr_xml = static_cast<InstanceTraits::fl::XML&>(*vm.GetXMLSupport().GetITraitsXML());
                StringManager& sm = vm.GetStringManager();
                ASString str = sm.CreateEmptyString();

                if (!arg.Convert2String(str))
                    return;

                StringDataPtr s(str.ToCStr(), str.GetSize());
                const Classes::fl::XML& cl_xml = static_cast<const Classes::fl::XML&>(vm.GetXMLSupport().GetITraitsXML()->GetClass());
                const bool iw = cl_xml.ignoreWhitespace;

                while (!s.IsEmpty())
                {
                    const char first_char = *ASUtils::SkipWhiteSpace(s.ToCStr(), s.GetSize());

                    if (first_char == ';')
                    {
                        s.TrimLeft(1);
                        continue;
                    }

                    if (first_char != '<')
                    {
                        // Treat this string as a regular string node.
                        StringDataPtr txt;

                        SPInt len = s.FindChar('<');
                        if (len == -1)
                        {
                            txt = s;
                            s.TrimLeft(s.GetSize());
                        }
                        else
                        {
                            txt = StringDataPtr(s.ToCStr(), len);
                            s.TrimLeft(len);
                        }

                        if (iw)
                            txt.TruncateWhitespace();

                        Pickable<Instances::fl::XML> el = itr_xml.MakeInstanceText(itr_xml, txt, NULL);

                        List.PushBack(el);
                    }
                    else
                    {
                        UPInt pos = 0;
                        XMLParser parser(itr_xml);

                        if (!parser.Parse(s, pos, true))
                        {
                            if (pos == 0)
                                // Something is critically wrong.
                                // We couldn't parse anything.
                                return;

                            const char c = s[pos];

                            if (c == ';')
                            {
                                s.TrimLeft(1);
                                vm.IgnoreException();
                            }
                            else if (c == '<')
                            {
                                pos = s.FindLastChar('>', pos) + 1;
                                vm.IgnoreException();
                            }
                            else
                                break;
                        }

                        parser.GetRootNodes(List);
                        s.TrimLeft(pos);
                    }
                }
            }
        }
    }

    void XMLList::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::fl::Object::ForEachChild_GC(prcc, op);

        AS3::ForEachChild_GC(prcc, TargetObject, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, TargetNamespace, op SF_DEBUG_ARG(*this));

        const UPInt size = List.GetSize();
        for (UPInt i = 0; i < size; ++i)
            AS3::ForEachChild_GC(prcc, List[i], op SF_DEBUG_ARG(*this));
    }

    Pickable<Instances::fl::XMLList> XMLList::MakeInstance()
    {
        InstanceTraits::fl::XMLList& itr = static_cast<InstanceTraits::fl::XMLList&>(GetInstanceTraits());

        if (TargetNamespace && TargetObject && TargetProperty)
            return itr.MakeInstance(itr, *TargetObject, ASString(TargetProperty), *TargetNamespace);

        return itr.MakeInstance(itr);
    }

    Pickable<Instances::fl::XMLList> XMLList::MakeInstance(const Multiname& mn)
    {
        Pickable<XMLList> result;

        if (mn.GetName().IsString())
        {
            Namespace* ns = NULL;

            if (mn.IsQName() && !mn.IsAnyNamespace())
            {
                ns = &mn.GetNamespace();

                if (ns->GetPrefix().IsUndefined())
                {
                    // Namespace can have prefix in this XML.
                    Namespace* local_ns = FindNamespaceByURI(ns->GetUri());
                    if (local_ns)
                        ns = local_ns;
                }
            }
            else
            {
                ns = GetVM().GetDefXMLNamespace();
                if (ns == NULL)
                    ns = &GetVM().GetPublicNamespace();
                else if (ns->GetPrefix().IsUndefined())
                {
                    // Default namespace can have prefix in this XML.
                    Namespace* local_ns = FindNamespaceByURI(ns->GetUri());
                    if (local_ns)
                        ns = local_ns;
                }
            }

            result = MakeInstance(
                *this,
                mn.GetName().AsString(),
                *ns
                );
        }
        else
            result = MakeInstance();

        return result;
    }

    Pickable<Instances::fl::XMLList> XMLList::MakeInstance(Instances::fl::Object& tgt_obj, const ASString& tgt_prop, Namespace& tgt_ns)
    {
        InstanceTraits::fl::XMLList& itr = static_cast<InstanceTraits::fl::XMLList&>(GetInstanceTraits());
        return itr.MakeInstance(itr, tgt_obj, tgt_prop, tgt_ns);
    }

    CheckResult XMLList::Equals(bool& result, const Value& v)
    {
        if (v.IsUndefined() && List.IsEmpty())
        {
            result = true;
            return true;
        }

        if (IsXMLListObject(v))
        {
            XMLList* other = static_cast<XMLList*>(v.GetObject());

            if (other->GetSize() == GetSize())
            {
                const UPInt size = GetSize();
                for (UPInt i = 0; i < size; ++i)
                {
                    if (!AbstractEqual(result, Value(List[i]), Value(other->List[i])))
                        return false;

                    if (result == false)
                        break;
                }

                return true;
            }
        }
        else if (List.GetSize() == 1)
        {
            return AbstractEqual(result, Value(List[0]), v);
        }

        result = false;
        return true;
    }

    void XMLList::Apppend(XMLList& v)
    {
        const UPInt size = v.GetSize();

        for (UPInt i = 0; i < size; ++i)
            List.PushBack(v.List[i]);
    }

    CheckResult XMLList::HasOneItem(SF_DEBUG_CODE(const char* fn)) const
    {
        bool result = true;
        if (List.GetSize() != 1)
        {
            VM& vm = GetVM();
            vm.ThrowTypeError(VM::Error(VM::eXMLOnlyWorksWithOneItemLists, vm
                SF_DEBUG_ARG(fn)
                ));
            result = false;
        }
        return result;
    }

    Pickable<XMLList> XMLList::DeepCopy(XML* parent)
    {
        Pickable<XMLList> result = MakeInstance();
        const UPInt size = List.GetSize();

        for (UPInt i = 0; i < size; ++i)
        {
            result->List.PushBack(List[i]->DeepCopy(parent));
        }

        return result;
    }

    Pickable<XMLList> XMLList::ShallowCopy()
    {
        Pickable<XMLList> copy = MakeInstance();
        const UPInt csize = GetSize();

        for (UPInt j = 0; j < csize; ++j)
        {
            SF_ASSERT(List[j]);
            copy->List.PushBack(List[j]);
        }

        return copy;
    }

    void XMLList::SetTargetProperty(ASStringNode* v) 
    {
        if (TargetProperty)
            TargetProperty->Release();

        TargetProperty = v;

        if (TargetProperty)
            TargetProperty->AddRef();
    }

    UInt32 XMLList::ForEachChild(const Multiname& prop_name, CallBack& cb)
    {
        SF_ASSERT(!prop_name.IsAttr());
        UInt32 result = 0;

        if (prop_name.GetName().IsString())
        {
            const ASString name = prop_name.GetName().AsString();
            const UPInt size = List.GetSize();

            for (UPInt i = 0; i < size; ++i)
            {
                XML* el = List[i];
                SF_ASSERT(el);
                const XML::Kind kind = el->GetKind();

                if (kind == XML::kElement)
                {
                    XMLElement* other = static_cast<XMLElement*>(el);
                    SF_ASSERT(other);

                    const ArrayLH<SPtr<XML> >& children = other->GetElementChildren();
                    const UPInt children_size = children.GetSize();

                    for (UPInt k = 0; k < children_size; ++k)
                    {
                        XML* child = children[k];
                        SF_ASSERT(child);

                        if (child->GetName() == name || prop_name.IsAnyType())
                        {
                            if (prop_name.IsQName())
                            {
                                if (prop_name.IsAnyNamespace())
                                {
                                    cb.Call(i, k);
                                    ++result;
                                }
                                else
                                {
                                    const Instances::fl::Namespace& ns = prop_name.GetNamespace();
                                    if (ns == child->GetNamespace())
                                    {
                                        cb.Call(i, k);
                                        ++result;
                                    }
                                }
                            }
                            else
                            {
                                const NamespaceSet& nss = prop_name.GetNamespaceSet();
                                const NamespaceSet::TContainer& namespaces = nss.GetNamespaces();
                                const UPInt size = namespaces.GetSize();

                                for(UPInt j = 0; j < size; ++j)
                                {
                                    const Instances::fl::Namespace& ns = *namespaces[j];
                                    if (ns == child->GetNamespace())
                                    {
                                        cb.Call(i, k);
                                        ++result;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return result;
    }

    // 9.2.1.10 [[ResolveValue]] ( )
    CheckResult XMLList::ResolveValue(XML*& result)
    {
        result = NULL;
        const UPInt size = GetSize();
        VM& vm = GetVM();

        // Step 1.
        if (size > 0)
        {
            if (size == 1)
                result = List[0].GetPtr();
            else
            {
                vm.ThrowTypeError(VM::Error(VM::eXMLAssigmentOneItemLists, vm));
                return false;
            }
        }
        // Step 2.a.
        else if (TargetObject.GetPtr() && TargetProperty && ASConstString(TargetProperty) != "*")
        {
            const Traits& tr = TargetObject->GetTraits();
            const BuiltinTraitsType tt = tr.GetTraitsType();
            XML* base = NULL;

            // Step 2.b.
            if (tt == Traits_XML && tr.IsInstanceTraits())
                base = static_cast<XML*>(TargetObject.GetPtr())->ResolveValue();
            else if (tt == Traits_XMLList && tr.IsInstanceTraits())
            {
                XMLList* target = static_cast<XMLList*>(TargetObject.GetPtr());
                if (!target->ResolveValue(base))
                    return false;
            }
            else
                return false;

            // Step 2.c.
            if (base)
            {
#if 1
                InstanceTraits::fl::XML& xml_itr = static_cast<InstanceTraits::fl::XML&>(*vm.GetXMLSupport().GetITraitsXML());
                SPtr<XML> el(xml_itr.MakeInstanceElement(
                    xml_itr,
                    *TargetNamespace,
                    ASString(TargetProperty),
                    base
                    ));
                base->AppendChild(el);

                List.PushBack(el);
                result = el.GetPtr();
#else
                // From E4X Specification.
                Multiname prop_name(*TargetNamespace, ASString(TargetProperty));

                // Step 2.c.
                if (!base->GetProperty(prop_name, *this))
                    return false;

                // Step 2.e.
                if (GetSize() == 0)
                {
                    // Step 2.e.i.
                    // ???
                    // If (Type(base) is XMLList) and (base.[[Length]] > 1), return null
                    // Step 2.e.ii.
                    if (!base->SetProperty(prop_name, Value(vm.GetStringManager().CreateEmptyString())))
                        return false;

                    // Step 2.e.iii.
                    if (!base->GetProperty(prop_name, *this))
                        return false;
                }
#endif
            }
        }

        // Step 2.f.
        return true;
    }

    // 9.2.1.5 [[HasProperty]] (P)
    bool XMLList::HasProperty(const Multiname& prop_name) const
    {
        bool result = false;

        UInt32 ind;
        if (GetVectorInd(prop_name, ind))
        {
            if (ind < List.GetSize())
                result = true;
        }
        else
        {
            const UPInt size = List.GetSize();
            for (UPInt i = 0; i < size; ++i)
            {
                XML* xml = List[i];
                if (xml->GetKind() == XML::kElement)
                {
                    XMLElement* el = static_cast<XMLElement*>(xml);;
                    if (el->HasProperty(prop_name))
                    {
                        result = true;
                        break;
                    }
                }
            }
        }

        return result;
    }

    // From E4X Specification 9.2.1.2
    CheckResult XMLList::SetProperty(const Multiname& prop_name, const Value& value)
    {
        VM& vm = GetVM();
        UInt32 i;

        if (GetVectorInd(prop_name, i))
        {
            // Step 2.
            XML* r = NULL;
            XMLList* rList = NULL;

            // Step 2.a.
            if (TargetObject != NULL)
            {
                const Traits& tr = TargetObject->GetTraits();
                SF_ASSERT(tr.IsInstanceTraits());

                // Step 2.a.i.
                if (tr.IsInstanceTraits())
                {
                    switch (tr.GetTraitsType())
                    {
                    case Traits_XML:
                        r = static_cast<XML*>(TargetObject.GetPtr())->ResolveValue();
                        break;
                    case Traits_XMLList:
                        rList = static_cast<XMLList*>(TargetObject.GetPtr());
                        if (!rList->ResolveValue(r))
                            return false;
                        break;
                    default:
                        SF_ASSERT(false);  // Target object should be either XML or XMLList
                        break;
                    }
                }

                // Step 2.a.ii.
                if (r == NULL)
                    return false;
            }

            // Step 2.c.
            if (i >= GetSize())
            {
                // Step 2.c.i.
                if (rList != NULL)
                {
                    // Step 2.c.i.1.
                    if (rList->GetSize() != 1)
                        return false;

                    // Step 2.c.i.2.
                    r = rList->List[0];
                }

                // Step 2.c.ii.
                if (r && r->GetKind() != XML::kElement)
                    return false;

                XMLElement* rElement = static_cast<XMLElement*>(r);  // we know it's an XMLElement, from above
                SPtr<Instances::fl::XML> y;
                InstanceTraits::fl::XML& itr_xml = static_cast<InstanceTraits::fl::XML&>(*vm.GetXMLSupport().GetITraitsXML());

                const bool isAttribute = (TargetNamespace && TargetProperty && Multiname(*TargetNamespace, ASString(TargetProperty)).IsAttr());

                // Step 2.c.iv.
                if (isAttribute) 
                {
                    UPInt attrIndex;
                    Multiname target_mn(*TargetNamespace, ASString(TargetProperty));

                    // Step 2.c.iv.2.
                    if (rElement->FindAttr(target_mn, attrIndex))
                        return false;

                    // Step 2.c.iv.3.
                    StringManager& sm = vm.GetStringManager();
                    y = itr_xml.MakeInstanceAttr(itr_xml, *TargetNamespace, ASString(TargetProperty), sm.CreateEmptyString(), r);
                }
                else if (TargetProperty == NULL || ASString(TargetProperty) == "*")
                    // Step 2.c.v.
                    y = itr_xml.MakeInstanceText(itr_xml, "", r);
                else
                    // Step 2.c.vi.
                    y = itr_xml.MakeInstanceElement(itr_xml, *TargetNamespace, ASString(TargetProperty), r);

                // Step 2.c.vii.
                i = (UInt32)GetSize();

                // Step 2.c.viii.
                if (!isAttribute)
                {
                    // Step 2.c.viii.1.
                    if (r != NULL)
                    {
                        UInt32 j;
                        const UPInt size = rElement->GetElementChildren().GetSize();

                        // Step 2.c.viii.1.a.
                        if (i > 0)
                        {
                            // Step 2.c.viii.1.a.i.
                            j = 0;
                            const XML* xml = List[i - 1];

                            // Step 2.c.viii.1.a.2.
                            while (j < size - 1 && rElement->GetChild(j) != xml)
                            {
                                ++j;
                            }
                        }
                        // Step 2.c.viii.1.b.
                        else
                            j = static_cast<UInt32>(size - 1);

                        // Step 2.c.viii.1.c.
                        // Call the [[Insert]] method of r with arguments ToString(j+1) and y.
                        // Why it is ToString(j+1) ?
                        if (!r->InsertChildAt(j + 1, Value(y)))
                            // Exception.
                            return false;
                    }

                    if (IsXMLObject(value))
                        // Step 2.c.viii.2.
                        y->AS3setName(static_cast<XML*>(value.GetObject())->GetName());
                    else if (IsXMLListObject(value))
                        // Step 2.c.viii.3.
                        y->AS3setName(static_cast<XMLList*>(value.GetObject())->GetTargetProperty());
                }

                // Step 2.c.ix.
                List.PushBack(y);
            }

            Value V(value);  // Spec says to modify V, but ours is const, so we make a copy

            // Step 2.d.
            {
                bool isTextValue = true;
                if (IsXMLObject(value))
                {
                    const XML* xmlValue = static_cast<XML*>(value.GetObject());
                    const XML::Kind xmlKind = xmlValue->GetKind();

                    isTextValue = (xmlKind == XML::kText || xmlKind == XML::kAttr);
                }
                else if (IsXMLListObject(value))
                    isTextValue = false;

                if (isTextValue)
                {
                    StringManager& sm = vm.GetStringManager();
                    ASString strValue = sm.CreateEmptyString();

                    if (value.Convert2String(strValue))
                        V = strValue;
                    else
                        // Exception.
                        return false;
                }
            }

            // Step 2.e.
            XML* xml = List[i];
            XML::Kind xmlKind = xml->GetKind();

            if (xmlKind == XML::kAttr)
            {
                // Step 2.e.i.
                Multiname z(const_cast<Namespace&>(xml->GetNamespace()), xml->GetName());

                // Step 2.e.ii.
                xml->GetParent()->SetProperty(z, V);

                // Step 2.e.iii.
                SPtr<XMLList> attr = MakeInstance();
                xml->GetParent()->GetProperty(z, *attr);

                // Step 2.e.iv.
                List[i] = attr->List[0];
            }
            // Step 2.f.
            else if (IsXMLListObject(V))
            {
                // Step 2.f.i.
                // Create shallow copy of V
                SPtr<XMLList> c = static_cast<XMLList*>(V.GetObject())->ShallowCopy();

                // Step 2.f.ii.
                XML* parent = xml->GetParent();
                const UPInt csize = c->GetSize();

                // Step 2.f.iii.
                if (parent != NULL)
                {
                    // Step 2.f.iii.1.
                    UPInt q;
                    if (xml->GetChildIndex(q))
                    {
                        // Step 2.f.iii.2.
                        if (!static_cast<XMLElement*>(parent)->Replace(q, Value(c)))
                            // Exception.
                            return false;

                        // Step 2.f.iii.2.
                        SF_ASSERT(parent->GetKind() == XML::kElement);
                        for (UPInt j = 0; j < csize; ++j)
                        {
                            XML* newElt = static_cast<XMLElement*>(parent)->GetChild(q + j);
                            SF_ASSERT(newElt != NULL);
                            c->List[j] = newElt;
                        }
                    }
                }

                UPInt oldSize = List.GetSize();
                // Step 2.f.vii.
                if (csize > 1)
                    // csize == 0 means "delete".
                    // csize == 1 means "do not change size".
                    // Add (csize - 1) elements.
                    List.Resize(oldSize + csize - 1);

                // Step 2.f.iv.
                if (csize == 0)
                    List.RemoveAt(i);
                // Step 2.f.v.
                else if (csize > 1)
                {
                    // Shift old values to the end.
                    // In case of csize == 1 we do not need to move anything.
                    // List[i] won't be moved.
                    for (UPInt j = oldSize - 1; j > i; --j)
                    {
                        // (csize - 1) is a number of newly added elements.
                        List[j + csize - 1] = List[j];
                        List[j] = NULL;
                    }
                }

                // Step 2.f.vi.
                for (UPInt j = 0; j < csize; ++j)
#if 0
                    List[i + j] = c->List[j];
#else
                {
                    // There should be an universal way of doing this.
                    XML* l_value = List[i + j];
                    XML* r_value = c->List[j];

                    if (l_value && r_value->GetKind() != XML::kElement)
                    {
                        const Multiname mn(l_value->GetCurrNamespace(), Value(GetStringManager().CreateConstString("*")));
                        Pickable<XML> new_xml = l_value->DeepCopy(l_value->GetParent());
                        List[i + j] = new_xml;

                        if (!new_xml->SetProperty(mn, Value(r_value)))
                            return false;
                    }
                    else
                        List[i + j] = r_value;
                }
#endif
            }
            // Step 2.g.
            else if (IsXMLObject(V) || xmlKind == XML::kText || xmlKind == XML::kComment || xmlKind == XML::kInstruction)
            {
                // Step 2.g.i.
                XML* parent = xml->GetParent();

                // Step 2.g.ii.
                if (parent != NULL)
                {
                    // Step 2.g.ii.1.
                    UPInt q;
                    if (xml->GetChildIndex(q))
                    {
                        // Step 2.g.ii.2.
                        if (!static_cast<XMLElement*>(parent)->Replace(q, V))
                            // Exception
                            return false;

                        if (static_cast<XMLElement*>(parent)->GetElementChildren().GetSize() <= q)
                            // Replace failed
                            return false;

                        // Step 2.g.ii.3.
                        SF_ASSERT(parent->GetKind() == XML::kElement);
                        V = static_cast<XMLElement*>(parent)->GetChild(q);
                    }
                }

                // Step 2.g.iii.
                if (V.IsString())
                {
                    InstanceTraits::fl::XML& itr_xml = static_cast<InstanceTraits::fl::XML&>(*vm.GetXMLSupport().GetITraitsXML());

                    // Step 2.g.iii.1 and 2.g.iii.2.
                    // !!! parent seems to have wrong value !!!.
                    List[i] = itr_xml.MakeInstanceText(itr_xml, V, parent);
                }
                else
                {
                    // Step 2.g.iv.
                    SF_ASSERT(V.GetObject() != NULL);
                    List[i] = static_cast<XML*>(V.GetObject());
                }
            }
            // Step 2.h.
            else
            {
                const Multiname mn(vm);

                if (!List[i]->SetProperty(mn, V))
                    return false;
            }
        }
        // Step 3.
        else if (GetSize() <= 1)
        {
            // Step 3.a.
            if (GetSize() == 0)
            {
                // Step 3.a.i.
                XML* r;
                if (!ResolveValue(r))
                    return false;

                // Step 3.a.ii.
                if (r == NULL || r->AS3length() != 1)
                    return false;

                // Step 3.a.iii.
                List.PushBack(r);
            }

            // Step 3.b.
            if (!List[0]->SetProperty(prop_name, value))
                return false;
        }
        else
        {
            // Tamarin's extension.
            // GetSize() > 1
            vm.ThrowTypeError(VM::Error(VM::eXMLAssigmentOneItemLists, vm));
            return false;
        }

        // Step 4.
        return true;
    }

    Namespace* XMLList::FindNamespaceByURI(const ASString& uri) const
    {
        Namespace* result = NULL;
        Object* to = TargetObject;

        while (to)
        {
            if (IsXMLObject(to))
            {
                XML* xml = static_cast<XML*>(to);

                result = xml->FindNamespaceByURI(uri, NULL);

                // Stop iteration.
                break;
            }
            else if (IsXMLListObject(to))
            {
                XMLList* list = static_cast<XMLList*>(to);
                Namespace* ns = list->TargetNamespace;

                if (ns)
                {
                    if (ns->GetUri() == uri)
                    {
                        result = ns;

                        // Stop iteration.
                        break;
                    }
                }

                to = list->TargetObject;
            }
            else
            {
                SF_ASSERT(false);
            }
        }

        return result;
    }

    class ListGet : public XMLList::CallBack
    {
    public:
        virtual ~ListGet() { }
        ListGet(XMLList& list, Instances::fl::XMLList& new_list) 
            : XMLList::CallBack(list) 
            , NewList(new_list)
        {
        }
        virtual void Call(UPInt li, UPInt ii)
        {
            XML* child = List.List[li];
            SF_ASSERT(child->GetKind() == XML::kElement);
            XMLElement* element = static_cast<XMLElement*>(child);

            NewList.List.PushBack(element->GetChild(ii));
        }

    protected:
        Instances::fl::XMLList& NewList;
    };

    CheckResult XMLList::GetProperty(const Multiname& prop_name, Value& value)
    {
        UInt32 ind;
        if (GetVectorInd(prop_name, ind))
        {
            if (ind < List.GetSize())
            {
                value = List[ind];
                return true;
            }

            return false;
        }

        Pickable<Instances::fl::XMLList> result = MakeInstance(prop_name);
        value = result;

        return GetProperty(prop_name, *result);
    }

    CheckResult XMLList::GetProperty(const Multiname& prop_name, XMLList& list)
    {
        if (prop_name.IsAttr())
        {
            const UPInt size = List.GetSize();
            for (UPInt i = 0; i < size; ++i)
                List[i]->GetProperty(prop_name, list).DoNotCheck();

            return list.GetSize() != 0;
        }

        ListGet cb(*this, list);
        return ForEachChild(prop_name, cb) != 0;
    }

    void XMLList::GetDynamicProperty(AbsoluteIndex ind, Value& value)
    {
        value = List[ind.Get()];
    }

    CheckResult XMLList::DeleteProperty(const Multiname& prop_name)
    {
        // Step 2.
        UInt32 ind;
        if (GetVectorInd(prop_name, ind))
        {
            // Step 2.a.
            if (ind >= GetSize())
                return true;

            // Step 2.b.
            XML* xml = List[ind];

            // Step 2.b.i.
            XML* parent = xml->GetParent();
            // Step 2.b.ii.
            if (parent != NULL)
            {
                // Step 2.b.ii.1.
                if (xml->GetKind() == XML::kAttr)
                {
                    const Multiname mn(xml->GetCurrNamespace(), Value(xml->GetName()));

                    // Step 2.b.ii.1.a.
                    parent->DeleteProperty(mn);
                }
                // Step 2.b.ii.2.
                else
                {
                    // Step 2.b.ii.2.a.
                    UPInt q;
                    if (xml->GetChildIndex(q))
                        // Step 2.b.ii.2.b.
                        parent->DeleteByIndex(q);
                }
            }

            // Step 2.b.iii.
            // Step 2.b.iv.
            // Step 2.b.v.
            List.RemoveAt(ind);
        }
        else
        {
            // Step 3.
            const UPInt size = GetSize();
            for (UPInt i = 0; i < size; ++i)
            {
                XML* q = List[i];

                // Step 3.a.
                if (q->GetKind() == XML::kElement)
                {
                    // Step 3.a.i.
                    if (!q->DeleteProperty(prop_name))
                        return false;
                }
            }
        }

        // Step 4.
        // Step 2.c.
        return true;
    }

    void XMLList::GetNextPropertyName(Value& name, GlobalSlotIndex ind) const
    {
        StringManager& sm = GetStringManager();

        if (ind.Get() <= static_cast<UInt32>(List.GetSize()))
        {
            LongFormatter f(AbsoluteIndex(ind).Get());

            f.Convert();
            name = sm.CreateString(f.ToCStr(), f.GetSize());
            return;
        }

        name = sm.GetBuiltin(AS3Builtin_null);
    }

    GlobalSlotIndex XMLList::GetNextDynPropIndex(GlobalSlotIndex ind) const
    {
        if (ind < static_cast<UInt32>(List.GetSize()))
            return ++ind;

        return GlobalSlotIndex(0);
    }

    void XMLList::GetNextPropertyValue(Value& value, GlobalSlotIndex ind)
    {
        if (ind.Get() <= static_cast<UInt32>(List.GetSize()))
        {
            value = List[AbsoluteIndex(ind).Get()];
            return;
        }

        value.SetUndefined();
    }
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl
{
    const ThunkInfo XMLList::ti[XMLList::ThunkInfoNum] = {
        {TFunc_Instances_XMLList_prototypeGet::Func, &AS3::fl::XMLListTI, "prototype", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_XMLList_prototypeSet::Func, NULL, "prototype", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_XMLList_AS3length::Func, &AS3::fl::int_TI, "length", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3toString::Func, &AS3::fl::StringTI, "toString", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3valueOf::Func, &AS3::fl::XMLListTI, "valueOf", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {&Instances::fl::XMLList::AS3hasOwnProperty, &AS3::fl::BooleanTI, "hasOwnProperty", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3propertyIsEnumerable::Func, &AS3::fl::BooleanTI, "propertyIsEnumerable", NS_AS3, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {TFunc_Instances_XMLList_AS3attribute::Func, &AS3::fl::XMLListTI, "attribute", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3attributes::Func, &AS3::fl::XMLListTI, "attributes", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3child::Func, &AS3::fl::XMLListTI, "child", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3children::Func, &AS3::fl::XMLListTI, "children", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3comments::Func, &AS3::fl::XMLListTI, "comments", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3contains::Func, &AS3::fl::BooleanTI, "contains", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3copy::Func, &AS3::fl::XMLListTI, "copy", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3descendants::Func, &AS3::fl::XMLListTI, "descendants", NS_AS3, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {TFunc_Instances_XMLList_AS3elements::Func, &AS3::fl::XMLListTI, "elements", NS_AS3, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {TFunc_Instances_XMLList_AS3hasComplexContent::Func, &AS3::fl::BooleanTI, "hasComplexContent", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3hasSimpleContent::Func, &AS3::fl::BooleanTI, "hasSimpleContent", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3name::Func, &AS3::fl::QNameTI, "name", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3normalize::Func, &AS3::fl::XMLListTI, "normalize", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3parent::Func, NULL, "parent", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3processingInstructions::Func, &AS3::fl::XMLListTI, "processingInstructions", NS_AS3, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {TFunc_Instances_XMLList_AS3text::Func, &AS3::fl::XMLListTI, "text", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3toXMLString::Func, &AS3::fl::StringTI, "toXMLString", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3addNamespace::Func, &AS3::fl::XMLTI, "addNamespace", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3appendChild::Func, &AS3::fl::XMLTI, "appendChild", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3childIndex::Func, &AS3::fl::int_TI, "childIndex", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3inScopeNamespaces::Func, &AS3::fl::ArrayTI, "inScopeNamespaces", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3insertChildAfter::Func, NULL, "insertChildAfter", NS_AS3, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Instances_XMLList_AS3insertChildBefore::Func, NULL, "insertChildBefore", NS_AS3, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Instances_XMLList_AS3nodeKind::Func, &AS3::fl::StringTI, "nodeKind", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3namespace_::Func, NULL, "namespace", NS_AS3, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {TFunc_Instances_XMLList_AS3localName::Func, &AS3::fl::StringTI, "localName", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3namespaceDeclarations::Func, &AS3::fl::ArrayTI, "namespaceDeclarations", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3prependChild::Func, &AS3::fl::XMLTI, "prependChild", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3removeNamespace::Func, &AS3::fl::XMLTI, "removeNamespace", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3replace::Func, &AS3::fl::XMLTI, "replace", NS_AS3, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Instances_XMLList_AS3setChildren::Func, &AS3::fl::XMLTI, "setChildren", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3setLocalName::Func, NULL, "setLocalName", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3setName::Func, NULL, "setName", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3setNamespace::Func, NULL, "setNamespace", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
    };

    XMLList::XMLList(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::XMLList::XMLList()"
        SetArrayLike();
        SetTraitsType(Traits_XMLList);
//##protect##"InstanceTraits::XMLList::XMLList()"
        SetMemSize(sizeof(Instances::fl::XMLList));

    }

    void XMLList::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<XMLList&>(t));
    }

//##protect##"instance_traits$methods"
    Pickable<Instances::fl::XMLList> XMLList::MakeInstance(Traits& t, Instances::fl::Object& target_obj, const ASString& target_prop, Instances::fl::Namespace& target_ns)
    {
        Pickable<Instances::fl::XMLList> list(new(t.Alloc()) Instances::fl::XMLList(t));

        list->SetTargetObject(&target_obj);
        list->SetTargetProperty(target_prop.GetNode());
        list->SetTargetNamespace(target_ns);
        return list;
    }

    void XMLList::toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
        SF_UNUSED4(ti, _this, argc, argv);

        if (_this.IsObject() && _this.GetObject() == &vm.GetXMLSupport().GetITraitsXMLList()->GetClass().GetPrototype())
            // This method is called on a prototype object.
            result = vm.GetStringManager().GetBuiltin(AS3Builtin_empty_);
        else
        {
            if (!IsXMLListObject(_this))
                return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm
                    SF_DEBUG_ARG("XMLList::toStringProto")
                    ));

            Instances::fl::XMLList* obj = static_cast<Instances::fl::XMLList*>(_this.GetObject());
            ASString str = vm.GetStringManager().GetBuiltin(AS3Builtin_empty_);

            obj->AS3toString(str);
            // We do not check for exception here on purpose. There should be not much harm.
            result = str;
        }
    }
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits

namespace Classes { namespace fl
{
    XMLList::XMLList(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::XMLList::XMLList()"
//##protect##"class_::XMLList::XMLList()"
    }
//##protect##"class_$methods"
    void XMLList::Construct(Value& _this, unsigned argc, const Value* argv, bool extCall)
    {
        if (argc == 1)
        {
            const Traits& tr = GetVM().GetValueTraits(argv[0]);
            const BuiltinTraitsType tt = tr.GetTraitsType();

            if (tt == Traits_XMLList && tr.IsInstanceTraits())
            {
                // We shouldn't create new object in this case.
                _this = argv[0];
                return;
            }
        }

        Class::Construct(_this, argc, argv, extCall);
    }

    void XMLList::Call(const Value& _this, Value& result, unsigned argc, const Value* const argv)
    {
        SF_UNUSED1(_this);

        // The same logic as in Construct.
        Construct(result, argc, argv);
    }

    // Created manually.
    const ThunkInfo XMLList::f[2] = {
        {&InstanceTraits::fl::XMLList::toStringProto, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {&Instances::fl::XMLList::AS3hasOwnProperty, &AS3::fl::BooleanTI, "hasOwnProperty", NULL, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
    };

    void XMLList::InitPrototype(AS3::Object& obj) const
    {
        if (GetParentClass())
            GetParentClass()->InitPrototype(obj);

        //InitPrototypeFromVTable(obj);
        InitPrototypeFromVTableCheckType(obj);

        for (unsigned i = 0; i < NUMBEROF(f); ++i)
            AddDynamicFunc(obj, f[i]);

        AddConstructor(obj);
    }
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl
{
    XMLList::XMLList(VM& vm)
    : Traits(vm, AS3::fl::XMLListCI)
    {
//##protect##"ClassTraits::XMLList::XMLList()"
        SetTraitsType(Traits_XMLList);
//##protect##"ClassTraits::XMLList::XMLList()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::XMLList(vm, AS3::fl::XMLListCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl::XMLList(*this));

    }

    Pickable<Traits> XMLList::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) XMLList(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl
{
    const TypeInfo XMLListTI = {
        TypeInfo::CompileTime | TypeInfo::DynamicObject | TypeInfo::Final,
        "XMLList", "", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo XMLListCI = {
        &XMLListTI,
        ClassTraits::fl::XMLList::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl::XMLList::ThunkInfoNum,
        0,
        NULL,
        NULL,
        InstanceTraits::fl::XMLList::ti,
        NULL,
    };
}; // namespace fl


}}} // namespace Scaleform { namespace GFx { namespace AS3

