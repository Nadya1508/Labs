
#include <iostream>
#include <limits>

using namespace std;

double calculate_a(int i) {
    if(i % 2 != 0) {
        return static_cast<double>(i);
    } else {
        return static_cast<double>(i) / 2;
    }
}

double calculate_b(int i) {
    if (i % 2 != 0) {
        return static_cast<double>(i * i);
    } else {
        return static_cast<double>(i * i * i);
    }
}

double calculate_sum(){
    double sum = 0.0;
    int i = 1;
    int n = 30;

    while(i <= n) {
        double a_i = calculate_a(i);
        double b_i = calculate_b(i);
        double term = (a_i - b_i) * (a_i - b_i);
        sum += term;
        i++;
    }
    return sum;
}

void show_context_menu() {
    cout << "==================================================\n";
    cout << "          Лабораторная работа №3\n";  
    cout << "          ВЫЧИСЛЕНИЕ СУММЫ РЯДА\n";
    cout << "==================================================\n";
    cout << "Суть задания: Вычислить сумму N = Σ(a_i - b_i)^2\n";
    cout << "          для i от 1 до 30,где:\n";
    cout << " a_i = i (если i нечётное), i/2 (если i чётное)\n";
    cout << " b_i = i^2 (если i нечётное), i^3 (если i чётное)\n";
    cout << "Выполнила: Седельник Надежда\n";
    cout << "===================================================\n\n";
}

void show_main_menu() {
    cout << "ГЛАВНОЕ МЕНЮ:\n";
    cout << "1. Вычислить сумму для i от 1 до 30\n";
    cout << "2. Показать контекстное меню\n";
    cout << "3. Выйти из программы\n";
    cout << " Выберите действие (1-3): ";
}

void clear_input_buffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;  
    bool running = true;
     
    show_context_menu();

    while (running) {
        show_main_menu();

        if(!(cin >> choice)) {
            cout << "Ошибка! Пожалуйста, введите число от 1 до 3.\n\n";
           cin.clear();
           cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
       cin.ignore(numeric_limits<streamsize>::max(),'\n');

        switch(choice) {
            case 1: {
                double result = calculate_sum();
                cout << "\nРЕЗУЛЬТАТЫ ВЫЧИСЛЕНИЙ:\n";
                cout << "Количество элементов: 30\n";
                cout << "Вычисленная сумма N = " << result << "\n\n";

                cout << "Нажмите Enter для возврата в меню ...";
                cin.get();
                break;
            }
            case 2: {
                show_context_menu();
                break;
            }
            case 3: {
                cout << "Выход из программы.\n";
                running = false;
                break;
            }
            default: {
                cout << "Ошибка! Пожалуйста, выберите действие от 1 до 3.\n\n";
                break;
            }
        }
    }
    
    return 0;  
}