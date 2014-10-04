cmake_minimum_required(VERSION 2.6)
project(gc)

SET(CMAKE_CXX_FLAGS "-std=c++11 -lpthread")

add_executable(gc main.cpp)

install(TARGETS gc RUNTIME DESTINATION bin)

add_subdirectory(src)