#include <Arduino.h>
#include "PinLayout.h"
#include "Arm.h"
#include "Hat.h"

Arm arm(ARM_VAC_PUMP, ARM_VALVE, ARM_VAC_SENSOR, &DYNAMIXELS_HALF_DUP_SERIAL, ARM_Z_DRIVER_STEP, ARM_Z_DRIVER_DIR, 
        ARM_Z_DRIVER_ENABLE, ARM_Z_LIMIT_SWITCH, ARM_Z_ROT_DYNAMIXEL_ID, ARM_Y_ROT_DYNAMIXEL_ID);

Hat hat(HAT_VAC_PUMP, HAT_VALVE, HAT_SERVO1, HAT_SERVO2);

void setup() {
  arm.init();
  hat.init();
}

void loop() {
  arm.loop();
}