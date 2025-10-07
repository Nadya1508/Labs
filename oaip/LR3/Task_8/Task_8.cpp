#include <iostream>
using namespace std;

void show_context_menu() {
    cout << "================================================" << endl;
    cout << "           Лабораторная работа № 3" << endl;
    cout << "           ВЫЧИСЛЕНИЕ СУММЫ РЯДА" << endl;
    cout << "================================================" << endl;
    cout << "СУТЬ ЗАДАНИЯ:" << endl;
    cout << "Вычислить сумму: a₀ - 2a₁ + 4a₂ - 8a₃ + ..." << endl;
    cout << "Знаки чередуются: +, -, +, -..." << endl;
    cout << "Числа умножаются на: 1, 2, 4, 8, 16..." << endl;
    cout << "ОГРАНИЧЕНИЕ: Использование вещественной арифметики запрещено" << endl;
    cout << endl;
    cout << "ВЫПОЛНИЛА: Седельник Надежда" << endl;
    cout << "================================================" << endl;
    cout << endl;
}

void show_main_menu() {
    cout << "ГЛАВНОЕ МЕНЮ:" << endl;
    cout << "1.Вычислить сумму ряда" << endl;
    cout << "2.Показать информацию о задании" << endl;
    cout << "3.Выход" << endl;
    cout << "Выберите действие: ";
}

bool safe_multiply(long long a, long long b, long long &result) {
    result = a * b;
    
    if (a != 0 && result / a != b) {
        return false; 
    }
    return true; 
}

bool safe_add(long long a, long long b, long long &result) {
    result = a + b;
    
    if (a > 0 && b > 0 && result < 0) return false;
    if (a < 0 && b < 0 && result > 0) return false;
    
    return true; 
}

bool safe_subtract(long long a, long long b, long long &result) {
    result = a - b;
    
    if (a > 0 && b < 0 && result < 0) return false;
    if (a < 0 && b > 0 && result > 0) return false;
    
    return true; 
}

void calculate_series() {
    int n;
    
    cout << "Введите количество чисел (n): ";
    cin >> n;
    
    if (cin.fail() || n <= 0) {
        cout << "Ошибка! Введите натуральное число больше 0." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Нажмите Enter для продолжения...";
        cin.get();
        return;
    }
    
    long long sum = 0;
    long long power = 1;  
    int sign = 1;         
    
    for (int i = 0; i < n; i++) {
        long long a;
        cout << "a[" << i << "] = ";
        cin >> a;
        
        if (cin.fail()) {
            cout << "Ошибка ввода! Введите целое число." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Нажмите Enter для продолжения...";
            cin.get();
            return;
        }
        
        long long term;
        if (!safe_multiply(power, a, term)) {
            cout << "Ошибка: Переполнение при умножении!" << endl;
            cout << "Нажмите Enter для продолжения...";
            cin.ignore(1000, '\n');
            cin.get();
            return;
        }
        
        if (sign > 0) {
            if (!safe_add(sum, term, sum)) {
                cout << "Ошибка: Переполнение при сложении!" << endl;
                cout << "Нажмите Enter для продолжения...";
                cin.ignore(1000, '\n');
                cin.get();
                return;
            }
        } else {
            if (!safe_subtract(sum, term, sum)) {
                cout << "Ошибка: Переполнение при вычитании!" << endl;
                cout << "Нажмите Enter для продолжения...";
                cin.ignore(1000, '\n');
                cin.get();
                return;
            }
        }
        
        if (i < n - 1) {
            if (!safe_multiply(power, 2, power)) {
                cout << "Ошибка: Переполнение при вычислении степени 2!" << endl;
                cout << "Нажмите Enter для продолжения...";
                cin.ignore(1000, '\n');
                cin.get();
                return;
            }
            sign = -sign;
        }
    }
    
    cout << "Результат: " << sum << endl;
    cout << "Нажмите Enter для продолжения...";
    cin.ignore(1000, '\n');
    cin.get();
}

int main() {
    int choice;

    show_context_menu();

    do {
        show_main_menu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        } else {
            cin.ignore(1000, '\n');
        }

        switch (choice) {
            case 1:
                calculate_series();
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