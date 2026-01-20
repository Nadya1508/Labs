#include <iostream>
#include "array_functions.h"

using namespace std;

void showContextMenu() {
    cout << "===============================================" << endl;
    cout << "           КОНТЕКСТНОЕ МЕНЮ" << endl;
    cout << "===============================================" << endl;
    cout << "Суть задания:" << endl;
    cout << "- Создать двумерный динамический массив" << endl;
    cout << "- Заполнить массив значениями с клавиатуры" << endl;
    cout << "- Создать новый массив из элементов, расположенных" << endl;
    cout << "  в четных столбцах и имеющих нечетное значение" << endl;
    cout << "- Вычислить среднее арифметическое нового массива" << endl;
    cout << "===============================================" << endl;
    cout << "Выполнила: Седельник Надежда" << endl;
    cout << "===============================================" << endl << endl;
}

int** create2DArray(int rows, int cols) {
    int** array = new int*[rows];
    for(int i = 0; i < rows; i++) {
        array[i] = new int[cols];
    }
    return array;
}

void fillArray(int** array, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            while(true) {
                cout << "Элемент [" << i << "][" << j << "]: ";
                if(cin >> array[i][j]) {
                    break;
                } else {
                    cout << "Ошибка! Введите целое число." << endl;
                    clearInputBuffer();
                }
            }
        }
    }
}

void printArray(int** array, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << array[i][j] << "\t";
        }
        cout << endl;
    }
}

int* createFilteredArray(int** sourceArray, int rows, int cols, int& resultSize) {
    int count = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(((j + 1) % 2 == 0) && (sourceArray[i][j] % 2 != 0)) {
                count++;
            }
        }
    }
    
    resultSize = count;
    if(count == 0) {
        return nullptr;
    }
    
    int* filteredArray = new int[count];
    int index = 0;
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(((j + 1) % 2 == 0) && (sourceArray[i][j] % 2 != 0)) {
                filteredArray[index++] = sourceArray[i][j];
            }
        }
    }
    
    return filteredArray;
}

double calculateAverage(int* array, int size) {
    if(size == 0) return 0.0;
    
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += array[i];
    }
    
    return static_cast<double>(sum) / size;
}

void freeMemory(int** array, int rows) {
    for(int i = 0; i < rows; i++) {
        delete[] array[i];
    }
    delete[] array;
}

void freeMemory(int* array) {
    delete[] array;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void runProgram() {
    int rows, cols;
    
    while(true) {
        cout << "\nВведите количество строк: ";
        if(cin >> rows && rows > 0) {
            clearInputBuffer();
            break;
        } else {
            cout << "Ошибка! Введите целое положительное число." << endl;
            clearInputBuffer();
        }
    }
    
    while(true) {
        cout << "Введите количество столбцов: ";
        if(cin >> cols && cols > 0) {
            clearInputBuffer();
            break;
        } else {
            cout << "Ошибка! Введите целое положительное число." << endl;
            clearInputBuffer();
        }
    }
    
    int** mainArray = create2DArray(rows, cols);
    cout << "\nЗаполнение массива:" << endl;
    fillArray(mainArray, rows, cols);
    
    cout << "\nИсходный массив:" << endl;
    printArray(mainArray, rows, cols);
    
    int filteredSize = 0;
    int* filteredArray = createFilteredArray(mainArray, rows, cols, filteredSize);
    
    if(filteredSize > 0) {
        cout << "\nФильтрованный массив (элементы из четных столбцов с нечетными значениями):" << endl;
        for(int i = 0; i < filteredSize; i++) {
            cout << filteredArray[i] << " ";
        }
        cout << endl;
        
        double average = calculateAverage(filteredArray, filteredSize);
        cout << "\nСреднее арифметическое: " << average << endl;
        
        freeMemory(filteredArray);
    } else {
        cout << "\nНет элементов, удовлетворяющих условию (четные столбцы с нечетными значениями)." << endl;
    }
    
    freeMemory(mainArray, rows);
}