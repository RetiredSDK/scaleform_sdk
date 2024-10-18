//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_ByteArray.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Utils_ByteArray.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#ifdef SF_ENABLE_ZLIB
#include <zlib.h>
#endif
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
#ifdef SF_ENABLE_ZLIB
class ZStream
{
public:
    ZStream();
    ~ZStream();

public:
    void SetInput(const UInt8* pbCompressed, UInt32 nb)
    {
	    Stream.next_in = (Bytef*)pbCompressed; 
        Stream.avail_in = nb; 
    }

    int GetAvailInput() const
    {
	    return Stream.avail_in; 
    }

    bool Decompress()
    {
        int error = inflate(&Stream, Z_NO_FLUSH);
        SF_ASSERT(error == Z_OK || error == Z_STREAM_END);
        return (error == Z_OK); 
    }
    int DecompressWithStatus()
    {
	    return inflate(&Stream, Z_NO_FLUSH); 
    }

    void SetOutput(UInt8* pbDecompressed, UInt32 nb)
    {
	    Stream.next_out = (Bytef*) pbDecompressed; 
        Stream.avail_out = nb; 
    }

    UInt8* GetOutput() const
    {
        return Stream.next_out; 
    }

    int GetAvailOutput() const
    {
	    return Stream.avail_out; 
    }

    int GetTotalOutput() const
    {
	    return Stream.total_out; 
    }

private:
    z_stream Stream;
};

ZStream::ZStream()
{
    memset(&Stream, 0, sizeof(Stream));
    int error = inflateInit(&Stream);
    SF_ASSERT(error == Z_OK); 
    SF_UNUSED1(error);
}
ZStream::~ZStream()
{
    int error = inflateEnd(&Stream);
    SF_ASSERT(error == Z_OK); 
    SF_UNUSED1(error);
}
#endif // SF_ENABLE_ZLIB
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_bytesAvailableGet, UInt32> TFunc_Instances_ByteArray_bytesAvailableGet;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_endianGet, ASString> TFunc_Instances_ByteArray_endianGet;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_endianSet, const Value, const ASString&> TFunc_Instances_ByteArray_endianSet;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_lengthGet, UInt32> TFunc_Instances_ByteArray_lengthGet;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_lengthSet, const Value, UInt32> TFunc_Instances_ByteArray_lengthSet;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_objectEncodingGet, UInt32> TFunc_Instances_ByteArray_objectEncodingGet;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_objectEncodingSet, const Value, UInt32> TFunc_Instances_ByteArray_objectEncodingSet;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_positionGet, UInt32> TFunc_Instances_ByteArray_positionGet;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_positionSet, const Value, UInt32> TFunc_Instances_ByteArray_positionSet;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_clear, const Value> TFunc_Instances_ByteArray_clear;
typedef ThunkFunc2<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_compress, Value, unsigned, const Value*> TFunc_Instances_ByteArray_compress;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_deflate, const Value> TFunc_Instances_ByteArray_deflate;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_inflate, const Value> TFunc_Instances_ByteArray_inflate;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readBoolean, bool> TFunc_Instances_ByteArray_readBoolean;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readByte, SInt32> TFunc_Instances_ByteArray_readByte;
typedef ThunkFunc3<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readBytes, const Value, Instances::fl_utils::ByteArray*, UInt32, UInt32> TFunc_Instances_ByteArray_readBytes;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readDouble, Value::Number> TFunc_Instances_ByteArray_readDouble;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readFloat, Value::Number> TFunc_Instances_ByteArray_readFloat;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readInt, SInt32> TFunc_Instances_ByteArray_readInt;
typedef ThunkFunc2<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readMultiByte, ASString, UInt32, const ASString&> TFunc_Instances_ByteArray_readMultiByte;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readObject, Value> TFunc_Instances_ByteArray_readObject;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readShort, SInt32> TFunc_Instances_ByteArray_readShort;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readUnsignedByte, UInt32> TFunc_Instances_ByteArray_readUnsignedByte;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readUnsignedInt, UInt32> TFunc_Instances_ByteArray_readUnsignedInt;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readUnsignedShort, UInt32> TFunc_Instances_ByteArray_readUnsignedShort;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readUTF, ASString> TFunc_Instances_ByteArray_readUTF;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_readUTFBytes, ASString, UInt32> TFunc_Instances_ByteArray_readUTFBytes;
typedef ThunkFunc0<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_toString, ASString> TFunc_Instances_ByteArray_toString;
typedef ThunkFunc2<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_uncompress, Value, unsigned, const Value*> TFunc_Instances_ByteArray_uncompress;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_writeBoolean, const Value, bool> TFunc_Instances_ByteArray_writeBoolean;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_writeByte, const Value, SInt32> TFunc_Instances_ByteArray_writeByte;
typedef ThunkFunc3<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_writeBytes, const Value, Instances::fl_utils::ByteArray*, UInt32, UInt32> TFunc_Instances_ByteArray_writeBytes;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_writeDouble, const Value, Value::Number> TFunc_Instances_ByteArray_writeDouble;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_writeFloat, const Value, Value::Number> TFunc_Instances_ByteArray_writeFloat;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_writeInt, const Value, SInt32> TFunc_Instances_ByteArray_writeInt;
typedef ThunkFunc2<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_writeMultiByte, const Value, const ASString&, const ASString&> TFunc_Instances_ByteArray_writeMultiByte;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_writeObject, const Value, const Value&> TFunc_Instances_ByteArray_writeObject;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_writeShort, const Value, SInt32> TFunc_Instances_ByteArray_writeShort;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_writeUnsignedInt, const Value, UInt32> TFunc_Instances_ByteArray_writeUnsignedInt;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_writeUTF, const Value, const ASString&> TFunc_Instances_ByteArray_writeUTF;
typedef ThunkFunc1<Instances::fl_utils::ByteArray, Instances::fl_utils::ByteArray::mid_writeUTFBytes, const Value, const Value&> TFunc_Instances_ByteArray_writeUTFBytes;

template <> const TFunc_Instances_ByteArray_bytesAvailableGet::TMethod TFunc_Instances_ByteArray_bytesAvailableGet::Method = &Instances::fl_utils::ByteArray::bytesAvailableGet;
template <> const TFunc_Instances_ByteArray_endianGet::TMethod TFunc_Instances_ByteArray_endianGet::Method = &Instances::fl_utils::ByteArray::endianGet;
template <> const TFunc_Instances_ByteArray_endianSet::TMethod TFunc_Instances_ByteArray_endianSet::Method = &Instances::fl_utils::ByteArray::endianSet;
template <> const TFunc_Instances_ByteArray_lengthGet::TMethod TFunc_Instances_ByteArray_lengthGet::Method = &Instances::fl_utils::ByteArray::lengthGet;
template <> const TFunc_Instances_ByteArray_lengthSet::TMethod TFunc_Instances_ByteArray_lengthSet::Method = &Instances::fl_utils::ByteArray::lengthSet;
template <> const TFunc_Instances_ByteArray_objectEncodingGet::TMethod TFunc_Instances_ByteArray_objectEncodingGet::Method = &Instances::fl_utils::ByteArray::objectEncodingGet;
template <> const TFunc_Instances_ByteArray_objectEncodingSet::TMethod TFunc_Instances_ByteArray_objectEncodingSet::Method = &Instances::fl_utils::ByteArray::objectEncodingSet;
template <> const TFunc_Instances_ByteArray_positionGet::TMethod TFunc_Instances_ByteArray_positionGet::Method = &Instances::fl_utils::ByteArray::positionGet;
template <> const TFunc_Instances_ByteArray_positionSet::TMethod TFunc_Instances_ByteArray_positionSet::Method = &Instances::fl_utils::ByteArray::positionSet;
template <> const TFunc_Instances_ByteArray_clear::TMethod TFunc_Instances_ByteArray_clear::Method = &Instances::fl_utils::ByteArray::clear;
template <> const TFunc_Instances_ByteArray_compress::TMethod TFunc_Instances_ByteArray_compress::Method = &Instances::fl_utils::ByteArray::compress;
template <> const TFunc_Instances_ByteArray_deflate::TMethod TFunc_Instances_ByteArray_deflate::Method = &Instances::fl_utils::ByteArray::deflate;
template <> const TFunc_Instances_ByteArray_inflate::TMethod TFunc_Instances_ByteArray_inflate::Method = &Instances::fl_utils::ByteArray::inflate;
template <> const TFunc_Instances_ByteArray_readBoolean::TMethod TFunc_Instances_ByteArray_readBoolean::Method = &Instances::fl_utils::ByteArray::readBoolean;
template <> const TFunc_Instances_ByteArray_readByte::TMethod TFunc_Instances_ByteArray_readByte::Method = &Instances::fl_utils::ByteArray::readByte;
template <> const TFunc_Instances_ByteArray_readBytes::TMethod TFunc_Instances_ByteArray_readBytes::Method = &Instances::fl_utils::ByteArray::readBytes;
template <> const TFunc_Instances_ByteArray_readDouble::TMethod TFunc_Instances_ByteArray_readDouble::Method = &Instances::fl_utils::ByteArray::readDouble;
template <> const TFunc_Instances_ByteArray_readFloat::TMethod TFunc_Instances_ByteArray_readFloat::Method = &Instances::fl_utils::ByteArray::readFloat;
template <> const TFunc_Instances_ByteArray_readInt::TMethod TFunc_Instances_ByteArray_readInt::Method = &Instances::fl_utils::ByteArray::readInt;
template <> const TFunc_Instances_ByteArray_readMultiByte::TMethod TFunc_Instances_ByteArray_readMultiByte::Method = &Instances::fl_utils::ByteArray::readMultiByte;
template <> const TFunc_Instances_ByteArray_readObject::TMethod TFunc_Instances_ByteArray_readObject::Method = &Instances::fl_utils::ByteArray::readObject;
template <> const TFunc_Instances_ByteArray_readShort::TMethod TFunc_Instances_ByteArray_readShort::Method = &Instances::fl_utils::ByteArray::readShort;
template <> const TFunc_Instances_ByteArray_readUnsignedByte::TMethod TFunc_Instances_ByteArray_readUnsignedByte::Method = &Instances::fl_utils::ByteArray::readUnsignedByte;
template <> const TFunc_Instances_ByteArray_readUnsignedInt::TMethod TFunc_Instances_ByteArray_readUnsignedInt::Method = &Instances::fl_utils::ByteArray::readUnsignedInt;
template <> const TFunc_Instances_ByteArray_readUnsignedShort::TMethod TFunc_Instances_ByteArray_readUnsignedShort::Method = &Instances::fl_utils::ByteArray::readUnsignedShort;
template <> const TFunc_Instances_ByteArray_readUTF::TMethod TFunc_Instances_ByteArray_readUTF::Method = &Instances::fl_utils::ByteArray::readUTF;
template <> const TFunc_Instances_ByteArray_readUTFBytes::TMethod TFunc_Instances_ByteArray_readUTFBytes::Method = &Instances::fl_utils::ByteArray::readUTFBytes;
template <> const TFunc_Instances_ByteArray_toString::TMethod TFunc_Instances_ByteArray_toString::Method = &Instances::fl_utils::ByteArray::toString;
template <> const TFunc_Instances_ByteArray_uncompress::TMethod TFunc_Instances_ByteArray_uncompress::Method = &Instances::fl_utils::ByteArray::uncompress;
template <> const TFunc_Instances_ByteArray_writeBoolean::TMethod TFunc_Instances_ByteArray_writeBoolean::Method = &Instances::fl_utils::ByteArray::writeBoolean;
template <> const TFunc_Instances_ByteArray_writeByte::TMethod TFunc_Instances_ByteArray_writeByte::Method = &Instances::fl_utils::ByteArray::writeByte;
template <> const TFunc_Instances_ByteArray_writeBytes::TMethod TFunc_Instances_ByteArray_writeBytes::Method = &Instances::fl_utils::ByteArray::writeBytes;
template <> const TFunc_Instances_ByteArray_writeDouble::TMethod TFunc_Instances_ByteArray_writeDouble::Method = &Instances::fl_utils::ByteArray::writeDouble;
template <> const TFunc_Instances_ByteArray_writeFloat::TMethod TFunc_Instances_ByteArray_writeFloat::Method = &Instances::fl_utils::ByteArray::writeFloat;
template <> const TFunc_Instances_ByteArray_writeInt::TMethod TFunc_Instances_ByteArray_writeInt::Method = &Instances::fl_utils::ByteArray::writeInt;
template <> const TFunc_Instances_ByteArray_writeMultiByte::TMethod TFunc_Instances_ByteArray_writeMultiByte::Method = &Instances::fl_utils::ByteArray::writeMultiByte;
template <> const TFunc_Instances_ByteArray_writeObject::TMethod TFunc_Instances_ByteArray_writeObject::Method = &Instances::fl_utils::ByteArray::writeObject;
template <> const TFunc_Instances_ByteArray_writeShort::TMethod TFunc_Instances_ByteArray_writeShort::Method = &Instances::fl_utils::ByteArray::writeShort;
template <> const TFunc_Instances_ByteArray_writeUnsignedInt::TMethod TFunc_Instances_ByteArray_writeUnsignedInt::Method = &Instances::fl_utils::ByteArray::writeUnsignedInt;
template <> const TFunc_Instances_ByteArray_writeUTF::TMethod TFunc_Instances_ByteArray_writeUTF::Method = &Instances::fl_utils::ByteArray::writeUTF;
template <> const TFunc_Instances_ByteArray_writeUTFBytes::TMethod TFunc_Instances_ByteArray_writeUTFBytes::Method = &Instances::fl_utils::ByteArray::writeUTFBytes;

namespace Instances { namespace fl_utils
{
    ByteArray::ByteArray(InstanceTraits::Traits& t)
    : Instances::fl::Object(t)
//##protect##"instance::ByteArray::ByteArray()$data"
    , Encoding(static_cast<Classes::fl_utils::ByteArray&>(t.GetClass()).GetDefEncoding())
    , Endian(GetDefaultEndian())
    , Position(0)
    , Length(0)
//##protect##"instance::ByteArray::ByteArray()$data"
    {
//##protect##"instance::ByteArray::ByteArray()$code"
//##protect##"instance::ByteArray::ByteArray()$code"
    }

    void ByteArray::bytesAvailableGet(UInt32& result)
    {
//##protect##"instance::ByteArray::bytesAvailableGet()"
        result = GetAvailableNum();
//##protect##"instance::ByteArray::bytesAvailableGet()"
    }
    void ByteArray::endianGet(ASString& result)
    {
//##protect##"instance::ByteArray::endianGet()"
        if (Endian == endianBig)
            result = GetVM().GetStringManager().CreateConstString("bigEndian");
        else
            result = GetVM().GetStringManager().CreateConstString("littleEndian");
//##protect##"instance::ByteArray::endianGet()"
    }
    void ByteArray::endianSet(const Value& result, const ASString& value)
    {
//##protect##"instance::ByteArray::endianSet()"
        SF_UNUSED1(result);

        if (value == "bigEndian")
            Endian = endianBig;
        else if (value == "littleEndian")
            Endian = endianLittle;
        else
            return GetVM().ThrowArgumentError(VM::Error(VM::eInvalidArgumentError, GetVM() SF_DEBUG_ARG(value.ToCStr())));
//##protect##"instance::ByteArray::endianSet()"
    }
    void ByteArray::lengthGet(UInt32& result)
    {
//##protect##"instance::ByteArray::lengthGet()"
        // Length is not the same as Data.GetSize().
        result = Length;
//##protect##"instance::ByteArray::lengthGet()"
    }
    void ByteArray::lengthSet(const Value& result, UInt32 value)
    {
//##protect##"instance::ByteArray::lengthSet()"
        SF_UNUSED1(result);

        Resize(value);
//##protect##"instance::ByteArray::lengthSet()"
    }
    void ByteArray::objectEncodingGet(UInt32& result)
    {
//##protect##"instance::ByteArray::objectEncodingGet()"
        result = Encoding;
//##protect##"instance::ByteArray::objectEncodingGet()"
    }
    void ByteArray::objectEncodingSet(const Value& result, UInt32 value)
    {
//##protect##"instance::ByteArray::objectEncodingSet()"
        SF_UNUSED1(result);

        if (value != encAMF0 && value != encAMF3)
            return GetVM().ThrowRangeError(VM::Error(VM::eIllegalOperandTypeError, GetVM() SF_DEBUG_ARG("some type") SF_DEBUG_ARG("encAMF0 or encAMF3")));

        Encoding = static_cast<EncodingType>(value);
//##protect##"instance::ByteArray::objectEncodingSet()"
    }
    void ByteArray::positionGet(UInt32& result)
    {
//##protect##"instance::ByteArray::positionGet()"
        result = Position;
//##protect##"instance::ByteArray::positionGet()"
    }
    void ByteArray::positionSet(const Value& result, UInt32 value)
    {
//##protect##"instance::ByteArray::positionSet()"
        SF_UNUSED1(result);

        Position = value;
//##protect##"instance::ByteArray::positionSet()"
    }
    void ByteArray::clear(const Value& result)
    {
//##protect##"instance::ByteArray::clear()"
        SF_UNUSED1(result);
        Data.Clear();
        Length = 0;
        Position = 0;
//##protect##"instance::ByteArray::clear()"
    }
    void ByteArray::compress(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::ByteArray::compress()"
        SF_UNUSED3(result, argc, argv);

        // There is only one argument called "algorithm".
        // We ignore it for the time being.
#ifdef SF_ENABLE_ZLIB
        if (GetLength() == 0)
            return;

        UPInt zlen = GetLength() * 3/2 + 32; 
        UInt8* zdata = static_cast<UInt8*>(SF_HEAP_AUTO_ALLOC(this, zlen));

        // Call zlib.
        compress2(zdata, (unsigned long*)&zlen, (const Bytef *)Data.GetDataPtr(), GetLength(), 9);

        // Replace current array with the compressed data.
        Resize(0);
        Write(zdata, static_cast<UInt32>(zlen));

        SF_FREE(zdata);
#endif
//##protect##"instance::ByteArray::compress()"
    }
    void ByteArray::deflate(const Value& result)
    {
//##protect##"instance::ByteArray::deflate()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::ByteArray::deflate()");
//##protect##"instance::ByteArray::deflate()"
    }
    void ByteArray::inflate(const Value& result)
    {
//##protect##"instance::ByteArray::inflate()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::ByteArray::inflate()");
//##protect##"instance::ByteArray::inflate()"
    }
    void ByteArray::readBoolean(bool& result)
    {
//##protect##"instance::ByteArray::readBoolean()"
        if (EOFError())
            return;

        result = Data[Position++] != 0;
//##protect##"instance::ByteArray::readBoolean()"
    }
    void ByteArray::readByte(SInt32& result)
    {
//##protect##"instance::ByteArray::readByte()"
        if (EOFError())
            return;

        result = static_cast<SInt8>(Data[Position++]);
//##protect##"instance::ByteArray::readByte()"
    }
    void ByteArray::readBytes(const Value& result, Instances::fl_utils::ByteArray* bytes, UInt32 offset, UInt32 length)
    {
//##protect##"instance::ByteArray::readBytes()"
        SF_UNUSED1(result);

        const UInt32 available_num = GetAvailableNum();

        if (length == 0)
            length = available_num;

        if (length > available_num)
            return ThrowEOFError();

        // Adjust size of the output array.
        if (offset + length >= bytes->Data.GetSize())
            bytes->Resize(offset + length);

        Read(bytes->Data.GetDataPtr() + offset, length).DoNotCheck();
//##protect##"instance::ByteArray::readBytes()"
    }
    void ByteArray::readDouble(Value::Number& result)
    {
//##protect##"instance::ByteArray::readDouble()"
        if (!Read(&result, sizeof(result)))
            return;

        AdjustByteOrder(result);
//##protect##"instance::ByteArray::readDouble()"
    }
    void ByteArray::readFloat(Value::Number& result)
    {
//##protect##"instance::ByteArray::readFloat()"
        float v;

        if (!Read(&v, sizeof(v)))
            return;

        AdjustByteOrder(v);
        result = v;
//##protect##"instance::ByteArray::readFloat()"
    }
    void ByteArray::readInt(SInt32& result)
    {
//##protect##"instance::ByteArray::readInt()"
        if (!Read(&result, sizeof(result)))
            return;

        AdjustByteOrder(result);
//##protect##"instance::ByteArray::readInt()"
    }
    void ByteArray::readMultiByte(ASString& result, UInt32 length, const ASString& charSet)
    {
//##protect##"instance::ByteArray::readMultiByte()"
		// In case of ASCII.
		for (unsigned i = 0; ASCII_Names[i]; ++i)
		{
			if (charSet == ASCII_Names[i])
			{
				length = Alg::Min(length, GetLength());
				result = GetVM().GetStringManager().CreateString(reinterpret_cast<char*>(Data.GetDataPtr() + Position), length);
				Position += length;
				return;
			}
		}

		// In case of UTF-8.
		for (unsigned i = 0; UTF8_Names[i]; ++i)
		{
			if (charSet == UTF8_Names[i])
			{
				ReadUTFBytes(result, length).DoNotCheck();
				return;
			}
		}

		/*
		// No ISO support for the time being
		// In case of ISO.
		for (unsigned i = 0; ISO_Names[i]; ++i)
		{
			if (charSet == ISO_Names[i])
			{
				length = Alg::Min(length, GetLength());
				result = GetVM().GetStringManager().CreateString(reinterpret_cast<char*>(Data.GetDataPtr() + Position), length);
				Position += length;
				return;
			}
		}
		*/

		// In case of UTF16.
		for (unsigned i = 0; UTF16_Names[i]; ++i)
		{
			if (charSet == UTF16_Names[i])
			{
				length = Alg::Min(length, GetLength());
				result = GetVM().GetStringManager().CreateString(reinterpret_cast<const wchar_t*>(Data.GetDataPtr() + Position), length);
				Position += length;
				return;
			}
		}

		VM& vm = GetVM();
		vm.ThrowTypeError(VM::Error(VM::eInvalidArgumentError, vm SF_DEBUG_ARG("charSet")));
//##protect##"instance::ByteArray::readMultiByte()"
    }
    void ByteArray::readObject(Value& result)
    {
//##protect##"instance::ByteArray::readObject()"
        SF_UNUSED1(result);
        NOT_IMPLEMENTED("ByteArray::readObject()");
//##protect##"instance::ByteArray::readObject()"
    }
    void ByteArray::readShort(SInt32& result)
    {
//##protect##"instance::ByteArray::readShort()"
        result = ReadS16();
//##protect##"instance::ByteArray::readShort()"
    }
    void ByteArray::readUnsignedByte(UInt32& result)
    {
//##protect##"instance::ByteArray::readUnsignedByte()"
        if (EOFError())
            return;

        result = Data[Position++];
//##protect##"instance::ByteArray::readUnsignedByte()"
    }
    void ByteArray::readUnsignedInt(UInt32& result)
    {
//##protect##"instance::ByteArray::readUnsignedInt()"
        if (!Read(&result, sizeof(result)))
            return;

        AdjustByteOrder(result);
//##protect##"instance::ByteArray::readUnsignedInt()"
    }
    void ByteArray::readUnsignedShort(UInt32& result)
    {
//##protect##"instance::ByteArray::readUnsignedShort()"
        result = ReadU16();
//##protect##"instance::ByteArray::readUnsignedShort()"
    }
    void ByteArray::readUTF(ASString& result)
    {
//##protect##"instance::ByteArray::readUTF()"
        ReadUTFBytes(result, ReadU16()).DoNotCheck();
//##protect##"instance::ByteArray::readUTF()"
    }
    void ByteArray::readUTFBytes(ASString& result, UInt32 length)
    {
//##protect##"instance::ByteArray::readUTFBytes()"
        ReadUTFBytes(result, length).DoNotCheck();
//##protect##"instance::ByteArray::readUTFBytes()"
    }
    void ByteArray::toString(ASString& result)
    {
//##protect##"instance::ByteArray::toString()"
        UPInt size = Data.GetSize();
        union {
            char* str;
            wchar_t* str_w;
        };

        str = (char*)Data.GetDataPtr();

        if (size > 1)
        {
            if (IsUTF16BE(str))
            {
                str +=2;
                size = (size - 2) >> 1;
                // Ignore BE/LE differences for the time being.
                result = GetVM().GetStringManager().CreateString(str_w, size);
                return;
            } else if (IsUTF16LE(str))
            {
                str +=2;
                size = (size - 2) >> 1;
                // Ignore BE/LE differences for the time being.
                result = GetVM().GetStringManager().CreateString(str_w, size);
                return;
            } else if (size > 2 && IsUTF8BOM(str))
            {
                result = GetVM().GetStringManager().CreateString((const char*)(str + 3), size - 3);
                return;
            }
        }

        // We are supposed to copy invalid UTF-8 sequences as single characters here.
        // Let's do it later.
        result = GetVM().GetStringManager().CreateString((const char*)str, size);
//##protect##"instance::ByteArray::toString()"
    }
    void ByteArray::uncompress(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::ByteArray::uncompress()"
        SF_UNUSED3(result, argc, argv);

        // There is only one argument called "algorithm".
        // We ignore it for the time being.
#ifdef SF_ENABLE_ZLIB
        if (GetLength() == 0)
            return;

        UPInt zlen = GetLength();
        UInt8* zdata = static_cast<UInt8*>(SF_HEAP_AUTO_ALLOC(this, zlen));
        memcpy(zdata, Data.GetDataPtr(), zlen);

        Resize(0);

        int error = Z_OK;
        ZStream zstream;
        zstream.SetInput(zdata, static_cast<UInt32>(zlen));

        const int kBufferSize = 8192;
        UInt8* buffer = static_cast<UInt8*>(SF_HEAP_AUTO_ALLOC(this, kBufferSize));

        do {
            zstream.SetOutput(buffer, kBufferSize);
            error = zstream.DecompressWithStatus();
            Write(buffer, kBufferSize - zstream.GetAvailOutput());
        } while (error == Z_OK);

        SF_FREE(buffer);
        SF_FREE(zdata);

        Position = 0;

        if (error != Z_OK && error != Z_STREAM_END)
            GetVM().ThrowError(VM::Error(VM::eShellCompressedDataError, GetVM()));
#endif
//##protect##"instance::ByteArray::uncompress()"
    }
    void ByteArray::writeBoolean(const Value& result, bool value)
    {
//##protect##"instance::ByteArray::writeBoolean()"
        SF_UNUSED1(result);

        Write(value);
//##protect##"instance::ByteArray::writeBoolean()"
    }
    void ByteArray::writeByte(const Value& result, SInt32 value)
    {
//##protect##"instance::ByteArray::writeByte()"
        SF_UNUSED1(result);

        Write((SInt8)value);
//##protect##"instance::ByteArray::writeByte()"
    }
    void ByteArray::writeBytes(const Value& result, Instances::fl_utils::ByteArray* bytes, UInt32 offset, UInt32 length)
    {
//##protect##"instance::ByteArray::writeBytes()"
        SF_UNUSED1(result);

        if (bytes == NULL)
            return;

        if (bytes->GetLength() < offset)
            offset = bytes->GetLength();

        if (length == 0)
            length = bytes->GetLength() - offset;

        if (length > bytes->GetLength() - offset)
            return GetVM().ThrowRangeError(VM::Error(VM::eParamRangeError, GetVM()));

        if (length > 0)
            Write(bytes->Data.GetDataPtr() + offset, length);
//##protect##"instance::ByteArray::writeBytes()"
    }
    void ByteArray::writeDouble(const Value& result, Value::Number value)
    {
//##protect##"instance::ByteArray::writeDouble()"
        SF_UNUSED1(result);

        AdjustByteOrder(value);
        Write(&value, sizeof(value));
//##protect##"instance::ByteArray::writeDouble()"
    }
    void ByteArray::writeFloat(const Value& result, Value::Number value)
    {
//##protect##"instance::ByteArray::writeFloat()"
        SF_UNUSED1(result);

        float v = static_cast<float>(value);
        AdjustByteOrder(v);
        Write(&v, sizeof(v));
//##protect##"instance::ByteArray::writeFloat()"
    }
    void ByteArray::writeInt(const Value& result, SInt32 value)
    {
//##protect##"instance::ByteArray::writeInt()"
        SF_UNUSED1(result);

        AdjustByteOrder(value);
        Write(&value, sizeof(value));
//##protect##"instance::ByteArray::writeInt()"
    }
    void ByteArray::writeMultiByte(const Value& result, const ASString& value, const ASString& charSet)
    {
//##protect##"instance::ByteArray::writeMultiByte()"
		SF_UNUSED3(result, value, charSet);

		// In case of ASCII.
		// No ISO support for the time being.

		// In case of UTF-8.
		for (unsigned i = 0; UTF8_Names[i]; ++i)
		{
			if (charSet == UTF8_Names[i])
			{
				Write((void*)value.ToCStr(), value.GetSize());
				return;
			}
		}

		// In case of ISO.
		// No ISO support for the time being.

		// In case of UTF16.
		for (unsigned i = 0; UTF16_Names[i]; ++i)
		{
			if (charSet == UTF16_Names[i])
			{
				WStringBuffer wbuff;

				wbuff.SetString(value.ToCStr(), value.GetSize());
                if (wbuff.GetLength() <= SF_MAX_UINT32)
				    Write(wbuff.GetBuffer(), static_cast<UInt32>(wbuff.GetLength()));
				return;
			}
		}

		VM& vm = GetVM();
		vm.ThrowTypeError(VM::Error(VM::eInvalidArgumentError, vm SF_DEBUG_ARG("charSet")));
//##protect##"instance::ByteArray::writeMultiByte()"
    }
    void ByteArray::writeObject(const Value& result, const Value& object)
    {
//##protect##"instance::ByteArray::writeObject()"
        SF_UNUSED2(result, object);
        NOT_IMPLEMENTED("ByteArray::writeObject()");
//##protect##"instance::ByteArray::writeObject()"
    }
    void ByteArray::writeShort(const Value& result, SInt32 value)
    {
//##protect##"instance::ByteArray::writeShort()"
        SF_UNUSED1(result);

        SInt16 v = static_cast<SInt16>(value);
        AdjustByteOrder(v);
        Write(&v, sizeof(v));
//##protect##"instance::ByteArray::writeShort()"
    }
    void ByteArray::writeUnsignedInt(const Value& result, UInt32 value)
    {
//##protect##"instance::ByteArray::writeUnsignedInt()"
        SF_UNUSED1(result);

        AdjustByteOrder(value);
        Write(&value, sizeof(value));
//##protect##"instance::ByteArray::writeUnsignedInt()"
    }
    void ByteArray::writeUTF(const Value& result, const ASString& value)
    {
//##protect##"instance::ByteArray::writeUTF()"
        SF_UNUSED1(result);

        if (value.GetSize() > 65535)
            return GetVM().ThrowRangeError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("ByteArray::writeUTF")));

        const UInt16 size = static_cast<UInt16>(value.GetSize());
        Write(size);
        Write((void*)value.ToCStr(), size);
//##protect##"instance::ByteArray::writeUTF()"
    }
    void ByteArray::writeUTFBytes(const Value& result, const Value& value)
    {
//##protect##"instance::ByteArray::writeUTFBytes()"
        SF_UNUSED1(result);

        if (value.IsNullOrUndefined())
            return GetVM().ThrowTypeError(VM::Error(VM::eNullArgumentError, GetVM() SF_DEBUG_ARG("value")));

        StringManager& sm = GetVM().GetStringManager();
        ASString str = sm.CreateEmptyString();
        if (value.Convert2String(str))
        {
            Write((void*)str.ToCStr(), str.GetSize());
        }
//##protect##"instance::ByteArray::writeUTFBytes()"
    }

//##protect##"instance$methods"
	const char* ByteArray::ASCII_Names[] =
	{
		"us-ascii",
		"ANSI_X3.4-1968",
		"ANSI_X3.4-1986",
		"ascii",
		"cp367",
		"csASCII",
		"IBM367",
		"ISO_646.irv:1991",
		"ISO646-US",
		"iso-ir-6us",
		NULL
	};

	const char* ByteArray::UTF8_Names[] =
	{
		"utf-8",
		"unicode-1-1-utf-8",
		"unicode-2-0-utf-8",
		"x-unicode-2-0-utf-8",
		NULL
	};

	const char* ByteArray::UTF16_Names[] =
	{
		"unicode",
		"utf-16",
		NULL
	};

	/*
	// No ISO support for the time being.
	const char* ByteArray::ISO_Names[] =
	{
		"iso-8859-1",
		"cp819",
		"csISO",
		"Latin1",
		"ibm819",
		"iso_8859-1",
		"iso_8859-1:1987",
		"iso8859-1",
		"iso-ir-100, l1",
		"latin1",
		NULL
	};
	*/

    ByteArray::ByteArray(InstanceTraits::Traits& t, EncodingType enc)
    : Instances::fl::Object(t)
    , Encoding(enc)
    , Endian(Instances::fl_utils::ByteArray::GetDefaultEndian())
    , Position(0)
    {
    }

    void ByteArray::ThrowEOFError()
    {
        Value v;
        if (!GetVM().ConstructBuiltinValue(v, "flash.errors.EOFError"))
            return;
        GetVM().Throw(v);
    }

    void ByteArray::ThrowMemoryError()
    {
        Value v;
        if (!GetVM().ConstructBuiltinValue(v, "flash.errors.MemoryError"))
            return;
        GetVM().Throw(v);
    }

    CheckResult ByteArray::EOFError()
    {
        if (Position >= Data.GetSize())
        {
            ThrowEOFError();
            return true;
        }

        return false;
    }

    CheckResult ByteArray::Read(void* dest, UInt32 buff_size)
    {
        if (Position + buff_size > Data.GetSize())
        {
            ThrowEOFError();
            return false;
        }

        memcpy(dest, Data.GetDataPtr() + Position, buff_size);
        Position += buff_size;

        return true;
    }

    void ByteArray::Write(const void* src, UInt32 buff_size)
    {
        const UInt32 size = Position + buff_size;
        if (size >= Data.GetSize())
            // Resize() will take care of Length.
            Resize(Position + buff_size);
        else if (size >= Length)
            Length = size;

        memcpy(Data.GetDataPtr() + Position, src, buff_size);
        Position += buff_size;
    }

    void ByteArray::Write(bool v)
    {
        const UInt32 size = Position + sizeof(v);
        if (size >= Data.GetSize())
            // Resize() will take care of Length.
            Resize(size);
        else if (size >= Length)
            Length = size;

        Data[Position++] = (v ? 1 : 0);
    }

    void ByteArray::Write(UInt8 v)
    {
        const UInt32 size = Position + sizeof(v);
        if (size >= Data.GetSize())
            // Resize() will take care of Length.
            Resize(size);
        else if (size >= Length)
            Length = size;

        Data[Position++] = v;
    }

    void ByteArray::Write(SInt8 v)
    {
        const UInt32 size = Position + sizeof(v);
        if (size >= Data.GetSize())
            // Resize() will take care of Length.
            Resize(size);
        else if (size >= Length)
            Length = size;

        Data[Position++] = static_cast<UInt8>(v);
    }

    void ByteArray::Resize(UInt32 size)
    {
        const UPInt oldSize = Data.GetSize();

        if (size > oldSize)
        {
            Data.Resize(size);
            memset(Data.GetDataPtr() + oldSize, 0, size - oldSize);
        }

        Length = size;

        if (Position > Length)
            Position = Length;
    }

    UInt16 ByteArray::ReadU16()
    {
        UInt16 v;

        if (!Read(&v, sizeof(v)))
            return v;

        AdjustByteOrder(v);
        return v;
    }

	CheckResult ByteArray::ReadUTFBytes(ASString& result, UInt32 len)
	{
		if (!CanRead(len))
		{
			ThrowEOFError();
			return false;
		}

		// Check for UTF8 BOM.
		if (len > 2 && IsUTF8BOM(reinterpret_cast<char*>(Data.GetDataPtr() + Position)))
		{
			len -= 3;
			Position += 3;
		}

		result = GetVM().GetStringManager().CreateString(reinterpret_cast<char*>(Data.GetDataPtr() + Position), len);
        Position += len;

		return true;
	}

    UInt8 ByteArray::Get(UInt32 ind) const
    {
        if (ind < GetLength())
            return Data[ind];

        GetVM().ThrowArgumentError(VM::Error(VM::eInvalidArgumentError, GetVM() SF_DEBUG_ARG("ByteArray::Get") SF_DEBUG_ARG(ind) SF_DEBUG_ARG(0) SF_DEBUG_ARG(GetLength() - 1)));
        return 0;
    }

    void ByteArray::Get(void *dest, UPInt destSz)
    {
        Position = 0;
        Read(dest, (UInt32)destSz).DoNotCheck();
        Position = 0;
    }

    void ByteArray::Set(UInt32 ind, UInt8 v)
    {
        if (ind >= GetLength())
            Resize(ind + 1);

        Data[ind] = v;
    }

    void ByteArray::Set(const void* data, UPInt sz)
    {
        Position = 0;
        Write(data, (int)sz);
        Position = 0;
    }

    CheckResult ByteArray::SetProperty(const Multiname& prop_name, const Value& value)
    {
        UInt32 ind;
        if (GetArrayInd(prop_name, ind))
        {
            UInt32 v;
            if (!value.Convert2UInt32(v))
                // Exception.
                return false;

            // Cast and set.
            Set(ind, static_cast<UInt8>(v));
            return true;
        }

        // Not an Array index. Let us treat it as a regular object.
        return Instances::fl::Object::SetProperty(prop_name, value);
    }

    CheckResult ByteArray::GetProperty(const Multiname& prop_name, Value& value)
    {
        UInt32 ind;
        if (GetArrayInd(prop_name, ind))
        {
            if (ind < GetLength())
            {
                // We should return unsigned int here. This is how it works.
                value.SetUInt32(static_cast<UInt8>(Get(ind)));
                return true;
            }

            return false;
        }

        // Not an Array index. Let us treat it as a regular object.
        return Instances::fl::Object::GetProperty(prop_name, value);
    }

    void ByteArray::GetDynamicProperty(AbsoluteIndex ind, Value& value)
    {
        value.SetSInt32(static_cast<SInt8>(Get(ind.Get())));
    }
//##protect##"instance$methods"

}} // namespace Instances

namespace InstanceTraits { namespace fl_utils
{
    const ThunkInfo ByteArray::ti[ByteArray::ThunkInfoNum] = {
        {TFunc_Instances_ByteArray_bytesAvailableGet::Func, &AS3::fl::uintTI, "bytesAvailable", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_endianGet::Func, &AS3::fl::StringTI, "endian", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_endianSet::Func, NULL, "endian", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_ByteArray_lengthGet::Func, &AS3::fl::uintTI, "length", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_lengthSet::Func, NULL, "length", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_ByteArray_objectEncodingGet::Func, &AS3::fl::uintTI, "objectEncoding", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_objectEncodingSet::Func, NULL, "objectEncoding", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_ByteArray_positionGet::Func, &AS3::fl::uintTI, "position", NULL, Abc::NS_Public, CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_positionSet::Func, NULL, "position", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Instances_ByteArray_clear::Func, NULL, "clear", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_compress::Func, NULL, "compress", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, NULL, "deflate", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "inflate", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readBoolean::Func, &AS3::fl::BooleanTI, "readBoolean", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readByte::Func, &AS3::fl::int_TI, "readByte", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readBytes::Func, NULL, "readBytes", NULL, Abc::NS_Public, CT_Method, 1, 3},
        {TFunc_Instances_ByteArray_readDouble::Func, &AS3::fl::NumberTI, "readDouble", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readFloat::Func, &AS3::fl::NumberTI, "readFloat", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readInt::Func, &AS3::fl::int_TI, "readInt", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readMultiByte::Func, &AS3::fl::StringTI, "readMultiByte", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Instances_ByteArray_readObject::Func, NULL, "readObject", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readShort::Func, &AS3::fl::int_TI, "readShort", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUnsignedByte::Func, &AS3::fl::uintTI, "readUnsignedByte", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUnsignedInt::Func, &AS3::fl::uintTI, "readUnsignedInt", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUnsignedShort::Func, &AS3::fl::uintTI, "readUnsignedShort", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUTF::Func, &AS3::fl::StringTI, "readUTF", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUTFBytes::Func, &AS3::fl::StringTI, "readUTFBytes", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_toString::Func, &AS3::fl::StringTI, "toString", NULL, Abc::NS_Public, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_uncompress::Func, NULL, "uncompress", NULL, Abc::NS_Public, CT_Method, 0, 1},
        {TFunc_Instances_ByteArray_writeBoolean::Func, NULL, "writeBoolean", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeByte::Func, NULL, "writeByte", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeBytes::Func, NULL, "writeBytes", NULL, Abc::NS_Public, CT_Method, 1, 3},
        {TFunc_Instances_ByteArray_writeDouble::Func, NULL, "writeDouble", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeFloat::Func, NULL, "writeFloat", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeInt::Func, NULL, "writeInt", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeMultiByte::Func, NULL, "writeMultiByte", NULL, Abc::NS_Public, CT_Method, 2, 2},
        {TFunc_Instances_ByteArray_writeObject::Func, NULL, "writeObject", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeShort::Func, NULL, "writeShort", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeUnsignedInt::Func, NULL, "writeUnsignedInt", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeUTF::Func, NULL, "writeUTF", NULL, Abc::NS_Public, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeUTFBytes::Func, NULL, "writeUTFBytes", NULL, Abc::NS_Public, CT_Method, 1, 1},
    };

    ByteArray::ByteArray(VM& vm, const ClassInfo& ci)
    : CTraits(vm, ci)
    {
//##protect##"InstanceTraits::ByteArray::ByteArray()"
        SetArrayLike();
//##protect##"InstanceTraits::ByteArray::ByteArray()"
        SetMemSize(sizeof(Instances::fl_utils::ByteArray));

    }

    void ByteArray::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(static_cast<ByteArray&>(t));
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

}} // namespace InstanceTraits

namespace Classes { namespace fl_utils
{
    ByteArray::ByteArray(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::ByteArray::ByteArray()"
        DefEncoding = Instances::fl_utils::ByteArray::encAMF3;
//##protect##"class_::ByteArray::ByteArray()"
    }
    void ByteArray::defaultObjectEncodingSet(const Value& result, UInt32 value)
    {
//##protect##"class_::ByteArray::defaultObjectEncodingSet()"
        SF_UNUSED1(result);

        if (value != Instances::fl_utils::ByteArray::encAMF0 && value != Instances::fl_utils::ByteArray::encAMF3)
            return GetVM().ThrowRangeError(VM::Error(VM::eIllegalOperandTypeError, GetVM() SF_DEBUG_ARG("something") SF_DEBUG_ARG("encAMF0 or encAMF3")));

        DefEncoding = static_cast<Instances::fl_utils::ByteArray::EncodingType>(value);
//##protect##"class_::ByteArray::defaultObjectEncodingSet()"
    }
    void ByteArray::defaultObjectEncodingGet(UInt32& result)
    {
//##protect##"class_::ByteArray::defaultObjectEncodingGet()"
        result = DefEncoding;
//##protect##"class_::ByteArray::defaultObjectEncodingGet()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

}} // namespace Classes

typedef ThunkFunc1<Classes::fl_utils::ByteArray, Classes::fl_utils::ByteArray::mid_defaultObjectEncodingSet, const Value, UInt32> TFunc_Classes_ByteArray_defaultObjectEncodingSet;
typedef ThunkFunc0<Classes::fl_utils::ByteArray, Classes::fl_utils::ByteArray::mid_defaultObjectEncodingGet, UInt32> TFunc_Classes_ByteArray_defaultObjectEncodingGet;

template <> const TFunc_Classes_ByteArray_defaultObjectEncodingSet::TMethod TFunc_Classes_ByteArray_defaultObjectEncodingSet::Method = &Classes::fl_utils::ByteArray::defaultObjectEncodingSet;
template <> const TFunc_Classes_ByteArray_defaultObjectEncodingGet::TMethod TFunc_Classes_ByteArray_defaultObjectEncodingGet::Method = &Classes::fl_utils::ByteArray::defaultObjectEncodingGet;

namespace ClassTraits { namespace fl_utils
{
    const ThunkInfo ByteArray::ti[ByteArray::ThunkInfoNum] = {
        {TFunc_Classes_ByteArray_defaultObjectEncodingSet::Func, NULL, "defaultObjectEncoding", NULL, Abc::NS_Public, CT_Set, 1, 1},
        {TFunc_Classes_ByteArray_defaultObjectEncodingGet::Func, &AS3::fl::uintTI, "defaultObjectEncoding", NULL, Abc::NS_Public, CT_Get, 0, 0},
    };
    ByteArray::ByteArray(VM& vm)
    : Traits(vm, AS3::fl_utils::ByteArrayCI)
    {
//##protect##"ClassTraits::ByteArray::ByteArray()"
//##protect##"ClassTraits::ByteArray::ByteArray()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::fl_utils::ByteArray(vm, AS3::fl_utils::ByteArrayCI));
        SetInstanceTraits(it);

        // There is no problem with Pickable not assigned to anything here. Class constructor takes care of this.
        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::fl_utils::ByteArray(*this));

    }

    Pickable<Traits> ByteArray::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ByteArray(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

}} // namespace ClassTraits

namespace fl_utils
{
    const TypeInfo* ByteArrayImplements[] = {
        &fl_utils::IDataInputTI,
        &fl_utils::IDataOutputTI,
        NULL
    };

    const TypeInfo ByteArrayTI = {
        TypeInfo::CompileTime,
        "ByteArray", "flash.utils", &fl::ObjectTI,
        ByteArrayImplements
    };

    const ClassInfo ByteArrayCI = {
        &ByteArrayTI,
        ClassTraits::fl_utils::ByteArray::MakeClassTraits,
        ClassTraits::fl_utils::ByteArray::ThunkInfoNum,
        0,
        InstanceTraits::fl_utils::ByteArray::ThunkInfoNum,
        0,
        ClassTraits::fl_utils::ByteArray::ti,
        NULL,
        InstanceTraits::fl_utils::ByteArray::ti,
        NULL,
    };
}; // namespace fl_utils


}}} // namespace Scaleform { namespace GFx { namespace AS3

