#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

bool isArmstrongNumber(int number) {
    int originalNumber = number;
    int sum = 0;
    int digits = 0;
    
    int temp = number;
    while (temp != 0) {
        digits++;
        temp /= 10;
    }
    
    temp = number;
    while (temp != 0) {
        int digit = temp % 10;
        sum += pow(digit, digits);
        temp /= 10;
    }
    
    return sum == originalNumber;
}

void show_context_menu() {
    cout << "===================================================\n";
    cout << "          Лабораторная работа №3\n";
    cout << "          ПОИСК ЧИСЕЛ АРМСТРОНГА\n";
    cout << "===================================================\n";
    cout << "Суть задания: найти все числа Армстронга, меньшие заданного числа.\n";
    cout << "Выполнила: Седельник Надежда\n";
    cout << "===================================================\n";
}

void show_main_menu() {
    cout << "\nГЛАВНОЕ МЕНЮ:\n";
    cout << "1. Найти числа Армстронга\n";
    cout << "2. Показать контекстное меню\n";
    cout << "3. Выйти из программы\n";
    cout << "Выберите действие (1-3)\n";
}


void find_armstrong_numbers() {
    int limit;
    
    cout << "Введите верхнюю границу поиска (число > 0): ";
    cin >> limit;
    
    if (cin.fail() || limit <= 0) {
        cout << "Ошибка! Введите корректное число больше 0." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Нажмите Enter для продолжения..." << endl;
        cin.get();
        return;
    }
    
    cout << endl << "РЕЗУЛЬТАТЫ ПОИСКА:" << endl;
    cout << "Числа Армстронга меньше " << limit << ":" << endl;
    
    int count = 0;
    bool firstNumber = true;
    
    for (int i = 1; i < limit; i++) {
        if (isArmstrongNumber(i)) {
            if (!firstNumber) {
                cout << ", ";
            }
            cout << i;
            count++;
            firstNumber = false;
        }
    }
    
    if (count == 0) {
        cout << "В указанном диапазоне чисел Армстронга не найдено." << endl;
    } else {
        cout << endl << "Всего найдено: " << count << " чисел" << endl;
    }
    
    cout << "Нажмите Enter для продолжения..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
 
int main () {
    int choice;

    show_context_menu();

    do {
        show_main_menu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            choice = 0;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }

        switch(choice) {
            case 1:
              find_armstrong_numbers();
            break;
            case 2:
              show_context_menu();
            break;
            case 3:
              cout << "Выход из программы." << endl;
            break;
            default:
              cout << "Ошибка! Выберите действие от 1 до 3." << endl;
              cout << "Нажмите Enter для продолжения..." << endl;
              cin.get();
            break;
        }
    } while (choice != 3);
    
    return 0;
}
