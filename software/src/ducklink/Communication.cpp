#include "ducklink/Communication.h"


Communication::Communication(HardwareSerial* serial) : receiveState_(Communication::eRcvState::START_1), serial_(serial) {}

void Communication::init(int baudrate) { serial_->begin(baudrate); }

Communication::eMessageStatus Communication::checkMessages(protoduck::Message& msg) {
    msg.clear();
    uint8_t byte;
    size_t readLen;
    if (receiveState_ == Communication::eRcvState::START_1) {
        rcvBuffer_.clear();
        checksum_ = 0;
        if (serial_->available()) {
            readLen = serial_->readBytes(&byte, 1);
            if (readLen == 1 && byte == 0xFF) {
                receiveState_ = Communication::eRcvState::START_2;
            }
        }
    }
    if (receiveState_ == Communication::eRcvState::START_2) {
        if (serial_->available()) {
            readLen = serial_->readBytes(&byte, 1);
            if (readLen == 1) {
                if (byte == 0xFF) {
                    receiveState_ = Communication::eRcvState::LEN;
                } else {
                    receiveState_ = Communication::eRcvState::START_1;
                }
            }
        }
    }
    if (receiveState_ == Communication::eRcvState::LEN) {
        if (serial_->available()) {
            readLen = serial_->readBytes(&byte, 1);
            if (readLen == 1) {
                nbBytesExpected_ = byte;
                receiveState_ = Communication::eRcvState::PAYLOAD;
            }
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
        if (serial_->available()) {
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
    }
    return Communication::eMessageStatus::NO_MSG;
}

void Communication::sendArmStatus(Arm& arm) {
    protoduck::Message msg;
    protoduck::Arm& armStatus = msg.mutable_arm();

    float zPriPosition = arm.getPosition(Arm::eJoint::PRISMATIC_Z);
    float zRotPosition = arm.getPosition(Arm::eJoint::REVOLUTE_Z);
    float yRotPosition = arm.getPosition(Arm::eJoint::REVOLUTE_Y);
    bool pumpEnabled = arm.isPumpStarted();
    bool valveClosed = arm.isValveOpen();
    unsigned int pressureValue = arm.pressure();

    armStatus.set_traZ(zPriPosition);
    armStatus.set_rotZ(zRotPosition);
    armStatus.set_rotY(yRotPosition);
    armStatus.set_pump(pumpEnabled);
    armStatus.set_valve(valveClosed);
    armStatus.set_pressure(pressureValue);
    send(msg);
}

void Communication::sendHatStatus(Hat& hat) {
    protoduck::Message msg;
    protoduck::Hat& hatStatus = msg.mutable_hat();
    hatStatus.set_height(hat.getHeight());
    hatStatus.set_pump(hat.isPumpStarted());
    hatStatus.set_valve(hat.isValveOpen());
    hatStatus.set_pressure(0.);
    send(msg);
}

void Communication::send(protoduck::Message msg) {
    msg.set_source(protoduck::Message::Agent::DIFF);
    msg.set_msg_type(protoduck::Message::MsgType::STATUS);
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