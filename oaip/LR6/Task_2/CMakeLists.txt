cmake_minimum_required(VERSION 3.10)
project(TextProcessor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Санитайзеры
if(APPLE)
    set(SANITIZER_FLAGS "-fsanitize=address,undefined -fno-omit-frame-pointer")
    message(STATUS "Using AddressSanitizer + UndefinedBehaviorSanitizer")
else()
    set(SANITIZER_FLAGS "-fsanitize=address,thread -fno-omit-frame-pointer")
    message(STATUS "Using AddressSanitizer + ThreadSanitizer")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SANITIZER_FLAGS}")

# Строгий Linter
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(WARNING_FLAGS "-Wall -Wextra -Wpedantic -Werror -Wconversion -Wshadow")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS}")
endif()

# Основная программа
add_executable(text_processor main.cpp)

# Google Tests
set(GTEST_ROOT "/opt/homebrew/Cellar/googletest/1.17.0")
add_executable(text_processor_tests main.cpp)
target_compile_definitions(text_processor_tests PRIVATE TEST_MODE)
target_include_directories(text_processor_tests PRIVATE ${GTEST_ROOT}/include)
target_link_directories(text_processor_tests PRIVATE ${GTEST_ROOT}/lib)
target_link_libraries(text_processor_tests gtest gtest_main pthread)

enable_testing()
add_test(NAME TextProcessorTests COMMAND text_processor_tests)