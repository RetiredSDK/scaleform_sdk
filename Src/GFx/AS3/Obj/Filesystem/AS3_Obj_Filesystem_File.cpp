//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filesystem_File.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filesystem_File.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class Icon;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits { namespace fl_filesystem
{
    const ThunkInfo File_ti[33] = {
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "exists", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_desktop::IconTI, "icon", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "isDirectory", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "isHidden", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "isPackage", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::BooleanTI, "isSymbolicLink", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "nativePath", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "nativePath", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &AS3::fl_filesystem::FileTI, "parent", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "url", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "url", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "browseForDirectory", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "browseForOpen", NULL, Abc::NS_Public, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "browseForOpenMultiple", NULL, Abc::NS_Public, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "browseForSave", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "cancel", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "canonicalize", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_filesystem::FileTI, "clone", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "copyTo", NULL, Abc::NS_Public, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "copyToAsync", NULL, Abc::NS_Public, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "createDirectory", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "deleteDirectory", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, NULL, "deleteDirectoryAsync", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, NULL, "deleteFile", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "deleteFileAsync", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "getDirectoryListing", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "getDirectoryListingAsync", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::StringTI, "getRelativePath", NULL, Abc::NS_Public, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "moveTo", NULL, Abc::NS_Public, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "moveToAsync", NULL, Abc::NS_Public, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "moveToTrash", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "moveToTrashAsync", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_filesystem::FileTI, "resolvePath", NULL, Abc::NS_Public, CT_Method, 1, 1},
    };

}} // namespace InstanceTraits

namespace Classes { namespace fl_filesystem
{
    File::File(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::File::File()"
//##protect##"class_::File::File()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl_filesystem
{
    const ThunkInfo File_ti[7] = {
        {ThunkInfo::EmptyFunc, &AS3::fl_filesystem::FileTI, "applicationDirectory", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_filesystem::FileTI, "applicationStorageDirectory", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_filesystem::FileTI, "desktopDirectory", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_filesystem::FileTI, "documentsDirectory", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_filesystem::FileTI, "createTempDirectory", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl_filesystem::FileTI, "createTempFile", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &AS3::fl::ArrayTI, "getRootDirectories", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };
    File::File(VM& vm)
    : Traits(vm, AS3::fl_filesystem::FileCI)
    {
//##protect##"ClassTraits::File::File()"
//##protect##"ClassTraits::File::File()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_events::EventDispatcher(vm, AS3::fl_filesystem::FileCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_filesystem::File(*this));

    }

    Pickable<Traits> File::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) File(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_filesystem
{
    const TypeInfo FileTI = {
        TypeInfo::CompileTime | TypeInfo::NotImplemented,
        "File", "flash.filesystem", &fl_net::FileReferenceTI,
        TypeInfo::None
    };

    const ClassInfo FileCI = {
        &FileTI,
        ClassTraits::fl_filesystem::File::MakeClassTraits,
        7,
        0,
        33,
        0,
        ClassTraits::fl_filesystem::File_ti,
        NULL,
        InstanceTraits::fl_filesystem::File_ti,
        NULL,
    };
}; // namespace fl_filesystem


}}} // namespace Scaleform { namespace GFx { namespace AS3

