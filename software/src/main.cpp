#include <Arduino.h>

#include "Arm.h"
#include "Hat.h"
#include "PinLayout.h"
#include "ducklink/Communication.h"

Arm arm(ARM_VAC_PUMP, ARM_VALVE, ARM_VAC_SENSOR, &DYNAMIXELS_HALF_DUP_SERIAL, ARM_Z_DRIVER_STEP, ARM_Z_DRIVER_DIR, ARM_Z_DRIVER_ENABLE,
        ARM_Z_LIMIT_SWITCH, ARM_Z_ROT_DYNAMIXEL_ID, ARM_Y_ROT_DYNAMIXEL_ID);

Hat hat(HAT_VAC_PUMP, HAT_VALVE, HAT_SERVO1, HAT_SERVO2);

Communication communication(&Serial2);

IOCommand cmd;

void setup() {
    arm.init();
    hat.init();
    arm.setZPrimsaticSpeed(-10);
}

void loop() {
    arm.loop();
    Communication::eMessageStatus msgStatus = communication.checkMessages(cmd);
    if (msgStatus == Communication::eMessageStatus::NEW_MSG) {
        if (cmd.has_arm_position_command()) {
            arm.sendPositionCommand(Arm::eJoint::PRISMATIC_Z, cmd.arm_position_command().z_prismatic_position());
            arm.sendPositionCommand(Arm::eJoint::REVOLUTE_Z, cmd.arm_position_command().z_rotational_position());
            arm.sendPositionCommand(Arm::eJoint::REVOLUTE_Y, cmd.arm_position_command().y_rotational_position());
        } else if (cmd.has_arm_pump_command()) {
            if (cmd.arm_pump_command().enable()) {
                arm.grasp();
            } else {
                arm.drop();
            }
        } else if (cmd.has_hat_position_command()) {
            hat.extendTo(cmd.hat_position_command().hat_height());
        } else if (cmd.has_hat_pump_command()) {
            if (cmd.hat_pump_command().enable()) {
                hat.grasp();
            } else {
                hat.drop();
            }
        } else if (cmd.has_io_request()) {
            if (cmd.io_request() == IORequest::ARM_STATUS) {
                communication.sendArmStatus(arm.getPosition(Arm::PRISMATIC_Z), arm.getPosition(Arm::REVOLUTE_Z), arm.getPosition(Arm::REVOLUTE_Y),
                                            arm.isPumpEnabled(), arm.isValveClosed(), arm.pressure());
            } else if (cmd.io_request() == IORequest::HAT_STATUS) {
                communication.sendHatStatus(hat.getHeight(), hat.isReleased(), hat.isReleased());  // TODO: Change message
            }
        }
    }
}