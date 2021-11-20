#include "VacuumSystem.h"

#include <Arduino.h>

VacuumSystem::VacuumSystem(unsigned int pumpPin, unsigned int valvePin, unsigned int vacuumSensorPin): 
pumpPin_(pumpPin), valvePin_(valvePin), vacuumSensorPin_ (vacuumSensorPin), vacuumDuration_(0), releaseDuration_(0){}

VacuumSystem::VacuumSystem(unsigned int pumpPin, unsigned int valvePin, unsigned int vacuumDuration, unsigned int releaseDuration):
pumpPin_(pumpPin), valvePin_(valvePin), vacuumSensorPin_(-1), vacuumDuration_(vacuumDuration), releaseDuration_(releaseDuration){}

void VacuumSystem::init(){
    pinMode(pumpPin_, OUTPUT);
    pinMode(valvePin_, OUTPUT);
    if (vacuumSensorPin_ != -1){
        pinMode((uint32_t) vacuumSensorPin_, INPUT);
    }
}

void VacuumSystem::suck(){
    digitalWrite(pumpPin_, HIGH);
    digitalWrite(valvePin_, LOW);
    suckStartTime_ = millis();
    isSucking_ = true;
    isReleasing_ = false;
}

void VacuumSystem::release(){
    digitalWrite(pumpPin_, LOW);
    digitalWrite(valvePin_, HIGH);
    releaseStartTime_ = millis();
    isReleasing_ = true;
    isSucking_ = false;
}

bool VacuumSystem::isReleased(){
    if (vacuumSensorPin_ != -1){
        return analogRead(vacuumSensorPin_) >= PRESSURE_SENSOR_ATMO_VALUE;
    }else{
        return isReleasing_ && (millis() - releaseStartTime_) >= releaseDuration_;
    }
}

bool VacuumSystem::isVacuumed(){
    if (vacuumSensorPin_ != -1){
        return analogRead(vacuumSensorPin_) <= PRESSURE_SENSOR_VACUUMED_VALUE;
    }else{
        return isSucking_ && (millis() - suckStartTime_) >= vacuumDuration_;
    }
}