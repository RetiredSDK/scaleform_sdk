/**************************************************************************

Filename    :   Render_Filters.cpp
Content     :   Filter and FilterSet implementations.
Created     :   May 18, 2011
Authors     :   Michael Antonov

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "Render_Filters.h"
#include "Kernel/SF_HeapNew.h"

namespace Scaleform { namespace Render {

//--------------------------------------------------------------------
bool BlurFilterImpl::CanCacheAcrossTransform(bool deltaTrans, bool deltaRot, bool deltaScale) const
{
    SF_UNUSED2(deltaTrans, deltaRot);
    return !deltaScale;
}

//--------------------------------------------------------------------
// ***** BlurFilter
Filter* BlurFilter::Clone(MemoryHeap *heap) const
{
    if (!heap)
        heap = Memory::GetHeapByAddress(this);
    return SF_HEAP_NEW(heap) BlurFilter(Params);
}

bool BlurFilter::IsContributing() const
{
    return (Params.BlurX > 20 || Params.BlurY > 20) && Params.Passes > 0;
}

//--------------------------------------------------------------------
// ***** ShadowFilter
Filter* ShadowFilter::Clone(MemoryHeap *heap) const
{
    if (!heap)
        heap = Memory::GetHeapByAddress(this);
    return SF_HEAP_NEW(heap) ShadowFilter(Params, Angle, TwipsToPixels(Distance));
}

bool ShadowFilter::IsContributing() const
{
    return Params.Colors[0].GetAlpha() > 0 && Params.Passes > 0;
}

bool ShadowFilter::CanCacheAcrossTransform(bool deltaTrans, bool deltaRot, bool deltaScale) const
{
    SF_UNUSED(deltaTrans);
    return !deltaRot && !deltaScale;
}

//--------------------------------------------------------------------
// ***** GlowFilter
Filter* GlowFilter::Clone(MemoryHeap *heap) const
{
    if (!heap)
        heap = Memory::GetHeapByAddress(this);
    return SF_HEAP_NEW(heap) GlowFilter(Params);
}

bool GlowFilter::IsContributing() const
{
    return Params.Colors[0].GetAlpha() > 0 && Params.Passes > 0;
}

//--------------------------------------------------------------------
// ***** BevelFilter
Filter* BevelFilter::Clone(MemoryHeap *heap) const
{
    if (!heap)
        heap = Memory::GetHeapByAddress(this);
    return SF_HEAP_NEW(heap) BevelFilter(Params, Angle, TwipsToPixels(Distance));
}

bool BevelFilter::IsContributing() const
{
    return (Params.Colors[0].GetAlpha() > 0 || 
           Params.Colors[1].GetAlpha() > 0) && Params.Passes > 0;
}

bool BevelFilter::CanCacheAcrossTransform(bool deltaTrans, bool deltaRot, bool deltaScale) const
{
    SF_UNUSED(deltaTrans);
    return !deltaRot && !deltaScale;
}

//--------------------------------------------------------------------
// ***** ColorMatrixFilter

static float ColorMatrix_Identity[20] =
{
    1.0f, 0.0f, 0.0f, 0.0f, 
    0.0f, 1.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 1.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 0.0f
};

ColorMatrixFilter::ColorMatrixFilter() : Filter(Filter_ColorMatrix)
{
    memcpy(MatrixData, ColorMatrix_Identity, sizeof(MatrixData));
}
ColorMatrixFilter::~ColorMatrixFilter()
{
}

bool ColorMatrixFilter::IsContributing() const
{
    return memcmp( MatrixData, ColorMatrix_Identity, sizeof(ColorMatrix_Identity)) != 0;
}

Filter* ColorMatrixFilter::Clone(MemoryHeap* heap) const
{
    if (!heap)
        heap = Memory::GetHeapByAddress(this);

    ColorMatrixFilter* newFilter = SF_HEAP_NEW(heap) ColorMatrixFilter();
    if (newFilter)
    {
        memcpy(newFilter->MatrixData, MatrixData, sizeof(MatrixData));
    }
    return newFilter;
}


//--------------------------------------------------------------------
// ***** FilterSet

FilterSet::FilterSet(Filter* filter)
    : Frozen(false), CacheAsBitmap(false)
{
    if (filter)
        AddFilter(filter);
}
FilterSet::~FilterSet()
{
}

void FilterSet::Freeze()
{
    if (!Frozen)
    {
        for (UPInt i=0; i<Filters.GetSize(); i++)
            Filters[i]->Freeze();
        Frozen = true;
    }
}

void FilterSet::RemoveFilter(Filter* filter)
{
    SF_ASSERT(!IsFrozen());
    for (UPInt i=0; i<Filters.GetSize(); i++)
    {
        if (Filters[i] == filter)
        {
            Filters.RemoveAt(i);
            i--;
        }
    }

    if (Filters.GetSize() == 0 && GetCacheAsBitmap())
        Filters.PushBack(CacheAsBitmapFilter::GetInstance());
}

void FilterSet::SetCacheAsBitmap(bool enable)
{
    // If we have no filters, we need to add in a 'bogus' cacheAsBitmap filter to the array.
    CacheAsBitmap = enable;
    if (enable && GetFilterCount() == 0)
        AddFilter(CacheAsBitmapFilter::GetInstance());
    else if (!enable && GetFilterCount() == 1 && Filters[0]->GetFilterType() == Filter_CacheAsBitmap)
        Filters.RemoveAt(0);
}

FilterSet* FilterSet::Clone(bool deepCopy, MemoryHeap *heap) const
{
    if (!heap)
        heap = Memory::GetHeapByAddress(this);

    FilterSet* newSet = SF_HEAP_NEW(heap) FilterSet;
    if (!newSet)
        return 0;

    newSet->CacheAsBitmap = CacheAsBitmap;

    for (UPInt i=0; i< Filters.GetSize(); i++)
    {
        if (deepCopy)
        {
            Ptr<Filter> newFilter = *Filters[i]->Clone(heap);
            newSet->AddFilter(newFilter);
        }
        else
        {
            newSet->AddFilter(Filters[i]);
        }
    }

    return newSet;
}

bool FilterSet::IsContributing() const
{
    // If a FilterSet has cacheAsBitmap set on it, report that it is always contributing,
    // regardless of whether its filters actually do anything or not (so it will always be
    // rendered to a texture).
    if (CacheAsBitmap)
        return true;

    unsigned f;
    for (f = 0; f < Filters.GetSize(); ++f )
    {
        const Filter* filter = Filters[f];
        if ( filter && filter->IsContributing() )
            return true;
    }
    return false;
}

bool FilterSet::CanCacheAcrossTransform(bool deltaTrans, bool deltaRot, bool deltaScale) const
{
    unsigned f;
    for (f = 0; f < Filters.GetSize(); ++f )
    {
        const Filter* filter = Filters[f];
        if ( filter && !filter->CanCacheAcrossTransform(deltaTrans, deltaRot, deltaScale) )
            return false;
    }
    return true;
}

}} // Scaleform::Render
