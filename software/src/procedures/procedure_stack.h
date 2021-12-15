#include "ProcedureManager.h"

class ProcStack: public AbstractProcedure {
public:
    ProcedureState loop();
    void setParam(int32_t p);
    void reset();
    protoduck::ProcedureStatus::Status getStatus();

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