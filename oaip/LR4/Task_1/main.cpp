#include <iostream>
#include "array_processor.h"

using namespace std;

void showContextMenu() {
    cout << "\n=== Контекстное меню ===" << endl;
    cout << "Задание: Удалить минимальный и максимальный элементы массива" << endl;
    cout << "Выполнил: Седельник Надежда" << endl;
    cout << "Вариант: 8" << endl;
    cout << "Суть: Найти и удалить все вхождения минимального" << endl;
    cout << "      и максимального элементов из массива" << endl;
    cout << "========================\n" << endl;
}

int main() {
    int* arr = nullptr;
    int size = 0;
    int choice;
    
    do {
        cout << "=== Программа обработки массива ===" << endl;
        cout << "1 - Ввести новый массив" << endl;
        cout << "2 - Показать текущий массив" << endl;
        cout << "3 - Удалить min и max элементы" << endl;
        cout << "0 - Выход" << endl;
        cout << "Выберите действие: ";
        
        choice = safeInput();
        
        switch(choice) {
            case 0:
                cout << "Выход из программы..." << endl;
                break;
                
            case 1:
                if (arr != nullptr) {
                    delete[] arr;
                }
                arr = inputArray(size);
                cout << "Массив успешно введен!" << endl;
                break;
                
            case 2:
                if (arr == nullptr) {
                    cout << "Массив не введен! Сначала введите массив." << endl;
                } else {
                    cout << "Текущий массив: ";
                    printArray(arr, size);
                }
                break;
                
            case 3:
                if (arr == nullptr) {
                    cout << "Массив не введен! Сначала введите массив." << endl;
                } else {
                    showContextMenu();
                    cout << "Исходный массив: ";
                    printArray(arr, size);
                    cout << "Размер: " << size << endl;
                    
                    removeMinMax(arr, size);
                    
                    cout << "Результат: ";
                    printArray(arr, size);
                    cout << "Новый размер: " << size << endl;
                }
                break;
                
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
        }
        
        cout << endl;
        
    } while (choice != 0);
    
    if (arr != nullptr) {
        delete[] arr;
    }
    
    return 0;
}