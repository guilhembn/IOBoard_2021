#pragma once

#include "generated/messages.h"
#include "Arm.h"
#include <etl/queue.h>

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
    virtual void setArmId(protoduck::ArmID id) {
        if(id == protoduck::ArmID::ARM1) {
            arm = &arm1;
            other_arm = &arm2;
        } else {
            arm = &arm2;
            other_arm = &arm1;
        }
    }
    virtual void setParam(int32_t p) {}
    virtual void reset() = 0;
    virtual protoduck::Procedure::Status getStatus() {return status;}

protected:
    AbstractProcedure(): arm(&arm1), other_arm(&arm2), status(protoduck::Procedure::Status::SUCCESS) {}
    Arm* arm;
    Arm* other_arm;
    protoduck::Procedure::Status status;
};



class ProcedureManager {
public:
    void init();
    void loop();
    int queueProcedure(protoduck::Procedure::Proc proc, protoduck::ArmID arm_id, uint32_t param);
    ProcedureParams getParams() {return params;}
    protoduck::Procedure::Status getStatus();

private:
    static constexpr size_t QUEUE_SIZE = 5;
    void sendProcedureStatus();
    int setProcedure(ProcedureParams& params);

    AbstractProcedure* procedures[4];

    ProcedureState state;
    ProcedureParams params;

    etl::queue<ProcedureParams, QUEUE_SIZE, etl::memory_model::MEMORY_MODEL_SMALL> procedures_queue;
};

extern ProcedureManager procedure_manager;