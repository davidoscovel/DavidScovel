//
// Created by David Scovel on 1/21/20.
//

#include <iostream>
#include "parse.h"

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Step.h"

int main(int argc, char **argv)
{
    //Catch::Session().run(argc, argv);

        PTR(Expr)e;
        try {
            e = parse(std::cin);
        }catch(const std::runtime_error& error){
            std::cerr << error.what();
            return 1;
        }

        if(argc < 2){
            try {
                std::cout << e->interp(NEW(EmptyEnv)())->stringify() << "\n";
            }catch(const std::runtime_error& error){
                std::cerr << error.what();
                return 2;
            }
            return 0;
        }
        else if(strncmp(argv[1], "--opt", 10) == 0){
            std::cout << e->optimize()->stringify() << "\n";
            return 0;
        }
        else if(strncmp(argv[1], "--step", 10) == 0){
            std::cout << Step::interp_by_steps(e)->stringify() << "\n";
        }
        else{
            std::cerr << "Error: invalid command \nValid commands: --opt --step\n";
            return -1;
        }

    return 0;
}