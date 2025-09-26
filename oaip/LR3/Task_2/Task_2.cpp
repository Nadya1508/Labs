#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

void show_context_menu() {
    cout << "======================================================\n";
    cout << "           Лабораторная работа №3\n";
    cout << "            ВЫЧИСЛЕНИЕ СУММЫ РЯДА С ТОЧНОСТЬЮ\n";
    cout << "=======================================================\n";
    cout << "Суть задания: Найти сумму ряда с точностью ε = 10⁻³\n";
    cout << "Общий член ряда: dₙ = 1/2ⁿ + 1/3ⁿ\n";
    cout << "Точность достигнута, когда dₙ < ε\n";
    cout << "Используется цикл do-while\n";
    cout << "Выполнила: Седельник Надежда\n";
    cout << "=======================================================\n";
}

void show_main_menu() {
    cout << "ГЛАВНОЕ МЕНЮ:\n";
    cout << "1.Вычислить сумму ряда\n";
    cout << "2.Показать контекстное меню\n";
    cout << "3.Выйти из программы\n";
    cout << " Выберите действие(1-3): ";
}

void clear_input_buffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
int main() {
    setlocale(LC_ALL,"Russian");

    int choise;
    bool running = true;

    show_context_menu();

    while(running) {
        show_main_menu();
        if(!(cin >> choise)) {
            cout << "Ошибка! Пожалуйста, введи числа от 1 до 3.\n\n";
            cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        switch(choise) {
            case 1: {
                const double epsilon = 0.001;
                double sum = 0.0;
                double term;
                int n = 1;

                do {
                    term = (1.0 / pow(2.0,n)) + (1.0 / pow(3.0,n));
                    sum +=term;
                    n++;
                } while (term >= epsilon);

                cout << "\nРЕЗУЛЬТАТЫ ВЫЧИСЛЕНИЙ:\n";
                cout << "Точность: ε = " << epsilon << endl;
                cout << "Количество просуммарных членов: " << n-1 <<endl;
                cout << "Вычисленная сумма ряда: " << sum << endl;

                cout << "Нажмите Enter для возврата в меню ...";
                cin.get();
                break;
            }
            case 2:{
                show_context_menu();
                break;
            }
            case 3 : {
                cout << "Выход из программы.\n";
                running = false;
                break;
            }
            default: {
                cout << "Ощибка! Пожалуйста, выберите действие от 1 до 3.\n\n";
                break;
            }
        }
    }
    return 0;
}