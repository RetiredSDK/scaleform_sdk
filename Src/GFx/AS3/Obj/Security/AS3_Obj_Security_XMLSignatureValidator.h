//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Security_XMLSignatureValidator.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Security_XMLSignatureValidator_H
#define INC_AS3_Obj_Security_XMLSignatureValidator_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
// Forward declaration.
namespace fl_security
{
    extern const TypeInfo XMLSignatureValidatorTI;
    extern const ClassInfo XMLSignatureValidatorCI;
    extern const TypeInfo IURIDereferencerTI;
    extern const ClassInfo IURIDereferencerCI;
} // namespace fl_security
namespace fl
{
    extern const TypeInfo StringTI;
    extern const ClassInfo StringCI;
    extern const TypeInfo ArrayTI;
    extern const ClassInfo ArrayCI;
    extern const TypeInfo BooleanTI;
    extern const ClassInfo BooleanCI;
} // namespace fl

namespace ClassTraits { namespace fl_security
{
    class XMLSignatureValidator;
}}

namespace InstanceTraits { namespace fl_security
{
    class XMLSignatureValidator;
}}

namespace Classes { namespace fl_security
{
    class XMLSignatureValidator;
}}

//##protect##"forward_declaration"
namespace Instances 
{
    class IURIDereferencer;
    class ByteArray;
    class XML;
}
//##protect##"forward_declaration"
    
namespace ClassTraits { namespace fl_security
{
    class XMLSignatureValidator : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::XMLSignatureValidator"; }
#endif
    public:
        typedef Classes::fl_security::XMLSignatureValidator ClassType;

    public:
        XMLSignatureValidator(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

