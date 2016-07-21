cmake_minimum_required(VERSION 3.5)
project(FalconCalc)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c11")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    INCLUDE(CodeCoverage)

    SETUP_TARGET_FOR_COVERAGE(
            ${PROJECT_NAME}_cov # Name for custom target.
            TestFalconCalc      # Name of the test driver executable that runs the tests.
            # NOTE! This should always have a ZERO as exit code
            # otherwise the coverage generation will not complete.
            coverage            # Name of output directory.
    )
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif ()

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()