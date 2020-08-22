//
// Created by David Scovel on 3/23/20.
//

#ifndef HOMEWORK1_CONT_H
#define HOMEWORK1_CONT_H


#include "Step.h"

class Cont {
public:
    virtual void step_continue()= 0;
    static PTR(Cont)done;
};

class DoneCont : public Cont{
public:
    DoneCont();
    void step_continue();
};

class RightThenAddCont ENABLE_THIS(RightThenAddCont) public Cont{
public:
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) rest;
public:
    RightThenAddCont(PTR(Expr) e, PTR(Env) envir, PTR(Cont) cont);
    void step_continue();
};

class AddCont ENABLE_THIS(AddCont) public Cont{
public:
    PTR(Val) lhs_val;
    PTR(Cont) rest;
public:
    AddCont(PTR(Val) val, PTR(Cont) cont);
    void step_continue();
};

class RightThenMultCont ENABLE_THIS(RightThenMultCont) public Cont {
public:
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) rest;
public:
    RightThenMultCont(PTR(Expr) e, PTR(Env) envir, PTR(Cont) cont);
    void step_continue();
};

class MultCont ENABLE_THIS(MultCont) public Cont{
public:
    PTR(Val) lhs_val;
    PTR(Cont) rest;
public:
    MultCont(PTR(Val) val, PTR(Cont) cont);
    void step_continue();
};

class IfBranchCont ENABLE_THIS(IfBranchCont) public Cont{
public:
    PTR(Expr) then_part;
    PTR(Expr) else_part;
    PTR(Env) env;
    PTR(Cont) rest;

    IfBranchCont(PTR(Expr) then, PTR(Expr) els, PTR(Env) envir, PTR(Cont) cont);
    void step_continue();
};

class LetBodyCont ENABLE_THIS(LetBodyCont) public Cont{
public:
    std::string var;
    PTR(Expr) body;
    PTR(Env) env;
    PTR(Cont) rest;

    LetBodyCont(std::string s, PTR(Expr) bod, PTR(Env) envir, PTR(Cont) cont);
    void step_continue();
};

class RightThenCompCont ENABLE_THIS(RightThenCompCont) public Cont{
public:
    PTR(Expr) rhs;
    PTR(Env) env;
    PTR(Cont) rest;
public:
    RightThenCompCont(PTR(Expr) e, PTR(Env) envir, PTR(Cont) cont);
    void step_continue();
};

class CompCont ENABLE_THIS(CompCont) public Cont{
public:
    PTR(Val) lhs_val;
    PTR(Cont) rest;
public:
    CompCont(PTR(Val) val, PTR(Cont) cont);
    void step_continue();
};

class ArgThenCallCont ENABLE_THIS(ArgThenCallCont) public Cont{
public:
    PTR(Expr) actual_arg;
    PTR(Env) env;
    PTR(Cont) rest;

    ArgThenCallCont(PTR(Expr) actualArg, PTR(Env) envir, PTR(Cont) cont);
    void step_continue();
};

class CallCont ENABLE_THIS(CallCont) public Cont{
public:
    PTR(Val) to_be_called_val;
    PTR(Cont) rest;

    CallCont(PTR(Val) toBeCalled, PTR(Cont) cont);
    void step_continue();

};

#endif //HOMEWORK1_CONT_H
