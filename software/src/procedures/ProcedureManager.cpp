#include "ProcedureManager.h"
#include "procedure_stack.h"
#include "ducklink/Communication.h"

ProcedureManager procedure_manager;

void ProcedureManager::init() {
    params = {
        protoduck::Procedure::Proc::HOME,
        protoduck::ArmID::ARM1,
        0
    };

    state = ProcedureState::IDLE;

    procedures[(int)protoduck::Procedure::Proc::HOME] = nullptr;
    procedures[(int)protoduck::Procedure::Proc::PUT_ON_STACK] = &proc_stack;
    procedures[(int)protoduck::Procedure::Proc::TURN_AND_PUT_ON_STACK] = nullptr;
    procedures[(int)protoduck::Procedure::Proc::TAKE_FROM_STACK] = nullptr;
}

void ProcedureManager::loop() {
    if(state == ProcedureState::RUNNING) {
        state = procedures[(int)params.proc]->loop();
        if(state != ProcedureState::RUNNING) {
            //communication.sendProcedureStatus(*this);
        }
    }    
}

int ProcedureManager::setProcedure(protoduck::Procedure::Proc proc, protoduck::ArmID arm_id, uint32_t param) {
    if(state == RUNNING) {
        return -1;
    }
    params = {proc, arm_id, param};
    procedures[(int)params.proc]->setArmId(arm_id);
    procedures[(int)params.proc]->setParam(param);
    procedures[(int)params.proc]->reset();
    state = ProcedureState::RUNNING;
    return 0;
}

protoduck::Procedure::Status ProcedureManager::getStatus() {
    auto proc = procedures[(int)params.proc];
    if(proc != nullptr) {
        return proc->getStatus();
    } else {
        return protoduck::Procedure::Status::SUCCESS;
    }
    
}

