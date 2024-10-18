//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_ApplicationDomain.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_System_ApplicationDomain.h"
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
typedef ThunkFunc0<Instances::fl_system::ApplicationDomain, Instances::fl_system::ApplicationDomain::mid_parentDomainGet, SPtr<Instances::fl_system::ApplicationDomain> > TFunc_Instances_ApplicationDomain_parentDomainGet;
typedef ThunkFunc1<Instances::fl_system::ApplicationDomain, Instances::fl_system::ApplicationDomain::mid_getDefinition, Value, const ASString&> TFunc_Instances_ApplicationDomain_getDefinition;
typedef ThunkFunc1<Instances::fl_system::ApplicationDomain, Instances::fl_system::ApplicationDomain::mid_hasDefinition, bool, const ASString&> TFunc_Instances_ApplicationDomain_hasDefinition;

template <> const TFunc_Instances_ApplicationDomain_parentDomainGet::TMethod TFunc_Instances_ApplicationDomain_parentDomainGet::Method = &Instances::fl_system::ApplicationDomain::parentDomainGet;
template <> const TFunc_Instances_ApplicationDomain_getDefinition::TMethod TFunc_Instances_ApplicationDomain_getDefinition::Method = &Instances::fl_system::ApplicationDomain::getDefinition;
template <> const TFunc_Instances_ApplicationDomain_hasDefinition::TMethod TFunc_Instances_ApplicationDomain_hasDefinition::Method = &Instances::fl_system::ApplicationDomain::hasDefinition;

namespace Instances { namespace fl_system
{
    ApplicationDomain::ApplicationDomain(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
//##protect##"instance::ApplicationDomain::ApplicationDomain()$data"
    , VMDomain(&GetVM().GetFrameAppDomain())
//##protect##"instance::ApplicationDomain::ApplicationDomain()$data"
    {
//##protect##"instance::ApplicationDomain::ApplicationDomain()$code"
//##protect##"instance::ApplicationDomain::ApplicationDomain()$code"
    }

    void ApplicationDomain::parentDomainGet(SPtr<Instances::fl_system::ApplicationDomain>& result)
    {
//##protect##"instance::ApplicationDomain::parentDomainGet()"
        VMAppDomain* parentDomain = VMDomain->GetParent();
        if (parentDomain == NULL)
        {
            result = NULL;
        }
        else
        {
            InstanceTraits::fl_system::ApplicationDomain& tr = static_cast<InstanceTraits::fl_system::ApplicationDomain&>(GetInstanceTraits());
            result = tr.MakeInstance(tr);
            result->VMDomain = parentDomain;
        }
//##protect##"instance::ApplicationDomain::parentDomainGet()"
    }
    void ApplicationDomain::getDefinition(Value& result, const ASString& name)
    {
//##protect##"instance::ApplicationDomain::getDefinition()"
        ClassTraits::Traits** classTraits = VMDomain->GetClassTrait(Multiname(GetVM(), name.GetBuffer()));
        result.SetNull();
        if (classTraits != NULL)
        {
            result = &(*classTraits)->GetInstanceTraits().GetClass();
        }
//##protect##"instance::ApplicationDomain::getDefinition()"
    }
    void ApplicationDomain::hasDefinition(bool& result, const ASString& name)
    {
//##protect##"instance::ApplicationDomain::hasDefinition()"
        result = (VMDomain->GetClassTrait(Multiname(GetVM(), name.GetBuffer())) != NULL);
//##protect##"instance::ApplicationDomain::hasDefinition()"
    }

//##protect##"instance$methods"
    void ApplicationDomain::AS3Constructor(unsigned argc, const Value* argv)
    {
        VM& vm = GetVM();
        if (argc == 0 || argv[0].IsNullOrUndefined())
        {
            VMDomain = &vm.GetFrameAppDomain().AddNewChild(vm);
        }
        else
        {
            ApplicationDomain& parentDomain = static_cast<ApplicationDomain&>(*argv[0].GetObject());
            VMDomain = &parentDomain.GetAppDomain().AddNewChild(vm);
        }
    }

    VMAppDomain& ApplicationDomain::GetAppDomain() const
    {
        return *VMDomain;
    }
    void ApplicationDomain::SetAppDomain(VMAppDomain& appDomain)
    {
        VMDomain = &appDomain;
    }
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_system
{
    const ThunkInfo ApplicationDomain::ti[ApplicationDomain::ThunkInfoNum] = {
        {TFunc_Instances_ApplicationDomain_parentDomainGet::Func, &AS3::fl_system::ApplicationDomainTI, "parentDomain", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_ApplicationDomain_getDefinition::Func, NULL, "getDefinition", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_ApplicationDomain_hasDefinition::Func, &AS3::fl::BooleanTI, "hasDefinition", NULL, Abc::NS_Public, CT_Method, 1, 1},
    };

    ApplicationDomain::ApplicationDomain(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::ApplicationDomain::ApplicationDomain()"
//##protect##"InstanceTraits::ApplicationDomain::ApplicationDomain()"
        SetMemSize(sizeof(Instances::fl_system::ApplicationDomain));

    }

    void ApplicationDomain::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<ApplicationDomain&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits

namespace Classes { namespace fl_system
{
    ApplicationDomain::ApplicationDomain(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::ApplicationDomain::ApplicationDomain()"
//##protect##"class_::ApplicationDomain::ApplicationDomain()"
    }
    void ApplicationDomain::currentDomainGet(SPtr<Instances::fl_system::ApplicationDomain>& result)
    {
//##protect##"class_::ApplicationDomain::currentDomainGet()"
        InstanceTraits::fl_system::ApplicationDomain& tr = static_cast<InstanceTraits::fl_system::ApplicationDomain&>(GetInstanceTraits());
        result = tr.MakeInstance(tr);
        result->VMDomain = &GetVM().GetCurrentAppDomain();
//##protect##"class_::ApplicationDomain::currentDomainGet()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes

typedef ThunkFunc0<Classes::fl_system::ApplicationDomain, Classes::fl_system::ApplicationDomain::mid_currentDomainGet, SPtr<Instances::fl_system::ApplicationDomain> > TFunc_Classes_ApplicationDomain_currentDomainGet;

template <> const TFunc_Classes_ApplicationDomain_currentDomainGet::TMethod TFunc_Classes_ApplicationDomain_currentDomainGet::Method = &Classes::fl_system::ApplicationDomain::currentDomainGet;

namespace ClassTraits { namespace fl_system
{
    const ThunkInfo ApplicationDomain::ti[ApplicationDomain::ThunkInfoNum] = {
        {TFunc_Classes_ApplicationDomain_currentDomainGet::Func, &AS3::fl_system::ApplicationDomainTI, "currentDomain", NULL, Abc::NS_Public, CT_Get, 0, 0},
    };
    ApplicationDomain::ApplicationDomain(VM& vm)
    : Traits(vm, AS3::fl_system::ApplicationDomainCI)
    {
//##protect##"ClassTraits::ApplicationDomain::ApplicationDomain()"
//##protect##"ClassTraits::ApplicationDomain::ApplicationDomain()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_system::ApplicationDomain(vm, AS3::fl_system::ApplicationDomainCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_system::ApplicationDomain(*this));

    }

    Pickable<Traits> ApplicationDomain::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ApplicationDomain(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_system
{
    const TypeInfo ApplicationDomainTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "ApplicationDomain", "flash.system", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo ApplicationDomainCI = {
        &ApplicationDomainTI,
        ClassTraits::fl_system::ApplicationDomain::MakeClassTraits,
        ClassTraits::fl_system::ApplicationDomain::ThunkInfoNum,
        0,
        InstanceTraits::fl_system::ApplicationDomain::ThunkInfoNum,
        0,
        ClassTraits::fl_system::ApplicationDomain::ti,
        NULL,
        InstanceTraits::fl_system::ApplicationDomain::ti,
        NULL,
    };
}; // namespace fl_system


}}} // namespace Scaleform { namespace GFx { namespace AS3

