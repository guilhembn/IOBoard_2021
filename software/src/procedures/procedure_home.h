#include "ProcedureManager.h"

class ProcHome: public AbstractProcedure {
public:
    ProcHome(): AbstractProcedure() {}
    ProcedureState loop();
    //void setParam(int32_t p);
protected:
    ProcedureState reset();

private:
    enum State {
        INITIAL_DOWN,
        WAIT,
        UP,
        DOWN_FINAL,
    };

    State current_state;
    uint32_t time_zstop_released;
};

extern ProcHome proc_home;
