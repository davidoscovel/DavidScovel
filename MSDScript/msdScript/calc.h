//
// Created by David Scovel on 1/13/20.
//

#ifndef HOMEWORK1_CALC_H
#define HOMEWORK1_CALC_H

#include <iostream>

int calc(std::istream &in, std::ostream &err);
static int calc_expr(std::istream &in, std::ostream &err, bool &ok);
static int calc_addend(std::istream &in, std::ostream &err, bool &ok);
static int calc_number_or_paren(std::istream &in, std::ostream &err, bool &ok);
static int calc_number(std::istream &in);
static char peek_next(std::istream &in);


#endif //HOMEWORK1_CALC_H
