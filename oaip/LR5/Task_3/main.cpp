#include <iostream>
#include "matrix_functions.h"  

using namespace std;

void showContextMenu() {
    cout << "===============================================\n";
    cout << "           ОБРАБОТКА МАТРИЦЫ\n";
    cout << "===============================================\n";
    cout << "Суть задания: Создать массив из четных элементов\n";
    cout << "главной диагонали матрицы и вычислить их произведение\n";
    cout << "Выполнила: Седельник Надежда\n";
    cout << "===============================================\n\n";
}

void clearInputBuffer() {
    int c;
    while ((c = cin.get()) != '\n' && c != EOF) {}
}

int inputInt(const char* prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cout << "Ошибка! Введите целое число.\n";
            cin.clear();
            clearInputBuffer();
        } else {
            clearInputBuffer();
            break;
        }
    }
    return value;
}

int inputPositiveInt(const char* prompt) {
    int value;
    while (true) {
        value = inputInt(prompt);
        if (value > 0) {
            break;
        } else {
            cout << "Ошибка! Число должно быть положительным.\n";
        }
    }
    return value;
}

int** createMatrix(int n, int k) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[k];
    }
    return matrix;
}

void deleteMatrix(int** matrix, int n) {
    if (matrix != nullptr) {
        for (int i = 0; i < n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

void inputMatrix(int** matrix, int n, int k) {
    cout << "\nВведите элементы матрицы " << n << "x" << k << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cout << "Элемент [" << i << "][" << j << "]: ";
            matrix[i][j] = inputInt("");
        }
    }
}

void printMatrix(int** matrix, int n, int k) {
    cout << "\nМатрица " << n << "x" << k << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void printArray(int* array, int size) {
    if (size == 0 || array == nullptr) {
        cout << "Массив пуст";
        return;
    }
    
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << array[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]";
}

void processMatrix() {
    
    int n = inputPositiveInt("Введите количество строк (n): ");
    int k = inputPositiveInt("Введите количество столбцов (k): ");
    
    int** matrix = createMatrix(n, k);
    inputMatrix(matrix, n, k);
    
    printMatrix(matrix, n, k);
    
    int resultSize;
    int* evenDiagonalArray = createEvenDiagonalArray(matrix, n, k, resultSize);
    
    long long product = calculateProduct(evenDiagonalArray, resultSize);
    
    cout << "\n===============================================\n";
    cout << "РЕЗУЛЬТАТЫ:\n";
    cout << "Массив из четных элементов главной диагонали: ";
    printArray(evenDiagonalArray, resultSize);
    cout << endl;
    
    cout << "Произведение элементов массива: ";
    if (resultSize == 0) {
        cout << "0 (массив пуст)";
    } else {
        cout << product;
    }
    cout << endl;
    cout << "===============================================\n";
    
    if (evenDiagonalArray != nullptr) {
        delete[] evenDiagonalArray;
    }
    deleteMatrix(matrix, n);
}

void showMainMenu() {
    cout << "\n===============================================\n";
    cout << "               ГЛАВНОЕ МЕНЮ\n";
    cout << "===============================================\n";
    cout << "1. Начать обработку матрицы\n";
    cout << "2. Показать информацию о задании\n";
    cout << "3. Выйти из программы\n";
    cout << "===============================================\n";
    cout << "Выберите действие (1-3): ";
}

int main() {
    bool running = true;
    
    showContextMenu();
    
    while (running) {
        showMainMenu();
        
        int choice = inputInt("");
        
        switch (choice) {
            case 1:
                processMatrix();
                break;
            case 2:
                showContextMenu();
                break;
            case 3:
                running = false;
                cout << "Выход из программы. До свидания!\n";
                break;
            default:
                cout << "Неверный выбор! Пожалуйста, выберите 1, 2 или 3.\n";
        }
    }
    
    return 0;
}