enable_testing()

find_package(Threads REQUIRED)
find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})

set(LIBS ${LIBS} -lm -lpthread ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
include_directories(. ../src)

set(TEST_SOURCE test_main.c)
add_executable(TestFalconCalc ${TEST_SOURCE})
target_link_libraries(TestFalconCalc ${LIBS})
add_test(TestFalconCalc ${CMAKE_CURRENT_BINARY_DIR}/TestFalconCalc)