/*
    PsychtoolboxGL/Source/Common/PsychHID/PsychHIDKbQueueCheck.c

    PROJECTS:

        PsychHID only.

    PLATFORMS:

        All.

    AUTHORS:

        rwoods@ucla.edu        rpw
        mario.kleiner@tuebingen.mpg.de      mk

    HISTORY:
        8/19/07  rpw        Created.
        8/23/07  rpw        Added PsychHIDQueueFlush to documentation; removed call to PsychHIDVerifyInit()

*/

#include "PsychHID.h"

PsychError PSYCHHIDKbQueueCheck(void)
{
    static char useString[] = "[keyIsDown, firstKeyPressTimes, firstKeyReleaseTimes, lastKeyPressTimes, lastKeyReleaseTimes]=PsychHID('KbQueueCheck' [, deviceIndex])";
    static char synopsisString[] =
        "Checks a queue for keyboard or button events generated by a device.\n"
        "PsychHID('KbQueueCreate') must be called before this routine "
        "and PsychHID('KbQueueStart') must then be called for any events "
        "to be returned.\n"
        "The optional 'deviceIndex' is the index of the HID input device whose queue should be checked. "
        "If omitted, the queue of the default device will be checked.\n";

    static char seeAlsoString[] = "KbQueueCreate, KbQueueStart, KbQueueStop, KbQueueFlush, KbQueueRelease";

    int deviceIndex;

    PsychPushHelp(useString, synopsisString, seeAlsoString);
    if (PsychIsGiveHelp()) {PsychGiveHelp(); return(PsychError_none);};

    PsychErrorExit(PsychCapNumOutputArgs(5));
    PsychErrorExit(PsychCapNumInputArgs(1));

    deviceIndex = -1;
    PsychCopyInIntegerArg(1, kPsychArgOptional, &deviceIndex);

    PsychHIDOSKbQueueCheck(deviceIndex);

    return(PsychError_none);
}

PsychError PSYCHHIDKbQueueGetEvent(void)
{
    static char useString[] = "[event, navail] = PsychHID('KbQueueGetEvent' [, deviceIndex][, maxWaitTimeSecs=0])";
    static char synopsisString[] =
        "Checks a queue for keyboard or button events generated by a device.\n"
        "If there are any events queued, the oldest one is returned in the struct "
        "'event', otherwise an empty matrix is returned. The number of queued events "
        "remaining in the queue after fetching is returned in 'navail'.\n"
        "'maxWaitTimeSecs' is an optional maximum wait time for a new event in seconds. "
        "It defaults to zero, which means to just poll for a pending event. A positive value "
        "will wait until either at least one event arrived or the given amount of time elapses, "
        "whatever comes first.\n"
        "The returned event struct, if any, currently contains the following fields:\n"
        "'Keycode' = The KbCheck / KbName style keycode of the key or button that triggered this event.\n"
        "'Time' = The GetSecs time of when the event was received.\n"
        "'Pressed' = 1 for a key press event, 0 for a key release event.\n"
        "'CookedKey' = Keycode translated into a GetChar() style ASCII character code. Or zero if key "
        "does not have a corresponding character. Or -1 if mapping is unsupported for given event.\n\n"
        "PsychHID('KbQueueCreate') must be called before this routine and PsychHID('KbQueueStart') "
        "must then be called for any events to get recorded into the event buffer.\n"
        "The optional 'deviceIndex' is the index of the HID input device whose queue should be queried. "
        "If omitted, the queue of the default device will be queried.\n";

    static char seeAlsoString[] = "KbQueueCreate, KbQueueStart, KbQueueStop, KbQueueFlush, KbQueueRelease";

    int deviceIndex;
    unsigned int navail;
    double maxWaitTimeSecs;

    PsychPushHelp(useString, synopsisString, seeAlsoString);
    if (PsychIsGiveHelp()) {PsychGiveHelp(); return(PsychError_none);};

    PsychErrorExit(PsychCapNumOutputArgs(2));
    PsychErrorExit(PsychCapNumInputArgs(2));

    deviceIndex = -1;
    PsychCopyInIntegerArg(1, kPsychArgOptional, &deviceIndex);

    maxWaitTimeSecs = 0;
    PsychCopyInDoubleArg(2, kPsychArgOptional, &maxWaitTimeSecs);

    // Get next event from buffer, return it as 1st return argument:
    navail = PsychHIDReturnEventFromEventBuffer(deviceIndex, 1, maxWaitTimeSecs);
    PsychCopyOutDoubleArg(2, FALSE, (double)navail);

    return(PsychError_none);
}
