cmake_minimum_required(VERSION 3.20)
project(RobotArmFunctions)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(RobotArmFunctions 
                main.cpp
                can_interface.cpp
                robotFunctions.cpp
                byte_order.cpp)
