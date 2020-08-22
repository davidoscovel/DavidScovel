//
// Created by David Scovel on 1/29/20.
//
#include "parse.h"
#include <iostream>
#include <sstream>
#include "catch.hpp"
#include "value.h"
#include "pointer.h"
#include "Step.h"


// for tests
static PTR(Expr)parse_str(std::string s) {
    std::istringstream in(s);
    return parse(in);
}

/* for tests */
void parse_str_error(std::string s) {
    std::istringstream in(s);
    std::ostringstream err(std::ios_base::out);
    (void)parse(in);
}

TEST_CASE( "equals" ) {
//Number
CHECK( (NEW(Number)(1))->equals(NEW(Number)(1)) );
CHECK( ! (NEW(Number)(1))->equals(NEW(Number)(2)) );
CHECK( ! (NEW(Number)(1))->equals(NEW(Mult)(NEW(Number)(2), NEW(Number)(4))) );
//Add
CHECK( (NEW(Add)(NEW(Number)(1), NEW(Number)(5)))->equals(NEW(Add)(NEW(Number)(1), NEW(Number)(5))));
CHECK( !(NEW(Add)(NEW(Number)(1), NEW(Number)(5)))->equals(NEW(Add)(NEW(Number)(1), NEW(Number)(7))));
//Mult
CHECK( (NEW(Mult)(NEW(Number)(4), NEW(Number)(3)))->equals(NEW(Mult)(NEW(Number)(4), NEW(Number)(3))));
CHECK( !(NEW(Mult)(NEW(Number)(4), NEW(Number)(3)))->equals(NEW(Mult)(NEW(Number)(4), NEW(Number)(2))));
//Var
CHECK( (NEW(Var)("d"))->equals(NEW(Var)("d")) );
CHECK( (NEW(Var)("HeLLo"))->equals(NEW(Var)("HeLLo")) );
//Differing types
CHECK( !(NEW(Number)(1))->equals(NEW(Var)("1")));
CHECK( !(NEW(Var)("1"))->equals(NEW(Number)(1)));
CHECK( !(NEW(Add)(NEW(Number)(1), NEW(Number)(5)))->equals(NEW(Mult)(NEW(Number)(1), NEW(Number)(5))));
CHECK( !(NEW(Mult)(NEW(Number)(7), NEW(Number)(5)))->equals(NEW(Add)(NEW(Number)(7), NEW(Number)(2))));
CHECK( !(NEW(Let)("x", NEW(Number)(2), NEW(Var)("x")))->equals(NEW(Add)(NEW(Var)("z"), NEW(Number)(2))));
}

TEST_CASE("parse"){
CHECK((parse_str("1+3"))->equals(NEW(Add)(NEW(Number)(1), NEW(Number)(3))));
CHECK((parse_str(" 1 + 3 "))->equals(NEW(Add)(NEW(Number)(1), NEW(Number)(3))));
CHECK((parse_str(" 1 + heYo "))->equals(NEW(Add)(NEW(Number)(1), NEW(Var)("heYo"))));
CHECK((parse_str("2*5"))->equals(NEW(Mult)(NEW(Number)(2), NEW(Number)(5))));
CHECK((parse_str("(9*6)"))->equals(NEW(Mult)(NEW(Number)(9), NEW(Number)(6))));
CHECK_THROWS_WITH(parse_str_error("(9*6"), ("expected a close parenthesis\n"));
CHECK((parse_str("4*(2+1)*(5+X)"))->equals(NEW(Mult)(NEW(Number)(4), NEW(Mult)(NEW(Add)(NEW(Number)(2), NEW(Number)(1)), NEW(Add)(NEW(Number)(5), NEW(Var)("X"))))) );
CHECK_THROWS_WITH(parse_str_error("4*(2+1)*(5+#)"), ("expected a digit, character, or open parenthesis\n") );
CHECK( parse_str("-1")->equals(NEW(Number)(-1)));
}

TEST_CASE("interp"){
CHECK((parse_str("2"))->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(2)));
CHECK((parse_str("1+3"))->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(4)));
CHECK((parse_str("3*4"))->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(12)));
CHECK((parse_str("1+-3"))->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(-2)));
CHECK((parse_str("3*-4"))->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(-12)));
CHECK_THROWS_WITH((parse_str("b"))->interp(NEW(EmptyEnv)()), "Cannot compute statements containing variables.\n");
CHECK_THROWS_WITH((parse_str("4+x"))->interp(NEW(EmptyEnv)()), "Cannot compute statements containing variables.\n");
CHECK_THROWS_WITH((parse_str("4*(2+1)*(5+X)"))->interp(NEW(EmptyEnv)()), "Cannot compute statements containing variables.\n");
}

TEST_CASE("substitute"){
CHECK( (NEW(Number)(8))->substitute("x", NEW(NumVal)(212))->equals(NEW(Number)(8)) );
CHECK( (NEW(Add)(NEW(Number)(2), NEW(Var)("x")))->substitute("x", NEW(NumVal)(20))->equals(NEW(Add)(NEW(Number)(2), NEW(Number)(20))) );
CHECK( (NEW(Mult)(NEW(Number)(6), NEW(Var)("heyo")))->substitute("heyo", NEW(NumVal)(5))->equals(NEW(Mult)(NEW(Number)(6), NEW(Number)(5))) );
}

TEST_CASE("containsVar"){
CHECK( !(NEW(Number)(8))->containsVar() );
CHECK( (NEW(Var)("x"))->containsVar() );
CHECK( (NEW(Add)(NEW(Number)(2), NEW(Var)("x")))->containsVar() );
CHECK( !(NEW(Add)(NEW(Number)(2), NEW(Number)(5)))->containsVar() );
CHECK( (NEW(Mult)(NEW(Number)(16), NEW(Var)("hello")))->containsVar() );
CHECK( !(NEW(Mult)(NEW(Number)(5), NEW(Number)(20)))->containsVar() );
CHECK( (parse_str("4*(2+1)*(5+X)"))->containsVar() );
}

TEST_CASE("_let"){
//Parsing
CHECK( (parse_str("_let x = 2 _in x"))->equals(NEW(Let)("x", NEW(Number)(2), NEW(Var)("x"))) );
CHECK( (parse_str("_let x = 5 _in x + 10"))->equals(NEW(Let)("x", NEW(Number)(5), NEW(Add)(NEW(Var)("x"), NEW(Number)(10)))) );
CHECK_THROWS_WITH(parse_str_error("_do x = 5 _in x + 10"), ("Invalid input\n") );
CHECK_THROWS_WITH((parse_str_error("_let x  5 _in x + 10")), ("improper _let format: No =\n") );
CHECK_THROWS_WITH((parse_str_error("_let x = 5 _into x + 10")), ("improper _let format: In\n") );
CHECK_THROWS_WITH((parse_str_error("_let x = 5 in x + 10")), ("improper _let format: _\n") );
//Calculate
CHECK((parse_str("_let x = 2 _in x"))->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(2)));
CHECK((parse_str("_let x = 2 _in x + 5"))->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(7)));
//Substitute
CHECK((parse_str("_let y = 5 _in _let x = 2 _in x + y"))->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(7)));
CHECK((parse_str("_let x = 5 _in _let x = 2 _in x + 9"))->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(11)));
CHECK((parse_str("_let x = 5 \n_in _let x = 2 _in x + 9"))->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(11)));
CHECK((parse_str("_let x = 3 _in _let y = x + 2 _in x + y"))->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(8)));
//Optimize
CHECK( (parse_str("_let x = 5 _in _let y = z + 2 _in x + y + (2 * 3)"))->optimize()->equals(NEW(Let)("y", NEW(Add)(NEW(Var)("z"), NEW(Number)(2)),
NEW(Add)(NEW(Number)(5), NEW(Add)(NEW(Var)("y"), NEW(Number)(6) )))) );
CHECK( (parse_str("_let x = 8 _in _let d = r + 3 _in x + y + (2 * 8)"))->optimize()->equals(NEW(Let)("d", NEW(Add)(NEW(Var)("r"), NEW(Number)(3)),
NEW(Add)(NEW(Number)(8), NEW(Add)(NEW(Var)("y"), NEW(Number)(16) )))) );
CHECK( (parse_str("_let x = 7 _in _let x = x _in x"))->optimize()->equals(NEW(Number)(7)));
}

TEST_CASE("BoolVal"){

}

TEST_CASE("stringify"){
CHECK( (parse_str("_let x = 2 _in x*3"))->stringify() == "_let x = 2 _in x * 3");
//Optimize
CHECK( (parse_str("_let x = 5 _in _let y = z + 2 _in x + y + (2 * 3)"))->optimize()->stringify() == "_let y = z + 2 _in 5 + y + 6");
CHECK( (parse_str("2 + 6"))->optimize()->stringify() == "8");
CHECK( (parse_str("2 * x"))->optimize()->stringify() == "2 * x");
CHECK( (parse_str("_let x = 2 _in _let y = 3 _in 4*6"))->optimize()->stringify() == "24");
}

TEST_CASE( "values equals" ) {
    CHECK( (NEW(NumVal)(5))->equals(NEW(NumVal)(5)) );
    CHECK( ! (NEW(NumVal)(7))->equals(NEW(NumVal)(5)) );

    CHECK( (NEW(BoolVal)(true))->equals(NEW(BoolVal)(true)) );
    CHECK( ! (NEW(BoolVal)(true))->equals(NEW(BoolVal)(false)) );
    CHECK( ! (NEW(BoolVal)(false))->equals(NEW(BoolVal)(true)) );

    CHECK( ! (NEW(NumVal)(7))->equals(NEW(BoolVal)(false)) );
    CHECK( ! (NEW(BoolVal)(false))->equals(NEW(NumVal)(8)) );
}

TEST_CASE( "add_to" ) {

    CHECK ( (NEW(NumVal)(5))->add_to(NEW(NumVal)(8))->equals(NEW(NumVal)(13)) );

    CHECK_THROWS_WITH ( (NEW(NumVal)(5))->add_to(NEW(BoolVal)(false)), "not a number" );
    CHECK_THROWS_WITH ( (NEW(BoolVal)(false))->add_to(NEW(BoolVal)(false)),
                        "no adding booleans" );
}

TEST_CASE( "mult_with" ) {

    CHECK ( (NEW(NumVal)(5))->mult_with(NEW(NumVal)(8))->equals(NEW(NumVal)(40)) );

    CHECK_THROWS_WITH ( (NEW(NumVal)(5))->mult_with(NEW(BoolVal)(false)), "not a number" );
    CHECK_THROWS_WITH ( (NEW(BoolVal)(false))->mult_with(NEW(BoolVal)(false)),
                        "no multiplying booleans" );
}

TEST_CASE( "value to_expr" ) {
    CHECK( (NEW(NumVal)(5))->to_expr()->equals(NEW(Number)(5)) );
    CHECK( (NEW(BoolVal)(true))->to_expr()->equals(NEW(BoolExpr)(true)) );
    CHECK( (NEW(BoolVal)(false))->to_expr()->equals(NEW(BoolExpr)(false)) );
}

TEST_CASE( "value stringify" ) {
    CHECK((NEW(NumVal)(5))->stringify() == "5" );
    CHECK((NEW(BoolVal)(true))->stringify() == "_true" );
    CHECK((NEW(BoolVal)(false))->stringify() == "_false" );
}

TEST_CASE("Comparisons"){
    CHECK(parse_str("2 == 2")->equals(NEW(Comparison)(NEW(Number)(2), NEW(Number)(2))));
    CHECK_THROWS_WITH(parse_str_error(" 2 = 2"), "Error: requires ==\n");
    CHECK(parse_str("4 == 4")->optimize()->equals(NEW(BoolExpr)(true)));
    CHECK(parse_str("2 + 2 == 4")->optimize()->equals(NEW(BoolExpr)(true)));
    CHECK(parse_str("3 * 5 == 5 + 10")->optimize()->equals(NEW(BoolExpr)(true)));
    CHECK(parse_str("3 * 8 == 5 + 7")->optimize()->equals(NEW(BoolExpr)(false)));
    CHECK(parse_str("(2 * 3 == 2 + 4) == (6 == 5 + 1)")->optimize()->equals(NEW(BoolExpr)(true)));
    CHECK(!parse_str("2 == 2")->equals(NEW(Add)(NEW(Number)(2), NEW(Number)(2))));
    CHECK(parse_str("2 == 2")->interp(NEW(EmptyEnv)())->equals(NEW(BoolVal)(true)));
    CHECK(parse_str("x == 2")->optimize()->equals(NEW(Comparison)(NEW(Var)("x"), NEW(Number)(2))));
    CHECK(parse_str("x == 2")->stringify() == "x == 2");
    CHECK(parse_str("x == 2")->substitute("x", NEW(NumVal)(4))->equals(NEW(Comparison)(NEW(Number)(4), NEW(Number)(2))));
    CHECK(parse_str("x == 2")->substitute("x", NEW(NumVal)(2))->optimize()->equals(NEW(BoolExpr)(true)));
}

TEST_CASE("bools"){
    CHECK(parse_str("_false")->equals(NEW(BoolExpr)(false)));
    CHECK(parse_str("_true")->equals(NEW(BoolExpr)(true)));
    CHECK(!parse_str("_true")->equals(NEW(Number)(4)));
    CHECK(parse_str("_false")->interp(NEW(EmptyEnv)())->equals(NEW(BoolVal)(false)));
    CHECK(parse_str("_false")->substitute("x", NEW(NumVal)(2))->equals(NEW(BoolExpr)(false)) );
    CHECK(parse_str("_false")->containsVar() == false );
    CHECK(parse_str("_false")->optimize()->equals(NEW(BoolExpr)(false)) );
    CHECK(parse_str("_false")->stringify() == "_false" );
    CHECK(parse_str("_true")->stringify() == "_true" );
    CHECK_THROWS_WITH(parse_str("_true")->interp(NEW(EmptyEnv)())->call(NEW(NumVal)(10)), "Error: cannot call a bool" );
}

TEST_CASE("If"){
    CHECK( (parse_str("_if _true _then 5 _else 6"))->equals(NEW(If)(NEW(BoolExpr)(true), NEW(Number)(5), NEW(Number)(6))) );
    CHECK((parse_str("_if _true _then 5 _else 6"))->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(5)));
    CHECK((parse_str("_if _false _then 5 _else 6"))->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(6)));
    CHECK( !(parse_str("_if _true _then 5 _else 6"))->equals(NEW(Number)(2) ));
    CHECK( (parse_str("_if _true _then x + 6 _else x + 2"))->substitute("x", NEW(NumVal)(8))->optimize()->equals(NEW(Number)(14)) );
    CHECK( (parse_str("_if _false _then x + 6 _else x + 2"))->substitute("x", NEW(NumVal)(8))->optimize()->equals(NEW(Number)(10)) );
    CHECK( (parse_str("_if _false _then 6 _else y"))->optimize()->equals( NEW(Var)("y")) );
    CHECK( (parse_str("_if x + y _then 5 _else 6"))->optimize()->equals(NEW(If)(NEW(Add)(NEW(Var)("x"), NEW(Var)("y")), NEW(Number)(5), NEW(Number)(6))) );
    CHECK( (parse_str("_if _true _then 23 _else x + 8"))->containsVar() == true);
    CHECK( (parse_str("_if _true _then 23 _else x + 8"))->stringify() == "_if _true _then 23 _else x + 8");
    CHECK_THROWS_WITH( (parse_str_error("_if _true then 5 _else 6")), "invalid if statement: missing _\n");
    CHECK_THROWS_WITH( (parse_str_error("_if _true _then 5 else 6")), "invalid if statement: missing _\n");
    CHECK_THROWS_WITH( (parse_str_error("_if _true _than 5 _else 6")), "invalid if statement: missing then\n");
    CHECK_THROWS_WITH( (parse_str_error("_if _true _then 5 _elseDo 6")), "invalid if statement: missing else\n");
    CHECK_THROWS_WITH((parse_str("_if 4 _then 5 _else 6"))->interp(NEW(EmptyEnv)()), "Error: Invalid if condition.\n");
    CHECK_THROWS_WITH( (parse_str("_if 4 _then 5 _else 6"))->optimize(), "Error: Invalid if condition.\n");
    CHECK((parse_str("_if _let x = 5 _in x + x == 10 _then _true _else _false"))->interp(NEW(EmptyEnv)())->equals(NEW(BoolVal)(true)));
    CHECK((parse_str("_let x = 8 _in _if x + 2 == 10 _then _true _else _false"))->interp(NEW(EmptyEnv)())->equals(NEW(BoolVal)(true)));
    CHECK( (parse_str("_if 8 + 2 == 10 _then _let y = 5 _in y + 3 _else _let x = 2 _in x * 433"))->optimize()->stringify() == "8");
}

TEST_CASE("Fun"){
    CHECK( parse_str("_fun (x) x * 2")->equals(NEW(Fun)("x", NEW(Mult)(NEW(Var)("x"), NEW(Number)(2)))) );
    CHECK_THROWS_WITH( parse_str_error("_fun x) x * 2"),  "invalid fun statement: missing (\n");
    CHECK_THROWS_WITH( parse_str_error("_fun (x x * 2"),  "invalid fun statement: missing )\n");
    CHECK(parse_str("(_fun (x) x + 10)(10)")->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(20)));
    CHECK(parse_str("(_let y = 4 _in _fun (x) x * y)(5)")->interp(NEW(EmptyEnv)())->stringify() == "20" );
    CHECK( !parse_str("_fun (x) x * 2")->equals(NEW(Mult)(NEW(Var)("x"), NEW(Number)(2))) );
    CHECK( parse_str("_fun (x) x * 2")->containsVar() == true );
    CHECK( parse_str("_fun (x) x + (2 + 7)")->optimize()->equals(NEW(Fun)("x", NEW(Add)(NEW(Var)("x"), NEW(Number)(9)))) );
    CHECK( parse_str("_fun (x) x + (2 + 7)")->optimize()->stringify() == "[function]\n");
    CHECK(parse_str("_let y = 8 _in _let f = _fun (x) x * y _in f(2)")->interp(NEW(EmptyEnv)())->stringify() == "16");
    CHECK(parse_str("_let f = _fun (x) _fun(y) x*x + y*y _in (f(2))(3)")->interp(NEW(EmptyEnv)())->stringify() == "13");
    CHECK(parse_str(
            "_let fib = _fun (fib)\n_fun (x)\n_if x == 0\n_then 1\n_else _if x == 2 + -1\n_then 1\n_else fib(fib)(x + -1)\n+ fib(fib)(x + -2)\n_in fib(fib)(10)")->interp(NEW(EmptyEnv)())->stringify() == "89" );
    CHECK(parse_str(("_let factorial = _fun (factorial) _fun(x) "
                     "_if x == 1 _then 1 _else x * (factorial)(factorial)(x + -1) "
                     "_in (factorial)(factorial)(5)"))->interp(NEW(EmptyEnv)())->stringify() == "120");
}

TEST_CASE("Call"){
    CHECK( parse_str("(_fun (x) x * 2)(4)")->equals(NEW(Call)(NEW(Fun)("x", NEW(Mult)(NEW(Var)("x"), NEW(Number)(2))), NEW(Number)(4))) );
    CHECK( !parse_str("(_fun (x) x * 2)(4)")->equals(NEW(Number)(4)) );
    CHECK( parse_str("(_fun (x) x + 6)(4)")->containsVar() == true );
    CHECK( parse_str("(_fun (x) (x * 3) + 6 + 4)(4)")->optimize()->stringify() == "([function]\n)(4)" );
    CHECK( parse_str("_let y = 7 _in (_fun (x) x * y + 7 + 1)(2)")->optimize()->stringify() == "([function]\n)(2)" );
    CHECK(parse_str("_let f = _fun (x) x + 1 _in f(10)")->interp(NEW(EmptyEnv)())->stringify() == "11" );
    CHECK(parse_str("(_fun (y) _fun(x) x + y)(4)(3)")->interp(NEW(EmptyEnv)())->stringify() == "7");
    CHECK_THROWS_WITH(parse_str("10")->interp(NEW(EmptyEnv)())->call(NEW(NumVal)(3)), "Error: cannot call a number");
}

TEST_CASE("FunVal"){
    CHECK(parse_str("_fun (x) x * 2")->interp(NEW(EmptyEnv)())->equals(NEW(FunVal)("x", NEW(Mult)(NEW(Var)("x"), NEW(Number)(2)), NEW(EmptyEnv)())));
    CHECK(parse_str("_fun (x) x * 2")->interp(NEW(EmptyEnv)())->stringify() == "[function]\n");
    CHECK( !parse_str("_fun (x) x * 2")->interp(NEW(EmptyEnv)())->equals(NEW(NumVal)(2)));
    CHECK_THROWS_WITH(!parse_str("_fun (x) x * 2")->interp(NEW(EmptyEnv)())->add_to(NEW(NumVal)(1)), "no adding functions");
    CHECK_THROWS_WITH(!parse_str("_fun (x) x * 2")->interp(NEW(EmptyEnv)())->mult_with(NEW(NumVal)(1)), "no multiplying functions");
}

TEST_CASE("Step"){
    CHECK(Step::interp_by_steps(parse_str(
            "_let fib = _fun (fib)\n_fun (x)\n_if x == 0\n_then 1\n_else _if x == 2 + -1\n_then 1\n_else fib(fib)(x + -1)\n+ fib(fib)(x + -2)\n_in fib(fib)(10)"))->stringify() == "89" );
}