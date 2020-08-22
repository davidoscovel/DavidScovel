//
// Created by David Scovel on 1/14/20.
//
#include "parse.h"
#include <iostream>
#include <sstream>
#include "catch.hpp"


/**
 * Takes in a stream and recursively parses it into an expression when it detects an end of file
 * Parses based on Grammar:
 * <expr> = <addend> || <addend> + <expr>
 * <addend> = <inner> || <inner> * <addend>
 * <inner> = <number> || (<expr>) || <variable> || _let <variable> = <expr> _in <expr> || _true || _false || _if <expr> _then <expr> _else <expr
 * Calls parseExpr
 * @return
 */
PTR(Expr)parse(std::istream &in){

    PTR(Expr)expression = parseExpr(in);

    char c = peek_next(in);
    if (in.eof()){
        return expression;
    }
    else{
        throw std::runtime_error("Invalid Input\n");}}

/**
 * Parses an expression based on:
 * <expr> = <comparg> || <expr> == <comparg>
 * Calls parseComparg
 * @param in
 * @return
 */
PTR(Expr)parseExpr(std::istream &in){
    PTR(Expr)comp = parseComparg(in);

    char c = peek_next(in);
    if(c == '='){
        in.get();
        c = peek_next(in);
        if(c == '=') {
            in.get();
            return NEW(Comparison)(comp, parseExpr(in));
        }
        else {
            throw std::runtime_error("Error: requires ==\n");
        }
    }
    return comp;
}

/**
 * Parses an comparg based on:
 * <comparg> = <addend> || <addend> + <comparg>
 * Calls parse_addend
 * @param in
 * @return
 */
PTR(Expr)parseComparg(std::istream &in){
    PTR(Expr)addend = parse_addend(in);

    char c = peek_next(in);

    if (c == '+') {
        in.get();
        return NEW(Add)(addend, parseComparg(in));
    }
    return addend;
}


/**
 * Parses an addend based on:
 * <addend> = <inner> || <inner> * <addend>
 * Calls parse_number_var_let
 * @param in
 * @return
 */
PTR(Expr)parse_addend(std::istream &in){
    PTR(Expr)multicand = parse_multicand(in);

    char c = peek_next(in);

    if (c == '*') {
        in.get();
        return NEW(Mult)(multicand, parse_addend(in));
    }
    return multicand;
}


PTR(Expr)parse_multicand(std::istream &in){
    PTR(Expr)expression = parse_inner(in);
    while(in.peek() == '('){
        in.get();
        PTR(Expr)actual_arg = parseExpr(in);
        char c = peek_next(in);
        if(c == ')'){
            in.get();
        }
        expression = NEW(Call)(expression, actual_arg);
    }
    return expression;}

/**
 * Parses an inner based on:
 * <inner> = <number> || (<expr>) || <variable> || _let <variable> = <expr> _in <expr> || _if <expr> _then <expr> _else <expr
 *      || _true || _false
 * Calls parse_number, parse_var, parse_let, or parseExpr if it encounters a parenthesis
 * @param in
 * @return either a Number, Var, Let
 */
PTR(Expr)parse_inner(std::istream &in) {
    PTR(Expr)num;

    char c = peek_next(in);

    if (c == '(') {
        in.get();
        num = parseExpr(in);

        // After that, there should be a `)`, and we're done
        c = peek_next(in);
        if (c != ')') {
            throw std::runtime_error("expected a close parenthesis\n");
        } else {
            in.get();
        }
    } else if (isdigit(c) || c == '-') {
        num = parse_number(in);
    } else if(isalpha(c)){
        num = parse_var(in);
    } else if(c == '_'){
        in.get();
        std::string check = variable_name(in);
        if(check == "let") {
            num = parse_let(in);
        }
        else if(check == "if"){
            num = parse_if(in);
        }
        else if(check == "fun"){
            num = parse_fun(in);
        }
        else if(check == "true"){
            num = NEW(BoolExpr)(true);
        }
        else if(check == "false"){
            num = NEW(BoolExpr)(false);
        }
        else{
            throw std::runtime_error("Invalid input\n");
        }
    }
    else{
        throw std::runtime_error("expected a digit, character, or open parenthesis\n");
    }
    return num;}

/**
 * Creates and returns a Number object
 * @param in
 * @return
 */
PTR(Expr)parse_number(std::istream &in){
    int num;
    in >> num;
    return NEW(Number)(num);}

/**
 * Creates and returns a Variable Object
 * @param in
 * @return
 */
PTR(Expr)parse_var(std::istream &in){
    std::string variable = variable_name(in);
    return NEW(Var)(variable);
}

/**
 * Parses a let expression from an input stream,
 * A let expression must follow the format: _let <variable> = <expr> _in <expr>
 * Calls parseExpr
 * @param in
 * @return
 */
PTR(Expr)parse_let(std::istream &in){
    std::string varToReplace;
    PTR(Expr)e1;
    PTR(Expr)e2;

    char c = peek_next(in); //Consumes spaces
    varToReplace = variable_name(in);
    c = peek_next(in);
    if(c == '='){
        in.get(); //Consumes =
        e1 = parseExpr(in);
    }
    else{
        throw std::runtime_error("improper _let format: No =\n");
    }
    c = peek_next(in);
    if(c == '_'){
        in.get();
        std::string formatCheck = variable_name(in);
        if(formatCheck == "in"){
            e2 = parseExpr(in);
        }
        else{
            throw std::runtime_error("improper _let format: In\n");
        }
    }
    else{
        throw std::runtime_error("improper _let format: _\n");
    }
    return NEW(Let)(varToReplace, e1, e2);
}

/**
 * Parses an If expression from an input stream,
 * An If expression must follow the format: _if <expr> _then <expr> _else <expr>
 * Calls parseExpr
 * @param in
 * @return
 */
PTR(Expr)parse_if(std::istream &in){
    PTR(Expr)cond;
    PTR(Expr)thenE;
    PTR(Expr)elseE;

    cond = parseExpr(in);

    char c = peek_next(in);
    if(c != '_'){
        throw std::runtime_error("invalid if statement: missing _\n");
    }
    in.get();
    std::string s = variable_name(in);
    if(s != "then"){
        throw std::runtime_error("invalid if statement: missing then\n");
    }

    thenE = parseExpr(in);

    c = peek_next(in);
    if(c != '_'){
        throw std::runtime_error("invalid if statement: missing _\n");
    }
    in.get();
    s = variable_name(in);
    if(s != "else"){
        throw std::runtime_error("invalid if statement: missing else\n");
    }

    elseE = parseExpr(in);

    return NEW(If)(cond, thenE, elseE);
}

PTR(Expr)parse_fun(std::istream &in){
    std::string var;
    PTR(Expr) bod;

    char c = peek_next(in);
    if(c != '(') {
        throw std::runtime_error("invalid fun statement: missing (\n");
    }
    in.get();
    c = peek_next(in);
    var = variable_name(in);

    c = peek_next(in);
    if(c != ')'){
        throw std::runtime_error("invalid fun statement: missing )\n");
    }
    in.get();

    bod = parseExpr(in);

    return NEW(Fun)(var, bod);
}
/**
 * returns but does not consume the next non space character of a stream
 * @param in
 * @return
 */
static char peek_next(std::istream &in) {
    char c = in.peek();
    while(c == ' ' || c == '\n'){
        in.get();
        c = in.peek();
    }
    return c;
}

/**
 * Returns the next string of characters up to a space from an input stream
 * @param in
 * @return
 */
std::string variable_name(std::istream &in){
    std::string variable = "";
    char c = in.peek();
    while (isalpha(c)) {
        variable += c;
        in.get();
        c = in.peek();
    }
    return variable;
}
