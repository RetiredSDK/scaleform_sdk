/**************************************************************************

Filename    :   AS3_Abc.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "AS3_Abc.h"

namespace Scaleform { namespace GFx { namespace AS3 { 

    const TypeInfo* TypeInfo::None[] = {NULL};

}}} // namespace Scaleform { namespace GFx { namespace AS3 { 

namespace Scaleform { namespace GFx { namespace AS3 { namespace Abc 
{

///////////////////////////////////////////////////////////////////////////
template <>
int Read16(const UInt8* data, TCodeOffset& cp)
{
    // Let's help CPU parallelize code below. Unroll loop and no data dependencies.
    const int b1 = data[cp + 0];
    const int b2 = data[cp + 1];
    cp += 2;

    return (b2 << 8) | b1;
}

template <>
int ReadS24(const UInt8* data, TCodeOffset& cp)
{
    // Let's help CPU parallelize code below. Unroll loop and no data dependencies.
    const int b1 = data[cp + 0];
    const int b2 = data[cp + 1];
    const int b3 = data[cp + 2];
    cp += 3;

    int r = b3 << 16 | b2 << 8 | b1;
    
    if(b3 & 0x80) 
        r = -1 - ( r ^ 0xffffff );
    
    return r;
}

template <>
int ReadU30(const UInt8* data, TCodeOffset& cp)
{
    UInt32 shift = 0;
    UInt32 s = 0;
    int nr = 0;

    while (true)
    {
        int b = Read8(data, cp);
        ++nr;
        s |= (b & 127) << shift;
        shift += 7;

        if (!(b & 128) || shift >= 32)
            break;
    }

    return s;
}

template <>
Double ReadDouble(const UInt8* data, TCodeOffset& cp)
{
    // The bytes in the abc are little endian.
    union {
        Double v;
#if (SF_BYTE_ORDER == SF_LITTLE_ENDIAN)
        struct { UInt32 lo, hi; } w;
#else
        struct { UInt32 hi, lo; } w;
#endif
    };

    // The words in memory can be little endian or big endian.
    // Let's help CPU parallelize code below. Unroll loop and no data dependencies.
    w.lo = data[cp + 0] | data[cp + 1] << 8 | data[cp + 2] << 16 | data[cp + 3] << 24;
    w.hi = data[cp + 4] | data[cp + 5] << 8 | data[cp + 6] << 16 | data[cp + 7] << 24;
    cp += 8;

    return v;
}

template <>
String ReadString(const UInt8* data, TCodeOffset& cp, UPInt size)
{
//     StringBuffer b(size);

    // !!! No checking.
    String b((const char*)(data + cp), size);
    cp += size;
    return b;
}
template <>
StringDataPtr ReadStringPtr(const UInt8* data, TCodeOffset& cp, UPInt size)
{
    // !!! No checking.
    StringDataPtr b((const char*)(data + cp), size);
    cp += size;
    return b;
}

///////////////////////////////////////////////////////////////////////////
template <>
int Read16(const UInt8*& cp)
{
    // Let's help CPU parallelize code below. Unroll loop and no data dependencies.
    const int b1 = *cp;
    const int b2 = *(cp + 1);
    cp += 2;

    return (b2 << 8) | b1;
}

template <>
int ReadS24(const UInt8*& cp)
{
    // Let's help CPU parallelize code below. Unroll loop and no data dependencies.
    const int b1 = *cp;
    const int b2 = *(cp + 1);
    const int b3 = *(cp + 2);
    cp += 3;

    int r = b3 << 16 | b2 << 8 | b1;

    if(b3 & 0x80) 
        r = -1 - ( r ^ 0xffffff );

    return r;
}

template <>
int ReadU30(const UInt8*& cp)
{
    UInt32 shift = 0;
    UInt32 s = 0;
    int nr = 0;

    while (true)
    {
        int b = Read8(cp);
        ++nr;
        s |= (b & 127) << shift;
        shift += 7;

        if (!(b & 128) || shift >= 32)
            break;
    }

    return s;
}

template <>
Double ReadDouble(const UInt8*& cp)
{
    // The bytes in the abc are little endian.
    union {
        Double v;
#if (SF_BYTE_ORDER == SF_LITTLE_ENDIAN)
        struct { UInt32 lo, hi; } w;
#else
        struct { UInt32 hi, lo; } w;
#endif
    };

    // The words in memory can be little endian or big endian.
    // Let's help CPU parallelize code below. Unroll loop and no data dependencies.
    w.lo =       *cp | *(cp + 1) << 8 | *(cp + 2) << 16 | *(cp + 3) << 24;
    w.hi = *(cp + 4) | *(cp + 5) << 8 | *(cp + 6) << 16 | *(cp + 7) << 24;
    cp += 8;

    return v;
}

template <>
String ReadString(const UInt8*& cp, UPInt size)
{
    //     StringBuffer b(size);

    // !!! No checking.
    String b((const char*)cp, size);
    cp += size;
    return b;
}
template <>
StringDataPtr ReadStringPtr(const UInt8*& cp, UPInt size)
{
    // !!! No checking.
    StringDataPtr b((const char*)cp, size);
    cp += size;
    return b;
}

///////////////////////////////////////////////////////////////////////////
bool IsValidValueKind(UInt8 vk)
{
    switch(vk)
    {
    case CONSTANT_Int:
    case CONSTANT_UInt:
    case CONSTANT_Double:
    case CONSTANT_Utf8:
    case CONSTANT_True:
    case CONSTANT_False:
    case CONSTANT_Null:
    case CONSTANT_Undefined:
    case CONSTANT_Namespace:
    case CONSTANT_PackageNamespace:
    case CONSTANT_PackageInternalNs:
    case CONSTANT_ProtectedNamespace:
    case CONSTANT_ExplicitNamespace:
    case CONSTANT_StaticProtectedNs:
    case CONSTANT_PrivateNs:
        return true;
    default:
        break;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
// So far we need operandCount only.
const Code::OpCodeInfo Code::opcode_info[0x100] =
{
    // operandCount  pop   pop_args
    //      canThrow    push pop_mn
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0x00") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0x01") },
    {    0,  false,   0, 0, 0, 0    SF_DEBUG_ARG("nop") },
    {    0,  true,    1, 0, 0, 0    SF_DEBUG_ARG("throw") },
    {    1,  true,    1, 1, 0, 1    SF_DEBUG_ARG("getsuper") },
    {    1,  true,    2, 0, 0, 1    SF_DEBUG_ARG("setsuper") },
    {    1,  true,    0, 0, 0, 0    SF_DEBUG_ARG("dxns") },
    {    0,  true,    1, 0, 0, 0    SF_DEBUG_ARG("dxnslate") },
    {    1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("kill") },
    {    0,  false,   0, 0, 0, 0    SF_DEBUG_ARG("label") },
    
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x0A") },
    {    1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("inclocal_ti") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x0B") },
    {    1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("declocal_ti") }, // My own ...
    
    {    1,  true,    2, 0, 0, 0    SF_DEBUG_ARG("ifnlt") },
    {    1,  true,    2, 0, 0, 0    SF_DEBUG_ARG("ifnle") },
    {    1,  true,    2, 0, 0, 0    SF_DEBUG_ARG("ifngt") },
    {    1,  true,    2, 0, 0, 0    SF_DEBUG_ARG("ifnge") },
    {    1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("jump") },
    {    1,  false,   1, 0, 0, 0    SF_DEBUG_ARG("iftrue") }, //
    {    1,  false,   1, 0, 0, 0    SF_DEBUG_ARG("iffalse") }, //
    {    1,  true,    2, 0, 0, 0    SF_DEBUG_ARG("ifeq") },
    {    1,  true,    2, 0, 0, 0    SF_DEBUG_ARG("ifne") },
    {    1,  true,    2, 0, 0, 0    SF_DEBUG_ARG("iflt") },
    {    1,  true,    2, 0, 0, 0    SF_DEBUG_ARG("ifle") },
    {    1,  true,    2, 0, 0, 0    SF_DEBUG_ARG("ifgt") },
    {    1,  true,    2, 0, 0, 0    SF_DEBUG_ARG("ifge") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifstricteq") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifstrictne") },
    {    2,  false,   1, 0, 0, 0    SF_DEBUG_ARG("lookupswitch") }, // Number of operands is variable.
    {    0,  false,   1, 0, 0, 0    SF_DEBUG_ARG("pushwith") }, // Push on a scope stack ...
    {    0,  false,   0, 0, 0, 0    SF_DEBUG_ARG("popscope") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("nextname") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("hasnext") }, // index ...
    {    0,  false,   0, 1, 0, 0    SF_DEBUG_ARG("pushnull") },
    {    0,  false,   0, 1, 0, 0    SF_DEBUG_ARG("pushundefined") },

    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x22") },
    {    0,  false,   1, 1, 0, 0    SF_DEBUG_ARG("not_tb") }, // My own ...

    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("nextvalue") },
    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("pushbyte") },
    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("pushshort") },
    {    0,  false,   0, 1, 0, 0    SF_DEBUG_ARG("pushtrue") },
    {    0,  false,   0, 1, 0, 0    SF_DEBUG_ARG("pushfalse") },
    {    0,  false,   0, 1, 0, 0    SF_DEBUG_ARG("pushnan") },
    {    0,  false,   1, 0, 0, 0    SF_DEBUG_ARG("pop") },
    {    0,  false,   1, 2, 0, 0    SF_DEBUG_ARG("dup") },
    {    0,  false,   2, 2, 0, 0    SF_DEBUG_ARG("swap") },
    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("pushstring") },
    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("pushint") },
    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("pushuint") },
    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("pushdouble") },
    {    0,  false,   1, 0, 0, 0    SF_DEBUG_ARG("pushscope") }, // Push on a scope stack ...
    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("pushnamespace") },
    {    2,  true,    0, 1, 0, 0    SF_DEBUG_ARG("hasnext2") },
    
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x33") },
    {    1,  false,   1, 0, 0, 0    SF_DEBUG_ARG("iftrue_tb") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x34") },
    {    1,  false,   1, 0, 0, 0    SF_DEBUG_ARG("iffalse_tb") }, // My own ...
    
    //{   0,   true,    0    SF_DEBUG_ARG("li8") },
    {    0,  false,   1, 1, 0, 0    SF_DEBUG_ARG("increment_tu") }, // My own ...
    //{   0,   true,    0    SF_DEBUG_ARG("li16") },
    {    0,  false,   1, 1, 0, 0    SF_DEBUG_ARG("decrement_tu") }, // My own ...
    //{   0,   true,    0    SF_DEBUG_ARG("li32") },
    {    1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("inclocal_tu") }, // My own ...
    //{   0,   true,    0    SF_DEBUG_ARG("lf32") },
    {    1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("declocal_tu") }, // My own ...
    {   0,   true,    1, 1, 0, 0    SF_DEBUG_ARG("lf64") },
    {   0,   true,    2, 0, 0, 0    SF_DEBUG_ARG("si8") },
    {   0,   true,    2, 0, 0, 0    SF_DEBUG_ARG("si16") },
    {   0,   true,    2, 0, 0, 0    SF_DEBUG_ARG("si32") },
    {   0,   true,    2, 0, 0, 0    SF_DEBUG_ARG("sf32") },
    {   0,   true,    2, 0, 0, 0    SF_DEBUG_ARG("sf64") },

    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x3F") },
    {    0,  false,   1, 1, 0, 0    SF_DEBUG_ARG("negate_ti") }, // My own ...

    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("newfunction") }, // Tamarin throws exceptions in this opcode.
    {    1,  true,    2, 1, 1, 0    SF_DEBUG_ARG("call") },
    {    1,  true,    1, 1, 1, 0    SF_DEBUG_ARG("construct") },
    {    2,  true,    1, 1, 1, 0    SF_DEBUG_ARG("callmethod") },
    {    2,  true,    1, 1, 1, 0    SF_DEBUG_ARG("callstatic") },
    {    2,  true,    1, 1, 1, 1    SF_DEBUG_ARG("callsuper") },
    {    2,  true,    1, 1, 1, 1    SF_DEBUG_ARG("callproperty") },
    {    0,  false,   0, 0, 0, 0    SF_DEBUG_ARG("returnvoid") },
    {    0,  false,   1, 0, 0, 0    SF_DEBUG_ARG("returnvalue") },
    {    1,  true,    1, 0, 1, 0    SF_DEBUG_ARG("constructsuper") },
    {    2,  true,    1, 1, 1, 1    SF_DEBUG_ARG("constructprop") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0x4B") },
    {    2,  true,    1, 1, 1, 1    SF_DEBUG_ARG("callproplex") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0x4D") },
    {    2,  true,    1, 0, 1, 1    SF_DEBUG_ARG("callsupervoid") },
    {    2,  true,    1, 0, 1, 1    SF_DEBUG_ARG("callpropvoid") },
    {    0,  false,   1, 1, 0, 0    SF_DEBUG_ARG("sxi1") },
    {    0,  false,   1, 1, 0, 0    SF_DEBUG_ARG("sxi8") },
    {    0,  false,   1, 1, 0, 0    SF_DEBUG_ARG("sxi16") },
    {    1,  true,    1, 1, 1, 0    SF_DEBUG_ARG("applytype") },

    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x54") },
    {    0,  false,   1, 1, 0, 0    SF_DEBUG_ARG("negate_td") }, // My own ...

    {    1,  false,   0, 1, 1, 0    SF_DEBUG_ARG("newobject") }, // Tamarin throws exceptions in this opcode.
    {    1,  false,   0, 1, 1, 0    SF_DEBUG_ARG("newarray") }, // Tamarin throws exceptions in this opcode.
    {    0,  false,   0, 1, 0, 0    SF_DEBUG_ARG("newactivation") }, // Tamarin throws exceptions in this opcode.
    {    1,  true,    1, 1, 0, 0    SF_DEBUG_ARG("newclass") },
    {    1,  true,    1, 1, 0, 1    SF_DEBUG_ARG("getdescendants") },
    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("newcatch") }, // Tamarin throws exceptions in this opcode.
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0x5B") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0x5C") },
    {    1,  true,    0, 1, 0, 1    SF_DEBUG_ARG("findpropstrict") },
    {    1,  true,    0, 1, 0, 1    SF_DEBUG_ARG("findproperty") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0x5F") },
    {    1,  true,    0, 1, 0, 0    SF_DEBUG_ARG("getlex") },
    {    1,  true,    2, 0, 0, 1    SF_DEBUG_ARG("setproperty") },
    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("getlocal") },
    {    1,  false,   1, 0, 0, 0    SF_DEBUG_ARG("setlocal") },
    {    0,  false,   0, 1, 0, 0    SF_DEBUG_ARG("getglobalscope") },
    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("getscopeobject") },
    {    1,  true,    1, 1, 0, 1    SF_DEBUG_ARG("getproperty") }, // undefined if property not found ...
    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("getouterscope") }, // My own
    {    1,  true,    2, 0, 0, 1    SF_DEBUG_ARG("initproperty") },

    {    0,  false,   1, 2, 0, 0    SF_DEBUG_ARG("dup_nrc") }, // My own ... (Not ref-counted version of dup)
    {    1,  true,    1, 1, 0, 1    SF_DEBUG_ARG("deleteproperty") },
    {    0,  false,   1, 0, 0, 0    SF_DEBUG_ARG("pop_nrc") }, // My own ... (Not ref-counted version of pop)

    {    1,  true,    1, 1, 0, 0    SF_DEBUG_ARG("getslot") },
    {    1,  true,    2, 0, 0, 0    SF_DEBUG_ARG("setslot") },
    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("getglobalslot") },
    {    1,  false,   1, 0, 0, 0    SF_DEBUG_ARG("setglobalslot") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("convert_s") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("esc_xelem") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("esc_xattr") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("convert_i") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("convert_u") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("convert_d") },
    {    0,  false,   1, 1, 0, 0    SF_DEBUG_ARG("convert_b") }, // Tamarin throws exceptions in this opcode.
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("convert_o") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("checkfilter") },

    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x79") },
    {    0,  false,   2, 1, 0, 0    SF_DEBUG_ARG("add_ti") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x7A") },
    {    0,  false,   2, 1, 0, 0    SF_DEBUG_ARG("subtract_ti") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x7B") },
    {    0,  false,   2, 1, 0, 0    SF_DEBUG_ARG("multiply_ti") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x7C") },
    {    0,  false,   2, 1, 0, 0    SF_DEBUG_ARG("add_td") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x7D") },
    {    0,  false,   2, 1, 0, 0    SF_DEBUG_ARG("subtract_td") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x7E") },
    {    0,  false,   2, 1, 0, 0    SF_DEBUG_ARG("multiply_td") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x7F") },
    {    0,  false,   2, 1, 0, 0    SF_DEBUG_ARG("divide_td") }, // My own ...

    {    1,  true,    1, 1, 0, 0    SF_DEBUG_ARG("coerce") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0x81") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("coerce_a") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0x83") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0x84") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("coerce_s") },   // convert_d is the same operation as coerce_d
    {    1,  true,    1, 1, 0, 0    SF_DEBUG_ARG("astype") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("astypelate") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0x88") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0x89") },
    
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x8A") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifnlt_ti") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x8B") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifnle_ti") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x8C") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifngt_ti") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x8D") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifnge_ti") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x8E") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifeq_ti") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x8F") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifge_ti") }, // My own ...
                       
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("negate") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("increment") },
    {    1,  true,    0, 0, 0, 0    SF_DEBUG_ARG("inclocal") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("decrement") },
    {    1,  true,    0, 0, 0, 0    SF_DEBUG_ARG("declocal") },
    {    0,  false,   1, 1, 0, 0    SF_DEBUG_ARG("typeof") },
    {    0,  false,   1, 1, 0, 0    SF_DEBUG_ARG("not") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("bitnot") },
    
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x98") },
    {    0,  false,   1, 1, 0, 0    SF_DEBUG_ARG("increment_ti") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x99") },
    {    0,  false,   1, 1, 0, 0    SF_DEBUG_ARG("decrement_ti") }, // My own ...
    
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0x9A") },
    {   -1,  true,    2, 1, 0, 0    SF_DEBUG_ARG("add_d") },
    
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x9C") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifgt_ti") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x9D") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifle_ti") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x9E") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("iflt_ti") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0x9F") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifne_ti") }, // My own ...
    
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("add") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("subtract") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("multiply") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("divide") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("modulo") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("lshift") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("rshift") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("urshift") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("bitand") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("bitor") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("bitxor") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("equals") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("strictequals") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("lessthan") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("lessequals") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("greaterthan") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("greaterequals") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("instanceof") },
    {    1,  true,    1, 1, 0, 0    SF_DEBUG_ARG("istype") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("istypelate") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("in") },

    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xB5") },
    {    1,  false,   0, 1, 0, 0    SF_DEBUG_ARG("getabsobject") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xB6") },
    {    1,  false,   1, 1, 0, 0    SF_DEBUG_ARG("getabsslot") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xB7") },
    {    1,  false,    2, 0, 0, 0    SF_DEBUG_ARG("setabsslot") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xB8") },
    {    1,  false,    2, 0, 0, 0    SF_DEBUG_ARG("initabsslot") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xB9") },
    {    1,  false,    1, 1, 1, 0    SF_DEBUG_ARG("callsupermethod") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xBA") },
    {    2,  false,    1, 1, 1, 0    SF_DEBUG_ARG("callgetter") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xBB") },
    {    2,  false,    1, 1, 1, 0    SF_DEBUG_ARG("callsupergetter") }, // My own ...

    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xBC") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifgt_td") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xBD") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifle_td") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xBE") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("iflt_td") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xBF") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifne_td") }, // My own ...
                       
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("increment_i") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("decrement_i") },
    {    1,  true,    0, 0, 0, 0    SF_DEBUG_ARG("inclocal_i") },
    {    1,  true,    0, 0, 0, 0    SF_DEBUG_ARG("declocal_i") },
    {    0,  true,    1, 1, 0, 0    SF_DEBUG_ARG("negate_i") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("add_i") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("subtract_i") },
    {    0,  true,    2, 1, 0, 0    SF_DEBUG_ARG("multiply_i") },
                       
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xC8") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifnlt_td") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xC9") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifnle_td") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xCA") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifngt_td") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xCB") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifnge_td") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xCC") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifeq_td") }, // My own ...
    //{   -1,  false,   0    SF_DEBUG_ARG("OP_0xCD") },
    {    1,  false,   2, 0, 0, 0    SF_DEBUG_ARG("ifge_td") }, // My own ...
    {    1,  false,   1, 1, 1, 0    SF_DEBUG_ARG("callobject") }, // My own ...

    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xCF") },
                       
    {    0,  false,   0, 1, 0, 0    SF_DEBUG_ARG("getlocal_0") },
    {    0,  false,   0, 1, 0, 0    SF_DEBUG_ARG("getlocal_1") },
    {    0,  false,   0, 1, 0, 0    SF_DEBUG_ARG("getlocal_2") },
    {    0,  false,   0, 1, 0, 0    SF_DEBUG_ARG("getlocal_3") },
    {    0,  false,   1, 0, 0, 0    SF_DEBUG_ARG("setlocal_0") },
    {    0,  false,   1, 0, 0, 0    SF_DEBUG_ARG("setlocal_1") },
    {    0,  false,   1, 0, 0, 0    SF_DEBUG_ARG("setlocal_2") },
    {    0,  false,   1, 0, 0, 0    SF_DEBUG_ARG("setlocal_3") },
                       
#ifdef ENABLE_STRICT_SETSLOT
    {    1,  false,  -2    SF_DEBUG_ARG("setslot_str") }, // My own ...
    {    1,  false,  -2    SF_DEBUG_ARG("setslot_num") }, // My own ...
    {    1,  false,  -2    SF_DEBUG_ARG("setslot_uint") }, // My own ...
    {    1,  false,  -2    SF_DEBUG_ARG("setslot_sint") }, // My own ...
    {    1,  false,  -2    SF_DEBUG_ARG("setslot_bool") }, // My own ...
    {    1,  false,  -2    SF_DEBUG_ARG("setslot_value") }, // My own ...
    {    1,  false,  -2    SF_DEBUG_ARG("setslot_obj_as") }, // My own ...
    {    1,  false,  -2    SF_DEBUG_ARG("setslot_obj_cpp") }, // My own ...
#else
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xD8") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xD9") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xDA") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xDB") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xDC") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xDD") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xDE") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xDF") },
#endif

    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xE0") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xE1") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xE2") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xE3") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xE4") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xE5") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xE6") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xE7") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xE8") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xE9") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xEA") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xEB") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xEC") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xED") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xEE") },
                       
    {    4,  true,    0, 0, 0, 0    SF_DEBUG_ARG("debug") }, // Tamarin throws exceptions in this opcode.
    {    1,  true,    0, 0, 0, 0    SF_DEBUG_ARG("debugline") }, // Tamarin throws exceptions in this opcode.
    {    1,  true,    0, 0, 0, 0    SF_DEBUG_ARG("debugfile") }, // Tamarin throws exceptions in this opcode.
    {    1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xF2") }, // op_0xF2 is used internally by the Tamarin VM.
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xF3") },
                       
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xF4") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xF5") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xF6") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xF7") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xF8") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xF9") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xFA") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xFB") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xFC") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xFD") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xFE") },
    {   -1,  false,   0, 0, 0, 0    SF_DEBUG_ARG("OP_0xFF") },
    // END
};

///////////////////////////////////////////////////////////////////////////
MethodBodyInfo::MethodBodyInfo()
: method_info_ind(-1)
, max_stack(-1)
, local_reg_count(-1)
, init_scope_depth(-1)
, max_scope_depth(-1)
{
}

MethodBodyInfo::~MethodBodyInfo()
{
}

///////////////////////////////////////////////////////////////////////////
MethodBodyInfo::ExceptionInfo::ExceptionInfo()
: from(0)
, to(0)
, target(0)
, exc_type_ind(0)
, var_name_ind(0)
{
}

MethodBodyInfo::ExceptionInfo::ExceptionInfo(UInd _from, UInd _to, UInd _target, UInd _exc_type_ind, UInt32 _var_name_ind)
: from(_from)
, to(_to)
, target(_target)
, exc_type_ind(_exc_type_ind)
, var_name_ind(_var_name_ind)
{
}

///////////////////////////////////////////////////////////////////////////
bool MethodBodyInfo::Exception::FindExceptionInfo(Abc::TCodeOffset offset, UPInt& handler_num) const
{
    const UPInt size = info.GetSize();
    for(; handler_num < size; ++handler_num)
    {
        const ExceptionInfo& ei = Get(handler_num);

        if (offset >= static_cast<TCodeOffset>(ei.GetFrom()) && offset <= static_cast<TCodeOffset>(ei.GetTo()))
            return true;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
void File::Clear()
{
    // DataSize = 0; // We do not clear DataSize on purpose.
    MinorVersion = 0;
    MajorVersion = 0;
    Const_Pool.Clear();
    Methods.Clear();
    Metadata.Clear();
    Traits.Clear();
    AS3_Classes.Clear();
    Scripts.Clear();
    MethodBodies.Clear();
}

File::~File()
{
}

///////////////////////////////////////////////////////////////////////////
MethodBodyTable::~MethodBodyTable()
{
    const UPInt size = Info.GetSize();
    for (UPInt i = 0; i < size; ++i)
        delete Info[i];
}

}}}} // namespace Scaleform { namespace GFx { namespace AS3 { namespace Abc {


