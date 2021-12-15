#include "procedure_stack.h"
#include "Arm.h"

ProcStack proc_stack;


ProcedureState ProcStack::loop() {
    if(current_state == State::INIT) {
        arm.sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 306);
        arm.sendPositionCommand(Arm::eJoint::REVOLUTE_Y, -180);

        float rz = arm.getPosition(Arm::eJoint::REVOLUTE_Z);
        float ry = arm.getPosition(Arm::eJoint::REVOLUTE_Y);

        if(abs(306-rz) < 5 && abs(-180-ry) < 5) {
            arm.startPump(true);
            arm.sendPositionCommand(Arm::eJoint::PRISMATIC_Z, -130);
            current_state = State::DOWN;
        }
    }

    if(current_state == State::DOWN) {
        if(arm.pressure() > 160) {
            auto zpos = arm.getPosition(Arm::eJoint::PRISMATIC_Z);
            arm.sendPositionCommand(Arm::eJoint::PRISMATIC_Z, zpos);
            //delay(200);
            arm.sendPositionCommand(Arm::eJoint::PRISMATIC_Z, drop_height);
            current_state = State::UP;
        }
    }

    if(current_state == State::UP) {
        auto pz = arm.getPosition(Arm::eJoint::PRISMATIC_Z);
        if(abs(drop_height - pz) < 2) {
            arm.sendPositionCommand(Arm::eJoint::REVOLUTE_Z, -100);
            current_state = State::TURN;
        }
    }

    if(current_state == State::TURN)  {
        float rz = arm.getPosition(Arm::eJoint::REVOLUTE_Z);
        if(abs(-100 - rz) < 10) {
            arm.startPump(false);
            arm.openValve(true);
            current_state = State::DROP;
        }
    }

    if(current_state == State::DROP)  {
        if(arm.pressure() < 130) {
            arm.openValve(false);
            return ProcedureState::IDLE;
        }
    }


    return ProcedureState::RUNNING;
}

void ProcStack::setParam(int32_t p) {
    drop_height = p;
}

void ProcStack::reset() {
    current_state = State::INIT;
}

protoduck::ProcedureStatus::Status ProcStack::getStatus() {
    return protoduck::ProcedureStatus::Status::RUNNING;
};
