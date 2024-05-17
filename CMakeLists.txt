cmake_minimum_required(VERSION 3.28)
project(BattleShip)

set(CMAKE_CXX_STANDARD 17)

add_executable(BattleShip main.cpp
        game_engine.cpp
        game_engine.h)
