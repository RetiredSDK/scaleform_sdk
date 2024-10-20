//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_StageOrientation.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_StageOrientation_H
#define INC_AS3_Obj_Events_StageOrientation_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
// Forward declaration.
namespace fl_events
{
    extern const TypeInfo StageOrientationTI;
    extern const ClassInfo StageOrientationCI;
} // namespace fl_events

namespace ClassTraits { namespace fl_events
{
    class StageOrientation;
}}

namespace InstanceTraits { namespace fl_events
{
    class StageOrientation;
}}

namespace Classes { namespace fl_events
{
    class StageOrientation;
}}

//##protect##"forward_declaration"
//##protect##"forward_declaration"
    
namespace ClassTraits { namespace fl_events
{
    class StageOrientation : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::StageOrientation"; }
#endif
    public:
        typedef Classes::fl_events::StageOrientation ClassType;

    public:
        StageOrientation(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 5 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}}

namespace Classes { namespace fl_events
{
    class StageOrientation : public Class
    {
        friend class ClassTraits::fl_events::StageOrientation;
        static const TypeInfo& GetTypeInfo() { return AS3::fl_events::StageOrientationTI; }
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::StageOrientation"; }
#endif
    public:
        typedef StageOrientation SelfType;
        typedef StageOrientation ClassType;
        
    private:
        StageOrientation(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API members.
        const char* DEFAULT;
        const char* ROTATED_LEFT;
        const char* ROTATED_RIGHT;
        const char* UNKNOWN;
        const char* UPSIDE_DOWN;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

