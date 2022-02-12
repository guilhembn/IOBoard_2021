#ifndef HAT_H
#define HAT_H

#include "VacuumSystem.h"
#include "Servo.h"

#define LEVER_LENGTH 30  // In mm

constexpr float EPSILON = 0.01;
constexpr float HEIGHT_SPEED = 10.0;
constexpr uint32_t HAT_PERIOD = 15;

class Hat{
public:
Hat(Gpios::Signal pumpPin, Gpios::Signal valvePin, Pressure::Sensor pressureSensor, unsigned int servoPin1, unsigned int servoPin2);

void init();

void loop();

void extendTo(const float height);  // Extend the hat to a length of 'height', from the top of the hat (0, is fully up). In mm
int getHeight();

void grasp();
void drop();

void startPump(bool start){vacuumSystem_.startPump(start);}
void openValve(bool open){vacuumSystem_.openValve(open);}
bool isPumpStarted() {return vacuumSystem_.isPumpOn();}
bool isValveOpen() {return vacuumSystem_.isValveOpen();}

bool isTaken();
bool isReleased();

protected:
VacuumSystem vacuumSystem_;
unsigned int servo1Pin_;
unsigned int servo2Pin_;
Servo servo1_;
Servo servo2_;
float height;
float height_setpoint;
};

extern Hat hat;

#endif /* HAT_H */
