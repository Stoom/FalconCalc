cmake_minimum_required(VERSION 3.5)
project(FalconCalc)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Werror")

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()