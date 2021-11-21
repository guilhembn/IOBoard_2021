#include "VacuumSystem.h"

#include <Arduino.h>

VacuumSystem::VacuumSystem(unsigned int pumpPin, unsigned int valvePin, unsigned int vacuumSensorPin)
    : pumpPin_(pumpPin), valvePin_(valvePin), vacuumSensorPin_(vacuumSensorPin), vacuumDuration_(0), releaseDuration_(0) {}

VacuumSystem::VacuumSystem(unsigned int pumpPin, unsigned int valvePin, unsigned int vacuumDuration, unsigned int releaseDuration)
    : pumpPin_(pumpPin), valvePin_(valvePin), vacuumSensorPin_(-1), vacuumDuration_(vacuumDuration), releaseDuration_(releaseDuration) {}

void VacuumSystem::init() {
    pinMode(pumpPin_, OUTPUT);
    pinMode(valvePin_, OUTPUT);
    if (vacuumSensorPin_ != -1) {
        pinMode((uint32_t)vacuumSensorPin_, INPUT);
    }
    release();
    openValve(false);
}

void VacuumSystem::startPump(bool start){
    digitalWrite(pumpPin_, start ? HIGH : LOW);
    isPumpOn_ = start;
    updateState();
}

void VacuumSystem::openValve(bool open){
    digitalWrite(valvePin_, open ? HIGH : LOW);
    isValveOpen_ = open;
    updateState();
}

void VacuumSystem::suck() {
    startPump(true);
    openValve(false);
}

void VacuumSystem::release() {
    startPump(false);
    openValve(true);
}

bool VacuumSystem::isReleased() {
    if (vacuumSensorPin_ != -1) {
        return analogRead(vacuumSensorPin_) >= PRESSURE_SENSOR_ATMO_VALUE;
    } else {
        return isReleasing_ && (millis() - releaseStartTime_) >= releaseDuration_;
    }
}

bool VacuumSystem::isVacuumed() {
    if (vacuumSensorPin_ != -1) {
        return analogRead(vacuumSensorPin_) <= PRESSURE_SENSOR_VACUUMED_VALUE;
    } else {
        return isSucking_ && (millis() - suckStartTime_) >= vacuumDuration_;
    }
}

int VacuumSystem::pressure() {
    if (vacuumSensorPin_ != -1) {
        return analogRead(vacuumSensorPin_);
    } else {
        return 0;
    }
}

void VacuumSystem::updateState(){
    if (isSucking_){
        if (!isPumpOn_ || isValveOpen_){
            isSucking_ = false;
        }
    }else{
        if (isPumpOn_ && !isValveOpen_){
            isSucking_ = true;
            suckStartTime_ = millis();
        }
    }
    if (isReleasing_){
        if (isPumpOn_ || !isValveOpen_){
            isReleasing_ = false;
        }
    }else{
        if (!isPumpOn_ && isValveOpen_){
            isReleasing_ = true;
            releaseStartTime_ = millis();
        }
    }
}