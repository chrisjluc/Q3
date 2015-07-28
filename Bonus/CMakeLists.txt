cmake_minimum_required(VERSION 3.2)
project(Q3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES hangman.cpp)
add_executable(Q3 ${SOURCE_FILES} Strategy.cpp Strategy.h State.cpp State.h BasicStrategy.cpp BasicStrategy.h FrequencyTextStrategy.cpp FrequencyTextStrategy.h FrequencyLengthStrategy.cpp FrequencyLengthStrategy.h)