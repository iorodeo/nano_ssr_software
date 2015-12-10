#include <util/atomic.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "TimerOne.h"
#include "SystemState.h"


int compareULong(const void *x_, const void *y_);


SystemState::SystemState() {
    for (int i=0; i<numSSR; i++) {
        numberOfEvents[i] = defaultNumberOfEvents;
        eventPeriod[i] = defaultEventPeriod_ms;
        numberOfRandomPulse[i] = defaultNumberOfRandomPulse;
        randomPulseDuration[i] = defaultRandomPulseDuration;
        running[i] = false;
        eventCnt[i] = 0;
        timerCnt[i] = 0;
        randomPulseCnt[i] = 0;
        unsigned long startPos = 0;
        for (int j=0; j<maxNumberOfRandomPulse;j++)
        {
            randomPulseStart[i][j] = startPos;
            startPos += defaultRandomPulseDuration + 10; 
        }
    }
}

void SystemState::initialize() {
    // Set SSR IO pins to output and set to low
    for (uint8_t i=0; i<numSSR; i++) {
        pinMode(ssrPin[i], OUTPUT);
        digitalWrite(ssrPin[i],LOW);
    }
    randomSeed(analogRead(A0));
}

void SystemState::start(unsigned int n) {
    // Start events on channel n
    if (n < numSSR) {

        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            running[n] = false;
        }

        generateRandomPulseStart(n);

        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            eventCnt[n] = 0;
            timerCnt[n] = 0;
            randomPulseCnt[n] = 0;
            running[n] = true;
        } 
    }
}

void SystemState::stop(unsigned int n) {
    // Stop events on channel n
    if (n < numSSR) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            running[n] = false;
        }
    }
}

void SystemState::startAll() {
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        for (int i=0; i<numSSR; i++)
        {
            running[i] = false;
        }
    }

    for (int i=0; i<numSSR; i++)
    {
        generateRandomPulseStart(i);
    }

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        for (int i=0; i<numSSR; i++) {
            if (numberOfEvents[i] > 0) {
                eventCnt[i] = 0;
                timerCnt[i] = 0;
                randomPulseCnt[i] = 0;
                running[i] = true;
            }
        }
    }
}

void SystemState::stopAll() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        for (int i=0; i<numSSR; i++) {
            running[i] = false;
        }
    }
}

void SystemState::setNumberOfEvents(unsigned int n, unsigned long value) {
    // Set number of events for channel n
    if (n < numSSR) {
        numberOfEvents[n] = value;
    }
}

void SystemState::setEventPeriod(unsigned int n, unsigned long value) {
    // Set period of events for channel n
    if (n < numSSR) {
        eventPeriod[n] = value;
    }
}

unsigned long SystemState::getNumberOfEvents(unsigned int n) {
    // Returns the number of events for channel n
    if (n < numSSR) {
        return numberOfEvents[n];
    }
}

unsigned long SystemState::getEventPeriod(unsigned int n) {
    // Returns the  event period for channel n
    if (n < numSSR) {
        return eventPeriod[n];
    }
    else {
        return 0;
    }
}

unsigned long SystemState::getEventCnt(unsigned int n) {
    // Returns the current event cnt for channel n
    unsigned long value = 0;
    if (n < numSSR) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            value = eventCnt[n];
        }
    }
    return value;
}

unsigned long SystemState::getRunning(unsigned int n) {
    // Returns the running state for channel n
    unsigned long value = 0; 
    if (n < numSSR) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            value = (unsigned long) running[n];
        }
    }
    return value;
}


void SystemState::generateRandomPulseStart(unsigned int n) {
    // Generate array of random pulses for channel n.  Generation requires that the pulses don't 
    // overlap and that there is a minimum amount of separation. 
    unsigned long pulsePlusMinSepDuration = randomPulseDuration[n] + minRandomPulseSeparation; 
    unsigned long startPos[maxNumberOfRandomPulse]; 

    // Generate start positions.
    for (int i=0; i<numberOfRandomPulse[n]; i++) {
        unsigned long numPosition = eventPeriod[n]/pulsePlusMinSepDuration;
        startPos[i] = random(numPosition);
        for (int j=0;j<i; j++)
        {
            if (startPos[i] == startPos[j])
            {
                startPos[i] = startPos[j] + 1; 
            }
        }
    }

    // Sort starting positions
    qsort((void*)(startPos), numberOfRandomPulse[n], sizeof(unsigned long), compareULong);

    // Convert start positions to start counts (ms)
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        for (int i=0; i<numberOfRandomPulse[n]; i++)
        {
            randomPulseStart[n][i] = startPos[i]*pulsePlusMinSepDuration;
        }
    }

    // TEMP - Display pulses
    Serial << " -- ssr " << n << endl;
    for (int i=0; i<numberOfRandomPulse[n]; i++)
    {
        Serial << "  " << randomPulseStart[n][i] << " - " << randomPulseStart[n][i] + randomPulseDuration[n] << endl;
    }
    Serial << endl;
}

void SystemState::incrEventCnt(unsigned int n) {
    // Increments the pulse counter for channel n. Also, resets the
    // timer counter. If the pulse count is greater than or equal to 
    // the number of pulses setting the channel is stopped.
    Serial << "incr event count: " << eventCnt[n] << "/" << numberOfEvents[n] << endl;
    if (n < numSSR) {
        eventCnt[n]++;
        timerCnt[n] = 0;
        randomPulseCnt[n] = 0;
        generateRandomPulseStart(n);
        if (eventCnt[n] >= numberOfEvents[n]) {
            running[n] = false;
        }
    }
}

void SystemState::incrRandomPulseCnt(unsigned int n)
{
    if (randomPulseCnt[n] < numberOfRandomPulse[n])
    {
        unsigned long pulseStart = randomPulseStart[n][randomPulseCnt[n]];
        unsigned long pulseStop  = pulseStart + randomPulseDuration[n];

        if (timerCnt[n] >= pulseStart)
        {
            if (timerCnt[n] == pulseStart)
            {
                Serial << " ssr: " << n << ", e: " << eventCnt[n] << ", p: " << randomPulseCnt[n] << ", start, count = " << timerCnt[n]  << endl;
            } 

            if (timerCnt[n] < pulseStop) 
            {
                digitalWrite(ssrPin[n], HIGH);
            }
            else
            {
                Serial << " ssr: " << n << ", e: " << eventCnt[n] << ", p: " << randomPulseCnt[n] << ", stop, count = "<< timerCnt[n]  << endl;
                digitalWrite(ssrPin[n], LOW);
                randomPulseCnt[n]++;
            }
        }
    } 
    else {
        digitalWrite(ssrPin[n],LOW);
    }
}

void SystemState::timerUpdate() {
    // Update function for timer callbacks.  Toggles the DIO for the pulses
    for (int i=0; i<numSSR; i++) {

        if (running[i]) {

            incrRandomPulseCnt(i);

            timerCnt[i]++;
            if (timerCnt[i] >= eventPeriod[i]) {
                incrEventCnt(i);
            }
        }
        else {
            digitalWrite(ssrPin[i],LOW); 
        }
    }
}



// Utility functions
// -------------------------------------------------------------------------------------
int compareULong(const void *x_, const void *y_)
{
    unsigned long x = *(unsigned long *)(x_);
    unsigned long y = *(unsigned long *)(y_);

    if (x>y) {
        return  1;
    }
    else if (x==y) {
        return  0;
    }
    else {
        return -1;
    }
}
