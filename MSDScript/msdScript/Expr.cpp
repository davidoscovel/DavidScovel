//
// Created by David Scovel on 1/21/20.
//

#include "Expr.h"
#include "value.h"
#include "pointer.h"
#include "Step.h"
#include "Cont.h"

///////////////////Number Constructor and Method Implementations///////////////////
Number::Number(int val) {
    this->val = val;
}

bool Number::equals(PTR(Expr)e) {
    PTR(Number)n = CAST(Number)(e);
    if (n == NULL)
        return false;
    else
        return val == n->val;
}

PTR(Val) Number::interp(PTR(Env) env) {
    return NEW(NumVal)(val);}


PTR(Expr) Number:: substitute(std::string var, PTR(Val)newVal){
    return NEW(Number)(THIS->val);}

bool Number::containsVar() {
    return false;
}

PTR(Expr) Number::optimize(){
    return NEW(Number)(THIS->val);}

std::string Number::stringify(){
    return std::to_string(val);
}

void Number::step_interp() {
    Step::mode = Step::continue_mode;
    Step::val = NEW(NumVal)(val);
    Step::cont = Step::cont;
}

/////////////////Add Constructor and Method Implementations/////////////////////
Add::Add(PTR(Expr)lhs, PTR(Expr)rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Add::equals(PTR(Expr)e) {
    PTR(Add)a = CAST(Add)(e);
    if (a == NULL)
        return false;
    else
        return (lhs->equals(a->lhs)
                && rhs->equals(a->rhs));
}

PTR(Val) Add::interp(PTR(Env) env) {
    return lhs->interp(env)->add_to(rhs->interp(env));
}


//Searches both the lhs and actualArg for variables that match the var in the parameters by calling substitute on them
PTR(Expr) Add:: substitute(std::string var, PTR(Val)newVal){
    return NEW(Add)( (lhs->substitute(var, newVal)), (rhs->substitute(var, newVal)) );}

bool Add::containsVar() {
    return lhs->containsVar() || rhs->containsVar();
}

//Optimizes both the actualArg and lhs, if it doesn't contain a variable then it computes a value and returns it in a number
PTR(Expr) Add::optimize(){
    PTR(Add) opAdd = NEW(Add)(lhs->optimize(), rhs->optimize());
    if(!containsVar()){
        return opAdd->interp(NEW(EmptyEnv)())->to_expr();
    }
    return opAdd;
}

std::string Add::stringify(){
    return lhs->stringify() + " + " + rhs->stringify();
}

void Add::step_interp() {
    Step::mode = Step::interp_mode;
    Step::expr = lhs;
    Step::env = Step::env;
    Step::cont = NEW(RightThenAddCont)(rhs, Step::env, Step::cont);
}

/////////////////Mult Constructor and Method implementations////////////////
Mult::Mult(PTR(Expr)lhs, PTR(Expr)rhs) {
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Mult::equals(PTR(Expr)e) {
    PTR(Mult)m = CAST(Mult)(e);
    if (m == NULL)
        return false;
    else
        return (lhs->equals(m->lhs)
                && rhs->equals(m->rhs));
}

PTR(Val) Mult::interp(PTR(Env) env) {
    return lhs->interp(env)->mult_with(rhs->interp(env));
}

//Searches both the lhs and actualArg for variables that match the var in the parameters by calling substitute on them
PTR(Expr) Mult:: substitute(std::string var, PTR(Val)newVal){
    return NEW(Mult)( (lhs->substitute(var, newVal)), (rhs->substitute(var, newVal)) );}

bool Mult::containsVar() {
    return lhs->containsVar() || rhs->containsVar();
}

//Optimizes both the actualArg and lhs, if it doesn't contain a variable then it computes a value and returns it in a number
PTR(Expr) Mult::optimize(){
    PTR(Mult) opMult = NEW(Mult)(lhs->optimize(), rhs->optimize());
    if(!containsVar()){
        return opMult->interp(NEW(EmptyEnv)())->to_expr();
    }
    return opMult;
}

std::string Mult::stringify(){
    return lhs->stringify() + " * " + rhs->stringify();}

void Mult::step_interp() {
    Step::mode = Step::interp_mode;
    Step::expr = lhs;
    Step::env = Step::env;
    Step::cont = NEW(RightThenAddCont)(rhs, Step::env, Step::cont);
}

//////////////////Var constructor and method implementations////////////////
Var::Var(std::string val) {
    this->val = val;
}

bool Var::equals(PTR(Expr)e) {
    PTR(Var)n = CAST(Var)(e);
    if (n == NULL)
        return false;
    else
        return val == n->val;
}

PTR(Val) Var::interp(PTR(Env) env) {
    return env->lookup(THIS->val);}

//If the val in the variable matches the input var then it replaces the Var structure with the newVal expression
PTR(Expr) Var:: substitute(std::string var, PTR(Val)newVal){
    if(var == val){
        return newVal->to_expr();
    }
    else
        return NEW(Var)(val);
}

bool Var::containsVar() {
    return true;
}

PTR(Expr) Var::optimize(){
    return NEW(Var)(val);}

std::string Var::stringify(){
    return val;
}

void Var::step_interp() {
    Step::mode = Step::continue_mode;
    Step::val = interp(Step::env);
    Step::cont = Step::cont;
}

////////////////Let constructor and method implementations/////////////
Let::Let(std::string toRep, PTR(Expr)replaceW, PTR(Expr)replaceI) {
    this->toReplace = toRep;
    this->variableSub = replaceW;
    this->body = replaceI;
}

bool Let::equals(PTR(Expr)e){
    PTR(Let)l = CAST(Let)(e);
    if (l == NULL)
        return false;
    else
        return (toReplace == (l->toReplace)
                && variableSub->equals(l->variableSub)
                && body->equals(l->body));
}

/**
 * Based on the let grammar: _let <variable> = <expr> _in <expr>
 * if the last expression(body) contains the variable, the variable is replaced with the other expression(variableSub)
 * then it computes the value of the last expression(body)
 * @return
 */
PTR(Val) Let::interp(PTR(Env) env){
    PTR(Val) rhs_val = variableSub->interp(env);
    PTR(Env) new_env = NEW(ExtendedEnv)(toReplace, rhs_val, env);
    return body->interp(new_env);}

/**
 * If the input var is the same as the toReplace variable, the let structure doesn't change
 * if they're different substitute is called on the body with the input parameters
 * Only called by other Lets
 * @param var
 * @param newVal
 * @return
 */
PTR(Expr) Let::substitute(std::string var, PTR(Val)newVal){
    if(var != toReplace){
        return NEW(Let)(toReplace, variableSub->substitute(var, newVal), body->substitute(var, newVal));
    }
    return NEW(Let)(toReplace, variableSub->substitute(var, newVal), body);}

//Let Structures always contain a variable
bool Let::containsVar(){
    return true;
}

/**
 * If the variableSub does not contain a variable then it just optimizes the body
 * if it does contain a variable then it substitutes the variableSub in for the toReplace variable in the body then optimizes the body
 * @return
 */
PTR(Expr) Let::optimize() {
    PTR(Let) opLet = NEW(Let)(toReplace, variableSub->optimize(), body);
    if (opLet->body->containsVar() && !opLet->variableSub->containsVar()) {
        return opLet->body->substitute(opLet->toReplace, opLet->variableSub->interp(NEW(EmptyEnv)()))->optimize();
    }
    else if(opLet->body->containsVar()){
        return NEW(Let)(opLet->toReplace, opLet->variableSub, opLet->body->optimize());
    }
    return opLet->interp(NEW(EmptyEnv)())->to_expr();
}

std::string Let::stringify(){
    return "_let " + toReplace + " = " + variableSub->stringify() + " _in " + body->stringify();
}

void Let::step_interp() {
    Step::mode = Step::interp_mode;
    Step::expr = variableSub;
    Step::env = Step::env;
    Step::cont = NEW(LetBodyCont)(toReplace, body, Step::env, Step::cont);
}

////////////////BoolExpr constructor and method implementations/////////////

BoolExpr::BoolExpr(bool rep) {
    this->rep = rep;
}

bool BoolExpr::equals(PTR(Expr)e) {
    PTR(BoolExpr)b = CAST(BoolExpr)(e);
    if (b == NULL)
        return false;
    else
        return rep == b->rep;
}

PTR(Val)BoolExpr::interp(PTR(Env) env) {
    return NEW(BoolVal)(rep);}

PTR(Expr)BoolExpr::substitute(std::string var, PTR(Val)new_val) {
    return NEW(BoolExpr)(rep);}

bool BoolExpr::containsVar(){
    return false;}

PTR(Expr)BoolExpr::optimize(){
    return NEW(BoolExpr)(rep);}

std::string BoolExpr::stringify(){
    if(rep){
        return "_true";
    }
    else{
        return "_false";
    }
}

void BoolExpr::step_interp() {
    Step::mode = Step::continue_mode;
    Step::val = NEW(BoolVal)(rep);
    Step::cont = Step::cont;
}

///////////////Comparison constructor and method implementations/////////////

Comparison::Comparison(PTR(Expr)lhs, PTR(Expr)rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

bool Comparison::equals(PTR(Expr)e){
    PTR(Comparison)c = CAST(Comparison)(e);
    if (c == NULL)
        return false;
    else
        return (lhs->equals(c->lhs)
                && rhs->equals(c->rhs));
}

PTR(Val) Comparison::interp(PTR(Env) env){
    return NEW(BoolVal)(lhs->interp(env)->equals(rhs->interp(env)));}

PTR(Expr) Comparison::substitute(std::string var, PTR(Val)newVal){
    return NEW(Comparison)(lhs->substitute(var, newVal), rhs->substitute(var, newVal));}

bool Comparison::containsVar(){
    return (lhs->containsVar() || rhs->containsVar());
}

PTR(Expr) Comparison::optimize(){
    if(lhs->containsVar() || rhs->containsVar()){
        return NEW(Comparison)(lhs->optimize(), rhs->optimize());
    }
    else{
        return NEW(BoolExpr)(lhs->interp(NEW(EmptyEnv)())->equals(rhs->interp(NEW(EmptyEnv)())));
    }
}

std::string Comparison::stringify(){
    return lhs->stringify() + " == " + rhs->stringify();
}

void Comparison::step_interp() {
    Step::mode = Step::interp_mode;
    Step::expr = lhs;
    Step::env = Step::env;
    Step::cont = NEW(RightThenCompCont)(rhs, Step::env, Step::cont);
}

///////////////If constructor and method implementations/////////////

If::If(PTR(Expr)cond, PTR(Expr)thenE, PTR(Expr)elseE){
    this->condition = cond;
    this->thenExpr = thenE;
    this->elseExpr = elseE;
}

bool If::equals(PTR(Expr)e){
    PTR(If)i = CAST(If)(e);
    if (i == NULL)
        return false;
    else
        return (condition->equals(i->condition)
                && thenExpr->equals(i->thenExpr)
                && elseExpr->equals(i->elseExpr));
}

PTR(Val) If::interp(PTR(Env) env){
    if(condition->interp(env)->equals(NEW(BoolVal)(true))){
        return thenExpr->interp(env);
    }
    else if(condition->interp(env)->equals(NEW(BoolVal)(false))){
        return elseExpr->interp(env);
    }
    else{
        throw std::runtime_error("Error: Invalid if condition.\n");
    }
}

PTR(Expr) If::substitute(std::string var, PTR(Val)newVal){
    return NEW(If)(condition->substitute(var, newVal), thenExpr->substitute(var, newVal), elseExpr->substitute(var, newVal));}

bool If::containsVar(){
    return(condition->containsVar() || thenExpr->containsVar() || elseExpr->containsVar());
}

PTR(Expr) If::optimize(){
    if(condition->optimize()->containsVar()){
        return NEW(If)(condition->optimize(), thenExpr->optimize(), elseExpr->optimize());
    }
    else {
        if (condition->interp(NEW(EmptyEnv)())->equals(NEW(BoolVal)(true))) {
            return thenExpr->optimize();
        } else if(condition->interp(NEW(EmptyEnv)())->equals(NEW(BoolVal)(false))) {
            return elseExpr->optimize();
        }
        else{
            throw std::runtime_error("Error: Invalid if condition.\n");
        }
    }
}

std::string If::stringify(){
    return "_if " + condition->stringify() + " _then " + thenExpr->stringify() + " _else " + elseExpr->stringify();
}

void If::step_interp() {
    Step::mode = Step::interp_mode;
    Step::expr = condition;
    Step::env = Step::env;
    Step::cont = NEW(IfBranchCont)(thenExpr, elseExpr, Step::env, Step::cont);
}

////////////////Fun constructor and method implementations/////////////

Fun::Fun(std::string var, PTR(Expr)bod){
    this->variable = var;
    this->body = bod;
}

bool Fun::equals(PTR(Expr)e){
    PTR(Fun)f = CAST(Fun)(e);
    if (f == NULL)
        return false;
    else
        return (variable == (f->variable)
                && body->equals(f->body));
}

PTR(Val) Fun::interp(PTR(Env) env){
    return NEW(FunVal)(variable, body, env);}

PTR(Expr) Fun::substitute(std::string var, PTR(Val)newVal){
    if(var != variable) {
        return NEW(Fun)(variable, body->substitute(var, newVal));
    }
    return NEW(Fun)(variable, body);
}

bool Fun::containsVar(){
    return true;
}

PTR(Expr) Fun::optimize(){
    return NEW(Fun)(variable, body->optimize());}

std::string Fun::stringify(){
    return "[function]\n";}

void Fun::step_interp() {
    Step::mode = Step::continue_mode;
    Step::val = NEW(FunVal)(variable, body, Step::env);
    Step::cont = Step::cont;
}

////////////////Callexpr constructor and method implementations/////////////

Call::Call(PTR(Expr)lhs, PTR(Expr)rhs){
    this->toBeCalled = lhs;
    this->actualArg = rhs;
}

bool Call::equals(PTR(Expr)e){
    PTR(Call)ce = CAST(Call)(e);
    if (ce == NULL)
        return false;
    else
        return (toBeCalled->equals(ce->toBeCalled)
                && actualArg->equals(ce->actualArg));
}

PTR(Val) Call::interp(PTR(Env) env){
    return toBeCalled->interp(env)->call(actualArg->interp(env));}

PTR(Expr) Call::substitute(std::string var, PTR(Val)newVal){
    return NEW(Call)(toBeCalled->substitute(var, newVal), actualArg->substitute(var, newVal));}

bool Call::containsVar(){
    return (toBeCalled->containsVar() || actualArg->containsVar());
}

PTR(Expr) Call::optimize(){
    return NEW(Call)(toBeCalled->optimize(), actualArg->optimize());}

std::string Call::stringify(){
    return "(" + toBeCalled->stringify() + ")(" + actualArg->stringify() + ")";
}

void Call::step_interp() {
    Step::mode = Step::interp_mode;
    Step::expr = toBeCalled;
    Step::cont = NEW(ArgThenCallCont)(actualArg, Step::env, Step::cont);
}
