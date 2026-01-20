#include <iostream>
#include <cmath>
#include "matrix_utils.h"

using namespace std;

bool isOrthonormal(double** matrix, int n) {
    const double tolerance = 1e-5; 
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            double product = dotProduct(matrix, i, j, n);
            
            if (i == j) {
                
                if (abs(product - 1.0) > tolerance) {
                    cout << "Строка " << i << " не нормирована: " << product << " (отклонение: " << abs(product - 1.0) << ")" << endl;
                    return false;
                }
            } else {
                
                if (abs(product) > tolerance) {
                    cout << "Строки " << i << " и " << j << " не ортогональны: " << product << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

double dotProduct(double** matrix, int row1, int row2, int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += matrix[row1][i] * matrix[row2][i];
    }
    return result;
}

double** createMatrix(int n) {
    double* array = new double[n];

    return matrix;
}

void inputMatrix(double** matrix, int n) {
    cout << "Введите элементы квадратной матрицы " << n << "x" << n << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Элемент [" << i << "][" << j << "]: ";
            while (!(cin >> matrix[i])) {
                cout << "Ошибка! Введите число: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }
}

void printMatrix(double** matrix, int n) {
    cout << "Матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void showTaskInfo() {
    cout << "================================================" << endl;
    cout << "     ПРОВЕРКА ОРТОНОРМИРОВАННОСТИ МАТРИЦЫ" << endl;
    cout << "================================================" << endl;
    cout << "СУТЬ ЗАДАНИЯ: Проверить, является ли матрица" << endl;
    cout << "ортонормированной:" << endl;
    cout << "- Скалярное произведение разных строк = 0" << endl;
    cout << "- Скалярное произведение строки на себя = 1" << endl;
    cout << "ВЫПОЛНИЛА: Седельник Надежда" << endl;
    cout << "ВАРИАНТ: 8" << endl;
    cout << "================================================" << endl;
}

void clearMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}