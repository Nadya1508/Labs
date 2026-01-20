cmake_minimum_required(VERSION 3.16)
project(FloatNumberExtractor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опция для выбора санитайзера (по умолчанию address)
option(USE_THREAD_SANITIZER "Use ThreadSanitizer instead of AddressSanitizer" OFF)

if(USE_THREAD_SANITIZER)
    # ThreadSanitizer
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -Wall -Wextra -Wpedantic -Werror")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=thread")
    message(STATUS "Using ThreadSanitizer")
else()
    # AddressSanitizer (по умолчанию)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -Wall -Wextra -Wpedantic -Werror")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
    message(STATUS "Using AddressSanitizer")
endif()

# Основная программа
add_executable(float_number_extractor main.cpp)

# Обходим проблему с Threads
find_library(GTEST_LIB NAMES gtest PATHS /opt/homebrew/lib REQUIRED)
find_library(GTEST_MAIN_LIB NAMES gtest_main PATHS /opt/homebrew/lib REQUIRED)

target_link_libraries(float_number_extractor 
    ${GTEST_LIB}
    ${GTEST_MAIN_LIB}
    pthread
)

target_include_directories(float_number_extractor PRIVATE /opt/homebrew/include)

enable_testing()
add_test(NAME FloatNumberExtractor_Tests COMMAND float_number_extractor --tests)