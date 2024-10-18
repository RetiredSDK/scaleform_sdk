//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_GradientBevelFilter.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Filters_GradientBevelFilter_H
#define INC_AS3_Obj_Filters_GradientBevelFilter_H

#include "AS3_Obj_Filters_BitmapFilter.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
// Forward declaration.
namespace fl_filters
{
    extern const TypeInfo GradientBevelFilterTI;
    extern const ClassInfo GradientBevelFilterCI;
    extern const TypeInfo BitmapFilterTI;
    extern const ClassInfo BitmapFilterCI;
} // namespace fl_filters
namespace fl
{
    extern const TypeInfo ArrayTI;
    extern const ClassInfo ArrayCI;
    extern const TypeInfo NumberTI;
    extern const ClassInfo NumberCI;
    extern const TypeInfo BooleanTI;
    extern const ClassInfo BooleanCI;
    extern const TypeInfo int_TI;
    extern const ClassInfo int_CI;
    extern const TypeInfo StringTI;
    extern const ClassInfo StringCI;
} // namespace fl

namespace ClassTraits { namespace fl_filters
{
    class GradientBevelFilter;
}}

namespace InstanceTraits { namespace fl_filters
{
    class GradientBevelFilter;
}}

namespace Classes { namespace fl_filters
{
    class GradientBevelFilter;
}}

//##protect##"forward_declaration"
//##protect##"forward_declaration"
    
namespace ClassTraits { namespace fl_filters
{
    class GradientBevelFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::GradientBevelFilter"; }
#endif
    public:
        typedef Classes::fl_filters::GradientBevelFilter ClassType;

    public:
        GradientBevelFilter(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

