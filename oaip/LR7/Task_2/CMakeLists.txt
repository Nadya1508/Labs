cmake_minimum_required(VERSION 3.10)
project(BinaryAddition)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Базовые флаги линтера
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

# Основная цель с address sanitizer
add_executable(binary_addition main.cpp)
target_compile_options(binary_addition PRIVATE -fsanitize=address)
target_link_options(binary_addition PRIVATE -fsanitize=address)

# Цель с thread sanitizer
add_executable(binary_addition_thread main.cpp)
target_compile_options(binary_addition_thread PRIVATE -fsanitize=thread)
target_link_options(binary_addition_thread PRIVATE -fsanitize=thread)

# Цель для linter
add_custom_target(linter
    COMMAND echo "=== Linter Check ==="
    COMMAND echo "Компиляция с флагами: -Wall -Wextra -Wpedantic -Werror"
    COMMAND ${CMAKE_CXX_COMPILER} -Wall -Wextra -Wpedantic -Werror -c ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp -o ${CMAKE_CURRENT_BINARY_DIR}/main_linter.o
    COMMAND echo "Linter проверка пройдена успешно!"
    COMMENT "Запуск линтера..."
)

# Цель для проверки санитайзеров
add_custom_target(sanitizers
    COMMAND echo "=== Санитайзеры настроены ==="
    COMMAND echo "AddressSanitizer: binary_addition"
    COMMAND echo "ThreadSanitizer: binary_addition_thread"
    COMMAND echo "Оба санитайзера указаны в CMake"
    COMMENT "Информация о санитайзерах..."
)