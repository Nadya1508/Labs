cmake_minimum_required(VERSION 3.10)
project(NumberSystemCalculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Санитайзеры
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(APPLE)
        set(SANITIZER_FLAGS "-fsanitize=address -fsanitize=undefined")
    else()
        set(SANITIZER_FLAGS "-fsanitize=address -fsanitize=thread")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS} -g")
endif()

add_executable(calculator main.cpp)

# Линтер с кастомными настройками
find_program(CPPCHECK cppcheck)
if(CPPCHECK)
    # Создаем отдельную команду для линтера
    add_custom_target(linter
        COMMAND ${CPPCHECK}
                --enable=all
                --suppress=missingIncludeSystem
                --suppress=unusedFunction  
                --suppress=*:${CMAKE_BINARY_DIR}/*
                --force
                --language=c++
                ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running cppcheck linting (ignoring build directory)"
        VERBATIM
    )
endif()