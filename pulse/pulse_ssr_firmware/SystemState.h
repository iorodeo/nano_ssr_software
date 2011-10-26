#ifndef SystemState_h
#define SystemState_h
#include "constants.h"

class SystemState {
    public:
        SystemState();
        void initialize();
        void start(unsigned int n);
        void stop(unsigned int n);
        void startAll();
        void stopAll();
        void setNumPulse(unsigned int n, unsigned long value);
        void setPeriod(unsigned int n, unsigned long value);
        unsigned long getNumPulse(unsigned int n);
        unsigned long getPeriod(unsigned int n);
        unsigned long getPulseCnt(unsigned int n);
        unsigned long getRunning(unsigned int n);
        void timerUpdate();

    private:
        bool running[numSSR];
        unsigned long numPulse[numSSR];
        unsigned long period[numSSR];
        unsigned long pulseCnt[numSSR];
        unsigned long timerCnt[numSSR];
        void incrPulseCnt(unsigned int n);
};

typedef void (SystemState::*setPinFunc)(unsigned int); 
typedef void (SystemState::*setValueFunc)(unsigned int, unsigned long);
typedef unsigned long (SystemState::*getValueFunc)(unsigned int);

#endif
