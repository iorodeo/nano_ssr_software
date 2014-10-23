#include <util/atomic.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "TimerOne.h"
#include "SystemState.h"
#include "Streaming.h"

SystemState::SystemState() {
    for (int i=0; i<numSSR; i++) {
        numPulse[i] = defaultNumPulse;
        period[i] = defaultPeriod;
        running[i] = false;
        pulseCnt[i] = 0;
        timerCnt[i] = 0;
    }
}

void SystemState::initialize() {
    // Set SSR IO pins to output and set to low
    for (uint8_t i=0; i<numSSR; i++) {
        pinMode(ssrPin[i], OUTPUT);
        digitalWrite(ssrPin[i],LOW);
    }
}

void SystemState::start(unsigned int n) {
    // Start pulses on channel n
    if (n < numSSR) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            pulseCnt[n] = 0;
            timerCnt[n] = 0;
            running[n] = true;
        } 
    }
}

void SystemState::stop(unsigned int n) {
    // Stop pulses on channel n
    if (n < numSSR) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            running[n] = false;
        }
    }
}

void SystemState::startAll() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        for (int i=0; i<numSSR; i++) {
            if (numPulse[i] > 0) {
                pulseCnt[i] = 0;
                timerCnt[i] = 0;
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

void SystemState::setNumPulse(unsigned int n, unsigned long value) {
    // Set number of pulses for channel n
    if (n < numSSR) {
        numPulse[n] = value;
    }
}

void SystemState::setPeriod(unsigned int n, unsigned long value) {
    // Set period of pulses for channel n
    if (n < numSSR) {
        period[n] = value;
    }
}

unsigned long SystemState::getNumPulse(unsigned int n) {
    // Returns the number of pulses for channel n
    if (n < numSSR) {
        return numPulse[n];
    }
}

unsigned long SystemState::getPeriod(unsigned int n) {
    // Returns the  period for channel n
    if (n < numSSR) {
        return period[n];
    }
    else {
        return 0;
    }
}

unsigned long SystemState::getPulseCnt(unsigned int n) {
    // Returns the current pulse cnt for channel n
    unsigned long value = 0;
    if (n < numSSR) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            value = pulseCnt[n];
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

void SystemState::incrPulseCnt(unsigned int n) {
    // Increments the pulse counter for channel n. Also, resets the
    // timer counter. If the pulse count is greater than or equal to 
    // the number of pulses setting the channel is stopped.
    if (n < numSSR) {
        pulseCnt[n]++;
        timerCnt[n] = 0;
        if (pulseCnt[n] >= numPulse[n]) {
            running[n] = false;
        }
    }
}

void SystemState::timerUpdate() {
    // Update function for timer callbacks.  Toggles the DIO for the pulses
    for (unsigned int i=0; i<numSSR; i++) {
        if (running[i]) {
            if (timerCnt[i] < period[i]/2) {
                digitalWrite(ssrPin[i],HIGH);
            }
            else {
                digitalWrite(ssrPin[i],LOW); 
            }

            timerCnt[i]++;
            if (timerCnt[i] >= period[i]) {
                incrPulseCnt(i);
            }
        }
        else {
            digitalWrite(ssrPin[i],LOW); 
        }
    }
}

