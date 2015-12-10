/**************************************************************************
pulse_ssr_firmware  

Firmware for pulsing solid state relays connected to an Arduino. 

Will Dickson.

***************************************************************************/
#include <util/atomic.h>
#include <Streaming.h>
#include "SerialReceiver.h"
#include "TimerOne.h"
#include "constants.h"
#include "MessageHandler.h"
#include "SystemState.h"

void timerCallback();

MessageHandler msgHandler = MessageHandler();
SystemState sysState = SystemState();

void setup() {
    msgHandler.initialize(baudrate);
    sysState.initialize();
    Timer1.initialize(timerPeriod_us);
    Timer1.attachInterrupt(timerCallback);
    Timer1.start();
}

void loop() {
    msgHandler.update();
}

void timerCallback() {
    sysState.timerUpdate();
}

