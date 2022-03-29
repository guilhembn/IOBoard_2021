#include "procedure_unstack.h"
#include "Arm.h"
#include "Arduino.h"

ProcUnstack proc_unstack;

ProcedureState ProcUnstack::loop() {
    if(current_state == State::UP) {
        if(arm->isNear(Arm::eJoint::PRISMATIC_Z, 2)) {
            arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 412);
            current_state = State::TURN_IN;
            setTimeout(1000);
        }
    }

    if(current_state == State::TURN_IN) {
        if(arm->isNear(Arm::eJoint::REVOLUTE_Z, 10)) {
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, -65);
            arm->startPump(true);
            current_state = State::DOWN;
            setTimeout(4000);
        }
    }

    if(current_state == State::DOWN) {
        if(arm->pressure() < -50) {
            float pz = arm->getPosition(Arm::eJoint::PRISMATIC_Z);
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, pz + 30);
            current_state = State::CLEAR_UP;
            setTimeout(2000);
        }
    }

    if(current_state == State::CLEAR_UP) {
        if(arm->isNear(Arm::eJoint::PRISMATIC_Z, 2)) {
            arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 820);
            current_state = State::TURN_OUT;
            setTimeout(1000);
        }
    }

    if(current_state == State::TURN_OUT) {
        if(arm->isNear(Arm::eJoint::REVOLUTE_Z, 10)) {
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, -130);
            current_state = State::DOWN_DROP;
            setTimeout(3000);
        }
    }

    if(current_state == State::DOWN_DROP) {
        if(arm->isNear(Arm::eJoint::PRISMATIC_Z, 2)) {
            arm->startPump(false);
            arm->openValve(true);
            current_state = State::DROP;
            setTimeout(1000);
        }
    }
    
    if(current_state == State::DROP) {
        if(arm->pressure() > -50) {
            arm->openValve(false);
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, -50);
            current_state = State::CLEAR_FINAL;
        }
    }

    if(current_state == State::CLEAR_FINAL) {
        if(arm->isNear(Arm::eJoint::PRISMATIC_Z, 2)) {
            status = protoduck::Procedure::Status::SUCCESS;
            return ProcedureState::IDLE;
        }
    }

    return ProcedureState::RUNNING;
}

ProcedureState ProcUnstack::reset() {
    if(!arm->isZMotorEnabled()) {
        setFailed();
        return ProcedureState::IDLE;
    }
    current_state = State::UP;
    status = protoduck::Procedure::Status::RUNNING;
    other_arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 700);
    arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Y, 332);
    arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, height);
    setTimeout(5000);
    return ProcedureState::RUNNING;
}

void ProcUnstack::setParam(int32_t p) {
    height = p;
}