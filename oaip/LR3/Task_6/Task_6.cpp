#include <iostream>
#include <limits>

using namespace std;

void show_context_menu() {
    cout << "==================================================\n";
    cout << "             Лабораторная работа №6\n";
    cout << "          ОПРЕДЕЛЕНИЕ МИНИМАЛЬНОГО ЗНАЧЕНИЯ\n";
    cout << "==================================================\n";
    cout << "Суть задания: Из величин a = sin(x), b = cos(x), c = ln|x|\n";
    cout << "определить и вывести минимальное значение\n";
    cout << "Использование стандартных математических методов запрещено\n";
    cout << "Выполнила: Седельник Надежда\n";
    cout << "Вариант: 8\n";
    cout << "==================================================\n";
}

void show_main_menu() {
    cout << "\nГЛАВНОЕ МЕНЮ:\n";
    cout << "1. Вычислить минимальное значение\n";
    cout << "2. Показать контекстное меню\n";
    cout << "3. Выйти из программы\n";
    cout << "Выберите действие (1-3): ";
}

double custom_abs(double x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

double custom_sin(double x) {
    double term = x;
    double sum = term;
    double x_squared = x * x;
    
    for (int i = 3; i <= 15; i += 2) {
        term = term * (-x_squared) / ((i-1) * i);
        sum += term;
    }
    return sum;
}

double custom_cos(double x) {
    double term = 1.0;
    double sum = term;
    double x_squared = x * x;
    
    for (int i = 2; i <= 14; i += 2) {
        term = term * (-x_squared) / ((i-1) * i);
        sum += term;
    }
    return sum;
}

double custom_ln(double x) {
    double abs_x = custom_abs(x);
    
    if (abs_x <= 0) {
        return -1e10; 
    }
    
    double z = (abs_x - 1) / (abs_x + 1);
    double z_squared = z * z;
    double term = 2 * z;
    double sum = term;
    
    for (int i = 3; i <= 21; i += 2) {
        term = term * z_squared * (i-2) / i;
        sum += term;
    }
    return sum;
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

void find_minimum() {
    double x = safe_input_double("Введите значение x: ");
    
    double a = custom_sin(x);
    double b = custom_cos(x);
    double c = custom_ln(x);
    
    double min_value = a;

    if (b < min_value) {
        min_value = b;
    }
    if (c < min_value) {
        min_value = c;
    }
    cout << "\n==================================================" << endl;
    cout << "РЕЗУЛЬТАТЫ ВЫЧИСЛЕНИЙ:" << endl;
    cout << "x = " << x << endl;
    cout << "a = sin(x) = " << a << endl;
    cout << "b = cos(x) = " << b << endl;
    cout << "c = ln|x| = " << c << endl;
    cout << "==================================================" << endl;
    cout << "МИНИМАЛЬНОЕ ЗНАЧЕНИЕ: " << min_value << endl;
    cout << "==================================================" << endl;

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
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            choice = 0;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }

        switch (choice) {
            case 1:
            find_minimum();
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