/**************************************************************************

Filename    :   SF_System.cpp
Content     :   General kernel initalization/cleanup, including that
                of the memory allocator.
Created     :   Ferbruary 5, 2009
Authors     :   Michael Antonov

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "SF_System.h"
#include "SF_Threads.h"
#include "SF_Debug.h"
#include "SF_Timer.h"
#include "SF_SysFile.h"
#ifdef SF_AMP_SERVER
    #include "GFx/AMP/Amp_Server.h"
#endif

namespace Scaleform {

// *****  GFxSystem Implementation

static SysAllocBase*   System_pSysAlloc = 0;
bool                   System::HasMemoryLeaks = false;

// Initializes GFxSystem core, setting the global heap that is needed for GFx
// memory allocations.
void System::Init(const MemoryHeap::HeapDesc& rootHeapDesc, SysAllocBase* psysAlloc)
{
    SF_DEBUG_WARNING((System_pSysAlloc != 0), "System::Init failed - duplicate call.");

    if (!System_pSysAlloc)
    {
        Timer::initializeTimerSystem();

        bool initSuccess = psysAlloc->initHeapEngine(&rootHeapDesc);
        SF_ASSERT(initSuccess);
        SF_UNUSED(initSuccess);

        System_pSysAlloc = psysAlloc;

#ifdef SF_OS_WIIU
        SysFile::initializeSysFileSystem();
#endif
    }
}

void System::Destroy()
{
    SF_DEBUG_WARNING(!System_pSysAlloc, "System::Destroy failed - System not initialized.");
    if (System_pSysAlloc)
    {
        // Wait for all threads to finish; this must be done so that memory
        // allocator and all destructors finalize correctly.
#ifdef SF_ENABLE_THREADS
        Thread::FinishAllThreads();
#endif

#ifdef SF_OS_WIIU
        SysFile::shutdownSysFileSystem();
#endif

        // Shutdown heap and destroy SysAlloc singleton, if any.
        // Report leaks *after* AMP has been uninitialized.
        // shutdownHeapEngine() will report leaks so there is no need to do it explicitly.
        HasMemoryLeaks = !System_pSysAlloc->shutdownHeapEngine();
        System_pSysAlloc = 0;
        SF_ASSERT(Memory::GetGlobalHeap() == 0);

        Timer::shutdownTimerSystem();
    }

}

} // Scaleform

