#include "array_utils.h"
#include <iostream>

Array3D::Array3D(int n) : size(n) {
    data = new int**[size];
    int i = 0;
    while (i < size) {
        data[i] = new int*[size];
        int j = 0;
        while (j < size) {
            data[i][j] = new int[size];
            int k = 0;
            while (k < size) {
                data[i][j][k] = 0;
                k++;
            }
            j++;
        }
        i++;
    }
}

Array3D::~Array3D() {
    int i = 0;
    while (i < size) {
        int j = 0;
        while (j < size) {
            delete[] data[i][j];
            j++;
        }
        delete[] data[i];
        i++;
    }
    delete[] data;
}

void Array3D::fillRandom() {
    int seed = 1;
    
    int i = 0;
    while (i < size) {
        int j = 0;
        while (j < size) {
            int k = 0;
            while (k < size) {
                seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
                data[i][j][k] = seed % 100;
                k++;
            }
            j++;
        }
        i++;
    }
}

void Array3D::fillFromInput() {
    std::cout << "Введите " << size * size * size << " элементов массива:" << std::endl;
    
    int total = size * size * size;
    int index = 0;
    
    while (index < total) {
        int i = index / (size * size);
        int j = (index % (size * size)) / size;
        int k = index % size;
        
        int value;
        bool valid = false;
        
        while (!valid) {
            std::cout << "Элемент [" << i << "][" << j << "][" << k << "]: ";
            
            if (std::cin >> value) {
                if (value >= 0) {
                    data[i][j][k] = value;
                    valid = true;
                } else {
                    std::cout << "Ошибка: число должно быть неотрицательным!" << std::endl;
                }
            } else {
                std::cout << "Ошибка: введите целое число!" << std::endl;
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        }
        index++;
    }
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void Array3D::setValue(int x, int y, int z, int value) {
    data[x][y][z] = value;
}

int Array3D::getValue(int x, int y, int z) const {
    return data[x][y][z];
}

int Array3D::findMaxDiagonalSum() const {
    int maxSum = -1;
    
    int sum1 = 0;
    int i = 0;
    while (i < size) {
        sum1 += data[i][i][i];
        i++;
    }
    if (sum1 > maxSum) maxSum = sum1;
    
    int sum2 = 0;
    i = 0;
    while (i < size) {
        sum2 += data[i][i][size-1-i];
        i++;
    }
    if (sum2 > maxSum) maxSum = sum2;
    
    int sum3 = 0;
    i = 0;
    while (i < size) {
        sum3 += data[i][size-1-i][i];
        i++;
    }
    if (sum3 > maxSum) maxSum = sum3;
    
    int sum4 = 0;
    i = 0;
    while (i < size) {
        sum4 += data[size-1-i][i][i];
        i++;
    }
    if (sum4 > maxSum) maxSum = sum4;
    
    return maxSum;
}

void printMenu() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "           ГЛАВНОЕ МЕНЮ" << std::endl;
    std::cout << "========================================" << std::endl;
    printTaskInfo();
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "1 - Создать и заполнить случайными числами" << std::endl;
    std::cout << "2 - Создать и заполнить вручную" << std::endl;
    std::cout << "3 - Найти диагональ с максимальной суммой" << std::endl;
    std::cout << "4 - Удалить текущий массив" << std::endl;
    std::cout << "0 - Выход из программы" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Выберите действие: ";
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

void printTaskInfo() {
    std::cout << "ЗАДАНИЕ: Найти диагональ с наибольшей суммой" << std::endl;
    std::cout << "         в трехмерном массиве n×n×n" << std::endl;
    std::cout << "ВЫПОЛНИЛА: Седельник Надежда" << std::endl;
}

int getValidatedInput(const char* prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= minVal && value <= maxVal) {
                clearInputBuffer();
                return value;
            } else {
                std::cout << "Ошибка: число должно быть от " << minVal << " до " << maxVal << std::endl;
            }
        } else {
            std::cout << "Ошибка: введите целое число." << std::endl;
        }
        clearInputBuffer();
    }
}
