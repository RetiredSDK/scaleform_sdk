/**************************************************************************

Filename    :   AS3_AvmDisplayObjContainer.cpp
Content     :   Implementation of AS3-dependent part of DisplayObjectContainer.
Created     :   Jan, 2010
Authors     :   Artem Bolgar

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
#include "GFx/AS3/AS3_AvmDisplayObjContainer.h"
#include "GFx/GFx_PlayerImpl.h"

namespace Scaleform {
namespace GFx {
namespace AS3 {

AvmDisplayObjContainer::~AvmDisplayObjContainer() 
{
}

void AvmDisplayObjContainer::FillTabableArray(InteractiveObject::FillTabableParams* params)
{
    UPInt n = GetDisplayList().GetCount();
    if (n == 0)
        return;

    if (GetDisplayObjContainer()->IsTabChildrenDisabledFlagSet())
        return;

    DisplayObjectBase*   ch;

    for (UPInt i = 0; i < n; i++)
    {
        ch = GetDisplayList().GetDisplayObject(i);
        if (ch != NULL && ch->IsInteractiveObject() && ch->GetVisible())
        {
            InteractiveObject* asch = ch->CharToInteractiveObject_Unsafe();
            if (asch->IsTabIndexed() && !params->TabIndexed)
            {
                // the first char with tabIndex: release the current array and
                // start to fill it again according to tabIndex.
                params->Array->Clear();
                params->TabIndexed = true;
            }
            // Append for now; if tabIndexed - later it will be sorted by tabIndex
            // Note, we might add focusEnabled characters as well; we are doing this only for
            // 'moveFocus' extension: for regular focus handling these characters will
            // be ignored, if IsTabable returns false.
            if ((asch->IsTabable() || (params->InclFocusEnabled && 
                asch->IsFocusEnabled(GFx_FocusMovedByKeyboard))) && 
                (!params->TabIndexed || asch->IsTabIndexed()))
                params->Array->PushBack(asch);
            if (asch->IsDisplayObjContainer())
            {
                asch->CharToDisplayObjContainer_Unsafe()->FillTabableArray(params);
            }
        }
    }
}

bool AvmDisplayObjContainer::DetachChild(DisplayObjectBase* ch)
{
    if (RemoveChild(ch))
        return true;
    return false;
}

DisplayObjectBase*  AvmDisplayObjContainer::RemoveChild(DisplayObjectBase* ch)
{
    Ptr<DisplayObjectBase> sch = ch;

    if (ch->IsScriptableObject())
    {
        DisplayObject* cch = ch->CharToScriptableObject_Unsafe();
        cch->SetMask(NULL);
    }
    if (ch->HasIndirectTransform())
        GetMovieImpl()->RemoveTopmostLevelCharacter(ch);

    DisplayList& displayList = GetDisplayList();
    SPInt index = displayList.FindDisplayIndex(ch);
    if (index >= 0)
        displayList.RemoveEntryAtIndex(GetDispObj(), index);    
    else 
        return NULL;
    displayList.InvalidateDepthMappings();
    InteractiveObject* intobj = sch->CharToInteractiveObject();
    ToAvmDisplayObj(sch->CharToScriptableObject())->OnRemoved(false);
    sch->SetParent(NULL); // needs to be done AFTER OnRemoved

    if (intobj && intobj->IsInPlayList())
    {
        // need to re-insert.
        ToAvmInteractiveObj(intobj)->MoveBranchInPlayList();
    }
    DisplayObject* dob = static_cast<DisplayObject*>(sch.GetPtr());
    if (dob->IsTimelineObjectFlagSet())
    {
        dob->SetTimelineObjectFlag(false);
        dob->SetAcceptAnimMoves(false);
        dob->SetCreateFrame(0);
        dob->SetDepth(DisplayList::INVALID_DEPTH);

        ToAvmDisplayObj(dob)->OnDetachFromTimeline();
    }
    GetMovieImpl()->CheckPlaylistConsistency();

    return sch;
}
DisplayObjectBase*  AvmDisplayObjContainer::RemoveChildAt(unsigned index)
{
    if (index >= GetNumChildren())
        return NULL;

    DisplayList& displayList = GetDisplayList();
    Ptr<DisplayObjectBase> sch = displayList.GetDisplayObject(index);

    if (sch->IsScriptableObject())
    {
        DisplayObject* cch = sch->CharToScriptableObject_Unsafe();
        cch->SetMask(NULL);
    }
    if (sch->HasIndirectTransform())
        GetMovieImpl()->RemoveTopmostLevelCharacter(sch);

    displayList.RemoveEntryAtIndex(GetDispObj(), index);    
    displayList.InvalidateDepthMappings();
    InteractiveObject* intobj = sch->CharToInteractiveObject();
    ToAvmDisplayObj(sch->CharToScriptableObject())->OnRemoved(false);
    sch->SetParent(NULL); // needs to be done AFTER OnRemoved
    if (intobj && intobj->IsInPlayList())
    {
        // need to re-insert.
        ToAvmInteractiveObj(intobj)->MoveBranchInPlayList();
    }
    DisplayObject* dob = static_cast<DisplayObject*>(sch.GetPtr());
    if (dob->IsTimelineObjectFlagSet())
    {
        dob->SetTimelineObjectFlag(false);
        dob->SetAcceptAnimMoves(false);
        dob->SetCreateFrame(0);
        dob->SetDepth(DisplayList::INVALID_DEPTH);

        ToAvmDisplayObj(dob)->OnDetachFromTimeline();
    }
    GetMovieImpl()->CheckPlaylistConsistency();
    return sch;
}

bool            AvmDisplayObjContainer::SetChildIndex(DisplayObjectBase* ch, unsigned index)
{
    if (index >= GetNumChildren())
        return NULL;
    DisplayList& displayList = GetDisplayList();
    SPInt origIndex = displayList.FindDisplayIndex(ch);
    if (origIndex < 0)
        return false;
    Ptr<DisplayObjectBase> sch = ch;
    displayList.RemoveEntryAtIndex(GetDispObj(), origIndex);
    displayList.AddEntryAtIndex(GetDispObj(), index, sch);

    // set index changes the type of the character, actually:
    // it becomes completely independent from timeline, so even if timeline
    // rollovers the character remains on stage (unlike to just "touched" by AS
    // ones, which are removed in this case).
    sch->SetAcceptAnimMoves(false);
    sch->SetCreateFrame(0);
    sch->SetDepth(DisplayList::INVALID_DEPTH);
    displayList.InvalidateDepthMappings();
    return true;
}

bool            AvmDisplayObjContainer::SwapChildren(DisplayObjectBase* ch1, DisplayObjectBase* ch2)
{
    DisplayList& displayList = GetDisplayList();
    SPInt origIndex1 = displayList.FindDisplayIndex(ch1);
    SPInt origIndex2 = displayList.FindDisplayIndex(ch2);
    return SwapChildrenAt((unsigned)origIndex1, (unsigned)origIndex2);
}

bool            AvmDisplayObjContainer::SwapChildrenAt(unsigned i1, unsigned i2)
{
    DisplayList& displayList = GetDisplayList();
    if (i1 >= displayList.GetCount())
        return false;
    if (i2 >= displayList.GetCount())
        return false;
    if (!displayList.SwapEntriesAtIndexes(GetDisplayObjContainer(), i1, i2))
        return false;
    DisplayObjectBase* d1 = displayList.GetDisplayObject(i1);
    DisplayObjectBase* d2 = displayList.GetDisplayObject(i2);
    if (d1)
    {
        // swap children changes the type of the character, actually:
        // it becomes completely independent from timeline, so even if timeline
        // rollovers the character remains on stage (unlike to just "touched" by AS
        // ones, which are removed in this case).
        d1->SetAcceptAnimMoves(false);
        d1->SetCreateFrame(0);
        d1->SetDepth(DisplayList::INVALID_DEPTH);
    }
    if (d2)
    {
        d2->SetAcceptAnimMoves(false);
        d2->SetCreateFrame(0);
        d2->SetDepth(DisplayList::INVALID_DEPTH);
    }
    displayList.InvalidateDepthMappings();
    if (d1->IsInteractiveObject())
        ToAvmInteractiveObj(d1->CharToInteractiveObject_Unsafe())->MoveBranchInPlayList();
    if (d2->IsInteractiveObject())
        ToAvmInteractiveObj(d2->CharToInteractiveObject_Unsafe())->MoveBranchInPlayList();
    return true;
}

void AvmDisplayObjContainer::AddChild(DisplayObjectBase* ch)
{
    DisplayList& displayList = GetDisplayList();
    UPInt idx = displayList.GetCount();
    // check if the ch is already a child of other container;
    // if so, removed it from the old and re-insert into this one.
    if (ch->GetParent())
    {
        SF_ASSERT(ch->GetParent()->CharToDisplayObjContainer());
        
        // if parent is the same - just move the child to the end of displaylist
        if (ch->GetParent() == GetDisplayObjContainer())
        {
            SF_ASSERT(idx > 0);
            SetChildIndex(ch, unsigned(idx - 1));
            return;
        }
        ToAvmDisplayObjContainer(ch->GetParent()->CharToDisplayObjContainer_Unsafe())->RemoveChild(ch);
    }
    displayList.AddEntryAtIndex(GetDispObj(), (unsigned)idx, ch);
    displayList.InvalidateDepthMappings();
    ch->SetParent(GetIntObj());
    ch->SetDepth(DisplayList::INVALID_DEPTH);
    ch->SetUnloaded(false);
    if (ch->IsInteractiveObject())
    {
        InteractiveObject* intobj = ch->CharToInteractiveObject_Unsafe();
        if (intobj->IsInPlayList())
            ToAvmInteractiveObj(intobj)->MoveBranchInPlayList();
    }
    DisplayObject* sch = ch->CharToScriptableObject();
    AvmDisplayObj* avmObj = ToAvmDisplayObj(sch);
    avmObj->SetAppDomain(*AppDomain);
    avmObj->OnAdded(false);

    // re-apply scroll rect if it was set
    const RectD* sr = sch->GetScrollRect();
    if (sr)
    {
        RectD r = *sr;
        sch->SetScrollRect(&r);
    }
}

void AvmDisplayObjContainer::AddChildAt(DisplayObjectBase* ch, unsigned index)
{
    if (index > GetNumChildren())
        index = GetNumChildren();
    DisplayList& displayList = GetDisplayList();

    // check if the ch is already a child of other container;
    // if so, removed it from the old and re-insert into this one.
    if (ch->GetParent())
    {
        SF_ASSERT(ch->GetParent()->CharToDisplayObjContainer());

        // if parent is the same - just move the child to the end of displaylist
        if (ch->GetParent() == GetDisplayObjContainer())
        {
            SetChildIndex(ch, index);
            return;
        }
        ToAvmDisplayObjContainer(ch->GetParent()->CharToDisplayObjContainer_Unsafe())->RemoveChild(ch);
    }
    displayList.AddEntryAtIndex(GetDispObj(), index, ch);
    ch->SetParent(GetIntObj());
    ch->SetDepth(DisplayList::INVALID_DEPTH);
    ch->SetUnloaded(false);
    if (ch->IsInteractiveObject())
    {
        InteractiveObject* intobj = ch->CharToInteractiveObject_Unsafe();
        if (intobj->IsInPlayList())
            ToAvmInteractiveObj(intobj)->MoveBranchInPlayList();
    }
    DisplayObject* sch = ch->CharToScriptableObject();
    AvmDisplayObj* avmObj = ToAvmDisplayObj(sch);
    avmObj->SetAppDomain(*AppDomain);
    avmObj->OnAdded(false);

    // re-apply scroll rect if it was set
    const RectD* sr = sch->GetScrollRect();
    if (sr)
    {
        RectD r = *sr;
        sch->SetScrollRect(&r);
    }
}

SPtr<Instances::fl_display::DisplayObject> AvmDisplayObjContainer::GetAS3ChildAt(unsigned index)
{
    DisplayObjectBase* pch = GetDisplayObjContainer()->GetChildAt(index);
    if (pch)
    {
        AvmDisplayObj* avobj = ToAvmDisplayObj(static_cast<GFx::DisplayObject*>(pch));
        avobj->CreateASInstance(true);
        return avobj->GetAS3Obj();
    }
    return NULL;
}

SPtr<Instances::fl_display::DisplayObject> AvmDisplayObjContainer::GetAS3ChildByName(const ASString& name)
{
    DisplayObjectBase* pch = GetDisplayObjContainer()->GetChildByName(name);
    if (pch)
    {
        AvmDisplayObj* avobj = ToAvmDisplayObj(static_cast<GFx::DisplayObject*>(pch));
        avobj->CreateASInstance(true);
        return avobj->GetAS3Obj();
    }
    return NULL;
}

// searches for the character, after which the 'ch' should be inserted.
// returns NULL if needs to be inserted at the head of the list
InteractiveObject* AvmDisplayObjContainer::FindInsertToPlayList(InteractiveObject* ch)
{
    SF_ASSERT(ch->GetParent() == GetIntObj());

    // In the case when this object is already unloaded or is unloading the obj is already excluded
    // from the playlist.
    if (GetIntObj()->IsUnloaded() || GetIntObj()->IsUnloading())
        return NULL;

    InteractiveObject* afterCh = NULL;

    DisplayObjContainer* dobjParent = GetDisplayObjContainer();
    if (dobjParent->GetNumChildren() == 0)
    {
        // if parent doesn't have children, then we can insert the 'ch' right
        // in front of the parent
        SF_ASSERT(dobjParent->IsInPlayList());
        afterCh = dobjParent->pPlayPrev;
    }
    else 
    {
        const DisplayList& dl = dobjParent->GetDisplayList();
        // search for the 'ch' sprite in the display list. Save the sibling that is 
        // located before the 'ch' and in the displaylist.
        InteractiveObject* dobPrevSpr = NULL;
        unsigned i = 0, n = dobjParent->GetNumChildren();
        for (; i < n; ++i)
        {
            DisplayObjectBase* pcur = dl.GetDisplayObject(i);
            if (pcur == ch)
                break; // found
            if (pcur->IsInteractiveObject() && pcur->CharToInteractiveObject_Unsafe()->IsInPlayList())
                dobPrevSpr = pcur->CharToInteractiveObject_Unsafe(); // hold the last sprite
        }
        SF_ASSERT(i < n); // the 'ch' MUST be in the display list already!
        if (!dobPrevSpr)
        {
            // if parent doesn't have children in the playlist, then we can insert the 'ch' right
            // in front of the parent
            SF_ASSERT(dobjParent->IsInPlayList());
            afterCh = dobjParent->pPlayPrev;
        }
        else
        {
            InteractiveObject* dobNextSpr = NULL;
            // check, if the found ch has one more (next) sibling in the playlist....
            for (++i; i < n; ++i)
            {
                DisplayObjectBase* pcur = dl.GetDisplayObject(i);
                if (pcur->IsInteractiveObject() && pcur->CharToInteractiveObject_Unsafe()->IsInPlayList())
                {
                    dobNextSpr = pcur->CharToInteractiveObject_Unsafe();
                    break;
                }
            }
            if (dobNextSpr)
            {
                // if we found the next sibling, when just insert 'ch' in front of it....
                SF_ASSERT(dobNextSpr->IsInPlayList());
                afterCh = dobNextSpr;
            }
            else
            {
                // there are no more children in the display list.
                // to figure out where we need to put the 'ch' we need to take
                // the previous-in-playlist character and move backward while
                // the parent chain contain 'this'. Insert the 'ch' right after 
                // the last character with the parent chain containing 'this'.
                InteractiveObject* pcur = dobPrevSpr;
                InteractiveObject* parpar = GetParent();
                for (; pcur ; pcur = pcur->pPlayPrev)
                {
                    // check the parent chain.
                    InteractiveObject* c = pcur;
                    for (; c; c = c->GetParent())
                    {
                        if (c == GetIntObj())
                            break;
                        else if (c == parpar)
                        {
                            c = NULL;
                            break;
                        }
                    }
                    if (!c)
                    {
                        // we found the character w/o 'this' in the parent chain;
                        // insert 'ch' in front of it.
                        SF_ASSERT(pcur->IsInPlayList());
                        afterCh = pcur;
                        break;
                    }
                }
            }
        }
    }
    return afterCh;
}

void AvmDisplayObjContainer::PropagateEvent(const Instances::fl_events::Event& evtProto, bool inclChildren)
{
    // executes the event for itself
    AvmInteractiveObj::PropagateEvent(evtProto);

    if (inclChildren)
    {
        // iterate through children
        DisplayObjContainer* dobjParent = GetDisplayObjContainer();
        unsigned i = 0, n = dobjParent->GetNumChildren();
        const DisplayList& dl = dobjParent->GetDisplayList();
        for (; i < n; ++i)
        {
            DisplayObjectBase* pcur = dl.GetDisplayObject(i);
            ToAvmDisplayObj(pcur->CharToScriptableObject())->PropagateEvent(evtProto);
        }
    }
}

bool AvmDisplayObjContainer::GetObjectsUnderPoint(
    ArrayDH<Ptr<DisplayObjectBase> >* destArray, const PointF& pt) const
{
    // iterate through children
    const DisplayObjContainer* dobjParent = GetDisplayObjContainer();

    if (!dobjParent->GetVisible())
        return false;

    const DisplayList& dl = dobjParent->GetDisplayList();
    SPInt i, n = (SPInt)dl.GetCount();
    const UInt8 hitMask = DisplayObjectBase::HitTest_TestShape | DisplayObjectBase::HitTest_IgnoreInvisible;

    DisplayObject* pmask = dobjParent->GetMask();  
    if (pmask)
    {
        if (pmask->IsUsedAsMask() && !pmask->IsUnloaded())
        {
            Matrix2F matrix;
            matrix.SetInverse(pmask->GetWorldMatrix());
            matrix *= dobjParent->GetWorldMatrix();
            Render::PointF p = matrix.Transform(pt);

            if (!pmask->PointTestLocal(p, hitMask))
                return false;
        }
    }

    Array<UByte> hitTest;
    dobjParent->CalcDisplayListHitTestMaskArray(&hitTest, pt, hitMask);

    Matrix2F m;
    Render::PointF p = pt;
    UPInt oldSz = destArray->GetSize();

    // Go backwards, to check higher objects first.
    for (i = n - 1; i >= 0; i--)
    {
        DisplayObjectBase* pch = dl.GetDisplayObject(i);

        if (pch->IsScriptableObject())
        {
            if (!pch->GetVisible())
                continue;

            if (hitTest.GetSize() && (!hitTest[i] || pch->GetClipDepth()>0))
                continue;

            m = pch->GetMatrix();
            p = m.TransformByInverse(pt);   

            ToAvmDisplayObj(pch->CharToScriptableObject_Unsafe())->
                GetObjectsUnderPoint(destArray, p);
        }
    }   
    return destArray->GetSize() > oldSz;
}

}}} // SF::GFx::AS3
