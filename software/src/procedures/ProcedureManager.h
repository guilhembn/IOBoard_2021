#pragma once

#include "generated/messages.h"

enum ProcedureState {
    IDLE,
    RUNNING,
};

struct ProcedureParams {
    protoduck::Procedure::Proc proc;
    protoduck::ArmID arm_id;
    uint32_t param;
};

class AbstractProcedure {
    public:
    virtual ProcedureState loop() = 0;
    virtual void setArmId(protoduck::ArmID id) {arm_id = id;}
    virtual void setParam(int32_t p) {}
    virtual void reset() = 0;
    virtual protoduck::Procedure::Status getStatus() {return status;}

protected:
    AbstractProcedure(): status(protoduck::Procedure::Status::SUCCESS) {}
    protoduck::ArmID arm_id;
    protoduck::Procedure::Status status;
};



class ProcedureManager {
public:
    void init();
    void loop();
    int setProcedure(protoduck::Procedure::Proc proc, protoduck::ArmID arm_id, uint32_t param);
    ProcedureParams getParams() {return params;}
    protoduck::Procedure::Status getStatus();

private:
    void sendProcedureStatus();

    AbstractProcedure* procedures[4];

    ProcedureState state;
    ProcedureParams params;
};

extern ProcedureManager procedure_manager;