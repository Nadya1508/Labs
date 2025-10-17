cmake_minimum_required(VERSION 3.10)
project(MatrixProcessor)

set(CMAKE_CXX_STANDARD 11)


find_package(GTest REQUIRED)


add_executable(matrix_app main.cpp matrix_utils.cpp)


add_executable(matrix_tests tests.cpp matrix_utils.cpp)
target_link_libraries(matrix_tests GTest::gtest GTest::gtest_main)


enable_testing()
add_test(NAME MatrixTests COMMAND matrix_tests)