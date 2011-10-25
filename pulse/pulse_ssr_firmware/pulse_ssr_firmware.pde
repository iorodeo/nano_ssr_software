/*
pulse_ssr_firmware - firmware for pulsing solid state relays connected to an
Arduino. 

*/
#include <util/atomic.h>
#include <Streaming.h>
#include "SerialReceiver.h"
#include "MessageHandler.h"
#include "SystemState.h"

// Constants
const unsigned long baudrate = 9600;
const uint8_t numSSR = 8;
const uint8_t ssrPin[numSSR] = {2,3,4,5,6,7,8,9};

// Globals
MessageHandler msgHandler = MessageHandler();
SystemState sysState = SystemState();

// Function prototypes
void initRelayPins();

void setup() {
    msgHandler.initialize(baudrate);
    initIO();
}

void loop() {
    msgHandler.update();
}

void initIO() {
    for (uint8_t i=0; i<numSSR; i++) {
        pinMode(ssrPin[i], OUTPUT);
        digitalWrite(ssrPin[i],LOW);
    }
}
