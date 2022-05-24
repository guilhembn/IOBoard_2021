#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "generated/messages.h"

#include <HardwareSerial.h>

#include "ducklink/BytesReadBuffer.h"
#include "ducklink/BytesWriteBuffer.h"

class Arm;
class Hat;
class ProcedureManager;

#define NUM_MESSAGES 10

using Message = protoduck::Message<5, 4>;

class Communication {
   public:
    Communication(HardwareSerial* communicationSerial);

    void init(int baudrate);

    enum eMessageStatus { NO_MSG, NEW_MSG, COM_ERROR };
    eMessageStatus checkMessages(Message& msg);

    void sendArmStatus(Arm& arm);
    void sendHatStatus(Hat& hat);
    void sendProcedureStatus(ProcedureManager& pm);
    void sendError(::protoduck::Error::Errors e, uint32_t param);
    void sendHMI();

   protected:
    void send(Message msg);

    enum eRcvState { START_1, START_2, LEN, PAYLOAD, CHECKSUM };
    eRcvState receiveState_;
    uint8_t nbBytesExpected_;
    uint8_t checksum_;
    BytesReadBuffer rcvBuffer_;
    HardwareSerial* serial_;
};

extern Communication communication;

#endif /* COMMUNICATION_H */
