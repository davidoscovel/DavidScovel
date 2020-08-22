cmake_minimum_required(VERSION 3.15)
project(Homework1)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=undefined")

add_executable(msdscript parse.cpp calc.h parse.h Expr.cpp Expr.h main.cpp test.cpp value.cpp value.h pointer.h Env.cpp Env.h Step.cpp Step.h Cont.cpp Cont.h msdScriptLib.h)
add_executable(msdtestdriver exec.cpp exec.hpp runner_main.cpp)