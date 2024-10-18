//##protect##"disclaimer"
/**********************************************************************

Filename    :   AS3_Obj_Gfx_TextFieldEx.h
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_TextFieldEx_H
#define INC_AS3_Obj_Gfx_TextFieldEx_H

#include "AS3_Obj_Gfx_InteractiveObjectEx.h"
//##protect##"includes"
#include "../Text/AS3_Obj_Text_TextField.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
// Forward declaration.
namespace fl_gfx
{
    extern const TypeInfo TextFieldExTI;
    extern const ClassInfo TextFieldExCI;
} // namespace fl_gfx
namespace fl
{
    extern const TypeInfo StringTI;
    extern const ClassInfo StringCI;
    extern const TypeInfo BooleanTI;
    extern const ClassInfo BooleanCI;
} // namespace fl

namespace ClassTraits { namespace fl_gfx
{
    class TextFieldEx;
}}

namespace InstanceTraits { namespace fl_gfx
{
    class TextFieldEx;
}}

namespace Classes { namespace fl_gfx
{
    class TextFieldEx;
}}

//##protect##"forward_declaration"
namespace Instances
{
    namespace fl_display
    {
        class BitmapData;
    }
}
//##protect##"forward_declaration"
    
namespace ClassTraits { namespace fl_gfx
{
    class TextFieldEx : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TextFieldEx"; }
#endif
    public:
        typedef Classes::fl_gfx::TextFieldEx ClassType;

    public:
        TextFieldEx(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 7 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 10 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}}

namespace Classes { namespace fl_gfx
{
    class TextFieldEx : public Class
    {
        friend class ClassTraits::fl_gfx::TextFieldEx;
        static const TypeInfo& GetTypeInfo() { return AS3::fl_gfx::TextFieldExTI; }
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::TextFieldEx"; }
#endif
    public:
        typedef TextFieldEx SelfType;
        typedef TextFieldEx ClassType;
        
    private:
        TextFieldEx(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_appendHtml, 
            mid_setVerticalAlign, 
            mid_getVerticalAlign, 
            mid_setTextAutoSize, 
            mid_getTextAutoSize, 
            mid_setIMEEnabled, 
            mid_setImageSubstitutions, 
            mid_updateImageSubstitution, 
            mid_setNoTranslate, 
            mid_getNoTranslate, 
        };
        void appendHtml(const Value& result, Instances::fl_text::TextField* textField, const ASString& newHtml);
        void setVerticalAlign(const Value& result, Instances::fl_text::TextField* textField, const ASString& valign);
        void getVerticalAlign(ASString& result, Instances::fl_text::TextField* textField);
        void setTextAutoSize(const Value& result, Instances::fl_text::TextField* textField, const ASString& autoSz);
        void getTextAutoSize(ASString& result, Instances::fl_text::TextField* textField);
        void setIMEEnabled(const Value& result, Instances::fl_text::TextField* textField, bool isEnabled);
        void setImageSubstitutions(const Value& result, Instances::fl_text::TextField* textField, const Value& substInfo);
        void updateImageSubstitution(const Value& result, Instances::fl_text::TextField* textField, const ASString& id, Instances::fl_display::BitmapData* image);
        void setNoTranslate(const Value& result, Instances::fl_text::TextField* textField, bool noTranslate);
        void getNoTranslate(bool& result, Instances::fl_text::TextField* textField);

        // C++ friendly wrappers for AS3 methods.
        void appendHtml(Instances::fl_text::TextField* textField, const ASString& newHtml)
        {
            appendHtml(Value::GetUndefined(), textField, newHtml);
        }
        void setVerticalAlign(Instances::fl_text::TextField* textField, const ASString& valign)
        {
            setVerticalAlign(Value::GetUndefined(), textField, valign);
        }
        ASString getVerticalAlign(Instances::fl_text::TextField* textField)
        {
            ASString result(GetStringManager().CreateEmptyString());
            getVerticalAlign(result, textField);
            return result;
        }
        void setTextAutoSize(Instances::fl_text::TextField* textField, const ASString& autoSz)
        {
            setTextAutoSize(Value::GetUndefined(), textField, autoSz);
        }
        ASString getTextAutoSize(Instances::fl_text::TextField* textField)
        {
            ASString result(GetStringManager().CreateEmptyString());
            getTextAutoSize(result, textField);
            return result;
        }
        void setIMEEnabled(Instances::fl_text::TextField* textField, bool isEnabled)
        {
            setIMEEnabled(Value::GetUndefined(), textField, isEnabled);
        }
        void setImageSubstitutions(Instances::fl_text::TextField* textField, const Value& substInfo)
        {
            setImageSubstitutions(Value::GetUndefined(), textField, substInfo);
        }
        void updateImageSubstitution(Instances::fl_text::TextField* textField, const ASString& id, Instances::fl_display::BitmapData* image)
        {
            updateImageSubstitution(Value::GetUndefined(), textField, id, image);
        }
        void setNoTranslate(Instances::fl_text::TextField* textField, bool noTranslate)
        {
            setNoTranslate(Value::GetUndefined(), textField, noTranslate);
        }
        bool getNoTranslate(Instances::fl_text::TextField* textField)
        {
            bool result;
            getNoTranslate(result, textField);
            return result;
        }

    public:
        // AS3 API members.
        const char* VALIGN_NONE;
        const char* VALIGN_TOP;
        const char* VALIGN_CENTER;
        const char* VALIGN_BOTTOM;
        const char* TEXTAUTOSZ_NONE;
        const char* TEXTAUTOSZ_SHRINK;
        const char* TEXTAUTOSZ_FIT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

