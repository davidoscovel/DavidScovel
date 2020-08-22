//
// Created by David Scovel on 2/4/20.
//

#ifndef value_hpp
#define value_hpp

#include <string>
#include "pointer.h"
#include "Env.h"
#include "Cont.h"

/* A forward declaration, so `Val` can refer to `Expr`, while
   `Expr` still needs to refer to `Val`. */
class Expr;
class Env;
class Cont;

class Val {
public:
    virtual bool equals(PTR(Val)val) = 0;
    virtual PTR(Val)add_to(PTR(Val)other_val) = 0;
    virtual PTR(Val)mult_with(PTR(Val)other_val) = 0;
    virtual PTR(Expr)to_expr() = 0;
    virtual std::string stringify() = 0;
    virtual PTR(Val)call(PTR(Val) actual_arg) = 0;
    virtual bool is_true() = 0;
    virtual void call_step(PTR(Val) actual_arg_val, PTR(Cont) rest) = 0;
};

class NumVal ENABLE_THIS(NumVal) public Val {
public:
    int rep;
    NumVal(int rep);
    bool equals(PTR(Val)val);

    PTR(Val)add_to(PTR(Val)other_val);
    PTR(Val)mult_with(PTR(Val)other_val);
    PTR(Expr)to_expr();
    std::string stringify();
    PTR(Val)call(PTR(Val)actual_arg);
    bool is_true();
    void call_step(PTR(Val) actual_arg_val, PTR(Cont) rest);
};

class BoolVal ENABLE_THIS(BoolVal) public Val {
public:
    bool rep;
    BoolVal(bool rep);
    bool equals(PTR(Val)val);

    PTR(Val)add_to(PTR(Val)other_val);
    PTR(Val)mult_with(PTR(Val)other_val);
    PTR(Expr)to_expr();
    std::string stringify();
    PTR(Val)call(PTR(Val)actual_arg);
    bool is_true();
    void call_step(PTR(Val) actual_arg_val, PTR(Cont) rest);
};

class FunVal ENABLE_THIS(FunVal) public Val {
public:
    std::string variable;
    PTR(Expr) body;
    PTR(Env) env;

    FunVal(std::string var, PTR(Expr) bod, PTR(Env) env);
    bool equals(PTR(Val)val);
    PTR(Val)add_to(PTR(Val)other_val);
    PTR(Val)mult_with(PTR(Val)other_val);
    PTR(Expr)to_expr();
    std::string stringify();
    PTR(Val)call(PTR(Val)actual_arg);
    bool is_true();
    void call_step(PTR(Val) actual_arg_val, PTR(Cont) rest);
};


#endif /* value_hpp */
