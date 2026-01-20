#include <iostream>
#include "matrix_functions.h"

using namespace std;

void inputMatrix(double** matrix, int rows, int cols) {
    cout << "Введите элементы матрицы " << rows << "x" << cols << ":\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Элемент [" << i << "][" << j << "]: ";
            while (!(cin >> matrix[i][j])) {
                cout << "Ошибка! Введите вещественное число: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }
}

void printMatrix(double** matrix, int rows, int cols) {
    cout << "Матрица " << rows << "x" << cols << ":\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void findAndPrintZeroElements(double** matrix, int rows, int cols) {
    int count = 0;
    cout << "Поиск нулевых элементов...\n";
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0.0) {
                count++;
                cout << "Найден нулевой элемент по индексу [" << i << "][" << j << "]\n";
            }
        }
    }
    
    if (count == 0) {
        cout << "Нулевые элементы не найдены.\n";
    } else {
        cout << "Общее количество нулевых элементов: " << count << "\n";
    }
}

void showContextMenu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "           КОНТЕКСТНОЕ МЕНЮ\n";
    cout << "========================================\n";
    cout << "Суть задания: Работа с двумерным массивом\n";
    cout << "вещественных чисел - поиск нулевых элементов\n";
    cout << "и перестановка в обратном порядке\n";
    cout << "Выполнила: Седельник Надежда\n";
    cout << "========================================\n";
    cout << "\n";
}

void showMainMenu() {
    cout << "\n";
    cout << "=== ГЛАВНОЕ МЕНЮ ===\n";
    cout << "1. Ввести новые данные\n";
    cout << "2. Показать контекстное меню\n";
    cout << "3. Выйти из программы\n";
    cout << "Выберите действие: ";
}

int safeInputInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value > 0) {
                break;
            } else {
                cout << "Ошибка! Число должно быть положительным.\n";
            }
        } else {
            cout << "Ошибка! Введите целое число: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    return value;
}

int main() {
    double** matrix = nullptr;
    int rows = 0, cols = 0;
    char choice;
    
    showContextMenu();
    
    do {
        showMainMenu();
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка ввода! Пожалуйста, введите число от 1 до 3.\n";
            continue;
        }
        
        switch (choice) {
            case '1': {
                if (matrix != nullptr) {
                    deleteMatrix(matrix, rows);
                }
                
                rows = safeInputInt("Введите количество строк: ");
                cols = safeInputInt("Введите количество столбцов: ");
                
                matrix = createMatrix(rows, cols);
                inputMatrix(matrix, rows, cols);
                
                cout << "\nИсходная матрица:\n";
                printMatrix(matrix, rows, cols);
                
                findAndPrintZeroElements(matrix, rows, cols);
                
                reverseMatrix(matrix, rows, cols);
                
                cout << "\nМатрица после перестановки:\n";
                printMatrix(matrix, rows, cols);
                
                break;
            }
            
            case '2':
                showContextMenu();
                break;
                
            case '3':
                cout << "Выход из программы...\n";
                break;
                
            default:
                cout << "Неверный выбор! Пожалуйста, выберите 1, 2 или 3.\n";
                break;
        }
        
    } while (choice != '3');
    
    if (matrix != nullptr) {
        deleteMatrix(matrix, rows);
    }
    
    return 0;
}