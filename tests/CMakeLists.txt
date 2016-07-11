enable_testing()

find_package(Threads REQUIRED)
find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})

set(LIBS -lm -lpthread ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
set(PROJECT_LIBS lib_falcon)
include_directories(. ../src)

set(TEST_SOURCE test_main.c)
set(TEST_CASES test_convert.h)
set(TEST_HEADERS asserts.h)
add_executable(TestFalconCalc ${TEST_SOURCE} ${TEST_CASES} ${TEST_HEADERS})
target_link_libraries(TestFalconCalc ${PROJECT_LIBS} ${LIBS})
add_test(TestFalconCalc ${CMAKE_CURRENT_BINARY_DIR}/TestFalconCalc)