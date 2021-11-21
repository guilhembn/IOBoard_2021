#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "generated/messages.h"

#include <HardwareSerial.h>

#include "ducklink/BytesReadBuffer.h"
#include "ducklink/BytesWriteBuffer.h"


#define NUM_MESSAGES 10

class Communication {
   public:
    Communication(HardwareSerial* communicationSerial);

    void init();

    enum eMessageStatus { NO_MSG, NEW_MSG, COM_ERROR };
    eMessageStatus checkMessages(::protoduck::Message& msg);

    void sendArmStatus(unsigned int zPriPosition, unsigned int zRotPosition, unsigned int yRotPosition, bool pumpEnabled, bool valveClosed,
                       unsigned int pressureValue);
    void sendHatStatus(unsigned int hatHeight, bool pumpEnabled, bool valveClosed);

   protected:
    void send(::protoduck::Message msg);

    enum eRcvState { START_1, START_2, LEN, PAYLOAD, CHECKSUM };
    eRcvState receiveState_;
    uint8_t nbBytesExpected_;
    uint8_t checksum_;
    BytesReadBuffer rcvBuffer_;
    HardwareSerial* serial_;
};

#endif /* COMMUNICATION_H */
