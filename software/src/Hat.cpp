#include <Hat.h>
#include <math.h>

Hat::Hat(unsigned int pumpPin, unsigned int valvePin, unsigned int servoPin1, unsigned int servoPin2): vacuumSystem_(pumpPin, valvePin, 500, 200){
    servo1_.attach(servoPin1);
    servo2_.attach(servoPin2);
}

void Hat::init(){
    vacuumSystem_.init();
}

void Hat::extendTo(const int height){
    int servoAngle = round(asin(height / (2 * LEVER_LENGTH)));
    servo1_.write(servoAngle);
    servo2_.write(180 - servoAngle);
}

void Hat::grasp(){
    vacuumSystem_.suck();
}

void Hat::drop(){
    vacuumSystem_.release();
}

bool Hat::isReleased(){
    return vacuumSystem_.isReleased();
}

bool Hat::isTaken(){
    return vacuumSystem_.isVacuumed();
}