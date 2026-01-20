cmake_minimum_required(VERSION 3.10)
project(ArrayProcessor)

set(CMAKE_CXX_STANDARD 11)


add_executable(array_processor main.cpp array_processor.cpp)


enable_testing()

find_package(GTest REQUIRED)
add_executable(array_processor_test test_array_processor.cpp array_processor.cpp)
target_link_libraries(array_processor_test GTest::gtest GTest::gtest_main)

add_test(NAME ArrayProcessorTests COMMAND array_processor_test)