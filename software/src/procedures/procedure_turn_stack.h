#include "ProcedureManager.h"

class ProcTurnStack: public AbstractProcedure {
public:
    ProcTurnStack(): AbstractProcedure() {}
    ProcedureState loop();
    void leave_fail();
    void setParam(int32_t p);
protected:
    ProcedureState reset();

private:
    enum State {
        INIT,
        DOWN,
        UP,
        TURN_UP,
        TURN,
        UP_HAT,
        TRANSFER_HAT,
        CLEAR_HAT,
        TURN_BACK,
        DROP,
    };

    State current_state;
    int32_t drop_height;
};

extern ProcTurnStack proc_turn_stack;
