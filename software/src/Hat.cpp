#include <Hat.h>
#include <math.h>
#include <Arduino.h>

int clamp(float val, float lo, float hi) {
    if(val > hi) {return hi;}
    if(val < lo) {return lo;}
    return val;
}

Hat::Hat(unsigned int pumpPin, unsigned int valvePin, unsigned int servoPin1, unsigned int servoPin2) :
    vacuumSystem_(pumpPin, valvePin, 500, 200),
    servo1Pin_(servoPin1), servo2Pin_(servoPin2),
    height(0), height_setpoint(0)
{}

void Hat::init() {
    vacuumSystem_.init();
    servo1_.attach(servo1Pin_);
    servo2_.attach(servo2Pin_);
    extendTo(0);
}

void Hat::loop() {
    static uint32_t last_time = millis();
    uint32_t dt = millis() - last_time;
    if (dt < HAT_PERIOD) {
        return;
    }

    if(abs(height_setpoint - height) > EPSILON) {
        float dhMax = HEIGHT_SPEED*dt/1000.0;
        if(abs(height_setpoint - height) < dhMax) {
            height = height_setpoint;
        } else {
            if(height_setpoint > height) {
                height += dhMax;
            } else {
                height -= dhMax;
            }
        }
    }

    int u1 = 1925 + (1055-1925)/10 * height;
    int u2 = 1925 + (1055-1925)/10 * height;
    servo1_.writeMicroseconds(u1);
    servo2_.writeMicroseconds(u2);

    last_time = millis();
}

void Hat::extendTo(const float h) {
    // Extended 1055; Retracted 1925
    // int servoAngle = 90 + round(asin((float)height / (2. * (float)LEVER_LENGTH)) * 180. / 3.14159265);
    height_setpoint = clamp(h, 0, 10);
}

int Hat::getHeight() { 
    //return round(2 * LEVER_LENGTH * sin((float)servo1_.read() * 3.14159265 / 180.));
    return height;
}

void Hat::grasp() { vacuumSystem_.suck(); }

void Hat::drop() { vacuumSystem_.release(); }

bool Hat::isReleased() { return vacuumSystem_.isReleased(); }

bool Hat::isTaken() { return vacuumSystem_.isVacuumed(); }