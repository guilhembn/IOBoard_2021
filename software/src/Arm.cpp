#include "Arm.h"
#include "TeensyStep.h"
#include <Arduino.h>
#include "PinLayout.h"
#include "Gpios.h"
#include "generated/messages.h"

using Errors = protoduck::Error::Errors;
using protoduck::ArmID;

StepControl controller;

Arm arm1(Gpios::ARM1_VAC_PUMP, Gpios::ARM1_VALVE, Pressure::ARM1, &DYNAMIXELS_HALF_DUP_SERIAL,
    ARM1_Z_DRIVER_STEP, ARM1_Z_DRIVER_DIR, Gpios::ARM1_Z_DRIVER_ENABLE,
    Gpios::ARM1_Z_LIMIT_SWITCH, ARM1_Z_ROT_DYNAMIXEL_ID, ARM1_Y_ROT_DYNAMIXEL_ID, controller, ArmID::ARM1);

Arm arm2(Gpios::ARM2_VAC_PUMP, Gpios::ARM2_VALVE, Pressure::ARM2, &DYNAMIXELS_HALF_DUP_SERIAL,
    ARM2_Z_DRIVER_STEP, ARM2_Z_DRIVER_DIR, Gpios::ARM2_Z_DRIVER_ENABLE,
    Gpios::ARM2_Z_LIMIT_SWITCH, ARM2_Z_ROT_DYNAMIXEL_ID, ARM2_Y_ROT_DYNAMIXEL_ID, controller, ArmID::ARM2);


Arm::Arm(Gpios::Signal pumpPin, Gpios::Signal valvePin, Pressure::Sensor pressureSensor, HardwareSerial* dynamixelSerial, unsigned int zAxisStepPin,
         unsigned int zAxisDirPin, Gpios::Signal zAxisEnablePin, Gpios::Signal zAxisLimitSwitchPin, unsigned int zRotDynamixelId,
         unsigned int yRotDynamixelId,
         StepControl& controller, ArmID arm_id)
    : dynamixelSerial_(dynamixelSerial),
      zAxisRotDynamixelId_(zRotDynamixelId),
      yAxisRotDynamixelId_(yRotDynamixelId),
      vacuumSystem_(pumpPin, valvePin, pressureSensor),
      zAxisStepper_(zAxisStepPin, zAxisDirPin),
      zAxisEnablePin(zAxisEnablePin),
      zAxisLimitSwitchPin_(zAxisLimitSwitchPin),
      isStepperInSpeedMode_(false),
      controller(controller),
      time_z_cmd(0),
      watchZStop(true),
      ARM_ID(arm_id)
{

}

void Arm::init() {
    dynamixel_.init(dynamixelSerial_);
    sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 820);
    sendPositionCommand(Arm::eJoint::REVOLUTE_Y, 512);
    vacuumSystem_.init();

    zAxisStepper_.setAcceleration(STEPPER_MAX_ACC);
    zAxisStepper_.setMaxSpeed(STEPPER_MAX_SPEED/2);
    zAxisStepper_.setPullInSpeed(10);
    zAxisStepper_.setInverseRotation(true);
    gpios.setMode(zAxisLimitSwitchPin_, INPUT_PULLUP);
    gpios.setMode(zAxisEnablePin, OUTPUT);
    enableZMotor(true);
    time_z_cmd = millis();

    // for(int i=0; i<3; i++) {
    //     last_commands[0] = 0;
    // }
    
}

void Arm::loop() {
    if(watchZStop && gpios.read(zAxisLimitSwitchPin_) == LOW) {
        communication.sendError(Errors::Z_STOP_TRIGGERED, static_cast<uint32_t>(ARM_ID));
    }

    if(millis() - time_z_cmd > TIME_STEPPER_DISABLE) {
        enableZMotor(false);
    }
}

void Arm::enableZMotor(bool enable) {
    if (enable) {
        reset_stepper_timeout();
        gpios.write(zAxisEnablePin, LOW);
    } else {
        gpios.write(zAxisEnablePin, HIGH);
    }
}

bool Arm::isMoving() { return false;/*zAxisStepper_.isRunning(); */}

// void Arm::setZPrimsaticSpeed(int speed) {
//     isStepperInSpeedMode_ = true;
//     zAxisStepper_.setTargetRel(speed * 5);
//     //if(!controller.isRunning()) {
//         //controller.moveAsync(zAxisStepper_);
//     //}
//     //zAxisStepper_.setSpeed(speed);
// }

void Arm::sendPositionCommand(eJoint joint, float command) {
    // Dyn 1: neutral 512; extended : 820; pick : 412
    // Dyn 2: neutral 544; down: 320; up: 750
    switch (joint) {
        case eJoint::PRISMATIC_Z:
            {
                if(!isZMotorEnabled()) {
                    communication.sendError(Errors::STEPPER_DISABLED, static_cast<uint32_t>(ARM_ID));
                }
                isStepperInSpeedMode_ = false;
                int target = command * STEP_PER_MM;
                zAxisStepper_.setTargetAbs(target);
                controller.moveAsync(zAxisStepper_);
                reset_stepper_timeout();
            }
            break;
        case eJoint::REVOLUTE_Z:
            {
                auto ret = dynamixel_.moveSpeed(zAxisRotDynamixelId_, z_rot_cmd(command), 600);
                if(ret == -1) {communication.sendError(Errors::DYNAMIXEL_ERROR, zAxisRotDynamixelId_);}
            }
            break;
        case eJoint::REVOLUTE_Y:
            {
                auto ret = dynamixel_.moveSpeed(yAxisRotDynamixelId_, z_rot_cmd(command), 600);
                if(ret == -1) {communication.sendError(Errors::DYNAMIXEL_ERROR, yAxisRotDynamixelId_);}
            }
            break;
        default:
            break;
    }
    last_commands[static_cast<int>(joint)] = command;
}

bool Arm::isNear(eJoint joint, float precision) {
    float pos = getPosition(joint);
    float cmd = last_commands[static_cast<int>(joint)];

    if(abs(cmd - pos) < precision) {
        return true;
    }
    return false;
}

void Arm::rotateIdle() {
    sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 500);
    sendPositionCommand(Arm::eJoint::REVOLUTE_Y, 330);
}

float Arm::getPosition(eJoint joint) {
    switch (joint) {
        case eJoint::PRISMATIC_Z:
            return zAxisStepper_.getPosition() / STEP_PER_MM;
            break;
        case eJoint::REVOLUTE_Z:
            {
                auto pos = dynamixel_.readPosition(zAxisRotDynamixelId_);
                if(pos == -1) {communication.sendError(Errors::DYNAMIXEL_ERROR, zAxisRotDynamixelId_);}
                return z_rot_cmd(pos);
                //return pos;
            }
            break;
        case eJoint::REVOLUTE_Y:
            {
                auto pos = dynamixel_.readPosition(yAxisRotDynamixelId_);
                if(pos == -1) {communication.sendError(Errors::DYNAMIXEL_ERROR, yAxisRotDynamixelId_);}
                return z_rot_cmd(pos);
                //return pos;
            }
            break;
        default:
            break;
    }
    return 0.;
}

void Arm::grasp() { vacuumSystem_.suck(); }

void Arm::drop() { vacuumSystem_.release(); }
