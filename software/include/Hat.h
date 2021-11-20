#ifndef HAT_H
#define HAT_H

#include "VacuumSystem.h"
#include "Servo.h"

#define LEVER_LENGTH 30  // In mm

class Hat{
public:
Hat(unsigned int pumpPin, unsigned int valvePin, unsigned int servoPin1, unsigned int servoPin2);

void init();

void extendTo(const int height);  // Extend the hat to a length of 'height', from the top of the hat (0, is fully up). In mm

void grasp();
void drop();

bool isTaken();
bool isReleased();

protected:
VacuumSystem vacuumSystem_;
Servo servo1_;
Servo servo2_;


};

#endif /* HAT_H */
