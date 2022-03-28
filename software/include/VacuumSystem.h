#ifndef VACUUMSYSTEM_H
#define VACUUMSYSTEM_H

#include <stdint.h>
#include "Gpios.h"
#include "Pressure.h"

#define PRESSURE_SENSOR_VACUUMED_VALUE 100
#define PRESSURE_SENSOR_ATMO_VALUE 800

class VacuumSystem{
    public:
    VacuumSystem(Gpios::Signal pumpPin, Gpios::Signal valvePin, Pressure::Sensor vacuumSensorPin);
  
    void init();

    bool isVacuumed();
    bool isReleased();
    void suck();
    void release();
    void startPump(bool start = true);
    void openValve(bool open = true);
    bool isPumpOn() { return isPumpOn_;}
    bool isValveOpen() {return isValveOpen_;}
    float getPressure();

    protected:
    void updateState();

    Gpios::Signal pumpPin_;
    Gpios::Signal valvePin_;
    Pressure::Sensor vacuumSensor;
    uint32_t releaseStartTime_;
    uint32_t suckStartTime_;
    bool isSucking_;
    bool isReleasing_;
    bool isPumpOn_;
    bool isValveOpen_;
};

#endif /* VACUUMSYSTEM_H */
