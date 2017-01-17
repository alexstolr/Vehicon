cmake_minimum_required(VERSION 3.6)
project(Vehicon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Vehicon.cpp Vehicon.h Lpr.cpp Lpr.h Udplink.cpp Udplink.h)
add_executable(Vehicon ${SOURCE_FILES})