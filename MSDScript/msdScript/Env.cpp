//
// Created by David Scovel on 3/2/20.
//

#include "Env.h"

//////////////////Extended Env////////////////////////////////

ExtendedEnv::ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) rest){
    this->name = name;
    this->val = val;
    this->rest = rest;
}

PTR(Val) ExtendedEnv::lookup(std::string find_name){
    if(find_name == name){
        return val;
    }
    else{
        return rest->lookup(find_name);
    }
}

///////////////////Empty Env//////////////////////////////////

PTR(Val) EmptyEnv::lookup(std::string find_name){
    throw std::runtime_error("Cannot compute statements containing variables.\n");
}