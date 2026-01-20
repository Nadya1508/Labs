cmake_minimum_required(VERSION 3.10)
project(DivisibilityChecker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Проверка компилятора 
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Для MacBook с Clang - используем AddressSanitizer
    set(SANITIZER_FLAGS "-fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS} -Wall -Wextra -Wpedantic -Werror -g -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SANITIZER_FLAGS}")
    message(STATUS "Using Clang compiler with AddressSanitizer")
else()
    message(WARNING "Unsupported compiler for sanitizers: ${CMAKE_CXX_COMPILER_ID}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -g -O0")
endif()

set(CMAKE_BUILD_TYPE Debug)

add_executable(divisibility_checker main.cpp)

# Улучшенная цель для линтера
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    add_custom_target(linter
        COMMAND ${CLANG_TIDY_EXE} ${CMAKE_SOURCE_DIR}/main.cpp -checks='-*,readability-*,performance-*,portability-*,modernize-*' -- -std=c++17
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running clang-tidy static code analysis"
    )
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
else()
    add_custom_target(linter
        COMMAND ${CMAKE_COMMAND} -E echo "clang-tidy not found, skipping advanced linting"
        COMMAND ${CMAKE_COMMAND} -E echo "Install clang-tidy for better static analysis"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "clang-tidy not available"
    )
    message(STATUS "clang-tidy not found")
endif()

# Альтернативная цель для базовой проверки
add_custom_target(linter-basic
    COMMAND ${CMAKE_CXX_COMPILER} -Wall -Wextra -Wpedantic -Werror -fsyntax-only ${CMAKE_SOURCE_DIR}/main.cpp
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running basic syntax check with compiler warnings"
)

# Цель для форматирования кода (опционально)
find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(CLANG_FORMAT_EXE)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i ${CMAKE_SOURCE_DIR}/main.cpp
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Formatting code with clang-format"
    )
    message(STATUS "clang-format found: ${CLANG_FORMAT_EXE}")
endif()

message(STATUS "Build configuration complete")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")