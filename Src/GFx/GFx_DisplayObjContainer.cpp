/**************************************************************************

Filename    :   GFx_DisplayObjContainer.cpp
Content     :   Implementation of DisplayObjContainer
Created     :   
Authors     :   Artem Bolgar

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
#include "GFx/GFx_DisplayObjContainer.h"
#include "GFx/GFx_PlayerImpl.h"
#include "Render/Render_TreeLog.h"

namespace Scaleform { namespace GFx {

SF_INLINE MemoryHeap* DisplayObjContainer::GetMovieHeap() const
{
    return pASRoot->GetMovieImpl()->GetMovieHeap();
}


DisplayObjContainer::DisplayObjContainer(MovieDefImpl* pbindingDefImpl, 
                                         ASMovieRootBase* pasRoot,
                                         InteractiveObject* pparent, 
                                         ResourceId id)
:  InteractiveObject(pbindingDefImpl, pasRoot, pparent, id),
   pRootNode(0)
{
    SetDisplayObjContainerFlag();
}

DisplayObjContainer::~DisplayObjContainer()
{
    if (pRootNode)    
    {
        pRootNode->SpriteRefCount--;
        if (pRootNode->SpriteRefCount == 0)
        {
            pASRoot->GetMovieImpl()->RootMovieDefNodes.Remove(pRootNode);
            delete pRootNode;
        }
    }

    ClearDisplayList();
}

void DisplayObjContainer::AssignRootNode(bool importFlag)
{
    if (!pRootNode)
    {
        // We share the MovieDefRootNode with other root sprites based on a ref 
        // count. Try to find the root node for the same MovieDef and import flag
        // as ours, if not found create one.

        // An exhaustive search should be ok here since we don't expect too
        // many different MovieDefs and root sprite construction happens rarely;
        // furthermore, a list is cheap to traverse in Advance where updates need
        // to take place. If this becomes a bottleneck we could introduce a
        // hash table in movie root.    
        MovieDefRootNode *pnode = GetMovieImpl()->RootMovieDefNodes.GetFirst();

        while(!GetMovieImpl()->RootMovieDefNodes.IsNull(pnode))
        {
            if ((pnode->pDefImpl == pDefImpl) && (pnode->ImportFlag == importFlag))
            {
                // Found node identical to us.
                pnode->SpriteRefCount++;
                pRootNode = pnode;
                break;
            }
            pnode = pnode->pNext;
        }

        // If compatible root node not found, create one.
        if (!pRootNode)
        {
            MemoryHeap* pheap = GetMovieHeap();

            pRootNode = pASRoot->CreateMovieDefRootNode(pheap, pDefImpl, importFlag);
            // Bytes loaded must be grabbed first due to data race.        
            pRootNode->BytesLoaded  = pDefImpl->GetBytesLoaded();
            pRootNode->LoadingFrame = importFlag ? 0 : pDefImpl->GetLoadingFrame();

            // Create a local font manager.
            // Fonts created for sprite will match bindings of our DefImpl.
            pRootNode->pFontManager = *SF_HEAP_NEW(pheap) FontManager(
                GetMovieImpl(), pDefImpl, pASRoot->GetMovieImpl()->pFontManagerStates);
            pASRoot->GetMovieImpl()->RootMovieDefNodes.PushFront(pRootNode);
        }
    }
}

MovieDefRootNode* DisplayObjContainer::FindRootNode() const
{  
    const InteractiveObject *pchar = this;
    // Find a load root sprite and grab bytes loaded from it.
    while(pchar)
    {
        const DisplayObjContainer* psprite = pchar->CharToDisplayObjContainer();
        if (psprite)
        {
            if (psprite && psprite->pRootNode)
                return psprite->pRootNode;
        }
        pchar = pchar->GetParent();
    }
    // We should never end up here.
    return 0;
}

void DisplayObjContainer::OnInsertionAsLevel(int level)
{
    if (level == 0)
        SetFocusRectFlag(); // _focusrect in _root is true by default
    else if (level > 0)
    {
        // looks like levels above 0 inherits _focusrect from _level0. Probably
        // another properties are also inherited, need investigate.
        InteractiveObject* _level0 = GetMovieImpl()->GetMainContainer();
        if (_level0)
        {
            SetFocusRectFlag(_level0->IsFocusRectEnabled());
        }
    }
    AddToPlayList();
    ModifyOptimizedPlayList();
    FocusGroupMask = 0;
    --FocusGroupMask; // Set to 0xffff
}

void    DisplayObjContainer::MoveDisplayObject(const CharPosInfo &pos)
{
    mDisplayList.MoveDisplayObject(this, pos);
    SetDirtyFlag();
}

void DisplayObjContainer::CreateAndReplaceDisplayObject
    (const CharPosInfo &pos, const ASString& name, DisplayObjectBase** newChar)
{
    SF_ASSERT(GetCharacterDef());

    CharacterCreateInfo ccinfo = pDefImpl->GetCharacterCreateInfo(pos.CharacterId);    
    if (ccinfo.pCharDef == NULL)
    {
        LogError("DisplayObjContainer::ReplaceDisplayObject() - unknown cid = %d", pos.CharacterId.GetIdIndex());
        return;
    }
    SF_ASSERT(ccinfo.pCharDef && ccinfo.pBindDefImpl);

    Ptr<DisplayObjectBase> ch = *pASRoot->GetASSupport()->CreateCharacterInstance
        (GetMovieImpl(), ccinfo, this, pos.CharacterId);
    SF_ASSERT(ch);
    //SF_ASSERT(!ch->IsInteractiveObject()); //!AB: technically, AS chars shouldn't be used here

    ReplaceDisplayObject(pos, ch, name);

    if (newChar)
        *newChar = (ch.GetPtr()->GetRefCount() > 1) ? ch.GetPtr() : NULL;
}

void    DisplayObjContainer::ReplaceDisplayObject(const CharPosInfo &pos, DisplayObjectBase* ch, const ASString& name)
{
    SF_ASSERT(ch != NULL);
    if (!name.IsEmpty() && IsScriptableObject())
        ch->CharToScriptableObject_Unsafe()->SetName(name);  

    //!AB: ReplaceDisplayObject shouldn't be used for "active" objects, such as sprites, 
    // buttons or dynamic textfields. For such "active" object the Remove tag should be 
    // executed first. However, Flash CS5 sometimes uses EditTextChar instead of
    // StaticText and applies "replace" to it w/o Remove tag. Not sure if we need
    // to add such objects in playlist or not since they were not intended to be "active".
    //!AB: make sure the replacee char is already in play list (if it is AS char)
    //SF_ASSERT(!ch->IsInteractiveObject() || 
    //    ch->CharToInteractiveObject_Unsafe()->pPlayPrev != NULL || 
    //    GetMovieImpl()->pPlayListHead == ch->CharToInteractiveObject_Unsafe());

    mDisplayList.ReplaceDisplayObject(this, pos, ch);

    if (!name.IsEmpty() && ch->IsInteractiveObject())
        pASRoot->ResolveStickyVariables(ch->CharToInteractiveObject_Unsafe());
    SetDirtyFlag();
    GetMovieImpl()->CheckPlaylistConsistency();
}


void    DisplayObjContainer::RemoveDisplayObject(int depth, ResourceId id)
{
    mDisplayList.RemoveDisplayObject(this, depth, id);
    SetDirtyFlag();
    GetMovieImpl()->CheckPlaylistConsistency();
}

void    DisplayObjContainer::RemoveDisplayObject(DisplayObjectBase* ch) 
{ 
    SPInt i = mDisplayList.FindDisplayIndex(ch);
    if (i >= 0)
    {
        mDisplayList.RemoveEntryAtIndex(this, UPInt(i));
    }
    GetMovieImpl()->CheckPlaylistConsistency();
}

DisplayObjectBase* DisplayObjContainer::GetChildAt(unsigned index) const
{
    if (index >= mDisplayList.GetCount())
        return NULL;
    return mDisplayList.GetDisplayObject(index);
}

// For debugging -- return the id of the DisplayObjectBase at the specified depth.
// Return -1 if nobody's home.
ResourceId DisplayObjContainer::GetIdAtDepth(int depth)
{
    DisplayObjectBase* pch = GetCharacterAtDepth(depth);
    return pch ? pch->GetId() : ResourceId();
}

DisplayObjectBase* DisplayObjContainer::GetCharacterAtDepth(int depth)
{
    UPInt index = mDisplayList.GetDisplayIndex(depth);
    if (index == SF_MAX_UPINT)    
        return 0;   
    return mDisplayList.GetDisplayObject(index);
}

// void    DisplayObjContainer::Display(DisplayContext &context)
// {
//     DisplayContextStates save;
//     if (!BeginDisplay(context, save))
//         return;
// 
//     mDisplayList.Display(context);
// 
//     EndDisplay(context, save);
// }

void    DisplayObjContainer::PropagateMouseEvent(const EventId& id)
{
    Ptr<DisplayObjContainer> thisHolder(this); // PropagateMouseEvent may release "this"; preventing.

    if (id.Id == EventId::Event_MouseMove)
    {
        // Adjust x,y of this character if it is being dragged.
        if (GetMovieImpl()->IsMouseSupportEnabled())
            DisplayObjContainer::DoMouseDrag(id.MouseIndex);
    }

    // MA: Hidden clips don't receive mouse events.
    // Tested by assigning _visible property to false,
    // but the object didn't hide in Flash.
    if (GetVisible() == false)  
        return;

    mDisplayList.PropagateMouseEvent(id);
    // Notify us after children.
    if (HasAvmObject())
        GetAvmDispContainer()->OnEvent(id);
}

void    DisplayObjContainer::PropagateKeyEvent(const EventId& id, int* pkeyMask)
{
    Ptr<DisplayObjContainer> thisHolder(this); // PropagateKeyEvent may release "this"; preventing.

    // AB: Hidden clips don't receive key events.
    // Tested by assigning _visible property to false,
    // but the object didn't hide in Flash. nEed to test more:
    // what about hidden by timeline?
    if (!GetVisible())  
        return;

    mDisplayList.PropagateKeyEvent (id, pkeyMask);
    // Notify us after children.
    OnKeyEvent(id, pkeyMask);
}

void    DisplayObjContainer::CalcDisplayListHitTestMaskArray(
    Array<UByte> *phitTest, const Render::PointF &pt, bool testShape) const
{
    SF_UNUSED(testShape);

    UPInt i, n = mDisplayList.GetCount();

    // Mask support
    for (i = 0; i < n; i++)
    {
        DisplayObjectBase* pmaskch = mDisplayList.GetDisplayObject(i);

        if (pmaskch->GetClipDepth() > 0)
        {
            if (phitTest->GetSize()==0)
            {
                phitTest->Resize(n);
                memset(&(*phitTest)[0], 1, n);
            }

            Matrix2F   m = pmaskch->GetMatrix();
            Render::PointF             p = m.TransformByInverse(pt);

            (*phitTest)[i] = pmaskch->PointTestLocal(p, HitTest_TestShape);

            UPInt k = i+1;            
            while (k < n)
            {
                DisplayObjectBase* pch = mDisplayList.GetDisplayObject(k);
                if (pch && (pch->GetDepth() > pmaskch->GetClipDepth()))
                    break;
                (*phitTest)[k] = (*phitTest)[i];
                k++;
            }
            i = k-1;
        }
    }
}

// Return the topmost entity that the given point covers.  NULL if none.
// Coords are in parent's frame.
DisplayObject::TopMostResult DisplayObjContainer::GetTopMostMouseEntity(
    const Render::PointF &pt, TopMostDescr* pdescr) 
{
    SF_ASSERT(pdescr);
    Sprite* phitAreaHolder = GetHitAreaHolder();
    
    // Invisible sprites/buttons don't receive mouse events (i.e. are disabled), unless it is a hitArea.
    // Masks also shouldn't receive mouse events (!AB)
    if (IsHitTestDisableFlagSet() || (!GetVisible() && !phitAreaHolder) || IsUsedAsMask())
    {
        pdescr->pResult = NULL;
        return TopMost_FoundNothing;
    }

    if (pdescr->pIgnoreMC == this || !IsFocusAllowed(GetMovieImpl(), pdescr->ControllerIdx))
    {
        pdescr->pResult = NULL;
        return TopMost_FoundNothing;
    }

    Render::PointF localPt;
    if (!TransformPointToLocalAndCheckBounds(&localPt, pt))
        return TopMost_FoundNothing;

    DisplayObject* pmask = GetMask();  
    if (pmask)
    {
        if (pmask->IsUsedAsMask() && !pmask->IsUnloaded())
        {
            Render::PointF pp;
            if ( !pmask->Is3D() )
            {
                Matrix2F matrix;
                matrix.SetInverse(pmask->GetWorldMatrix());
                matrix *= GetWorldMatrix();
                pp = matrix.Transform(localPt);
            }
            else
            {
                Matrix3F view;
                Matrix4F proj; 
                Matrix3F world = pmask->GetWorldMatrix3D();
                Render::ScreenToWorld & stw = GetMovieImpl()->ScreenToWorld;
                
                if (pmask->GetProjectionMatrix3D(&proj))
                    stw.SetProjection(proj);

                if (pmask->GetViewMatrix3D(&view))
                    stw.SetView(view);

                stw.SetWorld(world);
                stw.GetWorldPoint(&pp);
            }

            if (!pmask->PointTestLocal(pp, HitTest_TestShape))
            {
                pdescr->pResult = NULL;
                return TopMost_FoundNothing;
            }
        }
    }

    Array<UByte> hitTest;
    CalcDisplayListHitTestMaskArray(&hitTest, localPt, 1);
    TopMostDescr    savedDescr;
    TopMostResult   savedTe = TopMost_FoundNothing;
    bool            foundButMouseDisabled = false;

    Sprite* phitArea = GetHitArea();

    // Go backwards, to check higher objects first.
    SPInt i, n;
    n = (SPInt)mDisplayList.GetCount();
    for (i = n - 1; i >= 0; i--)
    {
        DisplayObjectBase* ch = mDisplayList.GetDisplayObject(i);

        if (hitTest.GetSize() && (!hitTest[i] || ch->GetClipDepth()>0))
            continue;

        if (ch->IsTopmostLevelFlagSet()) // do not check children w/topmostLevel
            continue;

        // MA: This should consider submit masks in the display list,
        // such masks can obscure/clip out buttons for the purpose of
        // hit-testing as well.

        if (ch != NULL)
        {           
            TopMostResult te = ch->GetTopMostMouseEntity(localPt, pdescr);

            if (te == TopMost_Found)
            {
                //if (IsMouseChildrenDisabledFlagSet() || (pdescr->pResult && pdescr->pResult->IsMouseDisabledFlagSet()))
                if (IsMouseChildrenDisabledFlagSet())
                    pdescr->pResult = this;
                if (pdescr->pResult && pdescr->pResult->IsMouseDisabledFlagSet())
                {
                    pdescr->pResult = this;
                    foundButMouseDisabled = true;
                    //return TopMost_Continue;
                    continue;
                }
                if (pdescr->TestAll) 
                    te = TopMost_Found;
            }
            else if (te == TopMost_Continue && pdescr->pResult)
            {
                // if continue,
                savedTe     = TopMost_Found;
                savedDescr  = *pdescr;
            }

            // If we found anything and we are in button mode, this refers to us.
            if (ActsAsButton() || (phitAreaHolder && (pdescr->TestAll || phitAreaHolder->ActsAsButton())))
            {   
                // It is either child or us; no matter - button mode takes precedence.
                // Note, if both - the hitArea and the holder of hitArea have button handlers
                // then the holder (parent) takes precedence; otherwise, if only the hitArea has handlers
                // it should be returned.
                if (te == TopMost_Found || savedTe == TopMost_Found)
                {
                    if (phitAreaHolder && (pdescr->TestAll || phitAreaHolder->ActsAsButton()))
                    {
                        pdescr->pResult = phitAreaHolder;               
                        pdescr->pHitArea = this;
                        return TopMost_Found;
                    }
                    else 
                    {
                        // Sprites with hit area also shouldn't receive mouse events if this hit area is not the sprite's child
                        // We need to check here if a hit area is our child  
                        if (GetASMovieRoot()->GetAVMVersion() == 1)
                        {
                            // AS1.0 & 2.0 only.
                            if (phitArea)
                            {
                                InteractiveObject* parent = phitArea;
                                do {
                                    parent = parent->GetParent();
                                } while (parent && parent != this);
                                if (!parent)
                                {
                                    // hit area is not our child so we should not receive mouse events
                                    pdescr->pResult = NULL;
                                    return TopMost_FoundNothing;
                                }
                                if (phitArea == pdescr->pHitArea)
                                {
                                    pdescr->pResult = this;
                                    return TopMost_Found;
                                }
                                else
                                {
                                    pdescr->pResult = NULL;
                                    savedTe = TopMost_FoundNothing;
                                    continue;
                                }
                            }
                            else
                            { 
                                pdescr->pResult = this;
                                return TopMost_Found;
                            }
                        }
                        else // AS3
                        {
                            // according to AS3 tests 'test_nested_rollover_events' & 'hitAreaTest.swf'
                            // this code is not necessary should not be executed for AS3;
                            // however, AS2 still needs it ('test_hitarea_event_handlers.swf').
                            if (phitArea)
                            {
                                // hitArea must be ignored if hit occurred on a child that is InteractiveObject.
                                // In this case the child still should get the event (test_hitarea_and_child_mc.swf).
                                if (!pdescr->pResult || pdescr->pResult == this || !pdescr->pResult->IsInteractiveObject())
                                {
                                    if (phitArea == pdescr->pHitArea)
                                    {
                                        pdescr->pResult = this;
                                        return TopMost_Found;
                                    }
                                    else
                                    {
                                        pdescr->pResult = NULL;
                                        savedTe = TopMost_FoundNothing;
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                }
                if (te == TopMost_Found && pdescr->TestAll) 
                    return te;
            }
            else 
            {
                if (te == TopMost_Found && pdescr->TestAll) 
                    return te;

                if (te == TopMost_Found && pdescr->pResult != this)
                {
                    // Found one.
                    // @@ TU: GetVisible() needs to be recursive here!

                    // character could be _root, in which case it would have no parent.
                    if (pdescr->pResult->GetParent() && pdescr->pResult->GetParent()->GetVisible())
                        //if (te->GetVisible()) // TODO move this check to the base case(s) only
                    {
                        // @@
                        // Vitaly suggests "return ch" here, but it breaks
                        // samples/test_button_functions.swf
                        //
                        // However, it fixes samples/clip_as_button.swf
                        //
                        // What gives?
                        //
                        // Answer: a button event must be passed up to parent until
                        // somebody handles it.
                        //
                        return te;
                    }
                    else
                    {
                        pdescr->pResult = NULL;
                        return TopMost_FoundNothing;
                    }
                }           
            }
        }
    }
    // if we are here then we are going to return 'Continue'. But first, check
    // if there is a hitArea, and if there is one check if we hit into it. Otherwise,
    // return 'NotFound'. Refer to AS3 test_hitArea1.swf,test_hitArea2.swf,test_hitArea3.swf.
    if (phitArea)
    {
        // hitArea must be ignored if hit occurred on a child that is InteractiveObject.
        // In this case the child still should get the event (test_hitarea_and_child_mc.swf).
        if (!pdescr->pResult || pdescr->pResult == this || !pdescr->pResult->IsInteractiveObject())
        {
            if (phitArea == pdescr->pHitArea)
            {
                pdescr->pResult = this;
                return TopMost_Found;
            }
            else
            {
                pdescr->pResult = NULL;
                return TopMost_FoundNothing;
            }
        }
    }
    if (savedTe == TopMost_Found)
    {
        *pdescr = savedDescr;
        return TopMost_Found;
    }
    pdescr->LocalPt = localPt;
    if (foundButMouseDisabled)
    {
        pdescr->pResult = this;
        return TopMost_Found;
    }
    else
        pdescr->pResult = NULL;
    return TopMost_Continue;
}

// Test if point is inside of the movieclip. Coordinate is in child's coordspace.
bool DisplayObjContainer::PointTestLocal(const Render::PointF &pt, UInt8 hitTestMask) const 
{ 
    if (IsHitTestDisableFlagSet())
        return false;

    if (!DoesScale9GridExist() && !GetBounds(Matrix2F()).Contains(pt))
        return false;

    if ((hitTestMask & HitTest_IgnoreInvisible) && !GetVisible())
        return false;

    SPInt i, n = (SPInt)mDisplayList.GetCount();

    DisplayObject* pmask = GetMask();  
    if (pmask)
    {
        if (pmask->IsUsedAsMask() && !pmask->IsUnloaded())
        {
            Matrix2F matrix;
            matrix.SetInverse(pmask->GetWorldMatrix());
            matrix *= GetWorldMatrix();
            Render::PointF p = matrix.Transform(pt);

            if (!pmask->PointTestLocal(p, hitTestMask))
                return false;
        }
    }

    Array<UByte> hitTest;
    CalcDisplayListHitTestMaskArray(&hitTest, pt, hitTestMask & HitTest_TestShape);

    Matrix2F m;
    Render::PointF           p = pt;

    // Go backwards, to check higher objects first.
    for (i = n - 1; i >= 0; i--)
    {
        DisplayObjectBase* pch = mDisplayList.GetDisplayObject(i);

        if ((hitTestMask & HitTest_IgnoreInvisible) && !pch->GetVisible())
            continue;

        if (hitTest.GetSize() && (!hitTest[i] || pch->GetClipDepth()>0))
            continue;

        m = pch->GetMatrix();
        p = m.TransformByInverse(pt);   

        if (pch->PointTestLocal(p, hitTestMask))
            return true;
    }   

    return false;
}

void DisplayObjContainer::PropagateFocusGroupMask(unsigned mask)
{
    InteractiveObject::PropagateFocusGroupMask(mask);
    for (UPInt i = 0, n = mDisplayList.GetCount(); i < n; ++i)
    {
        InteractiveObject* ch = mDisplayList.GetDisplayObject(i)->CharToInteractiveObject();
        if (ch)
        {
            ch->FocusGroupMask = (UInt16)mask;
            ch->PropagateFocusGroupMask(mask);
        }
    }   
}


void DisplayObjContainer::FillTabableArray(FillTabableParams* params)
{
    if (HasAvmObject())
        GetAvmDispContainer()->FillTabableArray(params);
}

bool DisplayObjContainer::Contains(DisplayObjectBase* ch) const
{
    if (this == ch)
        return true;
    for (UPInt i = 0, n = mDisplayList.GetCount(); i < n; ++i)
    {
        DisplayObjectBase* pch = mDisplayList.GetDisplayObject(i);
        if (ch == pch)
            return true;
        DisplayObjContainer* cont = pch->CharToDisplayObjContainer();
        if (cont && cont->Contains(ch))
            return true;
    }   
    return false;
}

// These accessor methods have custom implementation in Sprite.
FontManager*  DisplayObjContainer::GetFontManager() const
{
    if (pRootNode)
        return pRootNode->pFontManager;
    if (!GetParent())
    {
        // where to get font manager if sprite does not have a parent???
        return pASRoot->GetMovieImpl()->RootMovieDefNodes.GetFirst()->pFontManager;
    }
    return GetParent()->GetFontManager();
}

void DisplayObjContainer::SetStateChangeFlags(UInt8 flags)
{
    InteractiveObject::SetStateChangeFlags(flags);
    UPInt size = mDisplayList.GetCount();
    for (UPInt i = 0; i < size; ++i)
    {
        DisplayObjectBase* ch = mDisplayList.GetDisplayObject(i);
        ch->SetStateChangeFlags(flags);
    }   
}

//////////////////////////////////////////////////////////////////////////
#ifdef SF_BUILD_DEBUG
void DisplayObjContainer::DumpDisplayList(int indent, const char* title)
{
    char indentStr[900];
    memset(indentStr, 32, indent*3);
    indentStr[indent*3] = 0;

    if (title)
        printf("%s -- %s --\n", indentStr, title);
    else
        printf("\n");

    if (indent == 0)
    {
        String nm;
        printf("%sSprite %s\n", indentStr, GetAbsolutePath(&nm));
        //printf("%sSprite %s\n", indentStr, GetCharacterHandle()->GetNamePath().ToCStr());
        printf("%sId          = %d\n", indentStr, (int)GetId().GetIdValue());
        printf("%sCreateFrame = %d\n", indentStr, (int)GetCreateFrame());
        printf("%sDepth       = %d\n", indentStr, (int)GetDepth());
        printf("%sVisibility  = %s\n", indentStr, GetVisible() ? "true" : "false");
        indent++;
        memset(indentStr, 32, indent*3);
        indentStr[indent*3] = 0;
    }

    for (unsigned i = 0; i < mDisplayList.GetCount(); i++)
    {
        const DisplayList::DisplayEntry& dobj = mDisplayList.GetDisplayEntry(i);
        DisplayObjectBase*                     ch = dobj.GetDisplayObject();

        InteractiveObject* pasch = NULL;
        if (ch->IsInteractiveObject())
        {
            String nm;
            pasch = ch->CharToInteractiveObject_Unsafe();
            if (pasch->IsSprite())
                printf("%sSprite %s\n", indentStr, pasch->GetAbsolutePath(&nm));
                //printf("%sSprite %s\n", indentStr, pasch->GetCharacterHandle()->GetNamePath().ToCStr());
            else
                printf("%sCharacter %s\n", indentStr, pasch->GetAbsolutePath(&nm));
                //printf("%sCharacter %s\n", indentStr, pasch->GetCharacterHandle()->GetNamePath().ToCStr());
        }
        else
            printf("%sCharacter (generic)\n", indentStr);
        if (dobj.IsMarkedForRemove())
            printf("%s(marked for remove)\n", indentStr);
        printf("%sId          = %d\n", indentStr, (int)ch->GetId().GetIdValue());
        printf("%sCreateFrame = %d\n", indentStr, (int)ch->GetCreateFrame());
        printf("%sDepth       = %d\n", indentStr, (int)ch->GetDepth());
        printf("%sClipDepth   = %d\n", indentStr, (int)ch->GetClipDepth());
        printf("%sVisibility  = %s\n", indentStr, ch->GetVisible() ? "true" : "false");

        char buff[2560];
        const Cxform& cx = ch->GetCxform();
        if (!cx.IsIdentity())
        {
            Format(buff, sizeof(buff), cx);
            printf("%sCxform:\n%s\n", indentStr, buff);
        }
        const Matrix& mx = ch->GetMatrix();
        if (mx != Matrix::Identity)
        {
            Format(buff, sizeof(buff), mx);
            printf("%sMatrix:\n%s\n", indentStr, buff);
        }

        if (pasch && pasch->IsSprite())
        {
            //            printf("\n");
            pasch->CharToSprite()->DumpDisplayList(indent+1);
        }
        else 
            printf("\n");
    }
    if (title)
        printf("%s-----------------\n", indentStr);
}
#endif // SF_BUILD_DEBUG

void DisplayObjContainer::ForceShutdown()
{
    mDisplayList.Clear(this);
}

// checks object and descendants
bool DisplayObjContainer::Has3D()
{
    if (InteractiveObject::Has3D())
        return true;

    for (UPInt i = 0, n = mDisplayList.GetCount(); i < n; ++i)
    {
        DisplayObjectBase* ch = mDisplayList.GetDisplayObject(i);
        if (ch && ch->Has3D())
            return true;
    }
    return false;
}


void DisplayObjContainer::UpdateViewAndPerspective() 
{
    InteractiveObject::UpdateViewAndPerspective();

    for (UPInt i = 0, n = mDisplayList.GetCount(); i < n; ++i)
    {
        DisplayObjectBase* ch = mDisplayList.GetDisplayObject(i);
        if (ch)
        {
            ch->UpdateViewAndPerspective();
        }
    }   
}

void DisplayObjContainer::SetScale9Grid(const RectF& rect)
{
    bool propagate = rect != GetScale9Grid();
    DisplayObject::SetScale9Grid(rect);
    SetScale9GridExists(!rect.IsEmpty());
    if (propagate)
        PropagateScale9GridExists();
}

void DisplayObjContainer::PropagateScale9GridExists()
{
    bool actualGrid = HasScale9Grid();
    // Stop cleaning up scale9Grid if actual one exists in the node
    if (!DoesScale9GridExist() && actualGrid)
        return; 

    for (UPInt i = 0, n = mDisplayList.GetCount(); i < n; ++i)
    {
        DisplayObjectBase* ch = mDisplayList.GetDisplayObject(i);
        ch->SetScale9GridExists(DoesScale9GridExist() || actualGrid);
        ch->PropagateScale9GridExists();
    }   
}

}} // namespace Scaleform::GFx
