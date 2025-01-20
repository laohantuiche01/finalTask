cmake_minimum_required(VERSION 3.28)
project(final_task)

set(CMAKE_CXX_STANDARD 17)

add_executable(final_task main.cpp
        RobotManager.h
        RobotManager.cpp
        Robot.h
        Robot.cpp
        Infantry.h
        Infantry.cpp
        Engineer.h
        Engineer.cpp)
