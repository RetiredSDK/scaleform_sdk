/**************************************************************************

Filename    :   Amp_Visitors.h
Content     :   Helper classes for memory fragmentation report
Created     :   March 2010
Authors     :   Maxim Shemenarev

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_GFX_AMP_MEMORY_IMAGE_H
#define INC_GFX_AMP_MEMORY_IMAGE_H

namespace Scaleform {
namespace GFx {
namespace AMP {

template<class T> 
class GFxMemDataArray
{
    enum 
    { 
        MaxPages  = 32,
        PageShift = 12,
        PageSize  = 1 << PageShift, 
        PageMask  =      PageSize - 1
    };

public:
    typedef T ValueType;

    GFxMemDataArray() : NumPages(0), Size(0) {}
    ~GFxMemDataArray() { ClearAndRelease(); }

    void ClearAndRelease()
    {
        if(NumPages)
        {
            ValueType** page = Pages + NumPages - 1;
            UPInt freeCount = Size & PageMask;
            while(NumPages--)
            {
                Memory::pGlobalHeap->FreeSysDirect(*page, PageSize * sizeof(ValueType));
                freeCount = PageSize;
                --page;
            }
        }
        Size = NumPages = 0;
    }

    void Clear()
    {
        Size = NumPages = 0;
    }

    void PushBack(const ValueType& v)
    {
        *acquireDataPtr() = v;
        ++Size;
    }

    UPInt GetSize() const 
    { 
        return Size; 
    }

    const ValueType& operator [] (UPInt i) const
    {
        return Pages[i >> PageShift][i & PageMask];
    }

    ValueType& operator [] (UPInt i)
    {
        return Pages[i >> PageShift][i & PageMask];
    }

private:
    SF_INLINE ValueType* acquireDataPtr()
    {
        UPInt np = Size >> PageShift;
        if(np >= NumPages)
        {
#ifdef SF_BUILD_DEBUG
            SF_ASSERT(np < MaxPages);
#else
            if (np >= MaxPages)
            {
                --Size;
                return Pages[Size >> PageShift] + (Size & PageMask);
            }
#endif
            Pages[np] = (ValueType*)Memory::pGlobalHeap->AllocSysDirect(PageSize * sizeof(ValueType));
            NumPages++;
        }
        return Pages[np] + (Size & PageMask);
    }

    ValueType*  Pages[MaxPages];
    UPInt       NumPages;
    UPInt       Size;
};

struct ImageVisitor : public MovieDef::ResourceVisitor 
{ 
    Array< Ptr<ImageResource> >     Images;

    virtual void Visit(MovieDef*, Resource* resource, ResourceId, const char*) 
    { 
        if (resource->GetResourceType() == Resource::RT_Image)
        {
            Images.PushBack(static_cast<ImageResource*>(resource));
        }
    }
};

struct FontVisitor : public MovieDef::ResourceVisitor
{        
    Array<String> Fonts;

    virtual void Visit(MovieDef*, Resource* presource, ResourceId rid, const char*)
    {
        FontResource* pfontResource = static_cast<FontResource*>(presource);

        char buf[100];
        String font;
        font = pfontResource->GetName();
        if (pfontResource->GetFont()->IsBold())
        {
            font += " - Bold";
        }
        else if (pfontResource->GetFont()->IsItalic())
        {
            font += " - Italic";
        }
        SFsprintf(buf, sizeof(buf), ", %d glyphs", pfontResource->GetFont()->GetGlyphShapeCount()); 
        font += buf;
        if (!pfontResource->GetFont()->HasLayout())
        {
            font += ", static only";
        }
        font += " (";
        rid.GenerateIdString(buf);
        font += buf;
        font += ")";

        Fonts.PushBack(font);
    }
};

} // namespace AMP
} // namespace GFx
} // namespace Scaleform

#endif   // INC_GFX_AMP_MEMORY_IMAGE_H
