#include "Arm.h"

#include <Arduino.h>

Arm::Arm(unsigned int pumpPin, unsigned int valvePin, unsigned int pressureSensorPin, HardwareSerial* dynamixelSerial, unsigned int zAxisStepPin,
         unsigned int zAxisDirPin, unsigned int zAxisEnablePin, unsigned int zAxisLimitSwitchPin, unsigned int zRotDynamixelId,
         unsigned int yRotDynamixelId)
    : dynamixelSerial_(dynamixelSerial),
      zAxisRotDynamixelId_(zRotDynamixelId),
      yAxisRotDynamixelId_(yRotDynamixelId),
      vacuumSystem_(pumpPin, valvePin, pressureSensorPin),
      zAxisStepper_(AccelStepper::DRIVER, zAxisStepPin, zAxisDirPin),
      zAxisLimitSwitchPin_(zAxisLimitSwitchPin),
      isStepperInSpeedMode_(false) {
    zAxisStepper_.setEnablePin(zAxisEnablePin);
    zAxisStepper_.setMaxSpeed(STEPPER_MAX_SPEED);
    zAxisStepper_.setAcceleration(STEPPER_MAX_ACC);
}

void Arm::init() {
    zAxisStepper_.disableOutputs();
    pinMode(zAxisLimitSwitchPin_, INPUT_PULLUP);
    dynamixel_.init(dynamixelSerial_);
    vacuumSystem_.init();
}

void Arm::loop() {
    if (isStepperInSpeedMode_) {
        zAxisStepper_.runSpeed();
    } else {
        zAxisStepper_.run();
    }
    if (digitalRead(zAxisLimitSwitchPin_) == LOW) {
        zAxisStepper_.setCurrentPosition(0);
    }
}

void Arm::enableZMotor(bool enable) {
    if (enable) {
        zAxisStepper_.enableOutputs();
    } else {
        zAxisStepper_.disableOutputs();
    }
}

bool Arm::isMoving() { return zAxisStepper_.isRunning(); }

void Arm::setZPrimsaticSpeed(int speed) {
    isStepperInSpeedMode_ = true;
    zAxisStepper_.setSpeed(speed);
}

void Arm::sendPositionCommand(eJoint joint, int command) {
    switch (joint) {
        case eJoint::PRISMATIC_Z:
            isStepperInSpeedMode_ = false;
            zAxisStepper_.moveTo(command);
            break;
        case eJoint::REVOLUTE_Z:
            dynamixel_.move(zAxisRotDynamixelId_, command + DYNAMIXEL_TO_0_1);
            break;
        case eJoint::REVOLUTE_Y:
            dynamixel_.move(yAxisRotDynamixelId_, command + DYNAMIXEL_TO_0_2);
            break;
        default:
            break;
    }
}

int Arm::getPosition(eJoint joint) {
    switch (joint) {
        case eJoint::PRISMATIC_Z:
            return (int)zAxisStepper_.currentPosition();
            break;
        case eJoint::REVOLUTE_Z:
            return dynamixel_.readPosition(zAxisRotDynamixelId_) - DYNAMIXEL_TO_0_1;
            break;
        case eJoint::REVOLUTE_Y:
            return dynamixel_.readPosition(yAxisRotDynamixelId_) - DYNAMIXEL_TO_0_2;
            break;
        default:
            break;
    }
}

void Arm::grasp() { vacuumSystem_.suck(); }

void Arm::drop() { vacuumSystem_.release(); }
