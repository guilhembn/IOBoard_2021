#ifndef VACUUMSYSTEM_H
#define VACUUMSYSTEM_H

#include <stdint.h>

#define PRESSURE_SENSOR_VACUUMED_VALUE 100
#define PRESSURE_SENSOR_ATMO_VALUE 800

class VacuumSystem{
    public:
    VacuumSystem(unsigned int pumpPin, unsigned int valvePin, unsigned int vacuumSensorPin);
    VacuumSystem(unsigned int pumpPin, unsigned int valvePin, unsigned int vacuumDuration, unsigned int releaseDuration);

    void init();

    bool isVacuumed();
    bool isReleased();
    void suck();
    void release();
    void startPump(bool start = true);
    void openValve(bool open = true);
    bool isPumpOn() { return isPumpOn_;}
    bool isValveOpen() {return isValveOpen_;}
    int pressure();

    protected:
    void updateState();

    unsigned int pumpPin_;
    unsigned int valvePin_;
    int vacuumSensorPin_;
    unsigned int vacuumDuration_;
    unsigned int releaseDuration_;
    uint32_t releaseStartTime_;
    uint32_t suckStartTime_;
    bool isSucking_;
    bool isReleasing_;
    bool isPumpOn_;
    bool isValveOpen_;
};

#endif /* VACUUMSYSTEM_H */
