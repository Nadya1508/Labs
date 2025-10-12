#include <iostream>
#include <limits>
#include "array_processor.h"

using namespace std;

int safeInput() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода! Введите целое число: ";
    }
    return value;
}

int* inputArray(int& size) {
    cout << "Введите размер массива: ";
    size = safeInput();
    
    while (size <= 0) {
        cout << "Размер должен быть положительным! Введите снова: ";
        size = safeInput();
    }
    
    int* arr = new int[size];
    cout << "Введите " << size << " элементов массива:" << endl;
    
    for (int i = 0; i < size; i++) {
        cout << "Элемент " << i + 1 << ": ";
        arr[i] = safeInput();
    }
    
    return arr;
}

void printArray(int* arr, int size) {
    if (size == 0 || arr == nullptr) {
        cout << "Массив пуст" << endl;
        return;
    }
    
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

int findMin(int* arr, int size) {
    if (size == 0) return 0;
    
    int minVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    return minVal;
}

int findMax(int* arr, int size) {
    if (size == 0) return 0;
    
    int maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

void removeMinMax(int*& arr, int& size) {
    if (size == 0 || arr == nullptr) {
        cout << "Массив пуст!" << endl;
        return;
    }
    
    int minVal = findMin(arr, size);
    int maxVal = findMax(arr, size);
    
    cout << "Найденные значения: min=" << minVal << ", max=" << maxVal << endl;
    
    if (minVal == maxVal) {
        cout << "Все элементы массива одинаковы" << endl;
        delete[] arr;
        arr = nullptr;
        size = 0;
        return;
    }
    
    int countToRemove = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == minVal || arr[i] == maxVal) {
            countToRemove++;
        }
    }
    
    if (countToRemove >= size) {
        cout << "Удаляются все элементы массива" << endl;
        delete[] arr;
        arr = nullptr;
        size = 0;
        return;
    }
    
    int newSize = size - countToRemove;
    int* newArr = new int[newSize];
    
    int newIndex = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] != minVal && arr[i] != maxVal) {
            newArr[newIndex++] = arr[i];
        }
    }
    
    delete[] arr;
    arr = newArr;
    size = newSize;
    
    cout << "Удалено " << countToRemove << " элементов. Новый размер: " << size << endl;
}