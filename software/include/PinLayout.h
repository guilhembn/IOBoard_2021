#ifndef PINLAYOUT_H
#define PINLAYOUT_H

#include <variant_NUCLEO_L432KC.h>
#include <HardwareSerial.h>

#define ARM_VAC_PUMP PA12
#define ARM_VAC_SENSOR PA4
#define ARM_VALVE PA10
#define ARM_Z_DRIVER_STEP PA1
#define ARM_Z_DRIVER_DIR PA0
#define ARM_Z_DRIVER_ENABLE PA6
#define ARM_Z_LIMIT_SWITCH PA7
#define ARM_Z_ROT_DYNAMIXEL_ID 1
#define ARM_Y_ROT_DYNAMIXEL_ID 2

#define HAT_VAC_PUMP PA5
#define HAT_VALVE PB5
#define HAT_SERVO1 PA8
#define HAT_SERVO2 PA11

#define UART_TX PA2
#define UART_RX PA3

#define DYNAMIXELS_HALF_DUP_SERIAL Serial1


#endif /* PINLAYOUT_H */
