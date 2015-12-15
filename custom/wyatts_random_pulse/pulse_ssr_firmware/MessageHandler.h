#ifndef MessageHandler_H
#define MESSAGE_HANDLER_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "SerialReceiver.h"
#include "constants.h"
#include "SystemState.h"

class MessageHandler: public SerialReceiver 
{
    public:
        MessageHandler();
        void initialize(unsigned long baudrate);
        void update();
    private:
        void processMessage();
        void setSysStateValue(setValueFunc);
        void setSysStatePin(setPinFunc);
        long getSysStateValue(getValueFunc);
};

#endif
