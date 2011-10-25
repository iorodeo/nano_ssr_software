#include <util/atomic.h>
#include "WProgram.h"
#include "SystemState.h"

SystemState::SystemState() {
    numPulse = defaultNumPulse;
    period = defaultPeriod;
    powerLevel = defaultPowerLevel;
    running = false;
}

void SystemState::start() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        pulseCnt = 0;
        running = true;
    } 
}

void SystemState::stop() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        running = false;
    }
}

void SystemState::setNumPulse(unsigned int value) {
    numPulse = value;
}

void SystemState::setPeriod(unsigned int value) {
    period = value;
}

void SystemState::setPowerLevel(unsigned int value) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (!running) {
            if (value <= 100) {
                // Change timer top
                powerLevel = value;
            }
        }
    }
}

unsigned int SystemState::getNumPulse() {
    return numPulse;
}

unsigned int SystemState::getPeriod() {
    return period;
}

unsigned int SystemState::getPowerLevel() {
    return powerLevel;
}

unsigned int SystemState::getPulseCnt() {
    return pulseCnt;
}

void SystemState::incrPulseCnt() {
    pulseCnt++;
    if (pulseCnt >= numPulse) {
        running = false;
    }
}


