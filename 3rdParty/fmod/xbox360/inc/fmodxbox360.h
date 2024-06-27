#ifndef _FMODXBOX360_H
#define _FMODXBOX360_H

/*
[ENUM] 
[
    [NAME] 
    FMOD_THREAD

    [DESCRIPTION]
    Values for the thread_ members of the FMOD_360_EXTRADRIVERDATA structure.

    [REMARKS]

    [PLATFORMS]
    Xbox360

    [SEE_ALSO]
    FMOD_360_EXTRADRIVERDATA
]
*/
typedef enum
{
    FMOD_THREAD_DEFAULT,       /* Use FMOD recommended default thread assignment. */
    FMOD_THREAD_CORE0THREAD0,  /* Thread will be created on HW Thread 0 of Core 0 */
    FMOD_THREAD_CORE0THREAD1,  /* Thread will be created on HW Thread 1 of Core 0 */
    FMOD_THREAD_CORE1THREAD0,  /* Thread will be created on HW Thread 0 of Core 1 */
    FMOD_THREAD_CORE1THREAD1,  /* Thread will be created on HW Thread 1 of Core 1 */
    FMOD_THREAD_CORE2THREAD0,  /* Thread will be created on HW Thread 0 of Core 2. Default for all threads (except recording) */
    FMOD_THREAD_CORE2THREAD1,  /* Thread will be created on HW Thread 1 of Core 2. Default for recording thread */
    
    FMOD_THREAD_MAX            /* Maximum number of thread options supported. */
} FMOD_THREAD;


/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Use this structure with System::init to set which processor(s) FMOD will create its
    threads on.
    Pass this structure in as the "extradriverdata" parameter in System::init.

    [REMARKS]

    [PLATFORMS]
    Xbox360

    [SEE_ALSO]      
    FMOD_THREAD
    System::init
]
*/
typedef struct FMOD_360_EXTRADRIVERDATA
{
    FMOD_THREAD thread_mixer;       /* [in] FMOD software mixer thread.  Optional, ie 0 or FMOD_THREAD_DEFAULT = default behaviour */
    FMOD_THREAD thread_stream;      /* [in] FMOD stream thread.  Optional, ie 0 or FMOD_THREAD_DEFAULT = default behaviour */
    FMOD_THREAD thread_nonblocking; /* [in] FMOD thread for FMOD_NONBLOCKING.  Optional, ie 0 or FMOD_THREAD_DEFAULT = default behaviour */
    FMOD_THREAD thread_file;        /* [in] FMOD file thread.  Optional, ie 0 or FMOD_THREAD_DEFAULT = default behaviour */
    FMOD_THREAD thread_xaudio;      /* [in] Thread XAudio runs on.  Optional, ie 0 or FMOD_THREAD_DEFAULT = default behaviour */
    FMOD_THREAD thread_geometry;    /* [in] FMOD geometry processing thread.  Optional, ie 0 or FMOD_THREAD_DEFAULT = default behaviour */
    FMOD_THREAD thread_recording;   /* [in] FMOD recording thread.  Optional, ie 0 or FMOD_THREAD_DEFAULT = default behaviour */
    void       *xaudio2instance;    /* [in] Instance of already initialized Xaudio2.  Optional.  0 = let FMOD initialize XAudio2. */
} FMOD_360_EXTRADRIVERDATA;

#endif