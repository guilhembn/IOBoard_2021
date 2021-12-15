#include "Arm.h"
#include "TeensyStep.h"
#include <Arduino.h>

StepControl controller; 

Arm::Arm(unsigned int pumpPin, unsigned int valvePin, unsigned int pressureSensorPin, HardwareSerial* dynamixelSerial, unsigned int zAxisStepPin,
         unsigned int zAxisDirPin, unsigned int zAxisEnablePin, unsigned int zAxisLimitSwitchPin, unsigned int zRotDynamixelId,
         unsigned int yRotDynamixelId)
    : dynamixelSerial_(dynamixelSerial),
      zAxisRotDynamixelId_(zRotDynamixelId),
      yAxisRotDynamixelId_(yRotDynamixelId),
      vacuumSystem_(pumpPin, valvePin, pressureSensorPin),
      zAxisStepper_(zAxisStepPin, zAxisDirPin),
      zAxisEnablePin(zAxisEnablePin),
      zAxisLimitSwitchPin_(zAxisLimitSwitchPin),
      isStepperInSpeedMode_(false),
      zStopHit(false)
{

}

void Arm::init() {
    dynamixel_.init(dynamixelSerial_);
    sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 308);
    sendPositionCommand(Arm::eJoint::REVOLUTE_Y, 0);
    vacuumSystem_.init();

    zAxisStepper_.setAcceleration(STEPPER_MAX_ACC);
    zAxisStepper_.setMaxSpeed(STEPPER_MAX_SPEED/2);
    zAxisStepper_.setPullInSpeed(10);
    zAxisStepper_.setInverseRotation(true);

    pinMode(zAxisLimitSwitchPin_, INPUT_PULLUP);
    pinMode(zAxisEnablePin, OUTPUT);
    enableZMotor(true);

    auto zstop_hit_isr = [this]() {
        zStopHit = true;
        
    };
    attachInterrupt(zAxisLimitSwitchPin_, zstop_hit_isr, FALLING);
    homeZ();
}

void Arm::homeZ() {
    zAxisStepper_.setMaxSpeed(STEPPER_HOME_SPEED);     // slow
    zAxisStepper_.setPosition(-10000);
    zAxisStepper_.setTargetAbs(0);
    controller.moveAsync(zAxisStepper_);
    while (!zStopHit){}     // wait to hit stop switch
    zAxisStepper_.setMaxSpeed(STEPPER_MAX_SPEED);
    zAxisStepper_.setPosition(5*STEP_PER_MM);
    zAxisStepper_.setTargetAbs(0);  // go down 5mm to release stop switch
    controller.move(zAxisStepper_);
    zStopHit = false;
}

void Arm::loop() {
    if(zStopHit) {
        while (digitalRead(zAxisLimitSwitchPin_) == LOW)
        {
            zAxisStepper_.setTargetRel(-5*STEP_PER_MM);
            controller.move(zAxisStepper_);
        }
        zStopHit = false;
        homeZ();
        zStopHit = false;
    }
}

void Arm::enableZMotor(bool enable) {
    if (enable) {
        digitalWrite(LOW, zAxisEnablePin);
    } else {
        digitalWrite(HIGH, zAxisEnablePin);
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
                isStepperInSpeedMode_ = false;
                int target = command * STEP_PER_MM;
                zAxisStepper_.setTargetAbs(target);
                controller.moveAsync(zAxisStepper_);
            }
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

float Arm::getPosition(eJoint joint) {
    switch (joint) {
        case eJoint::PRISMATIC_Z:
            return zAxisStepper_.getPosition() / STEP_PER_MM;
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
    return 0.;
}

void Arm::grasp() { vacuumSystem_.suck(); }

void Arm::drop() { vacuumSystem_.release(); }
