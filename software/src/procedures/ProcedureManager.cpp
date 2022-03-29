#include "ProcedureManager.h"
#include "procedure_stack.h"
#include "procedure_turn_stack.h"
#include "procedure_home.h"
#include "ducklink/Communication.h"

ProcedureManager procedure_manager;

void ProcedureManager::init() {
    params = {
        protoduck::Procedure::Proc::HOME,
        protoduck::ArmID::ARM1,
        0
    };

    state = ProcedureState::IDLE;

    procedures[(int)protoduck::Procedure::Proc::HOME] = &proc_home;
    procedures[(int)protoduck::Procedure::Proc::PUT_ON_STACK] = &proc_stack;
    procedures[(int)protoduck::Procedure::Proc::TURN_AND_PUT_ON_STACK] = &proc_turn_stack;
    procedures[(int)protoduck::Procedure::Proc::TAKE_FROM_STACK] = nullptr;
}

void ProcedureManager::loop() {
    auto current_proc = procedures[(int)params.proc];
    if(state == ProcedureState::RUNNING) {
        state = current_proc->loop();
        if(current_proc->isTimeout()) {
            current_proc->setFailed();
            current_proc->relax();
            state = ProcedureState::IDLE;
        }
        if(state != ProcedureState::RUNNING) {
            //communication.sendProcedureStatus(*this);
        }
    } else {
        if(!procedures_queue.empty()) {
            auto p = procedures_queue.front();
            setProcedure(p);
            procedures_queue.pop();
        }
    }
}

int ProcedureManager::queueProcedure(protoduck::Procedure::Proc proc, protoduck::ArmID arm_id, uint32_t param) {
    if(procedures_queue.full()) {
        return -1;
    }
    
    params = {proc, arm_id, param};
    procedures_queue.push(params);
    return 0;
}

int ProcedureManager::setProcedure(ProcedureParams& params) {
    if(state == RUNNING) {
        return -1;
    }
    procedures[(int)params.proc]->setArmId(params.arm_id);
    procedures[(int)params.proc]->setParam(params.param);
    procedures[(int)params.proc]->base_reset();
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

