#include <Hat.h>
#include <math.h>

Hat::Hat(unsigned int pumpPin, unsigned int valvePin, unsigned int servoPin1, unsigned int servoPin2) : vacuumSystem_(pumpPin, valvePin, 500, 200) {
    servo1_.attach(servoPin1);
    servo2_.attach(servoPin2);
}

void Hat::init() { vacuumSystem_.init(); }

void Hat::extendTo(const int height) {
    int servoAngle = round(asin((float)height / (2. * (float)LEVER_LENGTH)) * 180. / 3.14159265);
    servo1_.write(servoAngle);
    servo2_.write(180 - servoAngle);
}

int Hat::getHeight() { return round(2 * LEVER_LENGTH * sin((float)servo1_.read() * 3.14159265 / 180.)); }

void Hat::grasp() { vacuumSystem_.suck(); }

void Hat::drop() { vacuumSystem_.release(); }

bool Hat::isReleased() { return vacuumSystem_.isReleased(); }

bool Hat::isTaken() { return vacuumSystem_.isVacuumed(); }