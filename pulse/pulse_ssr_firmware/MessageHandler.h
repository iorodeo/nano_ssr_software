#ifndef MessageHandler_H
#define MESSAGE_HANDLER_H
#include <WProgram.h>
#include "SerialReceiver.h"
#include "SystemState.h"

#define DEBUG_PRINT


typedef enum {
    cmdStop,           // 0 
    cmdStart,          // 1
    cmdSetPeriod,      // 2
    cmdGetPeriod,      // 3
    cmdSetNumPulse,    // 4
    cmdGetNumPulse,    // 5
    cmdSetPowerLevel,  // 6
    cmdGetPowerLevel,  // 7
} CmdIdentifier;


class MessageHandler: public SerialReceiver {
    public:
        MessageHandler();
        void initialize(unsigned long baudrate);
        void update();
    private:
        void processMessage();
        void handleSetValue(SystemStateSetFunc);
};

#endif
