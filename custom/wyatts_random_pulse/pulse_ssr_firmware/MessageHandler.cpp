#include "MessageHandler.h"
#include "Streaming.h"

extern SystemState sysState;


MessageHandler::MessageHandler() {
}

void MessageHandler::initialize(unsigned long baudrate) {
    Serial.begin(baudrate);
}

void MessageHandler::update() { 
    // Check if message is available
    while (Serial.available() > 0) {
        process(Serial.read());
        if (messageReady()) {
            processMessage();
            reset();
        }
    }
}

void MessageHandler::processMessage() {
    int cmdId;

    cmdId = readInt(0);

    switch (cmdId) {

        case cmdStop:
            setSysStatePin(&SystemState::stop);
            break;

        case cmdStart:
            setSysStatePin(&SystemState::start);
            break;

        case cmdStartAll:
            sysState.startAll();
            break;

        case cmdStopAll:
            sysState.stopAll();
            break;
               
        case cmdSetEventPeriod:
            setSysStateValue(&SystemState::setEventPeriod);
            break;

        case cmdGetEventPeriod:
            Serial << getSysStateValue(&SystemState::getEventPeriod) << endl;
            break;
            
        case cmdSetNumberOfEvents:
            setSysStateValue(&SystemState::setNumberOfEvents);
            break;

        case cmdGetNumberOfEvents:
            Serial << getSysStateValue(&SystemState::getNumberOfEvents) << endl;
            break;

        case cmdGetRunning:
            Serial << getSysStateValue(&SystemState::getRunning) << endl;
            break;

        default:
            break;
    }

}

void MessageHandler::setSysStatePin(setPinFunc func) {
    int n;
    if (numberOfItems() >=2) {
        n = readInt(1);
        if (n >= 0) { 
            ((sysState).*(func))(n);
        }
    }
}

void MessageHandler::setSysStateValue(setValueFunc func) {
    int n;
    long value;
    if (numberOfItems() >= 3) {
        n = readInt(1);
        value = readLong(2);
        if ((n >= 0) && (value >= 0)) {
            ((sysState).*(func))(n, value);
        }
    }
}

long MessageHandler::getSysStateValue(getValueFunc func) {
    int n;
    long value = -1;
    if (numberOfItems() >= 2) {
        n = readInt(1);
        if ((n>=0) && (n<numSSR)) {
            value = (long) ((sysState).*(func))(n);
        }
    }
    return value;
}

