#include <iostream>
#include "array_functions.h"

using namespace std;

int main() {
    showContextMenu();
    
    char choice;
    do {
        cout << "\n=== МЕНЮ ПРОГРАММЫ ===" << endl;
        cout << "1 - Выполнить задание" << endl;
        cout << "2 - Показать контекстное меню" << endl;
        cout << "0 - Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        clearInputBuffer();

        switch(choice) {
            case '1':
                runProgram();
                break;
            case '2':
                showContextMenu();
                break;
            case '0':
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    } while(choice != '0');
    
    return 0;
}