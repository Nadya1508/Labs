#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

void show_context_menu() {
    cout << "==================================================\n";
    cout << "             Лабораторная работа №3\n";
    cout << "         ПРИБЛИЖЕННЫЙ ПОИСК КОРНЯ УРАВНЕНИЯ\n";
    cout << "==================================================\n";
    cout << "Суть задания: Найти корень уравнения f(x) = 0\n";
    cout << "Уравнение: sqrt(cos(x)) + ln(sin(x)) - 0.5 = 0\n";
    cout << "Интервал: x ∈ [0.5; 1.5]\n";
    cout << "Метод: перебор значений с поиском минимума |f(x)|\n";
    cout << "Выполнила: Седельник Надежда\n";
    cout << "Вариант: 8\n";
    cout << "==================================================\n";
}

void show_main_menu() {
    cout << "\nГЛАВНОЕ МЕНЮ:\n";
    cout << "1. Найти корень уравнения\n";
    cout << "2. Показать контекстное меню\n";
    cout << "3. Выйти из программы\n";
    cout << "Выберите действие (1-3): ";
}

double calculate_function(double x) {
    return sqrt(cos(x)) + log(sin(x)) - 0.5;
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

void find_root() {
    const double A = 0.5;
    const double B = 1.5;
    
    int n = safe_input_int("Введите количество частей для разбиения интервала: ");
    
    double step = (B - A) / n;
    double min_abs_value = 1000000.0; 
    double root = A;
    
    cout << "\nПоиск корня на интервале [" << A << "; " << B << "]" << endl;
    cout << "Количество частей: " << n << ", шаг: " << step << endl;
    cout << "==========================================" << endl;
    
    for (int i = 0; i <= n; i++) {
        double x = A + i * step;
        double fx = calculate_function(x);
        double abs_fx = fabs(fx);
        
        if (x >= 0.7 && x <= 0.9) {
            cout << "x = " << x << ", f(x) = " << fx << ", |f(x)| = " << abs_fx;
        }
        
        if (abs_fx < min_abs_value) {
            min_abs_value = abs_fx;
            root = x;
            if (x >= 0.7 && x <= 0.9) {
                cout << "  <-- МИНИМУМ";
            }
        }
        
        if (x >= 0.7 && x <= 0.9) {
            cout << endl;
        }
    }
    
    cout << "==========================================" << endl;
    cout << "НАЙДЕННЫЙ КОРЕНЬ:" << endl;
    cout << "x = " << root << endl;
    cout << "f(x) = " << calculate_function(root) << endl;
    cout << "|f(x)| = " << min_abs_value << endl;
    
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
                find_root();
                break;
            case 2:
                show_context_menu();
                break;
            case 3:
                cout << "Выход из программы." << endl;
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