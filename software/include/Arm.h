#pragma once

#include "Dynamixel/DynamixelSerial.h"
#include "VacuumSystem.h"
#include "TeensyStep.h"

#define DYNAMIXEL_TO_0_1 512
#define DYNAMIXEL_TO_0_2 512

#define STEPPER_HOME_SPEED 1000
#define STEPPER_MAX_ACC 5000
#define STEPPER_MAX_SPEED 2000

#define STEP_PER_MM 41.18

#define TIME_STEPPER_DISABLE 30000  // stepper automatically disable after 30s


class Arm{
public:
Arm(Gpios::Signal pumpPin, Gpios::Signal valvePin, Pressure::Sensor pressureSensor, HardwareSerial* dynamixelSerial, 
    unsigned int zAxisStepPin, unsigned int zAxisDirPin,
    Gpios::Signal zAxisEnablePin, Gpios::Signal zAxisLimitSwitchPin, unsigned int zRotDynamixelId, unsigned int yRotDynamixelId);

void init();
void loop();

void homeZ();

bool isMoving();

void enableZMotor(bool enable);

void grasp();
void drop();

void startPump(bool start){vacuumSystem_.startPump(start);}
void openValve(bool open){vacuumSystem_.openValve(open);}
bool isPumpStarted() {return vacuumSystem_.isPumpOn();}
bool isValveOpen() {return vacuumSystem_.isValveOpen();}
bool isZMotorEnabled() {return !digitalRead(zAxisEnablePin);}

enum eJoint{
    PRISMATIC_Z = 0,
    REVOLUTE_Z = 1,
    REVOLUTE_Y = 2
};

void sendPositionCommand(const eJoint joint, const float command);
float getPosition(const eJoint joint);
int pressure() {return vacuumSystem_.getPressure();}

// void setZPrimsaticSpeed(int speed);
void resetZPrimaticPosition();

protected:
DynamixelSerial dynamixel_;
HardwareSerial* dynamixelSerial_;
unsigned int zAxisRotDynamixelId_;
unsigned int yAxisRotDynamixelId_;

VacuumSystem vacuumSystem_;

Stepper zAxisStepper_;
Gpios::Signal zAxisEnablePin;
Gpios::Signal zAxisLimitSwitchPin_;
bool isStepperInSpeedMode_;

uint32_t time_z_cmd;

};

extern Arm arm1;
extern Arm arm2;
