#include <Hat.h>
#include <math.h>

Hat::Hat(unsigned int pumpPin, unsigned int valvePin, unsigned int servoPin1, unsigned int servoPin2)
    : vacuumSystem_(pumpPin, valvePin, 500, 200), servo1Pin_(servoPin1), servo2Pin_(servoPin2) {}

void Hat::init() {
    vacuumSystem_.init();
    servo1_.attach(servo1Pin_);
    servo2_.attach(servo2Pin_);
    extendTo(0);
}

void Hat::extendTo(const int height) {
    // Extended 1055; Retracted 1925
    // int servoAngle = 90 + round(asin((float)height / (2. * (float)LEVER_LENGTH)) * 180. / 3.14159265);
    // servo1_.writeMicroseconds(servoAngle);
    // servo2_.writeMicroseconds(servoAngle);
    if (height > 10) {
        servo1_.writeMicroseconds(1055);
        servo2_.writeMicroseconds(1055);
    } else {
        servo1_.writeMicroseconds(1925);
        servo2_.writeMicroseconds(1925);
    }
}

int Hat::getHeight() { return round(2 * LEVER_LENGTH * sin((float)servo1_.read() * 3.14159265 / 180.)); }

void Hat::grasp() { vacuumSystem_.suck(); }

void Hat::drop() { vacuumSystem_.release(); }

bool Hat::isReleased() { return vacuumSystem_.isReleased(); }

bool Hat::isTaken() { return vacuumSystem_.isVacuumed(); }