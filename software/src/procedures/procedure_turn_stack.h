#include "ProcedureManager.h"

class ProcTurnStack: public AbstractProcedure {
public:
    ProcTurnStack(): AbstractProcedure() {}
    ProcedureState loop();
    void setParam(int32_t p);
    void reset();

private:
    enum State {
        INIT,
        DOWN,
        UP,
        TURN_UP,
        TURN,
        UP_HAT,
        CLEAR_HAT,
        TURN_BACK,
        LOWER,
        DROP,
        HAT_UP,
    };

    State current_state;
    int32_t drop_height;
};

extern ProcTurnStack proc_turn_stack;
