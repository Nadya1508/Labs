#include <iostream>
#include "magic_square.h"

using namespace std;

int main() {
    cout << "ПРОГРАММА ДЛЯ ПОСТРОЕНИЯ МАГИЧЕСКИХ КВАДРАТОВ" << endl;
    cout << "=============================================" << endl;
    
    MagicSquare* magicSquare = nullptr;
    int choice;
    
    do {
        showContextMenu();
        printMainMenu();
        
        choice = getValidatedInput("", 0, 3);
        
        switch (choice) {
            case 1: {
                int size = getValidatedInput("Введите порядок квадрата (2-20): ", 2, 20);
                
                if (magicSquare != nullptr) {
                    delete magicSquare;
                }
                
                magicSquare = new MagicSquare(size);
                cout << "Магический квадрат порядка " << size << " создан!" << endl;
                magicSquare->printSquare();
                break;
            }
            
            case 2: {
                if (magicSquare != nullptr) {
                    if (magicSquare->isMagicSquare()) {
                        cout << "Поздравляем! Квадрат является магическим." << endl;
                        cout << "Магическая сумма: " << magicSquare->getMagicSum() << endl;
                    } else {
                        cout << "Квадрат не является магическим." << endl;
                    }
                } else {
                    cout << "Ошибка: магический квадрат не создан." << endl;
                }
                break;
            }
            
            case 3: {
                if (magicSquare != nullptr) {
                    magicSquare->printSquare();
                } else {
                    cout << "Ошибка: магический квадрат не создан." << endl;
                }
                break;
            }
            
            case 0: {
                cout << "Завершение работы программы." << endl;
                break;
            }
        }
        
        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            clearInputBuffer();
        }
        
    } while (choice != 0);
    
    if (magicSquare != nullptr) {
        delete magicSquare;
    }
    
    return 0;
}