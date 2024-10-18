//##protect##"disclaimer"
/**********************************************************************

Filename    :   AS3_Obj_Gfx_TextFieldEx.cpp
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_TextFieldEx.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "GFx/AS3/AS3_MovieRoot.h"
#include "../Display/AS3_Obj_Display_BitmapData.h"
#include "../AS3_Obj_Array.h"
#include "GFx/AS3/AS3_AvmTextField.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes { namespace fl_gfx
{
    TextFieldEx::TextFieldEx(ClassTraits::Traits& t)
    : Class(t)
    , VALIGN_NONE("none")
    , VALIGN_TOP("top")
    , VALIGN_CENTER("center")
    , VALIGN_BOTTOM("bottom")
    , TEXTAUTOSZ_NONE("none")
    , TEXTAUTOSZ_SHRINK("shrink")
    , TEXTAUTOSZ_FIT("fit")
    {
//##protect##"class_::TextFieldEx::TextFieldEx()"
//##protect##"class_::TextFieldEx::TextFieldEx()"
    }
    void TextFieldEx::appendHtml(const Value& result, Instances::fl_text::TextField* textField, const ASString& newHtml)
    {
//##protect##"class_::TextFieldEx::appendHtml()"
        
        SF_UNUSED(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            GFx::TextField* ptxtDisp = textField->GetTextField();
            if (ptxtDisp->HasStyleSheet()) // doesn't work if style sheet is set
                return;
            Text::StyledText::HTMLImageTagInfoArray imageInfoArray(Memory::GetHeapByAddress(ptxtDisp));
            ptxtDisp->AppendHtml(newHtml.ToCStr(), SF_MAX_UPINT, false, &imageInfoArray);
            if (imageInfoArray.GetSize() > 0)
            {
                ptxtDisp->ProcessImageTags(imageInfoArray);
            }
            ptxtDisp->SetDirtyFlag();
        }

//##protect##"class_::TextFieldEx::appendHtml()"
    }
    void TextFieldEx::setVerticalAlign(const Value& result, Instances::fl_text::TextField* textField, const ASString& valign)
    {
//##protect##"class_::TextFieldEx::setVerticalAlign()"

        SF_UNUSED(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            GFx::TextField* ptxtDisp = textField->GetTextField();
            if (valign == "none")
                ptxtDisp->SetVAlignment(Text::DocView::VAlign_None);
            else 
            {
                if (valign == "top")
                    ptxtDisp->SetVAlignment(Text::DocView::VAlign_Top);
                else if (valign == "bottom")
                    ptxtDisp->SetVAlignment(Text::DocView::VAlign_Bottom);
                else if (valign == "center")
                    ptxtDisp->SetVAlignment(Text::DocView::VAlign_Center);
            }
            ptxtDisp->SetDirtyFlag();
        }

//##protect##"class_::TextFieldEx::setVerticalAlign()"
    }
    void TextFieldEx::getVerticalAlign(ASString& result, Instances::fl_text::TextField* textField)
    {
//##protect##"class_::TextFieldEx::getVerticalAlign()"

        GFx::TextField* ptxtDisp = textField->GetTextField();
        switch (ptxtDisp->GetVAlignment())
        {
        case Text::DocView::VAlign_Bottom:  result = "bottom"; break;
        case Text::DocView::VAlign_Center:  result = "center"; break;
        case Text::DocView::VAlign_Top:     result = "top"; break;
        default:                            result = "none"; break;
        }

//##protect##"class_::TextFieldEx::getVerticalAlign()"
    }
    void TextFieldEx::setTextAutoSize(const Value& result, Instances::fl_text::TextField* textField, const ASString& autoSz)
    {
//##protect##"class_::TextFieldEx::setTextAutoSize()"

        SF_UNUSED(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            GFx::TextField* ptxtDisp = textField->GetTextField();
            if (autoSz == "none")
                ptxtDisp->SetTextAutoSize(Text::DocView::TAS_None);
            else 
            {
                if (autoSz == "shrink")
                    ptxtDisp->SetTextAutoSize(Text::DocView::TAS_Shrink);
                else if (autoSz == "fit")
                    ptxtDisp->SetTextAutoSize(Text::DocView::TAS_Fit);
            }
            ptxtDisp->SetDirtyFlag();
        }

//##protect##"class_::TextFieldEx::setTextAutoSize()"
    }
    void TextFieldEx::getTextAutoSize(ASString& result, Instances::fl_text::TextField* textField)
    {
//##protect##"class_::TextFieldEx::getTextAutoSize()"

        GFx::TextField* ptxtDisp = textField->GetTextField();
        switch (ptxtDisp->GetTextAutoSize())
        {
        case Text::DocView::TAS_Shrink:     result = "shrink"; break;
        case Text::DocView::TAS_Fit:        result = "fit"; break;
        default:                            result = "none"; break;
        }

//##protect##"class_::TextFieldEx::getTextAutoSize()"
    }
    void TextFieldEx::setIMEEnabled(const Value& result, Instances::fl_text::TextField* textField, bool isEnabled)
    {
//##protect##"class_::TextFieldEx::setIMEEnabled()"
		SF_UNUSED(result);
		GFx::TextField* pgfxTextField = textField->GetTextField();
		pgfxTextField->SetIMEDisabledFlag(!isEnabled);
//##protect##"class_::TextFieldEx::setIMEEnabled()"
    }
    void TextFieldEx::setImageSubstitutions(const Value& result, Instances::fl_text::TextField* textField, const Value& substInfo)
    {
//##protect##"class_::TextFieldEx::setImageSubstitutions()"
        SF_UNUSED2(result, substInfo);
        VM& vm = GetVM();
        if (!textField)
        {
            vm.ThrowArgumentError(VM::Error(VM::eNullArgumentError, GetVM() SF_DEBUG_ARG("TextFieldEx::setImageSubstitutions")));
            return;
        }
        GFx::TextField* pthis = textField->GetTextField();
        if (substInfo.IsNull() || substInfo.IsUndefined())
        {
            // clear all substitutions
            pthis->ClearIdImageDescAssoc();
            pthis->ClearImageSubstitutor();
            pthis->ForceCompleteReformat();
            pthis->SetDirtyFlag();
        }
        else
        {
            if (substInfo.IsObject())
            {
                Object& obj = *substInfo.GetObject();

                // if array is specified as a parameter, proceed it; otherwise
                // if an object is specified - proceed it as single element.
                if (vm.IsOfType(substInfo, vm.GetClassTraitsArray()))
                {
                    Instances::fl::Array& arr = static_cast<Instances::fl::Array&>(obj);
                    for (UPInt i = 0, n = arr.GetSize(); i < n; ++i)
                    {
                        const Value& ve = arr.At(i);
                        if (ve.IsObject())
                        {
                            ToAvmTextField(pthis)->ProceedImageSubstitution(vm, int(i), ve);
                        }
                    }
                }
                else
                {
                    const Value& ve = substInfo;
                    if (ve.IsObject())
                    {
                        ToAvmTextField(pthis)->ProceedImageSubstitution(vm, 0, ve);
                    }
                }
            }
            else
            {
                pthis->LogScriptWarning("%s.setImageSubstitutions() failed: parameter should be either 'null', object or array",
                    pthis->GetName().ToCStr());
            }
        }
//##protect##"class_::TextFieldEx::setImageSubstitutions()"
    }
    void TextFieldEx::updateImageSubstitution(const Value& result, Instances::fl_text::TextField* textField, const ASString& id, Instances::fl_display::BitmapData* image)
    {
//##protect##"class_::TextFieldEx::updateImageSubstitution()"
        SF_UNUSED3(result, id, image);
        VM& vm = GetVM();
        if (!textField)
        {
            vm.ThrowArgumentError(VM::Error(VM::eNullArgumentError, GetVM() SF_DEBUG_ARG("TextFieldEx::setImageSubstitutions")));
            return;
        }
        GFx::TextField* pthis = textField->GetTextField();
        StringHashLH<Ptr<Text::ImageDesc> >* pimageDescAssoc = pthis->GetImageDescAssoc();
        if (pimageDescAssoc)
        {
            Ptr<Text::ImageDesc>* ppimgDesc = pimageDescAssoc->Get(id.ToCStr());
            if (ppimgDesc)
            {
                Text::ImageDesc* pimageDesc = ppimgDesc->GetPtr();
                SF_ASSERT(pimageDesc);
                if (!image)
                {
                    // if null or undefined - remove the substitution and reformat
                    Text::DocView::ImageSubstitutor* pimgSubst = pthis->CreateImageSubstitutor();
                    if (pimgSubst)
                    {
                        pimgSubst->RemoveImageDesc(pimageDesc);
                        pthis->ForceCompleteReformat();
                        pthis->RemoveIdImageDescAssoc(id.ToCStr());
                        pthis->SetDirtyFlag();
                    }
                }
                else
                {
                    ImageResource* pimgRes = image->GetImageResource();

                    Ptr<MovieDefImpl> md = pthis->GetResourceMovieDef();
                    Ptr<Render::Image> img;
                    if (pimgRes->GetImage()->GetImageType() != Render::ImageBase::Type_ImageBase)
                        img = static_cast<Render::Image*>(pimgRes->GetImage());
                    else
                    {
                        if (!md->GetImageCreator())
                            LogDebugMessage(Log_Warning, "ImageCreator is null in UpdateImageSubstitution");
                        else
                        {
                            ImageCreateInfo cinfo(ImageCreateInfo::Create_SourceImage, Memory::GetHeapByAddress(pthis));
                            img = *md->GetImageCreator()->CreateImage(cinfo, static_cast<Render::ImageSource*>(pimgRes->GetImage()));
                        }
                    }
                    pimageDesc->pImage = img;
                    pthis->SetDirtyFlag();
                }
            }
        }
//##protect##"class_::TextFieldEx::updateImageSubstitution()"
    }
    void TextFieldEx::setNoTranslate(const Value& result, Instances::fl_text::TextField* textField, bool noTranslate)
    {
//##protect##"class_::TextFieldEx::setNoTranslate()"
        
        SF_UNUSED(result);
        VM& vm = GetVM();
        if (!textField)
        {
            vm.ThrowArgumentError(VM::Error(VM::eNullArgumentError, GetVM() SF_DEBUG_ARG("TextFieldEx::setNoTranslate")));
            return;
        }
        GFx::TextField* pthis = textField->GetTextField();
        pthis->SetNoTranslate(noTranslate);

//##protect##"class_::TextFieldEx::setNoTranslate()"
    }
    void TextFieldEx::getNoTranslate(bool& result, Instances::fl_text::TextField* textField)
    {
//##protect##"class_::TextFieldEx::getNoTranslate()"
        
        VM& vm = GetVM();
        if (!textField)
        {
            vm.ThrowArgumentError(VM::Error(VM::eNullArgumentError, GetVM() SF_DEBUG_ARG("TextFieldEx::getNoTranslate")));
            return;
        }
        GFx::TextField* pthis = textField->GetTextField();
        result = pthis->IsNoTranslate();

//##protect##"class_::TextFieldEx::getNoTranslate()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes

typedef ThunkFunc2<Classes::fl_gfx::TextFieldEx, Classes::fl_gfx::TextFieldEx::mid_appendHtml, const Value, Instances::fl_text::TextField*, const ASString&> TFunc_Classes_TextFieldEx_appendHtml;
typedef ThunkFunc2<Classes::fl_gfx::TextFieldEx, Classes::fl_gfx::TextFieldEx::mid_setVerticalAlign, const Value, Instances::fl_text::TextField*, const ASString&> TFunc_Classes_TextFieldEx_setVerticalAlign;
typedef ThunkFunc1<Classes::fl_gfx::TextFieldEx, Classes::fl_gfx::TextFieldEx::mid_getVerticalAlign, ASString, Instances::fl_text::TextField*> TFunc_Classes_TextFieldEx_getVerticalAlign;
typedef ThunkFunc2<Classes::fl_gfx::TextFieldEx, Classes::fl_gfx::TextFieldEx::mid_setTextAutoSize, const Value, Instances::fl_text::TextField*, const ASString&> TFunc_Classes_TextFieldEx_setTextAutoSize;
typedef ThunkFunc1<Classes::fl_gfx::TextFieldEx, Classes::fl_gfx::TextFieldEx::mid_getTextAutoSize, ASString, Instances::fl_text::TextField*> TFunc_Classes_TextFieldEx_getTextAutoSize;
typedef ThunkFunc2<Classes::fl_gfx::TextFieldEx, Classes::fl_gfx::TextFieldEx::mid_setIMEEnabled, const Value, Instances::fl_text::TextField*, bool> TFunc_Classes_TextFieldEx_setIMEEnabled;
typedef ThunkFunc2<Classes::fl_gfx::TextFieldEx, Classes::fl_gfx::TextFieldEx::mid_setImageSubstitutions, const Value, Instances::fl_text::TextField*, const Value&> TFunc_Classes_TextFieldEx_setImageSubstitutions;
typedef ThunkFunc3<Classes::fl_gfx::TextFieldEx, Classes::fl_gfx::TextFieldEx::mid_updateImageSubstitution, const Value, Instances::fl_text::TextField*, const ASString&, Instances::fl_display::BitmapData*> TFunc_Classes_TextFieldEx_updateImageSubstitution;
typedef ThunkFunc2<Classes::fl_gfx::TextFieldEx, Classes::fl_gfx::TextFieldEx::mid_setNoTranslate, const Value, Instances::fl_text::TextField*, bool> TFunc_Classes_TextFieldEx_setNoTranslate;
typedef ThunkFunc1<Classes::fl_gfx::TextFieldEx, Classes::fl_gfx::TextFieldEx::mid_getNoTranslate, bool, Instances::fl_text::TextField*> TFunc_Classes_TextFieldEx_getNoTranslate;

template <> const TFunc_Classes_TextFieldEx_appendHtml::TMethod TFunc_Classes_TextFieldEx_appendHtml::Method = &Classes::fl_gfx::TextFieldEx::appendHtml;
template <> const TFunc_Classes_TextFieldEx_setVerticalAlign::TMethod TFunc_Classes_TextFieldEx_setVerticalAlign::Method = &Classes::fl_gfx::TextFieldEx::setVerticalAlign;
template <> const TFunc_Classes_TextFieldEx_getVerticalAlign::TMethod TFunc_Classes_TextFieldEx_getVerticalAlign::Method = &Classes::fl_gfx::TextFieldEx::getVerticalAlign;
template <> const TFunc_Classes_TextFieldEx_setTextAutoSize::TMethod TFunc_Classes_TextFieldEx_setTextAutoSize::Method = &Classes::fl_gfx::TextFieldEx::setTextAutoSize;
template <> const TFunc_Classes_TextFieldEx_getTextAutoSize::TMethod TFunc_Classes_TextFieldEx_getTextAutoSize::Method = &Classes::fl_gfx::TextFieldEx::getTextAutoSize;
template <> const TFunc_Classes_TextFieldEx_setIMEEnabled::TMethod TFunc_Classes_TextFieldEx_setIMEEnabled::Method = &Classes::fl_gfx::TextFieldEx::setIMEEnabled;
template <> const TFunc_Classes_TextFieldEx_setImageSubstitutions::TMethod TFunc_Classes_TextFieldEx_setImageSubstitutions::Method = &Classes::fl_gfx::TextFieldEx::setImageSubstitutions;
template <> const TFunc_Classes_TextFieldEx_updateImageSubstitution::TMethod TFunc_Classes_TextFieldEx_updateImageSubstitution::Method = &Classes::fl_gfx::TextFieldEx::updateImageSubstitution;
template <> const TFunc_Classes_TextFieldEx_setNoTranslate::TMethod TFunc_Classes_TextFieldEx_setNoTranslate::Method = &Classes::fl_gfx::TextFieldEx::setNoTranslate;
template <> const TFunc_Classes_TextFieldEx_getNoTranslate::TMethod TFunc_Classes_TextFieldEx_getNoTranslate::Method = &Classes::fl_gfx::TextFieldEx::getNoTranslate;

namespace ClassTraits { namespace fl_gfx
{
    const MemberInfo TextFieldEx::mi[TextFieldEx::MemberInfoNum] = {
        {"VALIGN_NONE", NULL, OFFSETOF(Classes::fl_gfx::TextFieldEx, VALIGN_NONE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"VALIGN_TOP", NULL, OFFSETOF(Classes::fl_gfx::TextFieldEx, VALIGN_TOP), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"VALIGN_CENTER", NULL, OFFSETOF(Classes::fl_gfx::TextFieldEx, VALIGN_CENTER), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"VALIGN_BOTTOM", NULL, OFFSETOF(Classes::fl_gfx::TextFieldEx, VALIGN_BOTTOM), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"TEXTAUTOSZ_NONE", NULL, OFFSETOF(Classes::fl_gfx::TextFieldEx, TEXTAUTOSZ_NONE), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"TEXTAUTOSZ_SHRINK", NULL, OFFSETOF(Classes::fl_gfx::TextFieldEx, TEXTAUTOSZ_SHRINK), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
        {"TEXTAUTOSZ_FIT", NULL, OFFSETOF(Classes::fl_gfx::TextFieldEx, TEXTAUTOSZ_FIT), Abc::NS_Public, SlotInfo::BT_ConstChar, 1},
    };

    const ThunkInfo TextFieldEx::ti[TextFieldEx::ThunkInfoNum] = {
        {TFunc_Classes_TextFieldEx_appendHtml::Func, NULL, "appendHtml", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Classes_TextFieldEx_setVerticalAlign::Func, NULL, "setVerticalAlign", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Classes_TextFieldEx_getVerticalAlign::Func, &AS3::fl::StringTI, "getVerticalAlign", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_TextFieldEx_setTextAutoSize::Func, NULL, "setTextAutoSize", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Classes_TextFieldEx_getTextAutoSize::Func, &AS3::fl::StringTI, "getTextAutoSize", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Classes_TextFieldEx_setIMEEnabled::Func, NULL, "setIMEEnabled", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Classes_TextFieldEx_setImageSubstitutions::Func, NULL, "setImageSubstitutions", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Classes_TextFieldEx_updateImageSubstitution::Func, NULL, "updateImageSubstitution", NULL, Abc::NS_Public, CT_Method, 3, 3},
        {TFunc_Classes_TextFieldEx_setNoTranslate::Func, NULL, "setNoTranslate", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Classes_TextFieldEx_getNoTranslate::Func, &AS3::fl::BooleanTI, "getNoTranslate", NULL, Abc::NS_Public, CT_Method, 1, 1},
    };
    TextFieldEx::TextFieldEx(VM& vm)
    : Traits(vm, AS3::fl_gfx::TextFieldExCI)
    {
//##protect##"ClassTraits::TextFieldEx::TextFieldEx()"
//##protect##"ClassTraits::TextFieldEx::TextFieldEx()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::Object(vm, AS3::fl_gfx::TextFieldExCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_gfx::TextFieldEx(*this));

    }

    Pickable<Traits> TextFieldEx::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextFieldEx(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_gfx
{
    const TypeInfo TextFieldExTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "TextFieldEx", "scaleform.gfx", &fl_gfx::InteractiveObjectExTI,
        TypeInfo::None
    };

    const ClassInfo TextFieldExCI = {
        &TextFieldExTI,
        ClassTraits::fl_gfx::TextFieldEx::MakeClassTraits,
        ClassTraits::fl_gfx::TextFieldEx::ThunkInfoNum,
        ClassTraits::fl_gfx::TextFieldEx::MemberInfoNum,
        0,
        0,
        ClassTraits::fl_gfx::TextFieldEx::ti,
        ClassTraits::fl_gfx::TextFieldEx::mi,
        NULL,
        NULL,
    };
}; // namespace fl_gfx


}}} // namespace Scaleform { namespace GFx { namespace AS3

