#include "ProcedureManager.h"

class ProcStack: public AbstractProcedure {
public:
    ProcStack(): AbstractProcedure() {}
    ProcedureState loop();
    void setParam(int32_t p);

protected:
    ProcedureState reset();

private:
    enum State {
        INIT,
        DOWN,
        UP,
        TURN,
        WAIT,
        DROP,
    };

    State current_state;
    int32_t drop_height;
    uint32_t start_wait;
};

extern ProcStack proc_stack;
