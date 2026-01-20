#include <iostream>
#include <limits>
#include "array_processor.h"

using namespace std;

int safeInput() {
    int value;
    while (true) {
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Ошибка: введите целое число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void showContextMenu() {
    cout << "\n==========================================" << endl;
    cout << "           КОНТЕКСТНОЕ МЕНЮ             " << endl;
    cout << "==========================================" << endl;
    cout << " Задание: Удалить минимальный и          " << endl;
    cout << "          максимальный элементы массива  " << endl;
    cout << " Выполнил: Седельник Надежда            " << endl;
    cout << " Группа: 553503                         " << endl;
    cout << " Вариант: 8                             " << endl;
    cout << "==========================================" << endl;
}

void showInstructions() {
    cout << "\nИНСТРУКЦИЯ:" << endl;
    cout << "-----------" << endl;
    cout << "1. Введите массив чисел" << endl;
    cout << "2. Программа найдет минимальный и максимальный элементы" << endl;
    cout << "3. Удалит все вхождения этих элементов" << endl;
    cout << "4. Покажет исходный и результирующий массивы" << endl;
    cout << "Максимальный размер массива: " << MAX_SIZE << " элементов" << endl;
}

void inputArray(int arr[], int& size) {
    cout << "Введите размер массива (1-" << MAX_SIZE << "): ";
    
    while (true) {
        size = safeInput();
        if (size >= 1 && size <= MAX_SIZE) {
            break;
        }
        cout << "Ошибка: размер должен быть от 1 до " << MAX_SIZE << ": ";
    }
    
    cout << "Введите " << size << " элементов массива:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Элемент " << i + 1 << ": ";
        arr[i] = safeInput();
    }
}

void printArray(const int arr[], int size) {
    if (size == 0) {
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

int findMin(const int arr[], int size) {
    int min_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

int findMax(const int arr[], int size) {
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

void removeMinMax(int arr[], int& size) {
    if (size == 0) {
        cout << "Массив пуст - нечего удалять!" << endl;
        return;
    }
    
    int min_val = findMin(arr, size);
    int max_val = findMax(arr, size);
    
    cout << "Минимальный элемент: " << min_val << endl;
    cout << "Максимальный элемент: " << max_val << endl;
    
    if (min_val == max_val) {
        cout << "Все элементы массива одинаковы!" << endl;
        size = 0;
        return;
    }
    
    int new_size = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] != min_val && arr[i] != max_val) {
            arr[new_size] = arr[i];
            new_size++;
        }
    }
    
    int removed_count = size - new_size;
    size = new_size;
    
    cout << "Удалено элементов: " << removed_count << endl;
}