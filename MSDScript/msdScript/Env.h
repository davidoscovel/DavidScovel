//
// Created by David Scovel on 3/2/20.
//

#ifndef HOMEWORK1_ENV_H
#define HOMEWORK1_ENV_H

#include "pointer.h"
#include "value.h"
#include "Expr.h"

class Val;

class Env {
public:
    virtual PTR(Val) lookup(std::string find_name) = 0;
};

class ExtendedEnv ENABLE_THIS(ExtendedEnv) public Env {
    std::string name;
    PTR(Val) val;
    PTR(Env) rest;

public:
    ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) rest);
    PTR(Val) lookup(std::string find_name);
};

class EmptyEnv ENABLE_THIS(EmptyEnv) public Env {
public:
    PTR(Val) lookup(std::string find_name);
};


#endif //HOMEWORK1_ENV_H
