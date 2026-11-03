cmake_minimum_required(VERSION 4.3)
project(HSE_homework_C)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(HSE_homework_C
        Fighter.cpp
        Fighter.h
        Game.cpp
        Game.h
        main.cpp)
