//
// Created by David Scovel on 2/4/20.
// Adapted from Matthew Flatt's value.cpp
//
#include "Expr.h"
#include "value.h"
#include <stdexcept>
#include "catch.hpp"


NumVal::NumVal(int rep) {
    this->rep = rep;
}

bool NumVal::equals(PTR(Val)other_val) {
    PTR(NumVal)other_num_val = CAST(NumVal)(other_val);
    if (other_num_val == nullptr)
        return false;
    else
        return rep == other_num_val->rep;
}

PTR(Val)NumVal::add_to(PTR(Val)other_val) {
    PTR(NumVal)other_num_val = CAST(NumVal)(other_val);
    if (other_num_val == nullptr)
        throw std::runtime_error("not a number");
    else
        return NEW(NumVal)((unsigned)rep + (unsigned)other_num_val->rep);}

PTR(Val)NumVal::mult_with(PTR(Val)other_val) {
    PTR(NumVal)other_num_val = CAST(NumVal)(other_val);
    if (other_num_val == nullptr)
        throw std::runtime_error("not a number");
    else
        return NEW(NumVal)((unsigned)rep * (unsigned)other_num_val->rep);}

PTR(Expr)NumVal::to_expr() {
    return NEW(Number)(rep);}

std::string NumVal::stringify() {
    return std::to_string(rep);
}

PTR(Val)NumVal::call(PTR(Val)actual_arg){
    throw std::runtime_error("Error: cannot call a number");
}

bool NumVal::is_true() {
    throw std::runtime_error("Numbers are neither true nor false.");
}

void NumVal::call_step(PTR(Val) actual_arg_val, PTR(Cont) rest){
    throw std::runtime_error("Cannot call NumVals.");
}

BoolVal::BoolVal(bool rep) {
    this->rep = rep;
}

bool BoolVal::equals(PTR(Val)other_val) {
    PTR(BoolVal)other_bool_val = CAST(BoolVal)(other_val);
    if (other_bool_val == nullptr)
        return false;
    else
        return rep == other_bool_val->rep;
}

PTR(Val)BoolVal::add_to(PTR(Val)other_val) {
    throw std::runtime_error("no adding booleans");}

PTR(Val)BoolVal::mult_with(PTR(Val)other_val) {
    throw std::runtime_error("no multiplying booleans");}

PTR(Expr)BoolVal::to_expr() {
    return NEW(BoolExpr)(rep);}

std::string BoolVal::stringify() {
    if (rep)
        return "_true";
    else
        return "_false";
}

PTR(Val)BoolVal::call(PTR(Val)actual_arg) {
    throw std::runtime_error("Error: cannot call a bool");}

bool BoolVal::is_true() {
    return rep;
}

void BoolVal::call_step(PTR(Val) actual_arg_val, PTR(Cont) rest){
    throw std::runtime_error("Cannot call BoolVals.");
}

/////////////////FunVal Constructor and Method Implementations////////////////

FunVal::FunVal(std::string var, PTR(Expr) bod, PTR(Env) env){
    this->variable = var;
    this->body = bod;
    this->env = env;
}

bool FunVal::equals(PTR(Val)val){
    PTR(FunVal)f = CAST(FunVal)(val);
    if (f == NULL)
        return false;
    else
        return (variable == (f->variable)
                && body->equals(f->body));}

PTR(Val)FunVal::add_to(PTR(Val)other_val){
    throw std::runtime_error("no adding functions");}

PTR(Val)FunVal::mult_with(PTR(Val)other_val){
    throw std::runtime_error("no multiplying functions");}

PTR(Expr)FunVal::to_expr(){
    return NEW(Fun)(variable, body);}

std::string FunVal::stringify(){
    return "[function]\n";}

PTR(Val)FunVal::call(PTR(Val)actual_arg){
    return body->interp(NEW(ExtendedEnv)(variable, actual_arg, env));}

bool FunVal::is_true() {
    throw std::runtime_error("Functions are neither true nor false.");
}

void FunVal::call_step(PTR(Val) actual_arg_val, PTR(Cont) rest){
    Step::mode = Step::interp_mode;
    Step::expr = body;
    Step::env = NEW(ExtendedEnv)(variable, actual_arg_val, env);
    Step::cont = rest;
}
