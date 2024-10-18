//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_String.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_String.h"
#include "../AS3_VM.h"
#include "../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Array.h"
#include "AS3_Obj_RegExp.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace InstanceTraits { namespace fl
{
    const ThunkInfo String::ti[String::ThunkInfoNum] = {
        {&InstanceTraits::fl::String::lengthGet, &AS3::fl::int_TI, "length", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {&InstanceTraits::fl::String::AS3indexOf, &AS3::fl::int_TI, "indexOf", NS_AS3, Abc::NS_Public, CT_Method, 0, 2},
        {&InstanceTraits::fl::String::AS3lastIndexOf, &AS3::fl::int_TI, "lastIndexOf", NS_AS3, Abc::NS_Public, CT_Method, 0, 2},
        {&InstanceTraits::fl::String::AS3charAt, &AS3::fl::StringTI, "charAt", NS_AS3, Abc::NS_Public, CT_Method, 0, 1},
        {&InstanceTraits::fl::String::AS3charCodeAt, &AS3::fl::NumberTI, "charCodeAt", NS_AS3, Abc::NS_Public, CT_Method, 0, 1},
        {&InstanceTraits::fl::String::AS3concat, &AS3::fl::StringTI, "concat", NS_AS3, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {&InstanceTraits::fl::String::AS3localeCompare, &AS3::fl::int_TI, "localeCompare", NS_AS3, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {&InstanceTraits::fl::String::AS3match, &AS3::fl::ArrayTI, "match", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {&InstanceTraits::fl::String::AS3replace, &AS3::fl::StringTI, "replace", NS_AS3, Abc::NS_Public, CT_Method, 2, 2},
        {&InstanceTraits::fl::String::AS3search, &AS3::fl::int_TI, "search", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {&InstanceTraits::fl::String::AS3slice, &AS3::fl::StringTI, "slice", NS_AS3, Abc::NS_Public, CT_Method, 0, 2},
        {&InstanceTraits::fl::String::AS3split, &AS3::fl::ArrayTI, "split", NS_AS3, Abc::NS_Public, CT_Method, 0, 2},
        {&InstanceTraits::fl::String::AS3substr, &AS3::fl::StringTI, "substr", NS_AS3, Abc::NS_Public, CT_Method, 0, 2},
        {&InstanceTraits::fl::String::AS3substring, &AS3::fl::StringTI, "substring", NS_AS3, Abc::NS_Public, CT_Method, 0, 2},
        {&InstanceTraits::fl::String::AS3toLocaleLowerCase, &AS3::fl::StringTI, "toLocaleLowerCase", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {&InstanceTraits::fl::String::AS3toLocaleUpperCase, &AS3::fl::StringTI, "toLocaleUpperCase", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {&InstanceTraits::fl::String::AS3toLowerCase, &AS3::fl::StringTI, "toLowerCase", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {&InstanceTraits::fl::String::AS3toUpperCase, &AS3::fl::StringTI, "toUpperCase", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {&InstanceTraits::fl::String::AS3toString, &AS3::fl::StringTI, "toString", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
        {&InstanceTraits::fl::String::AS3valueOf, &AS3::fl::StringTI, "valueOf", NS_AS3, Abc::NS_Public, CT_Method, 0, 0},
    };

    String::String(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::String::String()"
        SetTraitsType(Traits_String);
//##protect##"InstanceTraits::String::String()"

    }

    void String::MakeObject(Value& result, Traits& t)
    {
        SF_UNUSED2(result, t); SF_ASSERT(false);
    }

    void String::lengthGet(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::lengthGet()"
        SF_UNUSED5(ti, vm, result, argc, argv);

        // This method shouldn't be generic.
        result.SetSInt32(_this.AsString().GetLength());
//##protect##"InstanceTraits::lengthGet()"
    }
    void String::AS3indexOf(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3indexOf()"
        // ECMA 15.5.4.7
        // NOTE: The indexOf function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.

        SF_UNUSED1(ti);

        if (argc == 0)
        {
            result.SetSInt32(-1);
            return;
        }

        // Convert to String to make this method generic.
        StringManager& sm = vm.GetStringManager();
        ASString thisStr = sm.CreateEmptyString();
        if (!_this.Convert2String(thisStr))
            // Exception
            return;

        ASString searchAddRef = sm.CreateEmptyString();
        if (!argv[0].Convert2String(searchAddRef))
            // Exception.
            return;

        if (searchAddRef.GetLength() == 0)
        {
            // if an empty string is being searched - return zero.
            result.SetSInt32(0);
            return;
        }
        const char* search = searchAddRef.ToCStr();
        // OK since GetString() returns ref to living object
        const char* str = thisStr.ToCStr();

        SInt32 start = 0;
        if (argc > 1)
            if (!argv[1].Convert2Int32(start))
                // Exception.
                return;

        UInt32 chr;
        UInt32 first = UTF8Util::DecodeNextChar(&search);

        for(int i = 0; 
            (chr = UTF8Util::DecodeNextChar(&str)) != 0;
            i++)
        {
            if(i >= start && chr == first)
            {
                const char* s1 = str;
                const char* s2 = search;
                UInt32 c1, c2=0;
                for(;;)
                {
                    c1 = UTF8Util::DecodeNextChar(&s1);
                    c2 = UTF8Util::DecodeNextChar(&s2);

                    if(c1 == 0 || c2 == 0 || c1 != c2) 
                        break;
                }

                if(c2 == 0)
                {
                    result.SetSInt32(i);
                    return;
                }

                if(c1 == 0)
                {
                    result.SetSInt32(-1);
                    return;
                }
            }
        }

        result.SetSInt32(-1);
//##protect##"InstanceTraits::AS3indexOf()"
    }
    void String::AS3lastIndexOf(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3lastIndexOf()"
        // ECMA 15.5.4.8
        // NOTE: The lastIndexOf function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.

        SF_UNUSED1(ti);

        if (argc < 1)
        {
            result.SetSInt32(-1);
            return;
        }

        // Convert to String to make this method generic.
        StringManager& sm = vm.GetStringManager();
        ASString thisStr = sm.CreateEmptyString();
        if (!_this.Convert2String(thisStr))
            // Exception
            return;

        ASString searchAddRef = sm.CreateEmptyString();
        if (!argv[0].Convert2String(searchAddRef))
            // Exception
            return;

        const char* str = thisStr.ToCStr();

        const char* search = searchAddRef.ToCStr();
        SInt32 start = 0x7FFFFFF;

        if (argc > 1)
        {
            Value::Number start_num = 0x7FFFFFF;
            if (!argv[1].Convert2Number(start_num))
                return;

            const Value start_value(start_num);
            if (start_value.IsNaN() || start_value.IsPOSITIVE_INFINITY())
                start = 0x7FFFFFF; // Let's make it clear.
            else if (start_value.IsNEGATIVE_INFINITY())
                start = 0;
            else
                start = static_cast<SInt32>(start_num);
        }

        if (searchAddRef.GetLength() == 0)
        {
            if (argc > 1)
                // if an empty string is being searched - return second argument if any.
                result.SetSInt32(start);
            else
                // If there is no second argument - return size of this string.
                result.SetSInt32(thisStr.GetSize());

            return;
        }

        UInt32 chr;
        UInt32 first = UTF8Util::DecodeNextChar(&search);
        SInt32 lastIndex = -1;

        for(int i = 0; 
            (chr = UTF8Util::DecodeNextChar(&str)) != 0;
            i++)
        {
            if(i <= start && chr == first)
            {
                const char* s1 = str;
                const char* s2 = search;
                UInt32 c1, c2=0;
                for(;;)
                {
                    c1 = UTF8Util::DecodeNextChar(&s1);
                    c2 = UTF8Util::DecodeNextChar(&s2);

                    if(c1 == 0 || c2 == 0 || c1 != c2) 
                        break;
                }
                if(c2 == 0)
                {
                    lastIndex = i;
                }
                if(c1 == 0)
                {
                    break;
                }
            }
        }

        result.SetSInt32(lastIndex);
//##protect##"InstanceTraits::AS3lastIndexOf()"
    }
    void String::AS3charAt(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3charAt()"
        // ECMA 15.5.4.4
        // NOTE: The charAt function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.

        SF_UNUSED1(ti);

        // Convert to String to make this method generic.
        StringManager& sm = vm.GetStringManager();
        ASString thisStr = sm.CreateEmptyString();
        if (!_this.Convert2String(thisStr))
            // Exception
            return;

        // 15.5.5.1 Parameters to string methods should be declared Number not int.
        // It HAS TO BE Number.
        Value::Number index = 0.0;
        if (argc > 0)
            if (!argv[0].Convert2Number(index))
                // Exception
                return;

        const SInt32 i = static_cast<SInt32>(index);
        ASString retVal = sm.CreateEmptyString();
        if (i >= 0 && static_cast<unsigned>(i) < thisStr.GetLength())
            retVal = retVal.AppendChar(thisStr.GetCharAt((unsigned)i));

        result = retVal;
//##protect##"InstanceTraits::AS3charAt()"
    }
    void String::AS3charCodeAt(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3charCodeAt()"
        // ECMA 15.5.4.5
        // NOTE: The charCodeAt function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.

        SF_UNUSED1(ti);

        // Convert to String to make this method generic.
        StringManager& sm = vm.GetStringManager();
        ASString thisStr = sm.CreateEmptyString();
        if (!_this.Convert2String(thisStr))
            // Exception
            return;

        // 15.5.5.1 Parameters to string methods should be declared Number not int.
        Value::Number index = 0.0;
        if (argc > 0)
            if (!argv[0].Convert2Number(index))
                // Exception
                return;

        const SInt32 i = static_cast<SInt32>(index);
        if (i >= 0 && static_cast<unsigned>(i) < thisStr.GetLength())
            result.SetNumber(thisStr.GetCharAt(static_cast<unsigned>(i)));
        else
            result.SetNumber(NumberUtil::NaN());
//##protect##"InstanceTraits::AS3charCodeAt()"
    }
    void String::AS3concat(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3concat()"
        // ECMA 15.5.4.6
        // NOTE: The concat function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.

        SF_UNUSED1(ti);

        // Convert to String to make this method generic.
        StringManager& sm = vm.GetStringManager();
        ASString thisStr = sm.CreateEmptyString();
        if (!_this.Convert2String(thisStr))
            // Exception
            return;

        ASString value = sm.CreateEmptyString();
        for(unsigned i = 0; i < argc; ++i)
        {
            if (!argv[i].Convert2String(value))
                return;

            thisStr += value;
        }

        result = thisStr;
//##protect##"InstanceTraits::AS3concat()"
    }
    void String::AS3localeCompare(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3localeCompare()"
        // ECMA 15.5.4.9
        // NOTE: The localeCompare function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.

        SF_UNUSED1(ti);

        // Convert to String to make this method generic.
        StringManager& sm = vm.GetStringManager();
        ASString thisStr = sm.CreateEmptyString();
        if (!_this.Convert2String(thisStr))
            // Exception
            return;

        if (argc < 1)
        {
            result.SetNumber(thisStr.IsEmpty() ? 1 : 0);
            return;
        }

        if (argc > 1)
            return vm.ThrowArgumentError(VM::Error(VM::eWrongArgumentCountError, vm SF_DEBUG_ARG("String::AS3localeCompare") SF_DEBUG_ARG(0) SF_DEBUG_ARG(1) SF_DEBUG_ARG(argc)));

        ASString str = sm.CreateEmptyString();
        if (!argv[0].Convert2String(str))
            // Exception
            return;

       result.SetNumber(Compare(str, thisStr));
//##protect##"InstanceTraits::AS3localeCompare()"
    }
    void String::AS3match(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3match()"
        // ECMA 15.5.4.10
        // NOTE: The match function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.
        SF_UNUSED(ti);
        StringManager& sm = vm.GetStringManager();

        ASString str = sm.CreateEmptyString();
        if (!_this.Convert2String(str))
            return;

        if (argc >= 1 && !argv[0].IsNullOrUndefined())
        {
            SPtr<Instances::fl::RegExp> pre;
            // RegExp class object
            if (argv[0].IsObject() && vm.IsOfType(argv[0], "RegExp", vm.GetCurrentAppDomain()))
            {
                pre = static_cast<Instances::fl::RegExp*>(argv[0].GetObject());
            }
            // Regular expression pattern
            else {
                ASString pattern = sm.CreateEmptyString();
                if (!argv[0].Convert2String(pattern))
                    return;

                Value args[] = { Value(pattern) };
                if (!vm.ConstructBuiltinObject(pre, "RegExp", 1, args))
                    return;
            }

            if (pre->globalGet())
            {
                SPtr<Instances::fl::Array> parr = vm.MakeArray();
                while (true)
                {
                    SPtr<Instances::fl::Object> pobj = pre->AS3exec(str);
                    if (!pobj) break;
                    parr->PushBack(Value(pobj));
                };
                result = parr;
            }
            else {
                result = pre->AS3exec(str);
            }
        }
//##protect##"InstanceTraits::AS3match()"
    }
    void String::AS3replace(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3replace()"
        // ECMA 15.5.4.11
        // NOTE: The replace function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.
        SF_UNUSED(ti);
        StringManager& sm = vm.GetStringManager();

        ASString str = sm.CreateEmptyString();
        if (!_this.Convert2String(str))
            return;

        if (argc >= 1 && !argv[0].IsNullOrUndefined())
        {
            SPtr<Instances::fl::RegExp> pre;
            // RegExp class object
            if (argv[0].IsObject() && vm.IsOfType(argv[0], "RegExp", vm.GetCurrentAppDomain()))
            {
                pre = static_cast<Instances::fl::RegExp*>(argv[0].GetObject());
            }
            // Regular expression pattern
            else {
                ASString pattern = sm.CreateEmptyString();
                if (!argv[0].Convert2String(pattern))
                    return;

                Value args[] = { Value(pattern) };
                if (!vm.ConstructBuiltinObject(pre, "RegExp", 1, args))
                    return;
            }

            // Replacement object
            // TBD: special $ replacement codes in the repl string
            if (argc >= 2 && !argv[1].IsNullOrUndefined())
            {
                ASString repl = sm.CreateEmptyString();
                if (!argv[1].Convert2String(repl))
                    return;

                while (pre->AS3exec(str))
                {
                    int offset = pre->GetMatchOffset();
                    int length = pre->GetMatchLength();
                    str = str.Substring(0, offset) + repl + 
                          str.Substring(offset + length, str.GetLength());
                    if(!pre->globalGet())
                        break;
                };
                result = str;
            }
        }
//##protect##"InstanceTraits::AS3replace()"
    }
    void String::AS3search(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3search()"
        // ECMA 15.5.4.12
        // NOTE: The search function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.
        SF_UNUSED(ti);
        StringManager& sm = vm.GetStringManager();

        result.SetSInt32(-1);

        ASString str = sm.CreateEmptyString();
        if (!_this.Convert2String(str))
            return;

        if (argc >= 1 && !argv[0].IsNullOrUndefined())
        {
            SPtr<Instances::fl::RegExp> pre;
            // RegExp class object
            if (argv[0].IsObject() && vm.IsOfType(argv[0], "RegExp", vm.GetCurrentAppDomain()))
            {
                pre = static_cast<Instances::fl::RegExp*>(argv[0].GetObject());
            }
            // Regular expression pattern
            else {
                ASString pattern = sm.CreateEmptyString();
                if (!argv[0].Convert2String(pattern))
                    return;

                Value args[] = { Value(pattern) };
                if (!vm.ConstructBuiltinObject(pre, "RegExp", 1, args))
                    return;
            }
            if (pre->AS3exec(str))
                result.SetSInt32(pre->GetMatchOffset());
        }
//##protect##"InstanceTraits::AS3search()"
    }
    void String::AS3slice(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3slice()"
        // ECMA 15.5.4.13
        // NOTE: The slice function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.

        SF_UNUSED1(ti);

        // Convert to String to make this method generic.
        StringManager& sm = vm.GetStringManager();
        ASString thisStr = sm.CreateEmptyString();
        if (!_this.Convert2String(thisStr))
            // Exception
            return;

        if (argc == 0)
        {
            result = thisStr;
            return;
        }

        Value::Number startNumber, endNumber;
        SInt32 utf8Len = (SInt32)thisStr.GetLength();
        SInt32 startIndex = 0;
        SInt32 endIndex = 0x7fffffff;

        if (argc >= 1)
        {
            if (!argv[0].Convert2Number(startNumber))
                return;
            startIndex = (startNumber > utf8Len) ? (SInt32)utf8Len : (SInt32)startNumber;
            if (startIndex < 0)
                startIndex += utf8Len;
        }
        if (argc >= 2)
        {
            if (!argv[1].Convert2Number(endNumber))
                return;
            endIndex = (endNumber > utf8Len) ? (SInt32)utf8Len : (SInt32)endNumber;
            if (endIndex < 0)
                endIndex += utf8Len;
            if (endIndex < startIndex) 
            {   // empty string
                //                 fn.Result->SetString(fn.Env->GetBuiltin(ASBuiltin_empty_));
                result = sm.CreateEmptyString();
                return;
            }
            //length = endIndex - startIndex;
        }    

        result = thisStr.Substring(startIndex, endIndex);
//##protect##"InstanceTraits::AS3slice()"
    }
    void String::AS3split(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3split()"
        // ECMA 15.5.4.14
        // NOTE: The split function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.
        SF_UNUSED1(ti);
        StringManager& sm = vm.GetStringManager();

        ASString str = sm.CreateEmptyString();
        if (!_this.Convert2String(str))
            return;

        // The delimiter parameter
        Value delimiter;    
        const char* psearch = NULL;
        if (argc >= 1 && !argv[0].IsNullOrUndefined())
            delimiter = argv[0];

        // The limit parameter
        UInt32 limit = 0x7fffffff;
        if (argc >= 2 && !argv[1].IsNullOrUndefined())
        {
            Value::Number nlimit;
            if (!argv[1].Convert2Number(nlimit))
                return;
            limit = (UInt32)nlimit;
        }

        // If the delimiter is RegExp object
        if (delimiter.IsObject() && vm.IsOfType(delimiter, "RegExp", vm.GetCurrentAppDomain()))
        {
            SPtr<Instances::fl::RegExp> pre =
                static_cast<Instances::fl::RegExp*>(delimiter.GetObject());
            pre->SetGlobal(true);   // Set global matching by default

            ASString src = pre->sourceGet();
            if (!src.IsEmpty())
            {
                SPtr<Instances::fl::Array> parr = vm.MakeArray();

                unsigned next = 0;
                unsigned cnt = 0;
                while (pre->AS3exec(str) && cnt++ < limit)
                {
                    int offset = pre->GetMatchOffset();
                    int length = pre->GetMatchLength();
                    parr->PushBack(str.Substring(next, offset));
                    next = offset + length;
                };
                if(cnt < limit)
                    parr->PushBack(str.Substring(next, str.GetLength()));

                result = parr;
                return;
            }
            delimiter = src;
        }

        // If the delimiter is not a regular expression,
        // then try to convert it to a string before executing
        ASString delimStr = sm.CreateEmptyString();
        if (!delimiter.Convert2String(delimStr))
            return;
        psearch = delimStr.ToCStr();

        result.Pick(StringSplit(vm, str, psearch, limit));
//##protect##"InstanceTraits::AS3split()"
    }
    void String::AS3substr(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3substr()"
        SF_UNUSED1(ti);

        // Convert to String to make this method generic.
        StringManager& sm = vm.GetStringManager();
        ASString thisStr = sm.CreateEmptyString();
        if (!_this.Convert2String(thisStr))
            // Exception
            return;

        Value::Number startNumber, lengthNumber;
        SInt32 start  = 0;
        SInt32 length = -1;
        unsigned stringLength = thisStr.GetLength();

        if (argc >= 1)
        {
            // ECMA B.2.3 states that we call ToInteger; however, ToInteger leaves large values
            // and +/-Infinity intact. To address this, convert to number first.
            if (!argv[0].Convert2Number(startNumber))
                return;
            start = (startNumber > stringLength) ?
                (SInt32)stringLength : (SInt32)startNumber;
            if(start < 0)
                start += stringLength;
        }

        if (argc >= 2)
        {
            if (!argv[1].Convert2Number(lengthNumber))
                return;
            length = (lengthNumber > stringLength) ?
                (SInt32)stringLength : (SInt32)lengthNumber;
            if (length < 0) 
            {
                // The behavior of method "substr" differs
                // from function "substring". 
                // In "substring" if length is negative it 
                // returns the tail, while in method it returns 
                // an empty string.
                length = 0;
            }
        }

        result = StringSubstring(sm, thisStr, start, length);
//##protect##"InstanceTraits::AS3substr()"
    }
    void String::AS3substring(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3substring()"
        // ECMA 15.5.4.15
        // NOTE: The substring function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.

        SF_UNUSED1(ti);

        // Convert to String to make this method generic.
        StringManager& sm = vm.GetStringManager();
        ASString thisStr = sm.CreateEmptyString();
        if (!_this.Convert2String(thisStr))
            // Exception
            return;

        //int           reassign_needs_research = 0; // It seems to work fine.
        unsigned      utf8Len = thisStr.GetLength();
        Value::Number startNumber = 0;
        Value::Number endNumber = 0x7fffffff;
        SInt32        start  = 0;
        SInt32        end    = 0;
        SInt32        length = -1;

        // Read arguments.
        {
            if (argc >= 1 && !argv[0].Convert2Number(startNumber))
                return;

            if (argc >= 2 && !argv[1].Convert2Number(endNumber))
                return;
        }

        const Value vb(startNumber);
        if (vb.IsNaN())
            startNumber = NumberUtil::NEGATIVE_INFINITY();

        const Value ve(endNumber);
        if (ve.IsNaN())
            endNumber = NumberUtil::NEGATIVE_INFINITY();

        if (endNumber == startNumber)
        {
            result = sm.CreateEmptyString();
            return;
        }

        start = (startNumber > utf8Len) ? (SInt32)utf8Len : (SInt32)startNumber;
        end = (endNumber > utf8Len) ? (SInt32)utf8Len : (SInt32)endNumber;

        //-------
        // "If the value of start is greater than the value 
        //  of end, the parameters are automatically swapped 
        //  before the function executes"
        //-------
        if (end < start) 
            Alg::Swap(start, end);

        if (start < 0)
            start = 0;

        length = end - start;

        result = StringSubstring(sm, thisStr, start, length);
//##protect##"InstanceTraits::AS3substring()"
    }
    void String::AS3toLocaleLowerCase(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toLocaleLowerCase()"
        // ECMA 15.5.4.17
        // NOTE: The toLocaleLowerCase function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.

        SF_UNUSED4(ti, vm, argc, argv);

        // Convert to String to make this method generic.
        StringManager& sm = vm.GetStringManager();
        ASString thisStr = sm.CreateEmptyString();
        if (!_this.Convert2String(thisStr))
            // Exception
            return;

        result = thisStr.ToLower();
//##protect##"InstanceTraits::AS3toLocaleLowerCase()"
    }
    void String::AS3toLocaleUpperCase(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toLocaleUpperCase()"
        // ECMA 15.5.4.19
        // NOTE: The toLocaleUpperCase function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.

        SF_UNUSED4(ti, vm, argc, argv);

        // Convert to String to make this method generic.
        StringManager& sm = vm.GetStringManager();
        ASString thisStr = sm.CreateEmptyString();
        if (!_this.Convert2String(thisStr))
            // Exception
            return;

        result = thisStr.ToUpper();
//##protect##"InstanceTraits::AS3toLocaleUpperCase()"
    }
    void String::AS3toLowerCase(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toLowerCase()"
        // ECMA 15.5.4.16
        // NOTE: The toLowerCase function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.

        SF_UNUSED4(ti, vm, argc, argv);

        // Convert to String to make this method generic.
        StringManager& sm = vm.GetStringManager();
        ASString thisStr = sm.CreateEmptyString();
        if (!_this.Convert2String(thisStr))
            // Exception
            return;

        result = thisStr.ToLower();
//##protect##"InstanceTraits::AS3toLowerCase()"
    }
    void String::AS3toUpperCase(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toUpperCase()"
        // ECMA 15.5.4.18
        // NOTE: The toUpperCase function is intentionally generic; it does not 
        // require that its this value be a String object. Therefore, it can be
        // transferred to other kinds of objects for use as a method.

        SF_UNUSED4(ti, vm, argc, argv);

        // Convert to String to make this method generic.
        StringManager& sm = vm.GetStringManager();
        ASString thisStr = sm.CreateEmptyString();
        if (!_this.Convert2String(thisStr))
            // Exception
            return;

        result = thisStr.ToUpper();
//##protect##"InstanceTraits::AS3toUpperCase()"
    }
    void String::AS3toString(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toString()"

        // ECMA 15.5.4.2
        // The toString function is not generic; it throws a TypeError exception if its 
        // this value is not a String object. Therefore, it cannot be transferred 
        // to other kinds of objects for use as a method.

        SF_UNUSED4(ti, vm, argc, argv);

        if (!_this.IsString())
        {
            return vm.ThrowTypeError(VM::Error(VM::eIllegalOperandTypeError, vm
                SF_DEBUG_ARG(_this.IsNullOrUndefined() ? "null" : vm.GetValueTraits(_this).GetName().ToCStr())
                SF_DEBUG_ARG("String")
                ));
        }

        result = _this;
//##protect##"InstanceTraits::AS3toString()"
    }
    void String::AS3valueOf(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3valueOf()"
        // ECMA 15.5.4.3
        // The valueOf function is not generic; it throws a TypeError 
        // exception if its this value is not a String object.
        // Therefore, it cannot be transferred to other kinds of objects 
        // for use as a method.

        SF_UNUSED4(ti, vm, argc, argv);

        if (!_this.IsString())
        {
            return vm.ThrowTypeError(VM::Error(VM::eIllegalOperandTypeError, vm
                SF_DEBUG_ARG(_this.IsNullOrUndefined() ? "null" : vm.GetValueTraits(_this).GetName().ToCStr())
                SF_DEBUG_ARG("String")
                ));
        }

        result = _this;
//##protect##"InstanceTraits::AS3valueOf()"
    }
//##protect##"instance_traits$methods"
    void String::toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
        if (_this.IsObject() && _this.GetObject() == &vm.GetClassString().GetPrototype())
            // This method is called on a prototype object.
            result = vm.GetStringManager().GetBuiltin(AS3Builtin_empty_);
        else
            AS3toString(ti, vm, _this, result, argc, argv);
    }

    void String::valueOfProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
        if (_this.IsObject() && _this.GetObject() == &vm.GetClassString().GetPrototype())
            // This method is called on a prototype object.
            result = vm.GetStringManager().GetBuiltin(AS3Builtin_empty_);
        else
            AS3valueOf(ti, vm, _this, result, argc, argv);
    }

    static ASString CreateStringFromCStr(StringManager& sm, const char* start, const char* end = NULL)
    {
        int len = (end == 0) ? (int)strlen(start) : int(end - start);    
        if (len < 0)
            len = 0;    
        if (len > 0)
            return sm.CreateString(start, len);
        return sm.CreateEmptyString();
    }

    Pickable<Instances::fl::Array> String::StringSplit(VM& vm, const ASString& str, const char* delimiters, UInt32 limit)
    {
        Pickable<Instances::fl::Array> retVal = vm.MakeArray();

        const char*        search = delimiters;
        const char*        pstr = str.ToCStr();

        UInt32 c1, c2;

        if (search == 0)
        {
            retVal->PushBack(Value(str));
        }
        else if (*search == 0)
        {
            if (str.GetSize() == 0)
                retVal->PushBack(str);
            else
            {
                Scaleform::String tmpStr;

                while((c1 = UTF8Util::DecodeNextChar(&pstr)) != 0)
                {
                    tmpStr.Clear();
                    tmpStr.AppendChar(c1);
                    retVal->PushBack(Value(vm.GetStringManager().CreateString(tmpStr)));
                }
            }
        }
        else
        {
            UInt32 count = 0;
            const char* start = pstr;

            for(;;)
            {
                const char* s2   = search;
                const char* end  = pstr;
                const char* prev = pstr;
                const char* pnext = NULL;

                for(;;)
                {
                    prev = pstr;
                    c1 = UTF8Util::DecodeNextChar(&pstr);
                    c2 = UTF8Util::DecodeNextChar(&s2);
                    if (!pnext)
                        pnext = pstr;
                    if (c1 == 0 || c2 == 0) 
                    {
                        break;
                    }
                    if (c1 != c2)
                    {
                        pstr = pnext;
                        break;
                    }
                }
                if (c2 == 0)
                {
                    if (count >= limit) break;
                    retVal->PushBack(Value(CreateStringFromCStr(vm.GetStringManager(), start, end)));
                    pstr = start = prev;
                    ++count;
                }
                if (c1 == 0)
                {
                    if (count < limit)
                    {                
                        if (c2 == 0)
                            retVal->PushBack(Value(CreateStringFromCStr(vm.GetStringManager(), start, end)));
                        else
                            retVal->PushBack(Value(CreateStringFromCStr(vm.GetStringManager(), start)));
                    }
                    break;
                }
            }
        }

        return retVal;
    }

    // This function reproduces the behavior of 
    // function "substring" (not method!) except
    // for that it's zero-based instead of one-based
    //
    // The rules:
    // start:  zero-based, 
    //         if < 0 then start = 0
    //         if >= strlen then return empty
    //
    // length: if = 0 then return empty
    //         if < 0    then return tail
    //         if > tail then return tail
    ASString String::StringSubstring(StringManager& sm, const ASString& self, int start, int length)
    {
        if(length == 0)    
            return sm.CreateEmptyString();

        if (start < 0)
            start = 0;

        int utf8Len = self.GetLength();
        if (start >= utf8Len)    
            return sm.CreateEmptyString();

        if (length < 0 || start + length > utf8Len)
        {
            length = utf8Len - start;
        }

        return self.Substring(start, start + length);
    }

    SInt32 String::Compare(ASString& l, ASString& r)
    {
        SInt32 result = 0;

        if (l == r)
            return 0;

        const char* l_str = l.ToCStr();
        const char* r_str = r.ToCStr();

        // NOTE: this routine cannot use memcmp(), or wcscoll()
        // because ecma3/String/localeCompare_rt.as depends on the difference
        // in character values.
        UInt32 l_char = UTF8Util::DecodeNextChar(&l_str);
        UInt32 r_char = UTF8Util::DecodeNextChar(&r_str);

        while (!result && l_char && r_char)
        {
            result = r_char - l_char;

            if (!result)
            {
                l_char = UTF8Util::DecodeNextChar(&l_str);
                r_char = UTF8Util::DecodeNextChar(&r_str);
            }
        }

        if (!result && l_char != r_char)
        {
            // string being equal so far, but we met zero character in one of the strings.
            if (r_char == 0)
                result = -1;
            else
                result = 1;
        }

        return result;
    }
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits

namespace Classes { namespace fl
{
    String::String(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::String::String()"
//##protect##"class_::String::String()"
    }
    void String::AS3fromCharCode(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"class_::String::AS3fromCharCode()"
        StringBuffer sb;
        UInt32 r;
        for(unsigned i = 0; i < argc; ++i)
        {
            if (!argv[i].Convert2UInt32(r))
                return;
            unsigned ch = (UInt16)r;
            sb.AppendChar(ch);
        }
        result = GetStringManager().CreateString(sb.ToCStr(), sb.GetSize());
//##protect##"class_::String::AS3fromCharCode()"
    }
    void String::fromCharCode(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"class_::String::fromCharCode()"
        AS3fromCharCode(result, argc, argv);
//##protect##"class_::String::fromCharCode()"
    }
//##protect##"class_$methods"
    void String::Call(const Value& /*_this*/, Value& result, unsigned argc, const Value* const argv)
    {
        // The same logic as in Construct.
        Construct(result, argc, argv);
    }

    void String::Construct(Value& result, unsigned argc, const Value* argv, bool /*extCall*/)
    {
        ASString r = GetStringManager().CreateEmptyString();

        if (argc > 0)
        {
            if (!argv[0].Convert2String(r))
                // Exception.
                return;
        }

        result = r;
    }

    // Created manually.
    const ThunkInfo String::f[2] = {
        {&InstanceTraits::fl::String::toStringProto, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {&InstanceTraits::fl::String::valueOfProto, &AS3::fl::StringTI, "valueOf", NULL, Abc::NS_Public, CT_Method, 0, 0},
    };

    void String::InitPrototype(AS3::Object& obj) const
    {
        if (GetParentClass())
            GetParentClass()->InitPrototype(obj);

        // String methods are generic. No type checking is required.
        InitPrototypeFromVTable(obj);

        for (unsigned i = 0; i < NUMBEROF(f); ++i)
            AddDynamicFunc(obj, f[i]);

        AddConstructor(obj);
    }
//##protect##"class_$methods"

}} // namespace Classes

typedef ThunkFunc2<Classes::fl::String, Classes::fl::String::mid_AS3fromCharCode, Value, unsigned, const Value*> TFunc_Classes_String_AS3fromCharCode;
typedef ThunkFunc2<Classes::fl::String, Classes::fl::String::mid_fromCharCode, Value, unsigned, const Value*> TFunc_Classes_String_fromCharCode;

template <> const TFunc_Classes_String_AS3fromCharCode::TMethod TFunc_Classes_String_AS3fromCharCode::Method = &Classes::fl::String::AS3fromCharCode;
template <> const TFunc_Classes_String_fromCharCode::TMethod TFunc_Classes_String_fromCharCode::Method = &Classes::fl::String::fromCharCode;

namespace ClassTraits { namespace fl
{
    const ThunkInfo String::ti[String::ThunkInfoNum] = {
        {TFunc_Classes_String_AS3fromCharCode::Func, &AS3::fl::StringTI, "fromCharCode", NS_AS3, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
        {TFunc_Classes_String_fromCharCode::Func, &AS3::fl::StringTI, "fromCharCode", NULL, Abc::NS_Public, CT_Method, 0, SF_AS3_VARARGNUM},
    };
    String::String(VM& vm)
    : Traits(vm, AS3::fl::StringCI)
    {
//##protect##"ClassTraits::String::String()"
        SetTraitsType(Traits_String);
//##protect##"ClassTraits::String::String()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::String(vm, AS3::fl::StringCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl::String(*this));

    }

    Pickable<Traits> String::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) String(vm));
    }
//##protect##"ClassTraits$methods"
    bool String::Coerce(const Value& value, Value& result) const
    {
        if (!value.IsNullOrUndefined())
        {
            StringManager& sm = GetVM().GetStringManager();
            ASString r = sm.CreateEmptyString();
            if (!value.Convert2String(r))
                return false;
            result = r;
        }
        else
        {
            result.Assign((ASStringNode*)NULL);
        }

        return true;
    }
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl
{
    const TypeInfo StringTI = {
        TypeInfo::CompileTime | TypeInfo::Final,
        "String", "", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo StringCI = {
        &StringTI,
        ClassTraits::fl::String::MakeClassTraits,
        ClassTraits::fl::String::ThunkInfoNum,
        0,
        InstanceTraits::fl::String::ThunkInfoNum,
        0,
        ClassTraits::fl::String::ti,
        NULL,
        InstanceTraits::fl::String::ti,
        NULL,
    };
}; // namespace fl


}}} // namespace Scaleform { namespace GFx { namespace AS3

