#include "ProcedureManager.h"

class ProcHalfUnstack: public AbstractProcedure {
public:
    ProcHalfUnstack(): AbstractProcedure() {}
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
        TURN_FRONT,
        DOWN_DEPOSE,
    };

    State current_state;
    int32_t height;
};

extern ProcHalfUnstack proc_half_unstack;
