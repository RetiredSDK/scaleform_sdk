/**************************************************************************

Filename    :   Render_Stats.cpp
Content     :   Rendering statistics declarations
Created     :   April 27, 2010
Authors     :   Michael Antonov

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "Render_Stats.h"
#include "Render/Render_HAL.h"
#include "Kernel/SF_Alg.h"
#include "Kernel/SF_Random.h"

namespace Scaleform {

// ***** Renderer Stat Constants

// GRenderer Memory.
SF_DECLARE_MEMORY_STAT_AUTOSUM_GROUP(StatRender_Mem,    "Renderer", Stat_Mem)

SF_DECLARE_MEMORY_STAT(StatRender_Buffers_Mem,      "Buffers", StatRender_Mem)
SF_DECLARE_MEMORY_STAT(StatRender_RenderBatch_Mem,  "RenderBatch", StatRender_Mem)
SF_DECLARE_MEMORY_STAT(StatRender_Primitive_Mem,    "Primitive", StatRender_Mem)
SF_DECLARE_MEMORY_STAT(StatRender_Fill_Mem,         "Fill", StatRender_Mem)
SF_DECLARE_MEMORY_STAT(StatRender_Mesh_Mem,         "Mesh", StatRender_Mem)
SF_DECLARE_MEMORY_STAT(StatRender_MeshBatch_Mem,    "MeshBatch", StatRender_Mem)
SF_DECLARE_MEMORY_STAT(StatRender_Context_Mem,      "Context", StatRender_Mem)
SF_DECLARE_MEMORY_STAT(StatRender_NodeData_Mem,     "NodeData", StatRender_Mem)
SF_DECLARE_MEMORY_STAT(StatRender_TreeCache_Mem,    "TreeCache", StatRender_Mem)
SF_DECLARE_MEMORY_STAT(StatRender_TextureManager_Mem, "TextureManager", StatRender_Mem)
SF_DECLARE_MEMORY_STAT(StatRender_MatrixPool_Mem,    "MatrixPool", StatRender_Mem)
SF_DECLARE_MEMORY_STAT(StatRender_MatrixPoolHandle_Mem, "MatrixPoolHandles", StatRender_Mem)
SF_DECLARE_MEMORY_STAT(StatRender_Text_Mem,          "Text", StatRender_Mem)
SF_DECLARE_MEMORY_STAT(StatRender_Font_Mem,          "Font", StatRender_Mem)

void Link_RenderStats()
{
}


#ifdef SF_RENDERER_PROFILE

namespace Render {

Color ProfileViews::GetColorForBatch(UPInt base, unsigned index) const
{
    UPInt key = base ^ (base << 4) ^ index;
    float hue = (key & 0x3FF) / 1023.f;

    // PPS: For analyzing covariance
    // printf("%f,\t%f,\t%lu,\t%u\n", key / (float)(((UInt64)0x1 << (sizeof(key) * 8)) - 1), hue, base, index);

    Color batchColor;
    batchColor.SetHSV(hue, 0.8f, 0.9f);
    batchColor.SetAlpha(192);

    return batchColor;
}

void ProfileViews::SetProfileViews(UInt64 modes)
{
    DisableProfileViews();

    // Apply flags, then strip them off.
    UInt64 flags = modes>>Channel_Flags;
    NoFilterCaching = ( flags & ProfileFlag_NoFilterCaching ) != 0;
    UInt64 flagMask = 0xFFFF;
    flagMask <<= Channel_Flags;
    modes &= ~flagMask;
    if ( !modes )
        return;

    for (int i = 0; i < 4; i++)
    {
        memset(FillCxforms[i].M, 0, sizeof(FillCxforms[i].M));
        FillCxforms[i].M[1][3] = 255;
    }

    OverrideMasks = 1;

    for (int i = 0; i < 3; i++)
    {
        UInt64 mode = modes >> (i << 4);
        if (mode & Profile_Fill)
        {
            FillCxforms[0].M[1][i] += ((mode & 0xff) * (1.f/255.f));
            FillCxforms[3].M[1][i] += ((mode & 0xff) * (1.f/255.f));
            FillMode = 1;
        }
        if (mode & Profile_Mask)
        {
            FillCxforms[1].M[1][i] += ((mode & 0xff) * (1.f/255.f));
            FillMode = 1;
        }
        if (mode & Profile_Filter)
        {
            FillCxforms[2].M[1][i] += ((mode & 0xff) * (1.f/255.f));
            FillMode = 1;
        }
        if (mode & Profile_Blend)
        {
            FillCxforms[3].M[1][i] += ((mode & 0xff) * (1.f/255.f));
            FillMode = 1;
        }

        if (mode & Profile_Batch)
            BatchMode |= (1 << i) | 8;
    }

    if (FillMode)
        OverrideBlend = Blend_Add;
}
}
#endif

} // Scaleform

