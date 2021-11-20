#ifndef ARM_H
#define ARM_H

#include "Dynamixel/DynamixelSerial.h"
#include "VacuumSystem.h"
#include "AccelStepper.h"

#define DYNAMIXEL_TO_0_1 512
#define DYNAMIXEL_TO_0_2 512

#define STEPPER_HOME_SPEED -10
#define STEPPER_MAX_ACC 15
#define STEPPER_MAX_SPEED 100


class Arm{
public:
Arm(unsigned int pumpPin, unsigned int valvePin, unsigned int pressureSensorPin, HardwareSerial* dynamixelSerial, 
    unsigned int zAxisStepPin, unsigned int zAxisDirPin,
    unsigned int zAxisEnablePin, unsigned int zAxisLimitSwitchPin, unsigned int zRotDynamixelId, unsigned int yRotDynamixelId);

void init();
void loop();

bool isMoving();

void enableZMotor(bool enable);

enum eJoint{
    PRISMATIC_Z = 0,
    REVOLUTE_Z = 1,
    REVOLUTE_Y = 2
};

void sendPositionCommand(const eJoint joint, const int command);

void setZPrimsaticSpeed(int speed);
void resetZPrimaticPosition();

protected:
DynamixelSerial dynamixel_;
HardwareSerial* dynamixelSerial_;
unsigned int zAxisRotDynamixelId_;
unsigned int yAxisRotDynamixelId_;

VacuumSystem vacuumSystem_;

AccelStepper zAxisStepper_;
unsigned int zAxisLimitSwitchPin_;
bool isStepperInSpeedMode_;

};


#endif /* ARM_H */
