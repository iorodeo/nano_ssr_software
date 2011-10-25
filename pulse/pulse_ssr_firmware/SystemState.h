#ifndef SystemState_h
#define SystemState_h

const unsigned int defaultNumPulse = 5;
const unsigned int defaultPeriod = 1000;
const unsigned int defaultPowerLevel = 100;

class SystemState {
    public:
        SystemState();
        void start();
        void stop();
        void setNumPulse(unsigned int value);
        void setPeriod(unsigned int value);
        void setPowerLevel(unsigned int value);
        unsigned int getNumPulse();
        unsigned int getPeriod();
        unsigned int getPowerLevel();
        unsigned int getPulseCnt();
        void incrPulseCnt();

    private:
        bool running;
        unsigned int numPulse;
        unsigned int period;
        unsigned int powerLevel;
        unsigned int pulseCnt;
};

typedef void (SystemState::*SystemStateSetFunc)(unsigned int);

#endif
