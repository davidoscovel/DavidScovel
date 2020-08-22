//
// Created by David Scovel on 1/20/20.
//

#ifndef HOMEWORK1_PARSE_H
#define HOMEWORK1_PARSE_H


#include <istream>
#include "Expr.h"
#include "pointer.h"

//Function Definitions in parse.cpp
PTR(Expr)parse(std::istream &in);

PTR(Expr)parseExpr(std::istream &in);

PTR(Expr)parseComparg(std::istream &in);

PTR(Expr)parse_addend(std::istream &in);

PTR(Expr)parse_multicand(std::istream &in);

PTR(Expr)parse_inner(std::istream &in);

PTR(Expr)parse_number(std::istream &in);

PTR(Expr)parse_var(std::istream &in);

PTR(Expr)parse_let(std::istream &in);

PTR(Expr)parse_if(std::istream &in);

PTR(Expr)parse_fun(std::istream &in);

static char peek_next(std::istream &in);

std::string variable_name(std::istream &in);

static PTR(Expr)parse_str(std::string s);

void parse_str_error(std::string s);

#endif //HOMEWORK1_PARSE_H
