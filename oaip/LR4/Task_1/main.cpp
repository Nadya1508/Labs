#include <iostream>
#include "array_processor.h"

using namespace std;

int main() {
    int arr[MAX_SIZE];  
    int size = 0;
    int choice;
    
    cout << "ПРОГРАММА ОБРАБОТКИ МАССИВОВ" << endl;
    cout << "=============================" << endl;
    
    do {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << endl;
        cout << "1 - Ввести массив" << endl;
        cout << "2 - Показать массив" << endl;
        cout << "3 - Показать задание" << endl;
        cout << "4 - Выполнить обработку" << endl;
        cout << "0 - Выход" << endl;
        cout << "Выберите действие: ";
        
        choice = safeInput();
        
        switch(choice) {
            case 0:
                cout << "Завершение работы программы. До свидания!" << endl;
                break;
                
            case 1:
                inputArray(arr, size);
                cout << "✓ Массив успешно сохранен!" << endl;
                break;
                
            case 2:
                if (size == 0) {
                    cout << "✗ Массив не введен! Сначала введите массив." << endl;
                } else {
                    cout << "Текущий массив:" << endl;
                    printArray(arr, size);
                    cout << "Размер: " << size << " элементов" << endl;
                }
                break;
                
            case 3:
                showContextMenu();
                showInstructions();
                break;
                
            case 4:
                if (size == 0) {
                    cout << "✗ Массив не введен! Сначала введите массив." << endl;
                } else {
                    showContextMenu();
                    cout << "\n--- ВЫПОЛНЕНИЕ ОБРАБОТКИ ---" << endl;
                    cout << "Исходный массив: ";
                    printArray(arr, size);
                    cout << "Исходный размер: " << size << endl;
                    
                    removeMinMax(arr, size);
                    
                    cout << "\n--- РЕЗУЛЬТАТ ---" << endl;
                    cout << "Результирующий массив: ";
                    printArray(arr, size);
                    cout << "Новый размер: " << size << endl;
                    cout << "✓ Обработка завершена успешно!" << endl;
                }
                break;
                
            default:
                cout << "✗ Неверный выбор! Введите число от 0 до 4." << endl;
                break;
        }
        
    } while (choice != 0);
    
    return 0;
}