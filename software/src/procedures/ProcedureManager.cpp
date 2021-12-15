#include "ProcedureManager.h"
#include "procedure_stack.h"
#include "ducklink/Communication.h"

ProcedureManager procedure_manager;

void ProcedureManager::init() {
    current = protoduck::ProcedureCmd::Procedure::HOME;
    state = ProcedureState::IDLE;

    procedures[(int)protoduck::ProcedureCmd::Procedure::HOME] = nullptr;
    procedures[(int)protoduck::ProcedureCmd::Procedure::PUT_ON_STACK] = &proc_stack;
    procedures[(int)protoduck::ProcedureCmd::Procedure::TURN_AND_PUT_ON_STACK] = nullptr;
    procedures[(int)protoduck::ProcedureCmd::Procedure::TAKE_FROM_STACK] = nullptr;
}

void ProcedureManager::loop() {
    if(state == ProcedureState::RUNNING) {
        state = procedures[(int)current]->loop();
        if(state != ProcedureState::RUNNING) {
            auto status = procedures[(int)current]->getStatus();
            communication.sendProcedureStatus(status);
        }
    }    
}

int ProcedureManager::setProcedure(protoduck::ProcedureCmd::Procedure proc, protoduck::ArmID arm_id, uint32_t param) {
    if(state == RUNNING) {
        return -1;
    }
    current = proc;
    procedures[(int)current]->setArmId(arm_id);
    procedures[(int)current]->setParam(param);
    procedures[(int)current]->reset();
    state = ProcedureState::RUNNING;
    return 0;
}

