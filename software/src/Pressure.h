#pragma once
#include <inttypes.h>

class Pressure {

public:

    enum Sensor {
        ARM1,
        ARM2,
        HAT,
    };

    Pressure(){};

    int32_t read(Sensor sensor) {return 42;}

};

extern Pressure pressure;