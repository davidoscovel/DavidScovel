//
// Created by David Scovel on 1/21/20.
//

#ifndef HOMEWORK1_EXPR_H
#define HOMEWORK1_EXPR_H

#include <string>
#include "value.h"
#include "pointer.h"
#include "Env.h"

class Val;
class Env;

class Expr {
public:
    virtual bool equals(PTR(Expr)e) = 0;
    virtual PTR(Val) interp(PTR(Env) env) = 0;
    virtual PTR(Expr)substitute(std::string var, PTR(Val)newVal) = 0;
    virtual bool containsVar() = 0;
    virtual PTR(Expr)optimize() = 0;
    virtual std::string stringify() = 0;
    virtual void step_interp() = 0;
};

class Number ENABLE_THIS(Number) public Expr   {
public:
    int val;

    Number(int val);
    bool equals(PTR(Expr)e);
    PTR(Val) interp(PTR(Env) env);
    PTR(Expr)substitute(std::string var, PTR(Val)newVal);
    bool containsVar();
    PTR(Expr)optimize();
    std::string stringify();
    void step_interp();
};

class Comparison ENABLE_THIS(Comparison) public Expr {
public:
    PTR(Expr)lhs;
    PTR(Expr)rhs;

    Comparison(PTR(Expr)lhs, PTR(Expr)rhs);
    bool equals(PTR(Expr)e);
    PTR(Val) interp(PTR(Env) env);
    PTR(Expr)substitute(std::string var, PTR(Val)newVal);
    bool containsVar();
    PTR(Expr)optimize();
    std::string stringify();
    void step_interp();
};

class Add ENABLE_THIS(Add) public Expr {
public:
    PTR(Expr)lhs;
    PTR(Expr)rhs;

    Add(PTR(Expr)lhs, PTR(Expr)rhs);
    bool equals(PTR(Expr)e);
    PTR(Val) interp(PTR(Env) env);
    PTR(Expr)substitute(std::string var, PTR(Val)newVal);
    bool containsVar();
    PTR(Expr)optimize();
    std::string stringify();
    void step_interp();
};

class Mult ENABLE_THIS(Mult) public Expr {
public:
    PTR(Expr)lhs;
    PTR(Expr)rhs;

    Mult(PTR(Expr)lhs, PTR(Expr)rhs);
    bool equals(PTR(Expr)e);
    PTR(Val) interp(PTR(Env) env);
    PTR(Expr)substitute(std::string var, PTR(Val)newVal);
    bool containsVar();
    PTR(Expr)optimize();
    std::string stringify();
    void step_interp();
};

class Call ENABLE_THIS(Call) public Expr {
public:
    PTR(Expr)toBeCalled;
    PTR(Expr)actualArg;

    Call(PTR(Expr)lhs, PTR(Expr)rhs);
    bool equals(PTR(Expr)e);
    PTR(Val) interp(PTR(Env) env);
    PTR(Expr)substitute(std::string var, PTR(Val)newVal);
    bool containsVar();
    PTR(Expr)optimize();
    std::string stringify();
    void step_interp();
};

class Var ENABLE_THIS(Var) public Expr {
public:
    std::string val;

    Var(std::string val);
    bool equals(PTR(Expr)e);
    PTR(Val) interp(PTR(Env) env);
    PTR(Expr)substitute(std::string var, PTR(Val)newVal);
    bool containsVar();
    PTR(Expr)optimize();
    std::string stringify();
    void step_interp();
};

class Let ENABLE_THIS(Let) public Expr {
public:
    std::string toReplace;
    PTR(Expr)variableSub;
    PTR(Expr)body;

    Let(std::string toRep, PTR(Expr)replaceW, PTR(Expr)replaceI);
    bool equals(PTR(Expr)e);
    PTR(Val) interp(PTR(Env) env);
    PTR(Expr)substitute(std::string var, PTR(Val)newVal);
    bool containsVar();
    PTR(Expr)optimize();
    std::string stringify();
    void step_interp();
};

class BoolExpr ENABLE_THIS(BoolExpr) public Expr {
public:
    bool rep;

    BoolExpr(bool rep);
    bool equals(PTR(Expr)e);

    PTR(Val)interp(PTR(Env) env);
    PTR(Expr)substitute(std::string var, PTR(Val)newVal);
    bool containsVar();
    PTR(Expr)optimize();
    std::string stringify();
    void step_interp();
};

class If ENABLE_THIS(If) public Expr {
public:
    PTR(Expr)condition;
    PTR(Expr)thenExpr;
    PTR(Expr)elseExpr;

    If(PTR(Expr)cond, PTR(Expr)thenE, PTR(Expr)elseE);
    bool equals(PTR(Expr)e);
    PTR(Val) interp(PTR(Env) env);
    PTR(Expr)substitute(std::string var, PTR(Val)newVal);
    bool containsVar();
    PTR(Expr)optimize();
    std::string stringify();
    void step_interp();
};

class Fun ENABLE_THIS(Fun) public Expr {
public:
    std::string variable;
    PTR(Expr) body;

    Fun(std::string var, PTR(Expr)bod);
    bool equals(PTR(Expr)e);
    PTR(Val) interp(PTR(Env) env);
    PTR(Expr)substitute(std::string var, PTR(Val)newVal);
    bool containsVar();
    PTR(Expr)optimize();
    std::string stringify();
    void step_interp();
};


#endif //HOMEWORK1_EXPR_H
