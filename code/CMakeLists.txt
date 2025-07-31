cmake_minimum_required(VERSION 3.31)
project(code)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(nr)
add_subdirectory(minilibg++)
add_subdirectory(util)
add_subdirectory(alg)

set(TSCOMMANDS)
add_subdirectory(clm)
message(STATUS "TSCOMMANDS = ${TSCOMMANDS}")

set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "Install path prefix" FORCE)
install(TARGETS nr minilibg++ util alg ${TSCOMMANDS}
        ARCHIVE DESTINATION tsa/lib
        LIBRARY DESTINATION tsa/lib
        RUNTIME DESTINATION tsa/bin)
