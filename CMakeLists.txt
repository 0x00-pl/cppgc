cmake_minimum_required(VERSION 2.6)
project(gc)

add_executable(gc main.cpp)

install(TARGETS gc RUNTIME DESTINATION bin)
