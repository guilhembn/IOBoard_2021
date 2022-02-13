#include "procedure_turn_stack.h"
#include "Arm.h"
#include "Hat.h"

ProcTurnStack proc_turn_stack;

ProcedureState ProcTurnStack::loop() {

    static uint32_t time_mark = 0;

    if(current_state == State::INIT) {
        arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 306);
        arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Y, -180);

        float rz = arm->getPosition(Arm::eJoint::REVOLUTE_Z);
        float ry = arm->getPosition(Arm::eJoint::REVOLUTE_Y);

        if(abs(306-rz) < 5 && abs(-180-ry) < 5) {
            arm->startPump(true);
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, -130);
            current_state = State::DOWN;
        }
    }

    if(current_state == State::DOWN) {
        if(arm->pressure() > 160) {
            auto zpos = arm->getPosition(Arm::eJoint::PRISMATIC_Z);
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, zpos);
            //delay(200);
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, -40);
            current_state = State::UP;
        }
    }

    if(current_state == State::UP) {
        auto pz = arm->getPosition(Arm::eJoint::PRISMATIC_Z);
        if(abs(-40 - pz) < 2) {
            arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Y, 240);
            current_state = State::TURN_UP;
        }
    }

    if(current_state == State::TURN_UP)  {
        float ry = arm->getPosition(Arm::eJoint::REVOLUTE_Y);
        if(abs(240 - ry) < 10) {
            arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, -100);
            current_state = State::TURN;
        }
    }

    if(current_state == State::TURN)  {
        float rz = arm->getPosition(Arm::eJoint::REVOLUTE_Z);
        if(abs(-100 - rz) < 10) {
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, -25);
            hat.startPump(true);
            time_mark = millis();
            current_state = State::UP_HAT;
        }
    }

    if(current_state == State::UP_HAT) {
        float pz = arm->getPosition(Arm::eJoint::PRISMATIC_Z);
        if(pz > -28 && millis() - time_mark > 1000) {
            arm->openValve(true);
            arm->startPump(false);
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, -40);
            current_state = State::CLEAR_HAT;
        }
    }

//WAIT a bit more ???

    if(current_state == State::CLEAR_HAT) {
        float pz = arm->getPosition(Arm::eJoint::PRISMATIC_Z);
        if(pz < -38) {
            arm->openValve(false);
            arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 306);
            current_state = State::TURN_BACK;
        }
    }

    if(current_state == State::TURN_BACK) {
        float rz = arm->getPosition(Arm::eJoint::REVOLUTE_Z);
        if(abs(306 - rz) < 10) {
            hat.extendTo(abs(drop_height));
            time_mark = millis();
            current_state = State::LOWER;
        }
    }

    if(current_state == State::LOWER) {
        if(millis() - time_mark > 1000) {
            hat.startPump(false);
            hat.openValve(true);
            time_mark = millis();
            current_state = State::DROP;
        }
    }

    if(current_state == State::DROP) {
        if(millis() - time_mark > 500) {
            hat.openValve(false);
            hat.extendTo(0);
            time_mark = millis();
            current_state = State::HAT_UP;
        }
    }

    if(current_state == State::HAT_UP) {
        if(millis() - time_mark > 500) {
            status = protoduck::Procedure::Status::SUCCESS;
            return ProcedureState::IDLE;
        }  
    }

    return ProcedureState::RUNNING;
}

void ProcTurnStack::setParam(int32_t p) {
    drop_height = p;
}

void ProcTurnStack::reset() {
    current_state = State::INIT;
    status = protoduck::Procedure::Status::RUNNING;
}
