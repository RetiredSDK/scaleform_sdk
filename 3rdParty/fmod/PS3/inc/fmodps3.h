/* ========================================================================================= */
/* FMOD PS3 Specific header file. Copyright (c), Firelight Technologies Pty, Ltd. 2005-2011. */
/* ========================================================================================= */

#ifndef _FMODPS3_H
#define _FMODPS3_H

#ifndef SPU

#include <sysutil/sysutil_sysparam.h>

#include "fmod.h"

/*
[ENUM]
[
    [DESCRIPTION]
    This sets whether the FMOD SPURS Task will be created with or without 256k context memory.
    This will determine whether or not the SPURS Task is able to swap out with other tasks
    or not.

    [REMARKS]

    [PLATFORMS]
    PS3

    [SEE_ALSO]      
]
*/
typedef enum
{
    FMOD_PS3_SPURSMODE_NOCONTEXT,       /* SPURS Task is created with no context memory. (Default) */
    FMOD_PS3_SPURSMODE_CREATECONTEXT,   /* SPURS Task is created with 256k context memory, hence is shareable with other tasks */
    FMOD_PS3_SPURSMODE_TWOTASKS,        /* Stream decoder and Mixer are split into 2 SPURS Tasks, or 2 SPU Threads. Tasks created with total of 512kb context memory, hence are shareable with other tasks */

    FMOD_PS3_SPURSMODE_FORCEINT = 65536 /* Makes sure this enum is signed 32bit. */
} FMOD_PS3_SPURSMODE;


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Use this structure with System::init to set the information required for ps3
    initialisation.

    Pass this structure in as the "extradriverdata" parameter in System::init.

    [REMARKS]
    libaudio_latency - When this value is set to 7, latency will be about 40ms from when a
                       playsound command is issued to when you hear it, when the output mode is
                       PCM.
                       When this value is set to 0, latency will be about 90ms with PCM output.
                       When using Dolby Digital output, it will add about 55ms latency to the
                       output.  When using DTS output, it will add about 40ms latency to the output.

    fios_scheduler   - FMOD will use this pointer to cell::fios::scheduler to make FIOS calls.
                       File reads and seeks for streaming files will use the following op attributes:
                        
                        opattr.deadline = kDEADLINE_NOW;
                        opattr.priority = cell::fios::kPRIO_MAX;

                       All other file operations including reads/seeks for non-streaming files use the
                       following op attritubes:

                        opattr.deadline = kDEADLINE_ASAP;
                        opattr.priority = cell::fios::kPRIO_DEFAULT;

    [PLATFORMS]
    PS3

    [SEE_ALSO]
    System::init
]
*/
typedef struct FMOD_PS3_EXTRADRIVERDATA
{
    int                 spu_thread_priority;            /* SPU thread priority of the FMOD SPU Thread.      (highest: 16, lowest: 255, default: 16).  Ignored if using SPURS. */
    int                 spu_thread_priority_streamer;   /* SPU thread priority of the FMOD SPUMPEG decoder. (highest: 16, lowest: 255, default: 200). Ignored if FMOD_PS3_SPURSMODE_TWOTASKS isn't specified. Ignored if using SPURS. */
    
    void               *spurs;                          /* Pointer to SPURS instance. (Set this to NULL if not using SPURS) */
    FMOD_PS3_SPURSMODE  spursmode;                      /* SPURS mode, whether or not to create Task with context memory. (Default:  FMOD_PS3_SPURSMODE_NOCONTEXT) */
    uint8_t            *spurs_taskset_priorities;       /* Pointer to array of 8 SPU priorities, passed internally to cellSpursCreateTaskset. Please refer to the SPURS documentation for explanation. (Set this to 0 to use default of {1, 1, 1, 1, 1, 1, 1, 1} )*/

    void               *rsx_pool;                       /* Pointer to start of RSX memory pool */
    unsigned int        rsx_pool_size;                  /* Size of RSX memory pool to use */
    FMOD_BOOL           rsx_pool_manager_in_mram;       /* Overhead for RSX pool memory manager in Main RAM. Use this to increase allocation/deallocation speed of RSX blocks in FMOD.
                                                           This MRAM overhead is equal to rsx_pool_size / 128 bytes. (Default: false) */
    int                 libaudio_latency;               /* Controls mixing latency. Value from 0 (safest, largest latency) to 7 (stutters at high DSP load, lowest latency). (Default: 0) */

    void               *fios_scheduler;                 /* Pointer to fios scheduler object. Set this to NULL if you do not wish to use FIOS. */

    CellAudioOutConfiguration *cell_audio_config;       /* Pass in a pointer to a CellAudioOutConfiguration and it will be filled out with the settings FMOD used to configure cellAudio.  */
    FMOD_BOOL                  cell_audio_initialized;  /* Set this to true if you have initialized libAudio yourself. You must then pass in a Cell Audio port number to 'cell_audio_port'below.
                                                           If this is set to true, FMOD will do no libAudio initialization at all. Because libAudio has been initialized outside of FMOD, 
                                                           FMOD_INIT_PS3_PREFERDTS and FMOD_INIT_PS3_FORCE2CHLPCM will have no effect. */
    unsigned int               cell_audio_port;         /* Pass in audio port number from cellAudioPortOpen, if 'cell_audio_initialized' is set to true. */

    int (*spu_runjob_cb)(int arg1, int arg2, 
        int arg3, int arg4);                            /* Pointer to external function for launching SPU mix/decode jobs. */
} FMOD_PS3_EXTRADRIVERDATA;

/*
[ENUM]
[
    [DESCRIPTION]
    These constants describe the amount of stack needed on the SPU

    [REMARKS]
    Some external job systems may require explicit setting of the amount of stack required
    for a SPU job. These values can be used.

    [PLATFORMS]
    PS3

    [SEE_ALSO]      
]
*/
typedef enum
{
    FMOD_SPU_STACKSIZE_VORBIS       = 24000,
    FMOD_SPU_STACKSIZE_MP3          = 24300,
    FMOD_SPU_STACKSIZE_CELT         = 40000,    
} FMOD_SPU_STACKSIZES;


#else
/* Entry point to FMOD code when using external job system to control SPU mix/decode jobs. */
extern "C" int FMODSPUmain(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4 );
#endif

#endif
