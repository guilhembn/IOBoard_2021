#include "procedure_home.h"
#include "Arm.h"
#include "Arduino.h"

ProcHome proc_home;

ProcedureState ProcHome::loop() {
    if(current_state == State::INITIAL_DOWN) {
        if(arm->zStopStatus() == HIGH) {
            time_zstop_released = millis();
            current_state = State::WAIT;
        }
    }

    if(current_state == State::WAIT) {
        if(millis() - time_zstop_released > 500) {
            arm->zAxisStepper_.setTargetRel(10000);
            arm->controller.moveAsync(arm->zAxisStepper_);
            current_state = State::UP;
        }
    }

    if(current_state == State::UP) {
        if(arm->zStopStatus() == LOW) {
            arm->zAxisStepper_.setMaxSpeed(STEPPER_MAX_SPEED);
            arm->zAxisStepper_.setPosition(5*STEP_PER_MM);
            arm->zAxisStepper_.setTargetAbs(0);  // go down 5mm to release stop switch
            arm->controller.move(arm->zAxisStepper_);
            current_state = State::DOWN_FINAL;
        }
    }

    if(current_state == State::DOWN_FINAL) {
        auto pos = arm->zAxisStepper_.getPosition();
        if(abs(pos) < STEP_PER_MM) {
            arm->rotateIdle();
            status = protoduck::Procedure::Status::SUCCESS;
            return ProcedureState::IDLE;
        }

    }

    return ProcedureState::RUNNING;
}

void ProcHome::reset() {
    arm->enableZMotor(true);
    arm->zAxisStepper_.setPosition(0);
    arm->zAxisStepper_.setMaxSpeed(STEPPER_HOME_SPEED);     // slow
    if(arm->zStopStatus()) {
        current_state = UP;
        arm->zAxisStepper_.setTargetAbs(10000);
    } else {
        current_state = INITIAL_DOWN;
        arm->zAxisStepper_.setTargetAbs(-10000);
    }
    
    arm->controller.moveAsync(arm->zAxisStepper_);

    arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 820);
    arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Y, 512);


    status = protoduck::Procedure::Status::RUNNING;
}
