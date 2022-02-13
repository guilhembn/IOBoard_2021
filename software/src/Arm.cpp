#include "Arm.h"
#include "TeensyStep.h"
#include <Arduino.h>
#include "PinLayout.h"
#include "Gpios.h"

Arm arm1(Gpios::ARM1_VAC_PUMP, Gpios::ARM1_VALVE, Pressure::ARM1, &DYNAMIXELS_HALF_DUP_SERIAL,
    ARM1_Z_DRIVER_STEP, ARM1_Z_DRIVER_DIR, Gpios::ARM1_Z_DRIVER_ENABLE,
    Gpios::ARM1_Z_LIMIT_SWITCH, ARM1_Z_ROT_DYNAMIXEL_ID, ARM1_Y_ROT_DYNAMIXEL_ID);

Arm arm2(Gpios::ARM2_VAC_PUMP, Gpios::ARM2_VALVE, Pressure::ARM2, &DYNAMIXELS_HALF_DUP_SERIAL,
    ARM2_Z_DRIVER_STEP, ARM2_Z_DRIVER_DIR, Gpios::ARM2_Z_DRIVER_ENABLE,
    Gpios::ARM2_Z_LIMIT_SWITCH, ARM2_Z_ROT_DYNAMIXEL_ID, ARM2_Y_ROT_DYNAMIXEL_ID);

StepControl controller; 

Arm::Arm(Gpios::Signal pumpPin, Gpios::Signal valvePin, Pressure::Sensor pressureSensor, HardwareSerial* dynamixelSerial, unsigned int zAxisStepPin,
         unsigned int zAxisDirPin, Gpios::Signal zAxisEnablePin, Gpios::Signal zAxisLimitSwitchPin, unsigned int zRotDynamixelId,
         unsigned int yRotDynamixelId)
    : dynamixelSerial_(dynamixelSerial),
      zAxisRotDynamixelId_(zRotDynamixelId),
      yAxisRotDynamixelId_(yRotDynamixelId),
      vacuumSystem_(pumpPin, valvePin, pressureSensor),
      zAxisStepper_(zAxisStepPin, zAxisDirPin),
      zAxisEnablePin(zAxisEnablePin),
      zAxisLimitSwitchPin_(zAxisLimitSwitchPin),
      isStepperInSpeedMode_(false),
      time_z_cmd(0)
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
    gpios.setMode(zAxisLimitSwitchPin_, INPUT_PULLUP);
    gpios.setMode(zAxisEnablePin, OUTPUT);
    enableZMotor(true);
    homeZ();
    time_z_cmd = millis();
}

void Arm::homeZ() {
    sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 308);
    sendPositionCommand(Arm::eJoint::REVOLUTE_Y, 0);
    zAxisStepper_.setMaxSpeed(STEPPER_HOME_SPEED);     // slow
    zAxisStepper_.setPosition(-10000);
    zAxisStepper_.setTargetAbs(0);
    controller.moveAsync(zAxisStepper_);
    while (gpios.read(zAxisLimitSwitchPin_)){}     // wait to hit stop switch
    zAxisStepper_.setMaxSpeed(STEPPER_MAX_SPEED);
    zAxisStepper_.setPosition(5*STEP_PER_MM);
    zAxisStepper_.setTargetAbs(0);  // go down 5mm to release stop switch
    controller.move(zAxisStepper_);
}

void Arm::loop() {
    if(gpios.read(zAxisLimitSwitchPin_) == LOW) {
        while (gpios.read(zAxisLimitSwitchPin_) == LOW)
        {
            zAxisStepper_.setTargetRel(-5*STEP_PER_MM);
            controller.move(zAxisStepper_);
        }
        homeZ();
    }

    if(millis() - time_z_cmd > TIME_STEPPER_DISABLE) {
        enableZMotor(false);
    }
}

void Arm::enableZMotor(bool enable) {
    if (enable) {
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
                    enableZMotor(true);
                    homeZ();
                }
                isStepperInSpeedMode_ = false;
                int target = command * STEP_PER_MM;
                zAxisStepper_.setTargetAbs(target);
                controller.moveAsync(zAxisStepper_);
                time_z_cmd = millis();
            }
            break;
        case eJoint::REVOLUTE_Z:
            dynamixel_.moveSpeed(zAxisRotDynamixelId_, command + DYNAMIXEL_TO_0_1, 300);
            break;
        case eJoint::REVOLUTE_Y:
            dynamixel_.moveSpeed(yAxisRotDynamixelId_, command + DYNAMIXEL_TO_0_2, 300);
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
