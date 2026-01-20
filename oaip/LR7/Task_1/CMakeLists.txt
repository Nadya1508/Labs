cmake_minimum_required(VERSION 3.10)
project(ReverseCodeConverter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Два санитайзера + линтер (для GCC или раздельная компиляция)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=thread -Wall -Wextra -Wpedantic -Werror")
else()
    # Для Clang используем раздельные цели
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
endif()

add_executable(reverse_converter main.cpp)

# Дополнительные цели для разных санитайзеров
add_executable(reverse_converter_address main.cpp)
target_compile_options(reverse_converter_address PRIVATE -fsanitize=address)
target_link_options(reverse_converter_address PRIVATE -fsanitize=address)

add_executable(reverse_converter_thread main.cpp)
target_compile_options(reverse_converter_thread PRIVATE -fsanitize=thread)
target_link_options(reverse_converter_thread PRIVATE -fsanitize=thread)

# Цель для linter
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
    COMMAND echo "AddressSanitizer: reverse_converter_address"
    COMMAND echo "ThreadSanitizer: reverse_converter_thread"
    COMMAND echo "Основная программа: reverse_converter"
    COMMENT "Информация о санитайзерах..."
)