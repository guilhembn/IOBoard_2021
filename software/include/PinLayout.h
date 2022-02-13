#ifndef PINLAYOUT_H
#define PINLAYOUT_H

#include <HardwareSerial.h>
#include <Arduino.h>

constexpr uint32_t ARM1_Z_DRIVER_STEP = PA1;
constexpr uint32_t ARM1_Z_DRIVER_DIR = PB0;
constexpr uint32_t ARM2_Z_DRIVER_STEP = PA0;
constexpr uint32_t ARM2_Z_DRIVER_DIR = PB1;

constexpr uint32_t PRESSURE_CLK = PA10;
constexpr uint32_t PRESSURE_HAT = PA5;
constexpr uint32_t PRESSURE_ARM1 = PA7;
constexpr uint32_t PRESSURE_ARM2 = PA6;

constexpr uint32_t DISPLAY_CLK = PB5;
constexpr uint32_t DISPLAY_DIO = PB4;


constexpr unsigned int ARM1_Z_ROT_DYNAMIXEL_ID = 1;
constexpr unsigned int ARM1_Y_ROT_DYNAMIXEL_ID = 2;
constexpr unsigned int ARM2_Z_ROT_DYNAMIXEL_ID = 3;
constexpr unsigned int ARM2_Y_ROT_DYNAMIXEL_ID = 4;

#define HAT_SERVO1 PA8
#define HAT_SERVO2 PA11

#define UART_TX PA2
#define UART_RX PA3

#define DYNAMIXELS_HALF_DUP_SERIAL Serial1

#define R_MEAS_PIN PA4


#endif /* PINLAYOUT_H */
