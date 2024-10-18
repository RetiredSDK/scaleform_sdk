//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_Camera.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Media_Camera.h"
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

namespace InstanceTraits { namespace fl_media
{
    const ThunkInfo Camera_ti[19] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "activityLevel", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "bandwidth", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "currentFPS", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::NumberTI, "fps", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "height", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "index", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "keyFrameInterval", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "loopback", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "motionLevel", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "motionTimeout", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "muted", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "name", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "quality", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::int_TI, "width", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "setKeyFrameInterval", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "setLoopback", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, NULL, "setMode", NULL, Abc::NS_Public, CT_Method, 3, 4},
        {ThunkInfo::EmptyFunc, NULL, "setMotionLevel", NULL, Abc::NS_Public, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "setQuality", NULL, Abc::NS_Public, CT_Method, 2, 2},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_media
{
    Camera::Camera(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Camera::Camera()"
//##protect##"class_::Camera::Camera()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_media
{
    const ThunkInfo Camera_ti[1] = {
        {ThunkInfo::EmptyFunc, &AS3::fl_media::CameraTI, "getCamera", NULL, Abc::NS_Public, CT_Method, 0, 1},
    };
    Camera::Camera(VM& vm)
    : Traits(vm, AS3::fl_media::CameraCI)
    {
//##protect##"ClassTraits::Camera::Camera()"
//##protect##"ClassTraits::Camera::Camera()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_media::CameraCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_media::Camera(*this));

    }

    Pickable<Traits> Camera::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Camera(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_media
{
    const TypeInfo CameraTI = {
        TypeInfo::CompileTime | TypeInfo::Final | TypeInfo::NotImplemented,
        "Camera", "flash.media", &fl_events::EventDispatcherTI,
        TypeInfo::None
    };

    const ClassInfo CameraCI = {
        &CameraTI,
        ClassTraits::fl_media::Camera::MakeClassTraits,
        1,
        0,
        19,
        0,
        ClassTraits::fl_media::Camera_ti,
        NULL,
        InstanceTraits::fl_media::Camera_ti,
        NULL,
    };
}; // namespace fl_media


}}} // namespace Scaleform { namespace GFx { namespace AS3

