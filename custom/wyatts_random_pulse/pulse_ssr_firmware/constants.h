#ifndef Constants_h
#define Constants_h

// Constants
const unsigned long baudrate = 9600;
const uint8_t numSSR = 8;
const uint8_t ssrPin[numSSR] = {2,3,4,5,6,7,8,9};
const unsigned long timerPeriod_us = 1000; 

const unsigned int defaultNumberOfEvents = 1440;
const unsigned int defaultEventPeriod_ms = 60000; 

const unsigned int defaultNumberOfRandomPulse = 4;
const unsigned int maxNumberOfRandomPulse = 10;
const unsigned int defaultRandomPulseDuration = 5000;
const unsigned int minRandomPulseSeparation = 1000;


// Serial command ids
typedef enum {
    cmdStop,                // 0 
    cmdStart,               // 1
    cmdStartAll,            // 2
    cmdStopAll,             // 3
    cmdSetEventPeriod,      // 4
    cmdGetEventPeriod,      // 5
    cmdSetNumberOfEvents,   // 6
    cmdGetNumberOfEvents,   // 7
    cmdGetRunning,          // 8
} CmdIdentifier;

#endif
