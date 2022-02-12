#include "VacuumSystem.h"

#include <Arduino.h>
#include "Gpios.h"
#include "Pressure.h"

VacuumSystem::VacuumSystem(Gpios::Signal pumpPin, Gpios::Signal valvePin, Pressure::Sensor vacuumSensor)
    : pumpPin_(pumpPin), valvePin_(valvePin), vacuumSensor(vacuumSensor){}

void VacuumSystem::init() {
    gpios.setMode(pumpPin_, OUTPUT);
    gpios.setMode(valvePin_, OUTPUT);
    release();
    openValve(false);
}

void VacuumSystem::startPump(bool start){
    gpios.write(pumpPin_, start ? HIGH : LOW);
    isPumpOn_ = start;
    updateState();
}

void VacuumSystem::openValve(bool open){
    gpios.write(valvePin_, open ? HIGH : LOW);
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
    return getPressure() >= PRESSURE_SENSOR_ATMO_VALUE;
}

bool VacuumSystem::isVacuumed() {
    return getPressure() <= PRESSURE_SENSOR_VACUUMED_VALUE;
}

int VacuumSystem::getPressure() {
    return pressure.read(vacuumSensor);
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
