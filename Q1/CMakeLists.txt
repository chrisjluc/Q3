cmake_minimum_required(VERSION 3.2)
project(Q1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    IteratorTestHarness.cpp
    Menu.cpp
    Menu.h
    MenuComponent.cpp
    MenuComponent.h
    MenuItem.cpp
    MenuItem.h)

add_executable(Q1 ${SOURCE_FILES})