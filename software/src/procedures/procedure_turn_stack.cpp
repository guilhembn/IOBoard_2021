#include "procedure_turn_stack.h"
#include "Arm.h"
#include "Hat.h"

ProcTurnStack proc_turn_stack;

ProcedureState ProcTurnStack::loop() {

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
            auto zpos = arm->getPosition(Arm::eJoint::PRISMATIC_Z);
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, zpos);
            //delay(200);
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, -40);
            current_state = State::UP;
            setTimeout(4000);
        }
    }

    if(current_state == State::UP) {
        if(arm->isNear(Arm::eJoint::PRISMATIC_Z, 2)) {
            arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Y, 750);
            current_state = State::TURN_UP;
            setTimeout(2000);
        }
    }

    if(current_state == State::TURN_UP)  {
        if(arm->isNear(Arm::eJoint::REVOLUTE_Y, 10)) {
            arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 412);
            current_state = State::TURN;
            setTimeout(2000);
        }
    }

    if(current_state == State::TURN)  {
        if(arm->isNear(Arm::eJoint::PRISMATIC_Z, 10)) {
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, 0);
            hat.startPump(true);
            current_state = State::UP_HAT;
            setTimeout(3000);
        }
    }

    if(current_state == State::UP_HAT) {
        if(hat.pressure() < -50) {
            arm->openValve(true);
            arm->startPump(false);
            arm->sendPositionCommand(Arm::eJoint::PRISMATIC_Z, -40);
            current_state = State::CLEAR_HAT;
            setTimeout(2000);
        }
    }

//WAIT a bit more ???

    if(current_state == State::CLEAR_HAT) {
        float pz = arm->getPosition(Arm::eJoint::PRISMATIC_Z);
        if(pz < -38) {
            arm->openValve(false);
            arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 820);
            current_state = State::TURN_BACK;
            setTimeout(2000);
        }
    }

    if(current_state == State::TURN_BACK) {
        if(arm->isNear(Arm::eJoint::REVOLUTE_Z, 10)) {
            hat.startPump(false);
            hat.openValve(true);
            current_state = State::DROP;
            setTimeout(2000);
        }
    }

    if(current_state == State::DROP) {
        if(hat.pressure() > -50) {
            hat.openValve(false);
            status = protoduck::Procedure::Status::SUCCESS;
            return ProcedureState::IDLE;
        }
    }

    return ProcedureState::RUNNING;
}

void ProcTurnStack::setParam(int32_t p) {
    drop_height = p;
}

ProcedureState ProcTurnStack::reset() {
    if(!arm->isZMotorEnabled()) {
        setFailed();
        return ProcedureState::IDLE;
    }
    current_state = State::INIT;
    status = protoduck::Procedure::Status::RUNNING;
    arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 820);
    arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Y, 330);
    other_arm->sendPositionCommand(Arm::eJoint::REVOLUTE_Z, 700);
    setTimeout(1000);
    return ProcedureState::RUNNING;
}
