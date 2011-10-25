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
#ifdef DEBUG_PRINT
    Serial << "cmdId: " << cmdId << endl;
#endif

    switch (cmdId) {

        case cmdStop:
            sysState.stop();
            break;

        case cmdStart:
            sysState.start();
            break;

        case cmdSetPeriod:
            handleSetValue(&SystemState::setPeriod);
            break;

        case cmdGetPeriod:
            Serial << sysState.getPeriod() << endl;
            break;
            
        case cmdSetNumPulse:
            handleSetValue(&SystemState::setNumPulse);
            break;

        case cmdGetNumPulse:
            Serial << sysState.getNumPulse() << endl;
            break;

        case cmdSetPowerLevel:
            handleSetValue(&SystemState::setPowerLevel);
            break;

        case cmdGetPowerLevel:
            Serial << sysState.getPowerLevel() << endl;
            break;

        default:
            break;
    }

}

void MessageHandler::handleSetValue(SystemStateSetFunc setFunc) {
    unsigned int value;
    if (numberOfItems() >= 2) {
        value = (unsigned int) readInt(1);
        ((sysState).*(setFunc))(value);
    }
}

