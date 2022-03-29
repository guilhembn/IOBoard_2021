#include "procedure_stack.h"
#include "Arm.h"

ProcStack proc_stack;

ProcedureState ProcStack::loop() {
    if(current_state == State::INIT) {
        if(arm->isNear(Arm::eJoint::REVOLUTE_Z, 5) && arm->isNear(Arm::eJoint::REVOLUTE_Y, 5)) {
            arm->startPump(true);
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, -135);
            current_state = State::DOWN;
            setTimeout(5000);
        }
    }

    if(current_state == State::DOWN) {
        if(arm->pressure() < -50) {
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, drop_height);
            current_state = State::UP;
            setTimeout(4000);
        }
    }

    if(current_state == State::UP) {
        if(arm->isNear(Arm::eJoint::PRISMATIC_Z, 2)) {
            arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 412);
            current_state = State::TURN;
            setTimeout(2000);
        }
    }

    if(current_state == State::TURN)  {
        if(arm->isNear(Arm::eJoint::REVOLUTE_Z, 10)) {
            arm->startPump(false);
            arm->openValve(true);
            current_state = State::DROP;
            setTimeout(2000);
        }
    }

    if(current_state == State::DROP)  {
        if(arm->pressure() > -50) {
            arm->openValve(false);
            status = protoduck::Procedure::Status::SUCCESS;
            return ProcedureState::IDLE;
        }
    }


    return ProcedureState::RUNNING;
}

void ProcStack::setParam(int32_t p) {
    drop_height = p;
}

ProcedureState ProcStack::reset() {
    if(!arm->isZMotorEnabled()) {
        setFailed();
        return ProcedureState::IDLE;
    }
    current_state = State::INIT;
    status = protoduck::Procedure::Status::RUNNING;
    arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 820);
    arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Y, 332);
    other_arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 700);
    setTimeout(1000);
    return ProcedureState::RUNNING;
}
