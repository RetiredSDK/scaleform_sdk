/* ========================================================================================= */
/* FMOD Wii Specific header file. Copyright (c), Firelight Technologies Pty, Ltd. 2006-2009. */
/* ========================================================================================= */

#ifndef _FMODWII_H
#define _FMODWII_H

#include "fmod.h"

typedef unsigned int FMOD_WII_CONTROLLER;


/*
[DEFINE]
[
    [NAME]
    FMOD_NMIC_BUFFERLENGTH_MS

    [DESCRIPTION]
    NMICOpenParam.bufferMilliseconds must be set to this
    when initializing NMIC.

    [REMARKS]

    [PLATFORMS]
    Wii

    [SEE_ALSO]
*/
#define FMOD_NMIC_BUFFERLENGTH_MS 50


/*
[DEFINE]
[
    [NAME]
    FMOD_WII_CONTROLLER

    [DESCRIPTION]   
    Pass this to FMOD_Channel_SetControllerSpeaker to specify which controller(s) the sound
    should be played out of.

    Or on FMOD_WII_CONTROLLER_AND_SPEAKERS to play the sound out of the normal speakers, as
    well as the controller.

    [REMARKS]

    [PLATFORMS]
    Wii

    [SEE_ALSO]
    FMOD_Channel_SetControllerSpeaker
    FMOD_Channel_GetControllerSpeaker
]
*/
#define FMOD_WII_CONTROLLER_0               0x00000001
#define FMOD_WII_CONTROLLER_1               0x00000002
#define FMOD_WII_CONTROLLER_2               0x00000004
#define FMOD_WII_CONTROLLER_3               0x00000008
#define FMOD_WII_CONTROLLER_AND_SPEAKERS    0x00000010
#define FMOD_WII_CONTROLLER_NONE            0x00000000


/*
[ENUM]
[
    [DESCRIPTION]   

    [REMARKS]

    [PLATFORMS]

    [SEE_ALSO]
    FMOD_Wii_Controller_Command
]
*/
typedef enum
{
    FMOD_WII_CONTROLLER_CMD_SPEAKER_ON,    /* Turn on controller speaker  */
    FMOD_WII_CONTROLLER_CMD_SPEAKER_OFF,   /* Turn off controller speaker */
    FMOD_WII_CONTROLLER_CMD_SPEAKER_MUTE,  /* Mute controller speaker */
    FMOD_WII_CONTROLLER_CMD_SPEAKER_UNMUTE /* Unmute controller speaker */
} FMOD_WII_CONTROLLER_CMD;


/*
[STRUCTURE] 
[
    [DESCRIPTION]
    Pass this structure in as the "extradriverdata" parameter in System::init.

    [REMARKS]
    If this structure is not used, FMOD will default to DVD read priority 1.
    If this structure is not used, FMOD will default to always having the
    remote speaker unmuted.

    [PLATFORMS]
    Wii

    [SEE_ALSO]
    System::init
]
*/
typedef struct FMOD_WII_INFO
{
    int         dvdreadpriority;            /* DVD read priority (highest: 0, lowest: 3, default: 1) */
    int         muteremotespeakerifnosound; /* Mute remote speaker when no sounds are playing. */
    FMOD_BOOL   audiolibsinitialized;       /* Set this to TRUE if audio libraries (AI, AX, MIX) have
                                               already been initialised. This will stop FMOD initialising
                                               them. (default: FALSE) */
    FMOD_BOOL   nmicrecording;              /* Set this to TRUE to record using NMIC. Set to FALSE for
                                               WiiSpeak recording with PMIC. (default: FALSE) */
} FMOD_WII_INFO;


#ifdef __cplusplus
extern "C" 
{
#endif

/*
[
	[DESCRIPTION]


	[PARAMETERS]
    'channel'   - Pointer to the channel that lowpass filtering should be applied to.
    'cutoff'    - Cutoff frequency of the lowpass filter. Must be within the range 0 - 16,000.
                  Set to -1 to disable filter.

	[RETURN_VALUE]
    FMOD_OK

	[REMARKS]

    [PLATFORMS]
    Wii

	[SEE_ALSO]
]
*/
FMOD_RESULT F_API FMOD_Channel_SetLowPassFilter(FMOD_CHANNEL *channel, int cutoff);


/*
[
	[DESCRIPTION]

	[PARAMETERS]
    'channel'   - Pointer to the channel that lowpass filtering should be applied to.
    'cutoff'    - Pointer to retrieve cutoff frequency of the lowpass filter.
                  -1 indicates filter is inactive.

	[RETURN_VALUE]
    FMOD_OK

	[REMARKS]

    [PLATFORMS]
    Wii

	[SEE_ALSO]
]
*/
FMOD_RESULT F_API FMOD_Channel_GetLowPassFilter(FMOD_CHANNEL *channel, int *cutoff);


/*
[
	[DESCRIPTION]

	[PARAMETERS]
    'channel'   - Pointer to the channel that biquad filtering should be applied to.
    'active'    - Set filter active / inactive.
    'b0'        - Filter coefficient.
    'b1'        - Filter coefficient.
    'b2'        - Filter coefficient.
    'a1'        - Filter coefficient.
    'a2'        - Filter coefficient.

	[RETURN_VALUE]
    FMOD_OK

	[REMARKS]
    For more information on the filter coefficients, please refer to _AXPBBIQUAD
    section of the Revolution Function Reference Manual.

    [PLATFORMS]
    Wii

	[SEE_ALSO]
]
*/
FMOD_RESULT F_API FMOD_Channel_SetBiquadFilter(FMOD_CHANNEL *channel, FMOD_BOOL active, unsigned short b0, unsigned short b1, unsigned short b2, unsigned short a1, unsigned short a2);


/*
[
	[DESCRIPTION]

	[PARAMETERS]
    'channel'   - Pointer to the channel that biquad filtering should be applied to.
    'active'    - Pointer to retrieve whether or not filter is active.
    'b0'        - Pointer to retreive filter coefficient.
    'b1'        - Pointer to retreive filter coefficient.
    'b2'        - Pointer to retreive filter coefficient.
    'a1'        - Pointer to retreive filter coefficient.
    'a2'        - Pointer to retreive filter coefficient.

	[RETURN_VALUE]
    FMOD_OK

	[REMARKS]
    For more information on the filter coefficients, please refer to _AXPBBIQUAD
    section of the Revolution Function Reference Manual.

    [PLATFORMS]
    Wii

	[SEE_ALSO]
]
*/
FMOD_RESULT F_API FMOD_Channel_GetBiquadFilter(FMOD_CHANNEL *channel, FMOD_BOOL *active, unsigned short *b0, unsigned short *b1, unsigned short *b2, unsigned short *a1, unsigned short *a2);


/*
[
	[DESCRIPTION]
    Set channel to play out of specified FMOD_WII_CONTROLLER(s).

	[PARAMETERS]
    'channel'           - Pointer to channel.
    'controller'        - Controller(s) which channel should play out of.
                          Set to FMOD_WII_CONTROLLER_NONE to play out of regular speakers.

	[RETURN_VALUE]
    FMOD_OK

	[REMARKS]

    [PLATFORMS]
    Wii

	[SEE_ALSO]
]
*/
FMOD_RESULT F_API FMOD_Channel_SetControllerSpeaker(FMOD_CHANNEL *channel, FMOD_WII_CONTROLLER controller);


/*
[
	[DESCRIPTION]
    Set specific sub-channel of FMOD channel to play out of specified FMOD_WII_CONTROLLER(s).

	[PARAMETERS]
    'channel'           - Pointer to channel.
    'controller'        - Controller(s) which channel should play out of.
                          Set to FMOD_WII_CONTROLLER_NONE to play out of regular speakers.
    'subchannel'        - Specify which sub-channel should play out of the controller.
                          A mono sound would have 1 sub-channel (0). A stereo sound would
                          have 2 sub-channels (0, 1).
                          Specify '-1' to choose all sub-channels.

	[RETURN_VALUE]
    FMOD_OK

	[REMARKS]

    [PLATFORMS]
    Wii

	[SEE_ALSO]
]
*/
FMOD_RESULT F_API FMOD_Channel_SetControllerSpeakerSubchannel(FMOD_CHANNEL *channel, FMOD_WII_CONTROLLER controller, int subchannel);


/*
[
	[DESCRIPTION]
    Get FMOD_WII_CONTROLLER(s) currently playing channel.

	[PARAMETERS]
    'channel'           - Pointer to channel.
    'controller'        - Pointer to FMOD_WII_CONTROLLER.

	[RETURN_VALUE]
    FMOD_OK

	[REMARKS]

    [PLATFORMS]
    Wii

	[SEE_ALSO]
]
*/
FMOD_RESULT F_API FMOD_Channel_GetControllerSpeaker(FMOD_CHANNEL *channel, FMOD_WII_CONTROLLER *controller);


/*
[
	[DESCRIPTION]
    Wii controller connect function. Call this function from your WPAD connect callback function.

    [PARAMETERS]

	[RETURN_VALUE]
    FMOD_OK

	[REMARKS]

    [PLATFORMS]
    Wii

	[SEE_ALSO]
]
*/
FMOD_RESULT F_API FMOD_Wii_Controller_Command(int chan, FMOD_WII_CONTROLLER_CMD command);


/*
[
	[DESCRIPTION]
    Returns the dvd status DVDGetDriveStatus() reported to the FMOD file system.

    [PARAMETERS]

	[RETURN_VALUE]
    Return values as described in RVL DVDGetDriveStatus() documentation.

	[REMARKS]

    [PLATFORMS]
    Wii

	[SEE_ALSO]
]
*/
int FMOD_Wii_GetDriveStatus();


/*
[
	[DESCRIPTION]
    Returns the last error returned to FMOD from NMIC.

    [PARAMETERS]

	[RETURN_VALUE]
    NMICErr values.

	[REMARKS]

    [PLATFORMS]
    Wii

	[SEE_ALSO]
]
*/
int FMOD_Wii_NMIC_GetLastError();

#ifdef __cplusplus
}
#endif

#endif
