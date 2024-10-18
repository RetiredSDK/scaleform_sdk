//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_IDynamicPropertyOutput.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Net_IDynamicPropertyOutput_H
#define INC_AS3_Obj_Net_IDynamicPropertyOutput_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
// Forward declaration.
namespace fl_net
{
    extern const TypeInfo IDynamicPropertyOutputTI;
    extern const ClassInfo IDynamicPropertyOutputCI;
} // namespace fl_net

namespace ClassTraits { namespace fl_net
{
    class IDynamicPropertyOutput;
}}

namespace InstanceTraits { namespace fl_net
{
    class IDynamicPropertyOutput;
}}

namespace Classes { namespace fl_net
{
    class IDynamicPropertyOutput;
}}

//##protect##"forward_declaration"
//##protect##"forward_declaration"
    
namespace ClassTraits { namespace fl_net
{
    class IDynamicPropertyOutput : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::IDynamicPropertyOutput"; }
#endif
    public:
        typedef Classes::fl_net::IDynamicPropertyOutput ClassType;

    public:
        IDynamicPropertyOutput(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

