#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

void show_context_menu(){
    cout << "==================================================\n";
    cout << "             Лабораторная работа №3\n";
    cout << "              ВЫЧИСЛЕНИЕ ЗНАЧЕНИЙ ФУНКЦИИ:\n";
    cout << "==================================================\n";
    cout << "Суть задания: Найти значения функции на отрезке [A,B]\n";
    cout << "Функция: y = sin(x) - cos(x)\n";
    cout << "M = 20 (количество точек)\n";
    cout << "Точки Xi = A + i * H, где H = (B - A) / M\n";
    cout << "По умолчанию: A = 0; B = π / 2\n";
    cout << "Используется цикл for\n";
    cout << "Выполнила: Седельник Надежда\n";
    cout << "==================================================\n";
}

void show_main_menu() {
    cout << "ГЛАВНОЕ МЕНЮ:\n";
    cout << "1. Вычислить значение функции y = sin(x) - cos(x)\n";
    cout << "2. Показать контекстное меню\n";
    cout << "3. Выйти из программы\n";
    cout << "Выберите действие (1-3): ";
}

void calculate_function(double A, double B, int M) {
    double H = (B - A) / M;
    
    cout.precision(6);
    cout << fixed;
    cout << "Результаты вычислений: " << endl;
    cout << "A = " << A << ", B = " << B << ", M = " << M << ", H = " << H << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "i\tX_i\t\tY(X_i)" << endl;
    cout << "---------------------------------------------------" << endl;

    for(int i = 0; i <= M; i++) {
         double X_i = A + i * H;
         double Y_i = sin(X_i) - cos(X_i);
         cout << i << "\t" << X_i << "\t" << Y_i << endl;
    }
    cout << "---------------------------------------------------" << endl;
}

double safe_input_double(const string & prompt) {
    double value;
    for(;;) {  
        cout << prompt;
        cin >> value; 

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Пожалуйста, введите число." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int safe_input_int(const string & prompt) {
    int value;
    for(;;) {  
        cout << prompt;
        cin >> value;

        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Пожалуйста, введите положительное целое число." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

void run_calculation() {
    double A, B;
    int M;

    cout << "Введите параметры для вычисления функции:" << endl;
    A = safe_input_double("Введите значение A (начало отрезка): ");
    B = safe_input_double("Введите значение B (конец отрезка): ");
     
    for (; B <= A;) {
        cout << "Ошибка: B должно быть больше A!" << endl;
        A = safe_input_double("Введите значение A (начало отрезка): ");
        B = safe_input_double("Введите значение B (конец отрезка): ");
    }
    
    M = safe_input_int("Введите значение M (количество интервалов): ");

    calculate_function(A, B, M);

    cout << "Нажмите Enter для продолжения...";
    cin.get();
}

int main() {
    int choice;
    
    for (;;) { 
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
                run_calculation();
                break;
            case 2:
                show_context_menu();
                cout << "Нажмите Enter для продолжения...";
                cin.get();
                break;
            case 3:
                cout << "Выход из программы" << endl;
                return 0;  
            default: 
                cout << "Ошибка! Пожалуйста, выберите действие от 1 до 3" << endl;
                cout << "Нажмите Enter для продолжения...";
                cin.get();
                break;
        }
        cout << endl;
    }

    return 0;
}