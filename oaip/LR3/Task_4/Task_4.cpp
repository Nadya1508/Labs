#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

void show_context_menu() {
    cout << "==================================================\n";
    cout << "             Лабораторная работа №4\n";
    cout << "         РАЗЛОЖЕНИЕ ФУНКЦИИ В РЯД ТЕЙЛОРА\n";
    cout << "==================================================\n";
    cout << "Суть задания: Разложить функцию Y(x) = e^(2x) в ряд S(x)\n";
    cout << "Ряд: S(x) = 1 + 2x/1! + (2x)^2/2! + ... + (2x)^n/n!\n";
    cout << "Затем сравнить значение через ряд со значением через\n";
    cout << "стандартную математическую функцию exp(2x)\n";
    cout << "Диапазон x: от 0.1 до 1\n";
    cout << "Выполнила: [Ваше имя]\n";
    cout << "Вариант: 8\n";
    cout << "==================================================\n";
}

void show_main_menu() {
    cout << "\nГЛАВНОЕ МЕНЮ:\n";
    cout << "1. Вычислить значения функции\n";
    cout << "2. Показать контекстное меню\n";
    cout << "3. Выйти из программы\n";
    cout << "Выберите действие (1-3): ";
}

double calculate_series(double x, int n) {
    double sum = 1.0; 
    double term = 1.0;
    
    for (int i = 1; i <= n; i++) {
        term *= (2 * x) / i; 
        sum += term;
    }
    
    return sum;
}

double calculate_standard(double x) {
    return exp(2 * x);
}

int safe_input_int(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите положительное целое число: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

double safe_input_double(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите число: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

void run_calculations() {
    int n = safe_input_int("Введите количество членов ряда (n): ");
    int count = safe_input_int("Введите количество чисел для расчета: ");
    
    cout << "\n";
    for (int i = 0; i < 60; i++) cout << "=";
    cout << endl;
    
    cout << "n = " << n << ", количество точек: " << count << endl;
    
    for (int i = 0; i < 60; i++) cout << "=";
    cout << endl;
    
    cout.setf(ios::fixed);
    cout.precision(6);
    
    cout << "    x        S(x) (ряд)       Y(x) (стандарт)     Разность\n";
    for (int i = 0; i < 60; i++) cout << "-";
    cout << endl;
    
    for (int i = 0; i < count; i++) {
        double x;
        while (true) {
            cout << "Введите x " << (i + 1) << " (от 0.1 до 1): ";
            cin >> x;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка ввода! ";
            } else if (x < 0.1 || x > 1) {
                cout << "x должен быть в диапазоне [0.1, 1]! ";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }
        
        double series_value = calculate_series(x,n);
        double standard_value = calculate_standard(x);
        double difference = fabs(series_value - standard_value);
        
        cout << "  " << x << "    " << series_value << "    " 
             << standard_value << "    " << difference << endl;
    }
    
    for (int i = 0; i < 60; i++) cout << "=";
    cout << endl;
    cout << "Нажмите Enter для продолжения...";
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        switch (choice) {
            case 1:
                run_calculations();
                break;
            case 2:
                show_context_menu();
                break;
            case 3:
                cout << "Выход из программы. До свидания!" << endl;
                break;
            default:
                cout << "Ошибка! Выберите действие от 1 до 3." << endl;
                cout << "Нажмите Enter для продолжения...";
                cin.get();
                break;
        }
    } while (choice != 3);
    
    return 0;
}