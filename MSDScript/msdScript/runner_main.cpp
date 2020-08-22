//
// Created by David Scovel on 1/30/20.
//

#include <iostream>
#include <string>
#include <cstdlib>

#include "exec.hpp"

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "pointer.h"

const int N = 1000000;
const int RANDOM_ITERS = 100;

static void check_success(ExecResult &r);
static std::string make_big_string(std::string word, int size);
static std::string random_word();
static std::string generate_Expr();

int main(int argc, const char * argv[]) {
    std::string big_string = make_big_string("hello", N);

    // Example: running `wc`
    const char * const wc_command[] = {argv[1], NULL };
    ExecResult add_result = exec_program(wc_command, generate_Expr());
    check_success(add_result);
    if(add_result.out != add_result.out){
        std::cout << "Error: Random Expression: " << add_result.out << "\n" ;
    }
    std::cout << add_result.out;

//    // Example: checking that `cat` echos its input
//    const char * const cat_command[] = { "/bin/cat", NULL };
//    ExecResult cat_result = exec_program(cat_command, big_string);
//    check_success(cat_result);
//    if (big_string != cat_result.out)
//        std::cerr << "bad cat result\n";
//
//    // Stress test by checking `cat` even more
//    for (int i = 0; i < RANDOM_ITERS; i++) {
//        int size = rand() % N;
//        std::string word = random_word();
//        std::string random_big_string = make_big_string(word, size);
//        ExecResult random_cat_result = exec_program(cat_command, random_big_string);
//        check_success(random_cat_result);
//        if (random_big_string != random_cat_result.out) {
//            std::cerr << "bad random cat result\n";
//            std::cerr << " word: ";
//            for (int i = 0; i < word.length(); i++)
//                std::cerr << " " << (int)(unsigned char)word[i];
//            std::cerr << "\n";
//            std::cerr << " word length: " << word.length() << "\n";
//            std::cerr << " size: " << size << "\n";
//            std::cerr << " input length:  " << random_big_string.length() << "\n";
//            std::cerr << " output length: " << random_cat_result.out.length() << "\n";
//        }
//    }

    return 0;
}

static void check_success(ExecResult &result) {
    std::cerr << result.err;
    if (result.exit_code != 0)
        std::cerr << "non-zero exit: " << result.exit_code << "\n";
}

static std::string make_big_string(std::string word, int size) {
    std::string big;
    for (int i = 0; i < size; i++)
        big += word + "\n";
    return big;
}

static std::string random_word() {
    std::string word = "";
    for (int i = rand() % 32; i-- > 0; ) {
        word += rand() % 256;
    }
    return word;
}


static std::string generate_Add(){
    std::string add = "";
    add += rand();
    add += " + ";
    add += rand();
    return add;
}

static std::string generate_Mult(){
    std::string mult = "";
    mult += rand();
    mult += " * ";
    mult += rand();
    return mult;
}

static std::string generate_If(){
    std::string If = "_if ";
    int num = rand();
    if((num % 2) == 1){
        If += "_true ";
    }
    else{
        If += "_false ";
    }
    If += "_then ";
    If += rand();
    If += "_else ";
    If += rand();
    return If;
}

static std::string generate_Comp(){
    std::string comp = "";
    comp += rand();
    comp += " == ";
    comp += rand();
    return comp;
}

static std::string generate_Fun(){
    std::string fun = "_fun (x) x + ";
    fun += rand();
    return fun;
}

static std::string generate_Call(){
    std::string call = "( ";
    call += generate_Fun();
    call += ")(";
    call += rand();
    call += ")";
}

static std::string generate_Let(){
    std::string let = "_let x = ";
    let += rand();
    let += " _in x + ";
    let += rand();
    return let;
}

static std::string generate_Expr(){
    int x = rand() % 7;
    if(x == 0){
        return generate_Add();
    }
    else if(x == 1){
        return generate_Mult();
    }
    else if(x == 1){
        return generate_Mult();
    }
    else if(x == 2){
        return generate_If();
    }
    else if(x == 3){
        return generate_Comp();
    }
    else if(x == 4){
        return generate_Fun();
    }
    else if(x == 5){
        return generate_Call();
    }
    else if(x == 6){
        return generate_Let();
    }
}
