#ifndef PINLAYOUT_H
#define PINLAYOUT_H

#include <variant_NUCLEO_L432KC.h>
#include <HardwareSerial.h>

constexpr uint32_t ARM1_Z_DRIVER_STEP = PA1;
constexpr uint32_t ARM1_Z_DRIVER_DIR = PB0;
constexpr uint32_t ARM2_Z_DRIVER_STEP = PA0;
constexpr uint32_t ARM2_Z_DRIVER_DIR = PB1;

#define ARM_Z_ROT_DYNAMIXEL_ID 1
#define ARM_Y_ROT_DYNAMIXEL_ID 2

#define HAT_SERVO1 PA8
#define HAT_SERVO2 PA11

#define UART_TX PA2
#define UART_RX PA3

#define DYNAMIXELS_HALF_DUP_SERIAL Serial1

#define R_MEAS_PIN PA4


#endif /* PINLAYOUT_H */
