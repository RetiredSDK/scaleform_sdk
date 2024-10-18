//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Vec_Vector.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Vec_Vector.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../../AS3_VTable.h"
#include "../AS3_Obj_int.h"
#include "../AS3_Obj_uint.h"
#include "../AS3_Obj_Number.h"
#include "../AS3_Obj_String.h"
#include "../AS3_Obj_Global.h"
#include "AS3_Obj_Vec_Vector_int.h"
#include "AS3_Obj_Vec_Vector_uint.h"
#include "AS3_Obj_Vec_Vector_double.h"
#include "AS3_Obj_Vec_Vector_String.h"
#include "AS3_Obj_Vec_Vector_object.h"
#include "../System/AS3_Obj_System_ApplicationDomain.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_vec
{
    Vector::Vector(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Vector::Vector()"
//##protect##"class_::Vector::Vector()"
    }
//##protect##"class_$methods"
    const ClassTraits::Traits& Vector::Resolve2Vector(const ClassTraits::Traits& elem, VMFile* file) const
    {
        VM& vm = GetVM();
        // We MAY NOT use "Vector$" instead of GetName() + "$" because this will break
        // Vector.<Vector.<XXX>> case.
        const ASString name = GetName() + "$" + elem.GetQualifiedName();

        // Try to find a Class first.
        const ClassTraits::Traits* vctr = vm.GetRegisteredClassTraits(name, vm.GetVectorNamespace(), file == NULL ? vm.GetFrameAppDomain() : file->GetAppDomain());

        if (vctr == NULL)
        {
            // Create Traits.
            SPtr<ClassTraits::Traits> tr = Pickable<ClassTraits::Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ClassTraits::fl_vec::Vector_object(vm, name, elem));

            // We have to store ClassTraits somewhere otherwise
            // newly created Traits will be deleted after exiting this block.

            // Register this Vector with a file of its element.
            VMFile* elemFile = (file == NULL ? elem.GetFilePtr() : file);
            if (elemFile)
            {
                elemFile->RegisterLoadedClass(tr);
                elemFile->GetAppDomain().AddClassTrait(name, vm.GetVectorNamespace(), tr.GetPtr());
            }
            else
            {
#ifdef SF_AS3_CLASS_AS_SLOT
                // We cannot use vm.ClassTraitsSet here because it stores weak references.
                // vm.GetLoadingAppDomain().AddClassTrait(name, vm.GetVectorNamespace(), tr.GetPtr());

                UPInt index = 0;
                Class& class_ = tr->GetInstanceTraits().GetClass();

                // Add Class to slots.
                // AddFixedSlot() will register ClassTraits with VM::ClassTraitsSet.
                vm.GetGlobalObjectCPP().AddFixedSlot(class_, Pickable<const Instances::fl::Namespace>(&vm.GetVectorNamespace(), PickValue), index);
#else
                vm.GenericClasses.PushBack(tr);
                vm.GetLoadingAppDomain().AddClassTrait(name, vm.GetVectorNamespace(), tr.GetPtr());
#endif
            }

            vctr = tr;
        }

        return *vctr;
    }

    AS3::Class& Vector::ApplyTypeArgs(unsigned argc, const Value* argv)
    {
        if (argc != 1)
        {
            GetVM().ThrowTypeError(VM::Error(VM::eWrongTypeArgCountError, GetVM()));
            return *this;
        }

        if (!argv[0].IsClass() && !argv[0].IsNullOrUndefined())
        {
            GetVM().ThrowTypeError(VM::Error(VM::eCorruptABCError, GetVM()));
            return *this;
        }

        // If we apply null we should get Vector<*>.
        const AS3::Class& cl = argv[0].IsNullOrUndefined() ? 
            GetVM().GetClassObject() :
            argv[0].AsClass();

        // This logic is similar to one in Resolve2ClassTraits(file, Abc::mn);
        const ClassTraits::Traits* ctr = &cl.GetClassTraits();

        if (ctr == &GetVM().GetClassTraitsSInt())
            return GetVM().GetClassVectorSInt();
        else if (ctr == &GetVM().GetClassTraitsUInt())
            return GetVM().GetClassVectorUInt();
        else if (ctr == &GetVM().GetClassTraitsNumber())
            return GetVM().GetClassVectorNumber();
        else if (ctr == &GetVM().GetClassTraitsString())
            return GetVM().GetClassVectorString();

        const ClassTraits::Traits& v_ctr = Resolve2Vector(*ctr, ctr->GetFilePtr());

        return v_ctr.GetInstanceTraits().GetClass();
    }
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_vec
{
    Vector::Vector(VM& vm)
    : Traits(vm, AS3::fl_vec::VectorCI)
    {
//##protect##"ClassTraits::Vector::Vector()"
//##protect##"ClassTraits::Vector::Vector()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_vec::VectorCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_vec::Vector(*this));

    }

    Pickable<Traits> Vector::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Vector(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_vec
{
    const TypeInfo VectorTI = {
        TypeInfo::CompileTime | TypeInfo::DynamicObject | TypeInfo::Final,
        "Vector", "__AS3__.vec", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo VectorCI = {
        &VectorTI,
        ClassTraits::fl_vec::Vector::MakeClassTraits,
        0,
        0,
        0,
        0,
        NULL,
        NULL,
        NULL,
        NULL,
    };
}; // namespace fl_vec


}}} // namespace Scaleform { namespace GFx { namespace AS3

