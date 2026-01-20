#include "matrix_ops.h"        
#include <iostream>  

MatrixOperations::MatrixOperations(int k) : size(k), matrixC(nullptr), matrixD(nullptr) {
    if(!isValidSize(k)) {
        throw "Неверный размер матрицы";
    }
    allocateMemory();
    calculateMatrixC();
    calculateMatrixD();
}

MatrixOperations::~MatrixOperations() {
    freeMemory();
}

void MatrixOperations::allocateMemory() {
    matrixC = new double*[size];
    for(int i = 0; i < size; ++i) {
        matrixC[i] = new double[size]();
    }

    matrixD = new double*[size];
    for(int i = 0; i < size; ++i) {
        matrixD[i] = new double[size]();
    }
}

void MatrixOperations::freeMemory() {
    if (matrixC != nullptr) {
        for (int i = 0; i < size; ++i) {
            delete[] matrixC[i];
        }
        delete [] matrixC;
        matrixC = nullptr;
    }

    if (matrixD != nullptr) {
        for (int i = 0; i < size; ++i) {
            delete[] matrixD[i];
        }
        delete[] matrixD;
        matrixD = nullptr;
    }
}

void MatrixOperations::calculateMatrixC() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            double denominator = i + j + 1;
            if (denominator == 0) {
                matrixC[i][j] = 0.0;
            } else {
                matrixC[i][j] = (i * i + j * j) / denominator;
            }
        }
    }
}

void MatrixOperations::calculateMatrixD() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            double value = i * i + j * j;
            if (j <= 8) {
                matrixD[i][j] = value;
            } else {
                matrixD[i][j] = value / 2.0;
            }
        }
    }
}

double MatrixOperations::getMatrixCValue(int i, int j) const {
    if (i < 0 || i >= size || j < 0 || j >= size) return 0.0;
    return matrixC[i][j];
}

double MatrixOperations::getMatrixDValue(int i, int j) const {
    if (i < 0 || i >= size || j < 0 || j >= size) return 0.0;
    return matrixD[i][j];
}

double MatrixOperations::sumMainDiagonalC() const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) sum += matrixC[i][i];
    return sum;
}

double MatrixOperations::sumSecondaryDiagonalC() const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) sum += matrixC[i][size-1-i];
    return sum;
}

double MatrixOperations::sumMainDiagonalD() const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) sum += matrixD[i][i];
    return sum;
}

double MatrixOperations::sumSecondaryDiagonalD() const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) sum += matrixD[i][size-1-i];
    return sum;
}

void MatrixOperations::printResults() const {
    std::cout << "\nРЕЗУЛЬТАТЫ ДЛЯ МАТРИЦ РАЗМЕРОМ " << size << "x" << size << ":\n";
    
    if (size <= 10) {
        std::cout << "\nМатрица C:\n";
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << matrixC[i][j] << " ";
            }
            std::cout << std::endl;
        }
        
        std::cout << "\nМатрица D:\n";
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << matrixD[i][j] << " ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "Размер матриц слишком большой для отображения.\n";
    }
    
    std::cout << "\nСУММЫ ЭЛЕМЕНТОВ НА ДИАГОНАЛЯХ:\n";
    std::cout << "Матрица C:\n";
    std::cout << "- Сумма главной диагонали: " << sumMainDiagonalC() << std::endl;
    std::cout << "- Сумма побочной диагонали: " << sumSecondaryDiagonalC() << std::endl;
    std::cout << "\nМатрица D:\n";
    std::cout << "- Сумма главной диагонали: " << sumMainDiagonalD() << std::endl;
    std::cout << "- Сумма побочной диагонали: " << sumSecondaryDiagonalD() << std::endl;
}

bool MatrixOperations::isValidSize(int size) {
    return size > 0 && size <= 1000;
}

void showContextMenu() {
    std::cout << "\n=== КОНТЕКСТНОЕ МЕНЮ ===";
    std::cout << "\nЗадание: Сформировать матрицы C и D, вычислить суммы диагоналей";
    std::cout << "\nФормулы:";
    std::cout << "\n  C[i][j] = (i*i + j*j) / (i + j + 1)";
    std::cout << "\n  D[i][j] = i*i + j*j (если j <= 8), иначе (i*i + j*j)/2";
    std::cout << "\nВыполнила: Седельник Надежда";
    std::cout << "\nВариант: 7";
    std::cout << "\n=======================\n";
}

void showInstructions() {
    std::cout << "\n=== ИНСТРУКЦИЯ ===";
    std::cout << "\n1. Введите размер матрицы k (1-1000)";
    std::cout << "\n2. Программа создаст матрицы C и D";
    std::cout << "\n3. Будут вычислены суммы на диагоналях";
    std::cout << "\n4. Для матриц размером <=10 будет показано полное содержимое";
    std::cout << "\n5. Можно повторить расчет без перезапуска программы";
    std::cout << "\n==================\n";
}

int getValidatedInput() {
    const int BUFFER_SIZE = 100;
    char input[BUFFER_SIZE];
    int value = 0;
    bool validInput = false;
    
    while (!validInput) {
        std::cout << "Введите размер матрицы k (1-1000): ";
        
        if (!std::cin.getline(input, BUFFER_SIZE)) {
            std::cout << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }
        
        if (input[0] == '\0') {
            std::cout << "Ошибка! Ввод не может быть пустым.\n";
            continue;
        }
        
        bool isNumber = true;
        for (int i = 0; input[i] != '\0'; ++i) {
            if (input[i] < '0' || input[i] > '9') {
                isNumber = false;
                break;
            }
        }
        
        if (!isNumber) {
            std::cout << "Ошибка! Введите целое положительное число.\n";
            continue;
        }
        
        value = 0;
        for (int i = 0; input[i] != '\0'; ++i) {
            value = value * 10 + (input[i] - '0');
            if (value > 10000) {
                value = 0;
                break;
            }
        }
        
        if (value < 1 || value > 1000) {
            std::cout << "Ошибка! Размер матрицы должен быть от 1 до 1000.\n";
            continue;
        }
        
        validInput = true;
    }
    
    return value;
}

bool askToContinue() {
    const int BUFFER_SIZE = 10;
    char input[BUFFER_SIZE];
    
    while (true) {
        std::cout << "\nВыполнить еще один расчет? (y/n): ";
        
        if (!std::cin.getline(input, BUFFER_SIZE)) {
            std::cout << "Ошибка ввода! ";
            continue;
        }
        
        if (input[0] == 'y' || input[0] == 'Y') {
            return true;
        } else if (input[0] == 'n' || input[0] == 'N') {
            return false;
        } else {
            std::cout << "Пожалуйста, введите 'y' или 'n'. ";
        }
    }
}

void printMainMenu() {
    for (int i = 0; i < 30; ++i) {
        std::cout << std::endl;
    }
    
    std::cout << "================================================";
    std::cout << "\n       СИСТЕМА РАБОТЫ С ДИНАМИЧЕСКИМИ МАТРИЦАМИ";
    std::cout << "\n================================================\n";
    
    static bool firstRun = true;
    if (firstRun) {
        showContextMenu();
        showInstructions();
        firstRun = false;
    }
}