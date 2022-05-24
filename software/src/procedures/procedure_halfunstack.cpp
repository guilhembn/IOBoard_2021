#include "procedure_halfunstack.h"
#include "Arm.h"
#include "Arduino.h"

ProcHalfUnstack proc_half_unstack;

ProcedureState ProcHalfUnstack::loop() {
    if(current_state == State::UP) {
        if(arm->isNear(Arm::eJoint::PRISMATIC_Z, 2)) {
            arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 412);
            current_state = State::TURN_IN;
            setTimeout(1000);
        }
    }

    if(current_state == State::TURN_IN) {
        if(arm->isNear(Arm::eJoint::REVOLUTE_Z, 10)) {
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, height);
            arm->startPump(true);
            arm->openValve(false);
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
            arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Y, 490);
            current_state = State::TURN_FRONT;
            setTimeout(2000);
        }
    }

    if(current_state == State::TURN_FRONT) {
        if(arm->isNear(Arm::eJoint::REVOLUTE_Y, 5)) {
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, -30);
            current_state = State::DOWN_DEPOSE;
            setTimeout(1000);
        }
    }
    
    if(current_state == State::DOWN_DEPOSE) {
        if(arm->isNear(Arm::eJoint::PRISMATIC_Z, 2)) {
            status = protoduck::Procedure::Status::SUCCESS;
            return ProcedureState::IDLE;
        }
    }

    return ProcedureState::RUNNING;
}

ProcedureState ProcHalfUnstack::reset() {
    if(!arm->isZMotorEnabled()) {
        setFailed();
        return ProcedureState::IDLE;
    }
    current_state = State::UP;
    status = protoduck::Procedure::Status::RUNNING;
    other_arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 700);
    arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Y, 332);
    arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, min(height+30, 0L));
    setTimeout(5000);
    return ProcedureState::RUNNING;
}

void ProcHalfUnstack::setParam(int32_t p) {
    height = p;
}