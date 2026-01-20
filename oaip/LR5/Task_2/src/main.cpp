#include <iostream>
#include <cmath>
#include <dlfcn.h>

using namespace std;

typedef bool (*check_all_cos_positive_func)(double*, int);

void clear_input_buffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

int input_integer(const char* prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cout << "Ошибка! Введите целое число.\n";
            clear_input_buffer();
        } else {
            char next_char = cin.peek();
            if (next_char != '\n' && next_char != ' ') {
                cout << "Ошибка! Введите только целое число без дополнительных символов.\n";
                clear_input_buffer();
            } else {
                clear_input_buffer();
                break;
            }
        }
    }
    return value;
}

double input_double(const char* prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cout << "Ошибка! Введите числовое значение.\n";
            clear_input_buffer();
        } else {
            char next_char = cin.peek();
            if (next_char != '\n' && next_char != ' ') {
                cout << "Ошибка! Введите только число без дополнительных символов.\n";
                clear_input_buffer();
            } else {
                clear_input_buffer();
                break;
            }
        }
    }
    return value;
}

char input_char(const char* prompt) {
    char choice;
    while (true) {
        cout << prompt;
        cin >> choice;
        
        if (cin.fail()) {
            cout << "Ошибка ввода! Попробуйте снова.\n";
            clear_input_buffer();
        } else {
            clear_input_buffer();
            break;
        }
    }
    return choice;
}

void show_context_menu() {
    cout << "===============================================\n";
    cout << "           ПРОВЕРКА УСЛОВИЯ cos(Xi) > 0\n";
    cout << "===============================================\n";
    cout << "Задание: Проверить, что для всех элементов массива\n";
    cout << "         выполняется условие cos(Xi) > 0\n";
    cout << "Выполнила: Седельник Надежда\n";
    cout << "Вариант: 8\n";
    cout << "===============================================\n";
    cout << "Рекурсивный алгоритм делит массив на первую треть\n";
    cout << "и остальные 2/3, проверяя каждую часть отдельно\n";
    cout << "===============================================\n\n";
}

int input_array_size() {
    int n;
    while (true) {
        n = input_integer("Введите размер массива (N > 0): ");
        
        if (n <= 0) {
            cout << "Ошибка! Размер массива должен быть положительным числом.\n";
        } else if (n > 10000) {
            cout << "Ошибка! Слишком большой размер массива (" << n << "). Максимум 10000.\n";
        } else {
            break;
        }
    }
    return n;
}

double* create_dynamic_array(int n) {
    double* array = new (nothrow) double[n];
    if (array == nullptr) {
        cout << "Не удалось выделить память для массива размером " << n << "!\n";
        return nullptr;
    }
    return array;
}

void safe_delete_array(double*& array) {
    if (array != nullptr) {
        delete[] array;
        array = nullptr;
    }
}

double* input_array_elements(int n) {
    double* array = create_dynamic_array(n);
    if (array == nullptr) {
        return nullptr;
    }
    
    cout << "Введите " << n << " элементов массива:\n";
    
    for (int i = 0; i < n; i++) {
        cout << "X[" << i << "] = ";
        array[i] = input_double("");
    }
    return array;
}

void print_array(double* array, int n) {
    if (array == nullptr) {
        cout << "Массив: [НЕИНИЦИАЛИЗИРОВАН]\n";
        return;
    }
    
    cout << "Массив: [";
    for (int i = 0; i < n; i++) {
        cout << array[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n";
}

void print_check_results(double* array, int n, bool result) {
    cout << "\n=== РЕЗУЛЬТАТЫ ПРОВЕРКИ ===\n";
    print_array(array, n);
    
    cout << "Значения cos(Xi): [";
    for (int i = 0; i < n; i++) {
        cout << cos(array[i]);
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n";
    
    if (result) {
        cout << " Все элементы удовлетворяют условию cos(Xi) > 0\n";
    } else {
        cout << " Не все элементы удовлетворяют условию cos(Xi) > 0\n";
    }
    cout << "============================\n\n";
}

int main() {
    char choice;
    
    cout << "Загрузка библиотеки libarraycheck.dylib..." << endl;
    void* load = dlopen("./libarraycheck.dylib", RTLD_LAZY);
    
    if (!load) {
        cerr << "Ошибка загрузки библиотеки: " << dlerror() << endl;
        return 1;
    }
    cout << " Библиотека успешно загружена!" << endl;

    cout << "Поиск функции check_all_cos_positive..." << endl;
    check_all_cos_positive_func check_all_cos_positive = 
        (check_all_cos_positive_func)dlsym(load, "check_all_cos_positive");
    
    if (!check_all_cos_positive) {
        cerr << "Ошибка получения функции: " << dlerror() << endl;
        dlclose(load);
        return 1;
    }
    cout << "Функция найдена в библиотеке!" << endl << endl;
    
    do {
        show_context_menu();
        
        int n = input_array_size();
        double* array = input_array_elements(n);
        
        if (array == nullptr) {
            cout << "Не удалось создать массив. Попробуйте снова с меньшим размером.\n\n";
            continue;
        }
        
        bool result = check_all_cos_positive(array, n);
        print_check_results(array, n, result);
        safe_delete_array(array);
        
        choice = input_char("Хотите выполнить проверку снова? (y/n): ");
        cout << "\n";
        
    } while (choice == 'y' || choice == 'Y');

    dlclose(load);
    cout << "Библиотека выгружена. Программа завершена.\n";
    return 0;
}