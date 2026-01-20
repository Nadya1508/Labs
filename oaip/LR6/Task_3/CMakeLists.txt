cmake_minimum_required(VERSION 3.10)
project(StringConversionLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main_app main.cpp)

# Программа с AddressSanitizer
add_executable(test_asan main.cpp)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(test_asan PRIVATE -fsanitize=address -fno-omit-frame-pointer)
    target_link_options(test_asan PRIVATE -fsanitize=address)
endif()

# Программа с ThreadSanitizer  
add_executable(test_tsan main.cpp)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(test_tsan PRIVATE -fsanitize=thread -fno-omit-frame-pointer)
    target_link_options(test_tsan PRIVATE -fsanitize=thread)
endif()

find_package(GTest REQUIRED)
target_link_libraries(main_app GTest::GTest GTest::Main)
target_link_libraries(test_asan GTest::GTest GTest::Main)
target_link_libraries(test_tsan GTest::GTest GTest::Main)

add_test(NAME AddressSanitizerTests COMMAND test_asan --gtest_filter="*")
add_test(NAME ThreadSanitizerTests COMMAND test_tsan --gtest_filter="*")

# Linter target
find_program(CPPCHECK cppcheck)
if(CPPCHECK)
    add_custom_target(lint
        COMMAND ${CPPCHECK} 
        --enable=all
        --suppress=missingIncludeSystem
        --suppress=unusedFunction
        --language=c++
        ${CMAKE_SOURCE_DIR}/main.cpp
        VERBATIM
    )
endif()