#pragma once
#include <Arduino.h>

constexpr uint8_t TCA1_ADDR = 0x20;
constexpr uint8_t TCA2_ADDR = 0x21;
constexpr uint32_t TCA_INT = PA12;

constexpr uint8_t TCA_INPUT_PORT = 0x00;
constexpr uint8_t TCA_OUTPUT_PORT = 0x01;
constexpr uint8_t TCA_POL_INV = 0x02;
constexpr uint8_t TCA_CONFIG = 0x03;

class Gpios {
public:

    enum Signal {
        HAT_VAC_PUMP,
        HAT_VALVE,
        ARM1_VALVE,
        ARM1_VAC_PUMP,
        ARM1_Z_DRIVER_ENABLE,
        ARM1_Z_LIMIT_SWITCH,
        ARM1_Z_DIR,
        ARM1_Z_STEP,
        ARM2_VALVE,
        ARM2_VAC_PUMP,
        ARM2_Z_DRIVER_ENABLE,
        ARM2_Z_LIMIT_SWITCH,
        ARM2_Z_DIR,
        ARM2_Z_STEP,
        PRESSURE_CLK,
        PRESSURE_HAT,
        PRESSURE_ARM1,
        PRESSURE_ARM2,
        DISPLAY_CLK,
        DISPLAY_DIO,
        COLOR,
        TIRETTE,
        LED_R,
        LED_G,
        LED_B,
        BUTTON,
        LED,
    };

    Gpios():tca_interrupt(false){}
    void init();
    
    void setMode(Signal signal, uint32_t mode);
    void write(Signal signal, uint32_t val);
    void toggle(Signal signal);
    int read(Signal signal);

private:
    enum Bank {
        GPIO,
        TCA1,
        TCA2,
    };

    struct PinDef
    {
        Signal signal;
        Bank bank;
        uint32_t pin;
    };
    
    PinDef getDefinition(Signal signal);
    uint8_t tcaConfigure(uint8_t addr, uint8_t config);
    uint8_t tcaWrite(uint8_t addr, uint8_t data);
    void tca1Read();

    bool tca_interrupt;
    uint8_t tca1_state;
    uint8_t tca2_state;
    
    // input=1, output=0
    static constexpr uint8_t TCA1_CONFIG = 0b11011001;
    static constexpr uint8_t TCA2_CONFIG = 0b00000000;

    static constexpr std::array<PinDef, 27> _definitions {{
        {HAT_VAC_PUMP, TCA2, 2},
        {HAT_VALVE, TCA2, 4},
        {ARM1_VALVE, TCA2, 3},
        {ARM1_VAC_PUMP, TCA2, 0},
        {ARM1_Z_DRIVER_ENABLE, TCA2, 6},
        {ARM1_Z_LIMIT_SWITCH, TCA1, 7},
        {ARM1_Z_DIR, GPIO, PB0},
        {ARM1_Z_STEP, GPIO, PA1},
        {ARM2_VALVE, TCA2, 5},
        {ARM2_VAC_PUMP, TCA2, 1},
        {ARM2_Z_DRIVER_ENABLE, TCA2, 7},
        {ARM2_Z_LIMIT_SWITCH, TCA1, 6},
        {ARM2_Z_DIR, GPIO, PB1},
        {ARM2_Z_STEP, GPIO, PA0},
        {PRESSURE_CLK, GPIO, PA10},
        {PRESSURE_HAT, GPIO, PA5},
        {PRESSURE_ARM1, GPIO, PA7},
        {PRESSURE_ARM2, GPIO, PA6},
        {DISPLAY_CLK, GPIO, PB5},
        {DISPLAY_DIO, GPIO, PB4},
        {COLOR, TCA1, 0},
        {TIRETTE, TCA1, 3},
        {LED_R, TCA1, 5},
        {LED_G, TCA1, 1},
        {LED_B, TCA1, 2},
        {BUTTON, TCA1, 4},
        {LED, GPIO, LED_BUILTIN},
    }};


};

extern Gpios gpios;