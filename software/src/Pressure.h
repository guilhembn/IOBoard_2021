#pragma once
#include <Arduino.h>
#include "Display.h"

constexpr int N = 3;
constexpr uint32_t PRESSURE_PERIOD = 200;

class Pressure {

public:
    static const int GAIN128 = 1;
    static const int GAIN64 = 2;
    static const int GAIN32 = 3;

    Pressure(int clk, std::array<int, N> dios):_clk(clk), _dio(dios), _gain(GAIN128){};

    enum Sensor {
        ARM1 = 0,
        ARM2 = 1,
        HAT = 2,
    };

    float read_sensor(Sensor sensor) {
        return last_read[static_cast<int>(sensor)]/1000.0;
    }


    void begin() {
        pinMode(_clk, OUTPUT);
        _offsets.fill(0);

        for(int i=0; i<N; i++) {
            pinMode(_dio[i], INPUT);
        }

        digitalWrite(_clk, LOW);
    }

    bool isReady() {
        bool ready = true;
        for(int i=0; i<N; i++) {
            if (digitalRead(_dio[i]) == HIGH) {
                ready = false;
            }
        }     
        return ready;
    }

    std::array<float, N> read() {
        std::array<float, N> ret = {0};;
        digitalWrite(_clk, LOW);
        while(!isReady()) {}

        noInterrupts();

        std::array<int32_t, N> values = {0};
        uint32_t mask = 0x800000;
        while (mask > 0)
        {
            digitalWrite(_clk, HIGH);
            delayMicroseconds(1);               // T2  >= 0.2 us

            for(int i=0; i<N; i++) {
                if (digitalRead(_dio[i]) == HIGH) {
                    values[i] |= mask;
                }
            }
            
            digitalWrite(_clk, LOW);
            delayMicroseconds(1);               // keep duty cycle ~50%
            mask >>= 1;
        }

        for(int i=0; i<_gain; i++) {
            digitalWrite(_clk, HIGH);
            delayMicroseconds(1);
            digitalWrite(_clk, LOW);
            delayMicroseconds(1);
        }

        interrupts();

        //  SIGN extend
        for(int i=0; i<N; i++) {
            if (values[i] & 0x800000) { values[i] |= 0xFF000000; }
        }
        
        for(int i=0; i<N; i++) {
            ret[i] = 0.01 * values[i];
        }

        return ret;
    }

    std::array<float, N> read_avg(int samples=10) {
        std::array<float, N> out = {0};

        for(int i=0; i<samples; i++) {
            auto vals = read();
            for(int i=0; i<N; i++) {
                out[i] += vals[i];
            }
        }
        for(int i=0; i<N; i++) {
            out[i] = out[i] / samples - _offsets[i];
        }
        return out;
    }

    void tare() {
        _offsets.fill(0);
        auto vals = read_avg();

        for(int i=0; i<N; i++) {
            _offsets[i] = vals[i];
        }
    }

    void loop() {
        if(millis() - last_time > PRESSURE_PERIOD) {
            last_read = read_avg(2);
            last_time = millis();
        }
    }


private:
    int _clk;
    std::array<int, N> _dio;
    int _gain;
    std::array<float, N> _offsets;
    uint32_t last_time;
    std::array<float, N> last_read;
};


extern Pressure pressure;