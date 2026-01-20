echo "=== Сборка проекта ==="

mkdir -p lib
mkdir -p bin

echo "1. Компиляция объектных файлов библиотеки..."
g++ -std=c++17 -c src/matrix_ops.cpp -Iinclude -o lib/matrix_ops.o

echo "2. Создание статической библиотеки .a..."
ar rcs lib/libmatrixops.a lib/matrix_ops.o

echo "3. Компиляция основной программы с библиотекой..."
g++ -std=c++17 src/main.cpp lib/libmatrixops.a -Iinclude -o bin/main

echo "4. Компиляция тестов с Google Test..."
g++ -std=c++17 tests/test_matrix_ops.cpp lib/libmatrixops.a -Iinclude -I/opt/homebrew/Cellar/googletest/1.17.0/include -L/opt/homebrew/Cellar/googletest/1.17.0/lib -lgtest -lgtest_main -pthread -o bin/tests

echo "=== Сборка завершена ==="
echo ""
echo "Для запуска программы: ./bin/main"
echo "Для запуска тестов: ./bin/tests"