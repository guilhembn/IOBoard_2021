#include <Arduino.h>

#include "Arm.h"
#include "Hat.h"
#include "PinLayout.h"
#include "ducklink/Communication.h"
#include "procedures/ProcedureManager.h"
#include "Gpios.h"
#include "Pressure.h"
#include "Display.h"

uint32_t status_time = 0;

Message cmd;

unsigned long lastSent = 0;
Arm* status_arm = &arm2;

void setup() {
    gpios.init();
    gpios.setMode(Gpios::LED, OUTPUT);
    Serial.begin(115200);
    communication.init(115200);
    pressure.begin();
    display.init();
    display.clearScreen();
    display.setBrightness(7);
    display.display(0);
    pressure.tare();
    hat.init();
    arm1.init();
    delay(500);
    arm2.init();
    procedure_manager.init();
}

void loop() {

    pressure.loop();
    arm1.loop();
    arm2.loop();
    hat.loop();
    procedure_manager.loop();

    Communication::eMessageStatus msgStatus = communication.checkMessages(cmd);
    if (msgStatus == Communication::eMessageStatus::NEW_MSG) {
        if (cmd.msg_type() == Message::MsgType::COMMAND) {
            if (cmd.has_arm()) {
                Arm* arm = &arm1;
                if(cmd.arm().arm_id() == protoduck::ArmID::ARM2) {
                    arm = &arm2;
                }
                arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, std::round(cmd.arm().traZ()));
                arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, std::round(cmd.arm().rotZ()));
                arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Y, std::round(cmd.arm().rotY()));
                arm->startPump(cmd.arm().pump());
                arm->openValve(cmd.arm().valve());
            } else if (cmd.has_hat()) {
                hat.extendTo(cmd.hat().height());
                hat.startPump(cmd.hat().pump());
                hat.openValve(cmd.hat().valve());
            } else if(cmd.has_procedure()) {
                protoduck::Procedure::Proc procedure = cmd.procedure().get_proc();
                auto param = cmd.procedure().get_param();
                auto arm_id = cmd.procedure().get_arm_id();
                if((int)procedure <= (int)protoduck::Procedure::Proc::TAKE_FROM_STACK ||
                    (int)procedure == (int)protoduck::Procedure::Proc::HALF_UNSTACK) {
                    procedure_manager.queueProcedure(procedure, arm_id, param);
                }
            } else if(cmd.has_hmi()) {
                uint32_t led = cmd.hmi().get_led();
                uint32_t score = cmd.hmi().get_hmi_display();
                display.clearScreen();
                display.display(score);
                // LED
                gpios.write(Gpios::Signal::LED_R, led & (1<<0));
                gpios.write(Gpios::Signal::LED_G, led & (1<<1));
                gpios.write(Gpios::Signal::LED_B, led & (1<<2));
            }
        }
    }

    if(millis() - status_time > 200) {
        communication.sendHatStatus(hat);
        communication.sendArmStatus(*status_arm);
        communication.sendProcedureStatus(procedure_manager);
        communication.sendHMI();
        status_time = millis();
        gpios.toggle(Gpios::LED);

        //alternate arm1 and arm2 status report
        if(status_arm == &arm1) {
            status_arm = &arm2;
        } else {
            status_arm = &arm1;
        }
    }    
}
