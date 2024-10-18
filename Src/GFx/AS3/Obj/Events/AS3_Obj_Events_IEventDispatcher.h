//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_IEventDispatcher.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_IEventDispatcher_H
#define INC_AS3_Obj_Events_IEventDispatcher_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
// Forward declaration.
namespace fl_events
{
    extern const TypeInfo IEventDispatcherTI;
    extern const ClassInfo IEventDispatcherCI;
} // namespace fl_events
namespace fl
{
    extern const TypeInfo BooleanTI;
    extern const ClassInfo BooleanCI;
} // namespace fl

namespace ClassTraits { namespace fl_events
{
    class IEventDispatcher;
}}

namespace InstanceTraits { namespace fl_events
{
    class IEventDispatcher;
}}

namespace Classes { namespace fl_events
{
    class IEventDispatcher;
}}

//##protect##"forward_declaration"
namespace Instances { 
    namespace fl_events
    {
        class Event;
    }
}
//##protect##"forward_declaration"
    
namespace ClassTraits { namespace fl_events
{
    class IEventDispatcher : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::IEventDispatcher"; }
#endif
    public:
        typedef Classes::fl_events::IEventDispatcher ClassType;

    public:
        IEventDispatcher(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

