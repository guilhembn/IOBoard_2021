#include "ducklink/Communication.h"

Communication::Communication(HardwareSerial* serial) : serial_(serial), receiveState_(Communication::eRcvState::START_1) { serial_->begin(57600); }

Communication::eMessageStatus Communication::checkMessages(IOCommand& msg) {
    msg.clear();
    uint8_t byte;
    size_t readLen;
    if (receiveState_ == Communication::eRcvState::START_1) {
        rcvBuffer_.clear();
        checksum_ = 0;
        readLen = serial_->readBytes(&byte, 1);
        if (readLen == 1 && byte == 0xFF) {
            receiveState_ = Communication::eRcvState::START_2;
        }
    }
    if (receiveState_ == Communication::eRcvState::START_2) {
        readLen = serial_->readBytes(&byte, 1);
        if (readLen == 1) {
            if (byte == 0xFF) {
                receiveState_ = Communication::eRcvState::LEN;
            } else {
                receiveState_ = Communication::eRcvState::START_1;
            }
        }
    }
    if (receiveState_ == Communication::eRcvState::LEN) {
        readLen = serial_->readBytes(&byte, 1);
        if (readLen == 1) {
            nbBytesExpected_ = byte;
            receiveState_ = Communication::eRcvState::PAYLOAD;
        }
    }
    if (receiveState_ == Communication::eRcvState::PAYLOAD) {
        if (serial_->available() >= nbBytesExpected_) {
            for (size_t i = 0; i < nbBytesExpected_; i++) {
                serial_->readBytes(&byte, 1);
                checksum_ ^= byte;
                rcvBuffer_.push(byte);
            }
            receiveState_ = Communication::eRcvState::CHECKSUM;
        }
    }
    if (receiveState_ == Communication::eRcvState::CHECKSUM) {
        readLen = serial_->readBytes(&byte, 1);
        if (readLen == 1) {
            receiveState_ = Communication::eRcvState::START_1;
            if (byte == checksum_) {
                EmbeddedProto::Error err = msg.deserialize(rcvBuffer_);
                if (err == EmbeddedProto::Error::NO_ERRORS) {
                    return Communication::eMessageStatus::NEW_MSG;
                } else {
                    return Communication::eMessageStatus::COM_ERROR;
                }
            } else {
                return Communication::eMessageStatus::COM_ERROR;
            }
        }
    }
    return Communication::eMessageStatus::NO_MSG;
}

void Communication::sendArmStatus(unsigned int zPriPosition, unsigned int zRotPosition, unsigned int yRotPosition, bool pumpEnabled, bool valveClosed,
                                  unsigned int pressureValue) {
    IOAnswer msg;
    ArmStatus& armStatus = msg.mutable_arm_status();
    armStatus.set_z_prismatic_position(zPriPosition);
    armStatus.set_z_rotational_position(zRotPosition);
    armStatus.set_y_rotational_position(yRotPosition);
    armStatus.set_pumpEnabled(pumpEnabled);
    armStatus.set_valveClosed(valveClosed);
    armStatus.set_pressureValue(pressureValue);
    send(msg);
}

void Communication::sendHatStatus(unsigned int hatHeight, bool pumpEnabled, bool valveClosed) {
    IOAnswer msg;
    HatStatus& hatStatus = msg.mutable_hat_status();
    hatStatus.set_hat_height(hatHeight);
    hatStatus.set_pumpEnabled(pumpEnabled);
    hatStatus.set_valveClosed(valveClosed);
    send(msg);
}

void Communication::send(const IOAnswer& msg) {
    BytesWriteBuffer sendBuffer;
    sendBuffer.clear();
    msg.serialize(sendBuffer);
    uint8_t header[] = {0xFF, 0xFF, 0};
    header[2] = sendBuffer.get_size();
    uint8_t* data = sendBuffer.get_data();
    uint8_t checksum = 0;
    for (size_t i = 0; i < sendBuffer.get_size(); i++) {
        checksum ^= data[i];
    }
    serial_->write(header, 3);
    serial_->write(data, sendBuffer.get_size());
    serial_->write(&checksum, 1);
}