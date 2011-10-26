#ifndef MessageHandler_H
#define MESSAGE_HANDLER_H
#include <WProgram.h>
#include "SerialReceiver.h"
#include "constants.h"
#include "SystemState.h"

class MessageHandler: public SerialReceiver {
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
