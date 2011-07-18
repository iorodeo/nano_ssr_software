// nano_ssr_firmware.pde 
//
// Basic firmware for IO Rodeo's solid state relay exapansion board for the
// Arduino Nano. Enables users to set the values of the relay uisng serial
// communications.  Requires the  SerialReceiver library from the
// iorodeo_arduino_libs http://bitbucket.org/iorodeo/iorodeo_arduino_libs.
//
// Author: Will Dickson, IO Rodeo Inc.
// 
// ----------------------------------------------------------------------------
#include "SerialReceiver.h"

// Global variables
const uint8_t numSSR = 8;
const uint8_t ssrPin[numSSR] = {2,3,4,5,6,7,8,9};
SerialReceiver receiver;

// Function prototypes
void handleMessage(uint16_t cmdNum, uint16_t cmdVal);

// System initialization
void setup() {
    
    Serial.begin(9600);
    // Set SSR pins to output and set to low
    for (uint8_t i=0; i<numSSR; i++) {
        pinMode(ssrPin[i], OUTPUT);
        digitalWrite(ssrPin[i],LOW);
    }
}

// Main loop
void loop() {
    uint16_t cmdNum;
    uint16_t cmdVal;
    
    while (Serial.available() > 0) {
        receiver.process(Serial.read());
        if (receiver.messageReady()) {
            cmdNum = receiver.readInt(0);
            cmdVal = receiver.readInt(1);
            handleMessage(cmdNum,cmdVal);
            receiver.reset();
        }
    }
}

// Handle any serial messages
void handleMessage(uint16_t cmdNum, uint16_t cmdVal) {
    // Set individual pins
    if (cmdNum < 8) {
        if ((cmdVal==0) || (cmdVal==1)) {
            digitalWrite(ssrPin[cmdNum], cmdVal);
        }
    }
    // Set all pins
    if (cmdNum == 8) {
        if ((cmdVal == 0 ) || (cmdVal==1)) {
            for (uint8_t i=0; i<numSSR; i++) {
                digitalWrite(ssrPin[i],cmdVal);
            }
        }
    }
}
