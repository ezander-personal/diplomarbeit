cmake_minimum_required(VERSION 3.31)
project(code)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(nr)
add_subdirectory(minilibg++)
add_subdirectory(util)
add_subdirectory(alg)

#add_executable(code)
add_custom_target(foo)