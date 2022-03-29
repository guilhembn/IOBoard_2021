#include "ProcedureManager.h"

class ProcUnstack: public AbstractProcedure {
public:
    ProcUnstack(): AbstractProcedure() {}
    ProcedureState loop();
    //void setParam(int32_t p);
    void setParam(int32_t p);
    
protected:
    ProcedureState reset();

private:
    enum State {
        UP,
        TURN_IN,
        DOWN,
        CLEAR_UP,
        TURN_OUT,
        DOWN_DROP,
        DROP,
        CLEAR_FINAL,
    };

    State current_state;
    int32_t height;
};

extern ProcUnstack proc_unstack;
