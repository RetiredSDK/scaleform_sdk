//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_RegExp.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_RegExp.h"
#include "../AS3_VM.h"
#include "../AS3_Marshalling.h"
//##protect##"includes"
#ifdef SF_ENABLE_PCRE
#include "AS3_Obj_Array.h"
#endif
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::fl::RegExp, Instances::fl::RegExp::mid_sourceGet, ASString> TFunc_Instances_RegExp_sourceGet;
typedef ThunkFunc0<Instances::fl::RegExp, Instances::fl::RegExp::mid_globalGet, bool> TFunc_Instances_RegExp_globalGet;
typedef ThunkFunc0<Instances::fl::RegExp, Instances::fl::RegExp::mid_ignoreCaseGet, bool> TFunc_Instances_RegExp_ignoreCaseGet;
typedef ThunkFunc0<Instances::fl::RegExp, Instances::fl::RegExp::mid_multilineGet, bool> TFunc_Instances_RegExp_multilineGet;
typedef ThunkFunc0<Instances::fl::RegExp, Instances::fl::RegExp::mid_lastIndexGet, SInt32> TFunc_Instances_RegExp_lastIndexGet;
typedef ThunkFunc1<Instances::fl::RegExp, Instances::fl::RegExp::mid_lastIndexSet, const Value, SInt32> TFunc_Instances_RegExp_lastIndexSet;
typedef ThunkFunc0<Instances::fl::RegExp, Instances::fl::RegExp::mid_dotallGet, bool> TFunc_Instances_RegExp_dotallGet;
typedef ThunkFunc0<Instances::fl::RegExp, Instances::fl::RegExp::mid_extendedGet, bool> TFunc_Instances_RegExp_extendedGet;
typedef ThunkFunc1<Instances::fl::RegExp, Instances::fl::RegExp::mid_AS3exec, SPtr<Instances::fl::Object>, const ASString&> TFunc_Instances_RegExp_AS3exec;
typedef ThunkFunc1<Instances::fl::RegExp, Instances::fl::RegExp::mid_AS3test, bool, const ASString&> TFunc_Instances_RegExp_AS3test;

template <> const TFunc_Instances_RegExp_sourceGet::TMethod TFunc_Instances_RegExp_sourceGet::Method = &Instances::fl::RegExp::sourceGet;
template <> const TFunc_Instances_RegExp_globalGet::TMethod TFunc_Instances_RegExp_globalGet::Method = &Instances::fl::RegExp::globalGet;
template <> const TFunc_Instances_RegExp_ignoreCaseGet::TMethod TFunc_Instances_RegExp_ignoreCaseGet::Method = &Instances::fl::RegExp::ignoreCaseGet;
template <> const TFunc_Instances_RegExp_multilineGet::TMethod TFunc_Instances_RegExp_multilineGet::Method = &Instances::fl::RegExp::multilineGet;
template <> const TFunc_Instances_RegExp_lastIndexGet::TMethod TFunc_Instances_RegExp_lastIndexGet::Method = &Instances::fl::RegExp::lastIndexGet;
template <> const TFunc_Instances_RegExp_lastIndexSet::TMethod TFunc_Instances_RegExp_lastIndexSet::Method = &Instances::fl::RegExp::lastIndexSet;
template <> const TFunc_Instances_RegExp_dotallGet::TMethod TFunc_Instances_RegExp_dotallGet::Method = &Instances::fl::RegExp::dotallGet;
template <> const TFunc_Instances_RegExp_extendedGet::TMethod TFunc_Instances_RegExp_extendedGet::Method = &Instances::fl::RegExp::extendedGet;
template <> const TFunc_Instances_RegExp_AS3exec::TMethod TFunc_Instances_RegExp_AS3exec::Method = &Instances::fl::RegExp::AS3exec;
template <> const TFunc_Instances_RegExp_AS3test::TMethod TFunc_Instances_RegExp_AS3test::Method = &Instances::fl::RegExp::AS3test;

namespace Instances { namespace fl
{
    RegExp::RegExp(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
//##protect##"instance::RegExp::RegExp()$data"
#ifdef SF_ENABLE_PCRE
    , CompRegExp(NULL)
    , MatchOffset(-1)
    , MatchLength(0)
    , IsGlobal(false)
    , LastIndex(0)
    , OptionFlags(PCRE_UTF8)
    , HasNamedGroups(false)
#endif
//##protect##"instance::RegExp::RegExp()$data"
    {
//##protect##"instance::RegExp::RegExp()$code"
//##protect##"instance::RegExp::RegExp()$code"
    }

    void RegExp::sourceGet(ASString& result)
    {
//##protect##"instance::RegExp::sourceGet()"
#ifdef SF_ENABLE_PCRE
        result = GetStringManager().CreateString(Pattern);
#else
        SF_UNUSED1(result);
        NOT_IMPLEMENTED("RegExp::sourceGet()");
#endif
//##protect##"instance::RegExp::sourceGet()"
    }
    void RegExp::globalGet(bool& result)
    {
//##protect##"instance::RegExp::globalGet()"
#ifdef SF_ENABLE_PCRE
        result = IsGlobal;
#else
        result = AS3::DefaultValue<bool>(GetStringManager());
#endif
//##protect##"instance::RegExp::globalGet()"
    }
    void RegExp::ignoreCaseGet(bool& result)
    {
//##protect##"instance::RegExp::ignoreCaseGet()"
#ifdef SF_ENABLE_PCRE
        result = hasOption(PCRE_CASELESS);
#else
        result = AS3::DefaultValue<bool>(GetStringManager());
#endif
//##protect##"instance::RegExp::ignoreCaseGet()"
    }
    void RegExp::multilineGet(bool& result)
    {
//##protect##"instance::RegExp::multilineGet()"
#ifdef SF_ENABLE_PCRE
        result = hasOption(PCRE_MULTILINE);
#else
        result = AS3::DefaultValue<bool>(GetStringManager());
#endif
//##protect##"instance::RegExp::multilineGet()"
    }
    void RegExp::lastIndexGet(SInt32& result)
    {
//##protect##"instance::RegExp::lastIndexGet()"
#ifdef SF_ENABLE_PCRE
        result = LastIndex;
#else
        result = AS3::DefaultValue<int>(GetStringManager());
#endif
//##protect##"instance::RegExp::lastIndexGet()"
    }
    void RegExp::lastIndexSet(const Value& result, SInt32 i)
    {
//##protect##"instance::RegExp::lastIndexSet()"
#ifdef SF_ENABLE_PCRE
        SF_UNUSED(result);
        LastIndex = i;
#else
        SF_UNUSED2(result, i);
        NOT_IMPLEMENTED("RegExp::lastIndexSet()");
#endif
//##protect##"instance::RegExp::lastIndexSet()"
    }
    void RegExp::dotallGet(bool& result)
    {
//##protect##"instance::RegExp::dotallGet()"
#ifdef SF_ENABLE_PCRE
        result = hasOption(PCRE_DOTALL);
#else
        result = AS3::DefaultValue<bool>(GetStringManager());
#endif
//##protect##"instance::RegExp::dotallGet()"
    }
    void RegExp::extendedGet(bool& result)
    {
//##protect##"instance::RegExp::extendedGet()"
#ifdef SF_ENABLE_PCRE
        result = hasOption(PCRE_EXTENDED);
#else
        result = AS3::DefaultValue<bool>(GetStringManager());
#endif
//##protect##"instance::RegExp::extendedGet()"
    }
    void RegExp::AS3exec(SPtr<Instances::fl::Object>& result, const ASString& s)
    {
//##protect##"instance::RegExp::AS3exec()"
#ifdef SF_ENABLE_PCRE
        SInt32 oldLastIndex = LastIndex;
        SInt32 startIndex = (globalGet() ? LastIndex : 0);
        MatchOffset = MatchLength = 0;

        const char *subject = s.ToCStr();
        int subjectLen = s.GetLength();
        int outputVector[OUTPUT_VECTOR_SIZE];
        int matchCount = 0;

        // Match a pattern
        if (startIndex < 0 || startIndex > subjectLen || (
            matchCount = pcre_exec(CompRegExp, NULL, subject, subjectLen, startIndex, 0,
                                   outputVector, OUTPUT_VECTOR_SIZE)) < 0)
        {
            MatchOffset = matchCount;
            result = NULL;
            return;
        }
        MatchOffset = outputVector[0];
        MatchLength = outputVector[1] - outputVector[0];

        VM& vm = GetVM();
        StringManager& sm = vm.GetStringManager();

        // Output array
        SPtr<Instances::fl::Array> parr = vm.MakeArray();
        for (SInt32 i = 0; i < matchCount; i++)
        {
            if (outputVector[i*2] > -1)
            {
                char match[MATCH_BUFFER_SIZE];
                const char *ptr = subject + outputVector[2*i];
                int len = outputVector[i*2 + 1] - outputVector[i*2];
                SFstrncpy(match, sizeof(match), ptr, len);
                match[len] = 0;
                parr->PushBack(Value(sm.CreateString(match)));
            }
            else
                parr->PushBack(Value::GetUndefined());
        }
        parr->AddDynamicSlotValuePair(sm.CreateString("index"), Value(MatchOffset));
        parr->AddDynamicSlotValuePair(sm.CreateString("input"), Value(sm.CreateString(subject)));

        // Named groups if any
		if (HasNamedGroups)
		{
            int nameCount, nameEntrySize;
            char *nameTable;
            pcre_fullinfo(CompRegExp, NULL, PCRE_INFO_NAMECOUNT, &nameCount);
			pcre_fullinfo(CompRegExp, NULL, PCRE_INFO_NAMEENTRYSIZE, &nameEntrySize);
            pcre_fullinfo(CompRegExp, NULL, PCRE_INFO_NAMETABLE, &nameTable);

			for (int i = 0; i < nameCount; i++)
			{
                char name[MATCH_BUFFER_SIZE];
                SFstrncpy(name, sizeof(name), nameTable + 2, SFstrlen(nameTable + 2));
                name[SFstrlen(nameTable + 2)] = 0;

                char value[MATCH_BUFFER_SIZE];
                int nameIdx = (nameTable[0] << 8) + nameTable[1];
                const char *ptr = subject + outputVector[nameIdx*2];
                int len = outputVector[nameIdx*2 + 1] - outputVector[nameIdx*2];
                SFstrncpy(value, sizeof(value), ptr, len);
                value[len] = 0;

                parr->AddDynamicSlotValuePair(sm.CreateString(name), sm.CreateString(value));

				nameTable += nameEntrySize;
			}
		}

        if (globalGet())
			LastIndex = MatchOffset + MatchLength;
        if (LastIndex == oldLastIndex)
            LastIndex++;

        result = parr;
#else
        SF_UNUSED1(s);
        result = AS3::DefaultValue<Instances::fl::Object*>(GetStringManager());
#endif
//##protect##"instance::RegExp::AS3exec()"
    }
    void RegExp::AS3test(bool& result, const ASString& s)
    {
//##protect##"instance::RegExp::AS3test()"
#ifdef SF_ENABLE_PCRE
        SPtr<Instances::fl::Object> pobj = AS3exec(s);
        result = pobj ? true : false;
#else
        SF_UNUSED1(s);
        result = AS3::DefaultValue<bool>(GetStringManager());
#endif
//##protect##"instance::RegExp::AS3test()"
    }

//##protect##"instance$methods"
#ifdef SF_ENABLE_PCRE
    void RegExp::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc >= 1 && !argv[0].IsNullOrUndefined())
        {
            VM& vm = GetVM();
            StringManager& sm = vm.GetStringManager();

            ASString src = sm.CreateEmptyString();
            ASString opt = sm.CreateEmptyString();

            // RegExp class object
            if (argv[0].IsObject() && vm.IsOfType(argv[0], "RegExp", vm.GetCurrentAppDomain()))
            {
                RegExp* pobj = static_cast<Instances::fl::RegExp*>(argv[0].GetObject());
                src = pobj->sourceGet();
                opt = pobj->optionFlagsGet();

                // Error #1100: Cannot supply flags when constructing one RegExp from another
                if (argc >= 2 && !argv[1].IsNullOrUndefined())
                {
                    vm.ThrowTypeError(VM::Error(VM::eRegExpFlagsArgumentError,vm));
                    return;
                }
            }
            else {
                // re:String - The pattern of the regular expression
                if (!argv[0].Convert2String(src))
                    return;
                // flags:String - The modifiers of the regular expression
                if (argc >= 2 && !argv[1].IsNullOrUndefined())
                {
                    if (!argv[1].Convert2String(opt))
                        return;
                }
            }
            const char* pattern = src.ToCStr();
            const char* flags = opt.ToCStr();
            Pattern = pattern;

            // Check pattern for options if any
            int slashNum = 0;
            while(*pattern)
            {
                if (pattern[0] == '(' && pattern[1] == '?' &&
                    pattern[2] == 'P' && pattern[3] == '<')
                {
                    HasNamedGroups = true;
                }
                else if (flags == NULL && pattern[0] == '/' && 
                        (pattern == src.ToCStr() || pattern[-1] != '\\') && slashNum++ > 0)
                {
                    flags = pattern;
                }
                pattern++;
            }

            // Option flags
            if (flags)
            {		
                for(; *flags; flags++)
                {
                    switch(*flags)
                    {
                    case 'g': IsGlobal = true;
                        break;
                    case 'i': OptionFlags |= PCRE_CASELESS;  break;
                    case 'm': OptionFlags |= PCRE_MULTILINE; break;
                    case 's': OptionFlags |= PCRE_DOTALL;    break;
                    case 'x': OptionFlags |= PCRE_EXTENDED;  break;
                    }
                }
            }

            // Compile source pattern
            const char *error;
            int errorOffset;
            CompRegExp = pcre_compile(Pattern.ToCStr(), OptionFlags, &error, &errorOffset, NULL);
            // If CompRegExp is NULL - compilation failed at errorOffset
        }
    }

    RegExp::~RegExp()
    {
        pcre_free(CompRegExp);
        CompRegExp = NULL;
    }

    bool RegExp::hasOption(int mask)
    {
        return (OptionFlags & mask) != 0;
    }

    ASString RegExp::optionFlagsGet()
    {
        StringManager& sm = GetVM().GetStringManager();

        ASString flags = sm.CreateEmptyString();
        flags += globalGet()     ? "g" : "";
        flags += ignoreCaseGet() ? "i" : "";
        flags += multilineGet()  ? "m" : "";
        flags += dotallGet()     ? "s" : "";
        flags += extendedGet()   ? "x" : "";
        return flags;
    }

    ASString RegExp::ToString()
    {
        StringManager& sm = GetVM().GetStringManager();
        return sm.CreateConstString("/") + sourceGet() +
               sm.CreateConstString("/") + optionFlagsGet();
    }
#endif

    void RegExp::toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
#ifdef SF_ENABLE_PCRE
        SF_UNUSED4(ti, vm, argc, argv);
        Instances::fl::RegExp* pobj = static_cast<Instances::fl::RegExp*>(_this.GetObject());
        result = pobj->ToString();
#else
        SF_UNUSED4(ti, _this, argc, argv);
        result = vm.GetStringManager().CreateConstString("/(?:)/");
#endif
    }
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl
{
    const ThunkInfo RegExp::ti[RegExp::ThunkInfoNum] = {
        {TFunc_Instances_RegExp_sourceGet::Func, &AS3::fl::StringTI, "source", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_globalGet::Func, &AS3::fl::BooleanTI, "global", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_ignoreCaseGet::Func, &AS3::fl::BooleanTI, "ignoreCase", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_multilineGet::Func, &AS3::fl::BooleanTI, "multiline", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_lastIndexGet::Func, &AS3::fl::int_TI, "lastIndex", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_lastIndexSet::Func, NULL, "lastIndex", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_RegExp_dotallGet::Func, &AS3::fl::BooleanTI, "dotall", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_extendedGet::Func, &AS3::fl::BooleanTI, "extended", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_AS3exec::Func, &AS3::fl::ObjectTI, "exec", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_RegExp_AS3test::Func, &AS3::fl::BooleanTI, "test", NS_AS3, Abc::NS_Public, CT_Method, 1, 1},
    };

    RegExp::RegExp(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::RegExp::RegExp()"
//##protect##"InstanceTraits::RegExp::RegExp()"
        SetMemSize(sizeof(Instances::fl::RegExp));

    }

    void RegExp::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<RegExp&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits

namespace Classes { namespace fl
{
    RegExp::RegExp(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::RegExp::RegExp()"
//##protect##"class_::RegExp::RegExp()"
    }
//##protect##"class_$methods"
    void RegExp::Call(const Value& _this, Value& result, unsigned argc, const Value* const argv)
    {
        SF_UNUSED(_this);

        // The same logic as in Construct.
        Construct(result, argc, argv);

#ifdef SF_ENABLE_PCRE
        Instances::fl::RegExp* pobj = static_cast<Instances::fl::RegExp*>(result.GetObject());
        result = pobj->ToString();                 
#endif
    }

    Pickable<AS3::Object> RegExp::MakePrototype() const
    {
        InstanceTraits::fl::RegExp& itr = static_cast<InstanceTraits::fl::RegExp&>(GetClassTraits().GetInstanceTraits());
        return itr.MakeInstance(itr);
    }

    void RegExp::InitPrototype(AS3::Object& obj) const
    {
        if (GetParentClass())
            GetParentClass()->InitPrototype(obj);

        InitPrototypeFromVTableCheckType(obj);

        // Created manually.
        static ThunkInfo f[] = {
            {&Instances::fl::RegExp::toStringProto, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
        };
        for (unsigned i = 0; i < NUMBEROF(f); ++i)
            AddDynamicFunc(obj, f[i]);

    }
//##protect##"class_$methods"

}} // namespace Classes


namespace ClassTraits { namespace fl
{
    RegExp::RegExp(VM& vm)
    : Traits(vm, AS3::fl::RegExpCI)
    {
//##protect##"ClassTraits::RegExp::RegExp()"
//##protect##"ClassTraits::RegExp::RegExp()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl::RegExp(vm, AS3::fl::RegExpCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl::RegExp(*this));

    }

    Pickable<Traits> RegExp::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) RegExp(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl
{
    const TypeInfo RegExpTI = {
        TypeInfo::CompileTime | TypeInfo::DynamicObject,
        "RegExp", "", &fl::ObjectTI,
        TypeInfo::None
    };

    const ClassInfo RegExpCI = {
        &RegExpTI,
        ClassTraits::fl::RegExp::MakeClassTraits,
        0,
        0,
        InstanceTraits::fl::RegExp::ThunkInfoNum,
        0,
        NULL,
        NULL,
        InstanceTraits::fl::RegExp::ti,
        NULL,
    };
}; // namespace fl


}}} // namespace Scaleform { namespace GFx { namespace AS3

