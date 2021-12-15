#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "generated/messages.h"

#include <HardwareSerial.h>

#include "ducklink/BytesReadBuffer.h"
#include "ducklink/BytesWriteBuffer.h"
#include "Arm.h"
#include "Hat.h"

#define NUM_MESSAGES 10

class Communication {
   public:
    Communication(HardwareSerial* communicationSerial);

    void init(int baudrate);

    enum eMessageStatus { NO_MSG, NEW_MSG, COM_ERROR };
    eMessageStatus checkMessages(::protoduck::Message& msg);

    void sendArmStatus(Arm& arm);
    void sendHatStatus(Hat& hat);
    void sendProcedureStatus(protoduck::ProcedureStatus::Status status);

   protected:
    void send(::protoduck::Message msg);

    enum eRcvState { START_1, START_2, LEN, PAYLOAD, CHECKSUM };
    eRcvState receiveState_;
    uint8_t nbBytesExpected_;
    uint8_t checksum_;
    BytesReadBuffer rcvBuffer_;
    HardwareSerial* serial_;
};

extern Communication communication;

#endif /* COMMUNICATION_H */
