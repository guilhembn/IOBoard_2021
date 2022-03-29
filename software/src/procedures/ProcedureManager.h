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
    ProcedureState base_reset() {
        timeout = 0;
        return reset();
    }
    
    virtual protoduck::Procedure::Status getStatus() {return status;}
    bool isTimeout() {
        return timeout != 0 && millis() - last_mark > timeout;
    }

    void setFailed() {
        status = protoduck::Procedure::Status::FAILURE;
    }

    void relax() {
        arm1.startPump(false);
        arm1.openValve(false);
        arm2.startPump(false);
        arm2.openValve(false);
    }

protected:
    AbstractProcedure(): arm(&arm1), other_arm(&arm2), status(protoduck::Procedure::Status::SUCCESS) {}
    virtual ProcedureState reset() = 0;
    // reset timeout
    void timeoutReset() {last_mark = millis();}
    // set and reset timeout
    void setTimeout(uint32_t t) {
        timeout = t;
        timeoutReset();
    }

    Arm* arm;
    Arm* other_arm;
    protoduck::Procedure::Status status;
    uint32_t last_mark;
    uint32_t timeout;
};



class ProcedureManager {
public:
    void init();
    void loop();
    int queueProcedure(protoduck::Procedure::Proc proc, protoduck::ArmID arm_id, uint32_t param);
    ProcedureParams getParams() {return current_params;}
    protoduck::Procedure::Status getStatus();

private:
    static constexpr size_t QUEUE_SIZE = 5;
    void sendProcedureStatus();
    int setProcedure(ProcedureParams params);

    AbstractProcedure* procedures[4];

    ProcedureState state;
    ProcedureParams current_params;

    etl::queue<ProcedureParams, QUEUE_SIZE, etl::memory_model::MEMORY_MODEL_SMALL> procedures_queue;
};

extern ProcedureManager procedure_manager;