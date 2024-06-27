/* ========================================================================================== */
/* FMOD WiiU Specific header file. Copyright (c), Firelight Technologies Pty, Ltd. 2011-2012. */
/* ========================================================================================== */

#ifndef _FMODWIIU_H
#define _FMODWIIU_H

#include "fmod.h"

typedef unsigned int FMOD_WIIU_CONTROLLER;

/*
[DEFINE]
[
    [DESCRIPTION]   
    Pass this to FMOD_WiiU_SetControllerSpeaker to specify which controllers the sound
    should be played out of.

    [REMARKS]
    By default audio will be played out of the TV speakers only.

    [SEE_ALSO]
    FMOD_WiiU_SetControllerSpeaker
    FMOD_WiiU_GetControllerSpeaker
]
*/
#define FMOD_WIIU_CONTROLLER_DEFAULT 0x00000000
#define FMOD_WIIU_CONTROLLER_TV      0x00000001
#define FMOD_WIIU_CONTROLLER_DRC     0x00000002


/*
[ENUM] 
[
    [DESCRIPTION]
    Values for the thread members of the FMOD_WIIU_EXTRADRIVERDATA structure.

    [REMARKS]

    [SEE_ALSO]
    FMOD_WIIU_EXTRADRIVERDATA
]
*/
typedef enum FMOD_THREAD
{
    FMOD_THREAD_DEFAULT,    /* Use FMOD recommended default thread assignment. */
    FMOD_THREAD_CORE0,      /* Thread will be created on Core 0. */
    FMOD_THREAD_CORE1,      /* Thread will be created on Core 1. */
    FMOD_THREAD_CORE2,      /* Thread will be created on Core 2. Default for all threads. */
    FMOD_THREAD_MAX         /* Maximum number of thread options supported. */
} FMOD_THREAD;


/*
[ENUM] 
[
    [DESCRIPTION]
    Preconfigured reverb settings that name environment types.

    [REMARKS]
    You can use these environments instead of filling the members of the property struct for FMOD_WIIU_SetReverbProperties.
    Use FMOD_WIIU_REVERB_ENV_NONE if you want to define the individual properties yourself in the struct.
    Use FMOD_WIIU_REVERB_ENV_OFF if you want to disable the reverb entirely.

    [SEE_ALSO]
    FMOD_WIIU_SetReverbProperties
]
*/
typedef enum FMOD_WIIU_REVERB_ENV
{
    FMOD_WIIU_REVERB_ENV_NONE,
    FMOD_WIIU_REVERB_ENV_OFF,
    FMOD_WIIU_REVERB_ENV_SMALL_ROOM,
    FMOD_WIIU_REVERB_ENV_LARGE_ROOM,
    FMOD_WIIU_REVERB_ENV_HALL,
    FMOD_WIIU_REVERB_ENV_CAVERNOUS_CATHEDRAL,
    FMOD_WIIU_REVERB_ENV_METAL_CORRIDOR
} FMOD_WIIU_REVERB_ENV;


/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Use this structure with System::init to set platform specific initialization settings.
    Pass this structure in as the "extradriverdata" parameter in System::init.

    [REMARKS]
    Set any member to zero for default behavior.

    [SEE_ALSO]      
    System::init
    FMOD_THREAD
]
*/
typedef struct FMOD_WIIU_EXTRADRIVERDATA
{
    FMOD_THREAD threadMixer;       /* [in] FMOD software mixer thread. */
    FMOD_THREAD threadStream;      /* [in] FMOD stream thread. */
    FMOD_THREAD threadNonBlocking; /* [in] FMOD thread for FMOD_NONBLOCKING. */
    FMOD_THREAD threadFile;        /* [in] FMOD file thread. */
    FMOD_THREAD threadGeometry;    /* [in] FMOD geometry processing thread. */
    FMOD_BOOL   enablePL2;         /* [in] Enable Dolby Pro Logic II (surround) encoding for HW voices. */
} FMOD_WIIU_EXTRADRIVERDATA;


/*
[STRUCTURE] 
[
    [DESCRIPTION]   
    Parameters to control the hardware reverb effect.

    [REMARKS]
    Some parameters are undocumented, these will be updated as more details become available.

    [SEE_ALSO]
    FMOD_WIIU_REVERB_ENV
    FMOD_WIIU_SetReverbProperties
    FMOD_WIIU_GetReverbProperties
]
*/
typedef struct FMOD_WIIU_REVERB_PROPERTIES
{
    unsigned int         instance;     /* 0 to 2       - [w]   Control independent reverb effects. */
    FMOD_WIIU_REVERB_ENV environment;  /* See enum     - [r/w] Preconfigured reverb settings, overrides below properties if not set to 'none'. */
    unsigned int         earlyMode;    /* 0 to 4       - [r/w] Early reflection mode (undocumented). */
    unsigned int         lateMode;     /* 0 to 4       - [r/w] Late reverb mode (undocumented and unused). */
    float                preDelayTime; /* 0.0 to 100.0 - [r/w] Delay (in milliseconds) between the dry sound and the first early reflection. */
    float                decayTime;    /* 0.1 to 20.0  - [r/w] Decay time (in seconds) for the late reverb. */
    float                hfDecayRatio; /* 0.1 to 1.0   - [r/w] Ratio of decay time at high frequencies to that at low frequencies. Low value means high frequencies decay more quickly. */
    float                coloration;   /* 0.0 to 1.0   - [r/w] Increasing this makes the reverb more colored and less neutral. High values should sound more natural, lower values sounding unusual. */
    float                earlyGain;    /* 0.0 to 1.0   - [r/w] Gain of the early reflections. */
    float                lateGain;     /* 0.0 to 1.0   - [r/w] Gain of the late reverb. */
    float                reverbGain;   /* 0.0 to 1.0   - [r/w] Overall gain of the reverb. */
} FMOD_WIIU_REVERB_PROPERTIES;


/*
[API]
[
    [DESCRIPTION]
    Sets parameters for the global reverb environment. This function is intended as a platform specific replacement for FMOD_System_SetReverbProperties.

    [PARAMETERS]
    'prop'	    Address of an FMOD_WIIU_REVERB_PROPERTIES structure which defines the attributes for the reverb.

    [REMARKS]
    These reverb properties will only affect FMOD_HARDWARE channels, see System::setReverbProperties for an FMOD_SOFTWARE alternative.
    It is important to specify the 'instance' value in the FMOD_WIIU_REVERB_PROPERTIES structure correctly, otherwise you will get an FMOD_ERR_REVERB_INSTANCE error.

    [SEE_ALSO]
    FMOD_HARDWARE
    FMOD_WIIU_REVERB_PROPERTIES
    FMOD_WiiU_GetReverbProperties
]
*/
FMOD_RESULT F_API FMOD_WiiU_SetReverbProperties(FMOD_SYSTEM *system, const FMOD_WIIU_REVERB_PROPERTIES *prop);


/*
[API]
[
    [DESCRIPTION]
    Retrieves the current reverb environment for the specified reverb instance. This function is intended as a platform specific replacement for FMOD_System_GetReverbProperties.

    [PARAMETERS]
    'prop'	    Address of a variable that receives the current reverb environment description.

    [REMARKS]	
    It is important to specify the 'instance' value in the FMOD_WIIU_REVERB_PROPERTIES structure correctly, otherwise you will get an FMOD_ERR_REVERB_INSTANCE error.

    [SEE_ALSO]
    FMOD_WIIU_REVERB_PROPERTIES
    FMOD_WiiU_SetReverbProperties
]
*/
FMOD_RESULT F_API FMOD_WiiU_GetReverbProperties(FMOD_SYSTEM *system, FMOD_WIIU_REVERB_PROPERTIES *prop);


/*
[API]
[
    [DESCRIPTION]
    Specify which controllers to play this channel on.

    [PARAMETERS]
    'controller'    Controller to output sound to, you can OR multiple FMOD_WIIU_CONTROLLER defines together.

    [REMARKS]	
    Only FMOD_HARDWARE channels can output to alternate locations, FMOD_SOFTWARE will always come out the TV speakers.
    By default audio will be played out of the TV speakers only.
    
    [SEE_ALSO]
    FMOD_WIIU_CONTROLLER
    FMOD_WiiU_GetControllerSpeaker
]
*/
FMOD_RESULT F_API FMOD_WiiU_SetControllerSpeaker(FMOD_CHANNEL *channel, FMOD_WIIU_CONTROLLER controller);


/*
[API]
[
    [DESCRIPTION]
    Get which destination the channel will be played on, the default is the TV speakers.

    [PARAMETERS]
    'controller'    Controller to output sound to, can be multiple FMOD_WIIU_CONTROLLER defines ORed together.

    [REMARKS]	

    [SEE_ALSO]
    FMOD_WIIU_CONTROLLER
    FMOD_WiiU_SetControllerSpeaker
]
*/
FMOD_RESULT F_API FMOD_WiiU_GetControllerSpeaker(FMOD_CHANNEL *channel, FMOD_WIIU_CONTROLLER *controller);

#endif  /* _FMODWIIU_H */
