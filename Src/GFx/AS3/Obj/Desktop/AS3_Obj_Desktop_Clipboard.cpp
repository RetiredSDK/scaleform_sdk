//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_Clipboard.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_Clipboard.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

    template <>
    SF_INLINE
    bool GetMethodDefArg<Instances::fl_desktop::Clipboard, Instances::fl_desktop::Clipboard::mid_setData, 2, bool>(AS3::StringManager&)
    {
        return true;
    }

    template <>
    SF_INLINE
    bool GetMethodDefArg<Instances::fl_desktop::Clipboard, Instances::fl_desktop::Clipboard::mid_setDataHandler, 2, bool>(AS3::StringManager&)
    {
        return true;
    }

} // namespace Impl
typedef ThunkFunc0<Instances::fl_desktop::Clipboard, Instances::fl_desktop::Clipboard::mid_formatsGet, SPtr<Instances::fl::Array> > TFunc_Instances_Clipboard_formatsGet;
typedef ThunkFunc0<Instances::fl_desktop::Clipboard, Instances::fl_desktop::Clipboard::mid_clear, const Value> TFunc_Instances_Clipboard_clear;
typedef ThunkFunc1<Instances::fl_desktop::Clipboard, Instances::fl_desktop::Clipboard::mid_clearData, const Value, const ASString&> TFunc_Instances_Clipboard_clearData;
typedef ThunkFunc2<Instances::fl_desktop::Clipboard, Instances::fl_desktop::Clipboard::mid_getData, SPtr<Instances::fl::Object>, const ASString&, const ASString&> TFunc_Instances_Clipboard_getData;
typedef ThunkFunc1<Instances::fl_desktop::Clipboard, Instances::fl_desktop::Clipboard::mid_hasFormat, bool, const ASString&> TFunc_Instances_Clipboard_hasFormat;
typedef ThunkFunc3<Instances::fl_desktop::Clipboard, Instances::fl_desktop::Clipboard::mid_setData, bool, const ASString&, const Value&, bool> TFunc_Instances_Clipboard_setData;
typedef ThunkFunc3<Instances::fl_desktop::Clipboard, Instances::fl_desktop::Clipboard::mid_setDataHandler, bool, const ASString&, const Value&, bool> TFunc_Instances_Clipboard_setDataHandler;

template <> const TFunc_Instances_Clipboard_formatsGet::TMethod TFunc_Instances_Clipboard_formatsGet::Method = &Instances::fl_desktop::Clipboard::formatsGet;
template <> const TFunc_Instances_Clipboard_clear::TMethod TFunc_Instances_Clipboard_clear::Method = &Instances::fl_desktop::Clipboard::clear;
template <> const TFunc_Instances_Clipboard_clearData::TMethod TFunc_Instances_Clipboard_clearData::Method = &Instances::fl_desktop::Clipboard::clearData;
template <> const TFunc_Instances_Clipboard_getData::TMethod TFunc_Instances_Clipboard_getData::Method = &Instances::fl_desktop::Clipboard::getData;
template <> const TFunc_Instances_Clipboard_hasFormat::TMethod TFunc_Instances_Clipboard_hasFormat::Method = &Instances::fl_desktop::Clipboard::hasFormat;
template <> const TFunc_Instances_Clipboard_setData::TMethod TFunc_Instances_Clipboard_setData::Method = &Instances::fl_desktop::Clipboard::setData;
template <> const TFunc_Instances_Clipboard_setDataHandler::TMethod TFunc_Instances_Clipboard_setDataHandler::Method = &Instances::fl_desktop::Clipboard::setDataHandler;

namespace Instances { namespace fl_desktop
{
    Clipboard::Clipboard(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
//##protect##"instance::Clipboard::Clipboard()$data"
//##protect##"instance::Clipboard::Clipboard()$data"
    {
//##protect##"instance::Clipboard::Clipboard()$code"
//##protect##"instance::Clipboard::Clipboard()$code"
    }

    void Clipboard::formatsGet(SPtr<Instances::fl::Array>& result)
    {
//##protect##"instance::Clipboard::formatsGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::formatsGet()");
//##protect##"instance::Clipboard::formatsGet()"
    }
    void Clipboard::clear(const Value& result)
    {
//##protect##"instance::Clipboard::clear()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::clear()");
//##protect##"instance::Clipboard::clear()"
    }
    void Clipboard::clearData(const Value& result, const ASString& format)
    {
//##protect##"instance::Clipboard::clearData()"
        SF_UNUSED2(result, format);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::clearData()");
//##protect##"instance::Clipboard::clearData()"
    }
    void Clipboard::getData(SPtr<Instances::fl::Object>& result, const ASString& format, const ASString& transferMode)
    {
//##protect##"instance::Clipboard::getData()"
        SF_UNUSED3(result, format, transferMode);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::getData()");
//##protect##"instance::Clipboard::getData()"
    }
    void Clipboard::hasFormat(bool& result, const ASString& format)
    {
//##protect##"instance::Clipboard::hasFormat()"
        SF_UNUSED2(result, format);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::hasFormat()");
//##protect##"instance::Clipboard::hasFormat()"
    }
    void Clipboard::setData(bool& result, const ASString& format, const Value& data, bool serializable)
    {
//##protect##"instance::Clipboard::setData()"
        SF_UNUSED4(result, format, data, serializable);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::setData()");
//##protect##"instance::Clipboard::setData()"
    }
    void Clipboard::setDataHandler(bool& result, const ASString& format, const Value& handler, bool serializable)
    {
//##protect##"instance::Clipboard::setDataHandler()"
        SF_UNUSED4(result, format, handler, serializable);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::setDataHandler()");
//##protect##"instance::Clipboard::setDataHandler()"
    }

    SPtr<Instances::fl::Array> Clipboard::formatsGet()
    {
        SPtr<Instances::fl::Array> result;
        formatsGet(result);
        return result;
    }
//##protect##"instance$methods"
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_desktop
{
    const ThunkInfo Clipboard::ti[Clipboard::ThunkInfoNum] = {
        {TFunc_Instances_Clipboard_formatsGet::Func, &AS3::fl::ArrayTI, "formats", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_Clipboard_clear::Func, NULL, "clear", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_Clipboard_clearData::Func, NULL, "clearData", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_Clipboard_getData::Func, &AS3::fl::ObjectTI, "getData", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Instances_Clipboard_hasFormat::Func, &AS3::fl::BooleanTI, "hasFormat", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_Clipboard_setData::Func, &AS3::fl::BooleanTI, "setData", NULL, Abc::NS_Public, CT_Method, 2, 3},
        {TFunc_Instances_Clipboard_setDataHandler::Func, &AS3::fl::BooleanTI, "setDataHandler", NULL, Abc::NS_Public, CT_Method, 2, 3},
    };

    Clipboard::Clipboard(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::Clipboard::Clipboard()"
//##protect##"InstanceTraits::Clipboard::Clipboard()"
        SetMemSize(sizeof(Instances::fl_desktop::Clipboard));

    }

    void Clipboard::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<Clipboard&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits


namespace ClassTraits { namespace fl_desktop
{
    Clipboard::Clipboard(VM& vm)
    : Traits(vm, AS3::fl_desktop::ClipboardCI)
    {
//##protect##"ClassTraits::Clipboard::Clipboard()"
//##protect##"ClassTraits::Clipboard::Clipboard()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_desktop::Clipboard(vm, AS3::fl_desktop::ClipboardCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));

    }

    Pickable<Traits> Clipboard::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Clipboard(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_desktop
{
    const TypeInfo ClipboardTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "Clipboard", "flash.desktop", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo ClipboardCI = {
        &ClipboardTI,
        ClassTraits::fl_desktop::Clipboard::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl_desktop::Clipboard::ThunkInfoNum,
        0,
        NULL,
        NULL,
        InstanceTraits::fl_desktop::Clipboard::ti,
        NULL,
    };
}; // namespace fl_desktop


}}} // namespace Scaleform { namespace GFx { namespace AS3

