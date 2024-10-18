//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Security_XMLSignatureValidator.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Security_XMLSignatureValidator.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Utils/AS3_Obj_Utils_ByteArray.h"
#ifdef GFX_ENABLE_XML
#include "../AS3_Obj_XML.h"
#endif
#include "AS3_Obj_Security_IURIDereferencer.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_security
{
    const ThunkInfo XMLSignatureValidator_ti[15] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "digestStatus", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "identityStatus", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "referencesStatus", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "revocationCheckSetting", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "revocationCheckSetting", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "signerCN", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "signerDN", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "signerExtendedKeyUsages", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "signerTrustSettings", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "uriDereferencer", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "useSystemTrustStore", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "useSystemTrustStore", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "validityStatus", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "addCertificate", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "verify", NULL, Abc::NS_Public, CT_Method, 1, 1},
    };

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_security
{
    XMLSignatureValidator::XMLSignatureValidator(VM& vm)
    : Traits(vm, AS3::fl_security::XMLSignatureValidatorCI)
    {
//##protect##"ClassTraits::XMLSignatureValidator::XMLSignatureValidator()"
//##protect##"ClassTraits::XMLSignatureValidator::XMLSignatureValidator()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_security::XMLSignatureValidatorCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> XMLSignatureValidator::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) XMLSignatureValidator(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_security
{
    const TypeInfo XMLSignatureValidatorTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "XMLSignatureValidator", "flash.security", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo XMLSignatureValidatorCI = {
        &XMLSignatureValidatorTI,
        ClassTraits::fl_security::XMLSignatureValidator::MakeClassTraits,
        0,
        0,
        15,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_security::XMLSignatureValidator_ti,
        NULL,
    };
}; // namespace fl_security


}}} // namespace Scaleform { namespace GFx { namespace AS3

