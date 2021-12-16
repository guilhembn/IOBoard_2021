#include "ProcedureManager.h"

class ProcStack: public AbstractProcedure {
public:
    ProcStack(): AbstractProcedure() {}
    ProcedureState loop();
    void setParam(int32_t p);
    void reset();

private:
    enum State {
        INIT,
        DOWN,
        UP,
        TURN,
        DROP,
    };

    State current_state;
    int32_t drop_height;
};

extern ProcStack proc_stack;