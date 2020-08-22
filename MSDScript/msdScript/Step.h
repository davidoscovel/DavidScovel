//
// Created by David Scovel on 3/23/20.
//

#ifndef HOMEWORK1_STEP_H
#define HOMEWORK1_STEP_H


#include <string>
#include "value.h"
#include "pointer.h"
#include "Env.h"
#include "Cont.h"

class Cont;
class Expr;
class Env;
class Val;

class Step {
public:
    typedef enum {
        interp_mode,
        continue_mode
    }mode_t;
    static mode_t mode;
    static PTR(Expr) expr;
    static PTR(Env) env;
    static PTR(Val) val;
    static PTR(Cont) cont;

    static PTR(Val) interp_by_steps(PTR(Expr) e);
};


#endif //HOMEWORK1_STEP_H
