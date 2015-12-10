#ifndef SystemState_h
#define SystemState_h
#include "constants.h"

#include "Streaming.h"
#include <stdlib.h>

class SystemState {
    public:
        SystemState();
        void initialize();
        void start(unsigned int n);
        void stop(unsigned int n);
        void startAll();
        void stopAll();
        void setNumberOfEvents(unsigned int n, unsigned long value);
        void setEventPeriod(unsigned int n, unsigned long value);
        unsigned long getNumberOfEvents(unsigned int n);
        unsigned long getEventPeriod(unsigned int n);
        unsigned long getEventCnt(unsigned int n);
        unsigned long getRunning(unsigned int n);
        void timerUpdate();

    protected:
        bool running[numSSR];
        unsigned long numberOfEvents[numSSR];
        unsigned long eventPeriod[numSSR];

        unsigned long numberOfRandomPulse[numSSR];
        unsigned long randomPulseDuration[numSSR]; 

        unsigned long timerCnt[numSSR];
        unsigned long eventCnt[numSSR];
        unsigned long randomPulseCnt[numSSR];
        unsigned long randomPulseStart[numSSR][maxNumberOfRandomPulse];

        void incrEventCnt(unsigned int n);
        void incrRandomPulseCnt(unsigned int n);
        void generateRandomPulseStart(unsigned int n);

};

typedef void (SystemState::*setPinFunc)(unsigned int); 
typedef void (SystemState::*setValueFunc)(unsigned int, unsigned long);
typedef unsigned long (SystemState::*getValueFunc)(unsigned int);

#endif 

