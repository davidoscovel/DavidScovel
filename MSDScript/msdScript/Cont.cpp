#include "Cont.h"
//
// Created by David Scovel on 3/23/20.
//

#include "Cont.h"

/////////////////Done///////////////////////
PTR(Cont) Cont::done = NEW(DoneCont)();

DoneCont::DoneCont(){}

void DoneCont::step_continue() {
    throw std::runtime_error("Cannot step through a Done cont.\n");
}

/////////////////Add////////////////////////
RightThenAddCont::RightThenAddCont(PTR(Expr) e, PTR(Env) envir, PTR(Cont) cont){
    rhs = e;
    env = envir;
    rest = cont;
}

void RightThenAddCont::step_continue() {
    PTR(Val) lhs_val = Step::val;
    Step::mode = Step::interp_mode;
    Step::expr = rhs;
    Step::env = env;
    Step::cont = NEW(AddCont)(lhs_val, rest);
}

AddCont::AddCont(PTR(Val) val, PTR(Cont) cont){
    lhs_val = val;
    rest = cont;
}

void AddCont::step_continue() {
    PTR(Val) rhs_val = Step::val;
    Step::mode = Step::continue_mode;
    Step::val = lhs_val->add_to(rhs_val);
    Step::cont = rest;

}

/////////////////Mult////////////////////////

RightThenMultCont::RightThenMultCont(PTR(Expr) e, PTR(Env) envir, PTR(Cont) cont){
    rhs = e;
    env = envir;
    rest = cont;
}

void RightThenMultCont::step_continue() {
    PTR(Val) lhs_val = Step::val;
    Step::mode = Step::interp_mode;
    Step::expr = rhs;
    Step::env = env;
    Step::cont = NEW(AddCont)(lhs_val, rest);
}

MultCont::MultCont(PTR(Val) val, PTR(Cont) cont){
    lhs_val = val;
    rest = cont;
}

void MultCont::step_continue() {
    PTR(Val) rhs_val = Step::val;
    Step::mode = Step::continue_mode;
    Step::val = lhs_val->mult_with(rhs_val);
    Step::cont = rest;
}

/////////////////If////////////////////////

IfBranchCont::IfBranchCont(PTR(Expr) then, PTR(Expr) els, PTR(Env) envir, PTR(Cont) cont){
    then_part = then;
    else_part = els;
    env = envir;
    rest = cont;
}
void IfBranchCont::step_continue(){
    PTR(Val) test_val = Step::val;
    Step::mode = Step::interp_mode;
    if(test_val->is_true())
        Step::expr = then_part;
    else
        Step::expr = else_part;
    Step::env = env;
    Step::cont = rest;
}

/////////////////Let////////////////////////

LetBodyCont::LetBodyCont(std::string s, PTR(Expr) bod, PTR(Env) envir, PTR(Cont) cont){
    var = s;
    body = bod;
    env = envir;
    rest = cont;
}

void LetBodyCont::step_continue(){
    Step::mode = Step::interp_mode;
    Step::expr = body;
    Step::env = NEW(ExtendedEnv)(var, Step::val, env);
    Step::cont = rest;
}

/////////////////Comp////////////////////////

RightThenCompCont::RightThenCompCont(PTR(Expr) e, PTR(Env) envir, PTR(Cont) cont){
    rhs = e;
    env = envir;
    rest = cont;
}

void RightThenCompCont::step_continue() {
    PTR(Val) lhs_val = Step::val;
    Step::mode = Step::interp_mode;
    Step::expr = rhs;
    Step::env = env;
    Step::cont = NEW(CompCont)(lhs_val, rest);
}

CompCont::CompCont(PTR(Val) val, PTR(Cont) cont){
    lhs_val = val;
    rest = cont;
}

void CompCont::step_continue() {
    PTR(Val) rhs_val = Step::val;
    Step::mode = Step::continue_mode;
    Step::val = NEW(BoolVal)(lhs_val->equals(rhs_val));
    Step::cont = rest;

}

/////////////////Call////////////////////////

ArgThenCallCont::ArgThenCallCont(PTR(Expr) actualArg, PTR(Env) envir, PTR(Cont) cont){
    actual_arg = actualArg;
    env = envir;
    rest = cont;
}

void ArgThenCallCont::step_continue(){
    Step::mode = Step::interp_mode;
    Step::expr = actual_arg;
    Step::env = env;
    Step::cont = NEW(CallCont)(Step::val, rest);
}

CallCont::CallCont(PTR(Val) toBeCalled, PTR(Cont) cont){
    to_be_called_val = toBeCalled;
    rest = cont;
}

void CallCont::step_continue(){
    to_be_called_val->call_step(Step::val, rest);
}