//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_DisplacementMapFilter.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Filters_DisplacementMapFilter_H
#define INC_AS3_Obj_Filters_DisplacementMapFilter_H

#include "AS3_Obj_Filters_BitmapFilter.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
// Forward declaration.
namespace fl_filters
{
    extern const TypeInfo DisplacementMapFilterTI;
    extern const ClassInfo DisplacementMapFilterCI;
    extern const TypeInfo BitmapFilterTI;
    extern const ClassInfo BitmapFilterCI;
} // namespace fl_filters
namespace fl
{
    extern const TypeInfo NumberTI;
    extern const ClassInfo NumberCI;
    extern const TypeInfo uintTI;
    extern const ClassInfo uintCI;
    extern const TypeInfo StringTI;
    extern const ClassInfo StringCI;
} // namespace fl
namespace fl_display
{
    extern const TypeInfo BitmapDataTI;
    extern const ClassInfo BitmapDataCI;
} // namespace fl_display
namespace fl_geom
{
    extern const TypeInfo PointTI;
    extern const ClassInfo PointCI;
} // namespace fl_geom

namespace ClassTraits { namespace fl_filters
{
    class DisplacementMapFilter;
}}

namespace InstanceTraits { namespace fl_filters
{
    class DisplacementMapFilter;
}}

namespace Classes { namespace fl_filters
{
    class DisplacementMapFilter;
}}

//##protect##"forward_declaration"
namespace Instances
{
    class Point;
    class BitmapData;
}
//##protect##"forward_declaration"
    
namespace ClassTraits { namespace fl_filters
{
    class DisplacementMapFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::DisplacementMapFilter"; }
#endif
    public:
        typedef Classes::fl_filters::DisplacementMapFilter ClassType;

    public:
        DisplacementMapFilter(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

