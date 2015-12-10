#ifndef Constants_h
#define Constants_h

// Constants
const unsigned long baudrate = 9600;
const uint8_t numSSR = 8;
const uint8_t ssrPin[numSSR] = {2,3,4,5,6,7,8,9};
const unsigned long timerPeriod_us = 1000; 

const unsigned int defaultNumPulse = 5;
const unsigned int defaultPeriod_ms = 1000; 

// Serial command ids
typedef enum {
    cmdStop,           // 0 
    cmdStart,          // 1
    cmdStartAll,       // 2
    cmdStopAll,        // 3
    cmdSetPeriod,      // 4
    cmdGetPeriod,      // 5
    cmdSetNumPulse,    // 6
    cmdGetNumPulse,    // 7
    cmdGetRunning,     // 8
} CmdIdentifier;

#endif
