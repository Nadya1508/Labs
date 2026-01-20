cmake_minimum_required(VERSION 3.10)
project(PoisonedBarrel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Базовые флаги для всех сборок
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

# Основной исполняемый файл
add_executable(poisoned_barrel main.cpp)

# AddressSanitizer версия
add_executable(poisoned_barrel_asan main.cpp)
target_compile_options(poisoned_barrel_asan PRIVATE -fsanitize=address)
target_link_options(poisoned_barrel_asan PRIVATE -fsanitize=address)

# ThreadSanitizer версия  
add_executable(poisoned_barrel_tsan main.cpp)
target_compile_options(poisoned_barrel_tsan PRIVATE -fsanitize=thread)
target_link_options(poisoned_barrel_tsan PRIVATE -fsanitize=thread)

# Цель для линтера
add_custom_target(linter
    COMMAND echo "=== Linter Check ==="
    COMMAND echo "Компиляция с флагами: -Wall -Wextra -Wpedantic -Werror"
    COMMAND ${CMAKE_CXX_COMPILER} -Wall -Wextra -Wpedantic -Werror -c ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp -o ${CMAKE_CURRENT_BINARY_DIR}/main_linter.o
    COMMAND echo "Linter проверка пройдена успешно!"
    COMMENT "Запуск линтера..."
)

# Цель для проверки всех санитайзеров
add_custom_target(sanitizers
    COMMAND echo "=== Проверка санитайзеров ==="
    COMMAND echo "AddressSanitizer: poisoned_barrel_asan"
    COMMAND echo "ThreadSanitizer: poisoned_barrel_tsan" 
    COMMAND echo "Основная программа: poisoned_barrel"
    COMMENT "Информация о санитайзерах..."
)