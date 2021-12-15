#ifndef ARM_H
#define ARM_H

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
Arm(unsigned int pumpPin, unsigned int valvePin, unsigned int pressureSensorPin, HardwareSerial* dynamixelSerial, 
    unsigned int zAxisStepPin, unsigned int zAxisDirPin,
    unsigned int zAxisEnablePin, unsigned int zAxisLimitSwitchPin, unsigned int zRotDynamixelId, unsigned int yRotDynamixelId);

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
int pressure() {return vacuumSystem_.pressure();}

// void setZPrimsaticSpeed(int speed);
void resetZPrimaticPosition();

protected:
DynamixelSerial dynamixel_;
HardwareSerial* dynamixelSerial_;
unsigned int zAxisRotDynamixelId_;
unsigned int yAxisRotDynamixelId_;

VacuumSystem vacuumSystem_;

Stepper zAxisStepper_;
int zAxisEnablePin;
unsigned int zAxisLimitSwitchPin_;
bool isStepperInSpeedMode_;

volatile bool zStopHit;
uint32_t time_z_cmd;

};


#endif /* ARM_H */
