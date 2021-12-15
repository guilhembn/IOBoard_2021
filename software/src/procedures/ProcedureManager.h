#pragma once

#include "generated/messages.h"

enum ProcedureState {
    IDLE,
    RUNNING,
};

class AbstractProcedure {
    public:
    virtual ProcedureState loop() = 0;
    virtual void setArmId(protoduck::ArmID id) {arm_id = id;}
    virtual void setParam(int32_t p) {}
    virtual void reset() = 0;
    virtual protoduck::ProcedureStatus::Status getStatus() = 0;

protected:
    protoduck::ArmID arm_id;
};



class ProcedureManager {
public:
    void init();
    void loop();
    int setProcedure(protoduck::ProcedureCmd::Procedure proc, protoduck::ArmID arm_id, uint32_t param);

private:
    void sendProcedureStatus();

    AbstractProcedure* procedures[4];

    protoduck::ProcedureCmd::Procedure current;
    ProcedureState state;
};

extern ProcedureManager procedure_manager;