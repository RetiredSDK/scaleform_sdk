//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Html_HTMLLoader.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Html_HTMLLoader_H
#define INC_AS3_Obj_Html_HTMLLoader_H

#include "../Display/AS3_Obj_Display_Sprite.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
// Forward declaration.
namespace fl_html
{
    extern const TypeInfo HTMLLoaderTI;
    extern const ClassInfo HTMLLoaderCI;
    extern const TypeInfo HTMLHostTI;
    extern const ClassInfo HTMLHostCI;
    extern const TypeInfo HTMLHistoryItemTI;
    extern const ClassInfo HTMLHistoryItemCI;
} // namespace fl_html
namespace fl
{
    extern const TypeInfo BooleanTI;
    extern const ClassInfo BooleanCI;
    extern const TypeInfo NumberTI;
    extern const ClassInfo NumberCI;
    extern const TypeInfo uintTI;
    extern const ClassInfo uintCI;
    extern const TypeInfo StringTI;
    extern const ClassInfo StringCI;
    extern const TypeInfo ObjectTI;
    extern const ClassInfo ObjectCI;
} // namespace fl
namespace fl_system
{
    extern const TypeInfo ApplicationDomainTI;
    extern const ClassInfo ApplicationDomainCI;
} // namespace fl_system

namespace ClassTraits { namespace fl_html
{
    class HTMLLoader;
}}

namespace InstanceTraits { namespace fl_html
{
    class HTMLLoader;
}}

namespace Classes { namespace fl_html
{
    class HTMLLoader;
}}

//##protect##"forward_declaration"
namespace Instances
{
    class HTMLHost;
    class ApplicationDomain;
    class URLRequest;
    //class NativeWindowInitOptions;
}
//##protect##"forward_declaration"
    
namespace ClassTraits { namespace fl_html
{
    class HTMLLoader : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::HTMLLoader"; }
#endif
    public:
        typedef Classes::fl_html::HTMLLoader ClassType;

    public:
        HTMLLoader(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

