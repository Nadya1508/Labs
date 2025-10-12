cmake_minimum_required(VERSION 3.10)
project(ArrayProcessorTest)

set(CMAKE_CXX_STANDARD 14)

Находим GoogleTest
find_package(GTest REQUIRED)

Основная программа
add_executable(main_program main.cpp array_processor.cpp)

Тестовая программа
add_executable(test_program test_main.cpp array_processor.cpp)
target_link_libraries(test_program GTest::gtest GTest::gtest_main)
