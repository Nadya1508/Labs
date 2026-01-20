#include <iostream>
#include <stdexcept>
#include "matrix_utils.h"

using namespace std;

void showContextMenu() {
    cout << "================================================" << endl;
    cout << "      ПОИСК МИНИМАЛЬНОГО ЭЛЕМЕНТА В МАТРИЦЕ" << endl;
    cout << "================================================" << endl;
    cout << "СУТЬ ЗАДАНИЯ: Найти минимальный среди элементов," << endl;
    cout << "лежащих ВЫШЕ главной диагонали матрицы" << endl;
    cout << "ВЫПОЛНИЛА: Седельник Надежда" << endl;
    cout << "ВАРИАНТ: 8" << endl;
    cout << "================================================" << endl;
    cout << endl;
}

int safeInputInt(const char* prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Пожалуйста, введите целое число." << endl;
        } else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

void initializeArray(int arr[M][N]) {
    cout << "Инициализация массива " << M << "x" << N << ":" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << "Элемент [" << i << "][" << j << "]: ";
            arr[i][j] = safeInputInt("");
        }
    }
}

void printArray(const char* title, int arr[M][N]) {
    cout << title << ":" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i][j] < 10 && arr[i][j] >= 0) {
                cout << "  " << arr[i][j] << " ";
            } else if (arr[i][j] < 100 && arr[i][j] > -10) {
                cout << " " << arr[i][j] << " ";
            } else {
                cout << arr[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int findMinAboveDiagonal(int arr[M][N]) {
    bool found = false;
    int min_val = 0;
    
    
    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < N; j++) {  
            if (!found) {
               
                min_val = arr[i][j];
                found = true;
            } else if (arr[i][j] < min_val) {
                min_val = arr[i][j];
            }
        }
    }
    
    if (!found) {
        throw runtime_error("Нет элементов выше главной диагонали");
    }
    
    return min_val;
}

void printAboveDiagonal(int arr[M][N]) {
    cout << "Элементы ВЫШЕ главной диагонали: ";
    bool first = true;
    for (int i = 0; i < M; i++) {
        for (int j = i + 1; j < N; j++) {
            if (!first) cout << ", ";
            cout << arr[i][j] << "([" << i << "][" << j << "])";
            first = false;
        }
    }
    cout << endl;
}

void printDiagonalInfo(int arr[M][N]) {
    cout << "Главная диагональ: ";
    for (int i = 0; i < M && i < N; i++) {
        if (i > 0) cout << ", ";
        cout << arr[i][i] << "([" << i << "][" << i << "])";
    }
    cout << endl;
    
    cout << "Элементы НИЖЕ главной диагонали: ";
    bool first_below = true;
    for (int i = 1; i < M; i++) {
        for (int j = 0; j < i && j < N; j++) {
            if (!first_below) cout << ", ";
            cout << arr[i][j] << "([" << i << "][" << j << "])";
            first_below = false;
        }
    }
    cout << endl;
}

void processTask() {
    int array[M][N];
    
    cout << "\n--- ВВОД ДАННЫХ ---" << endl;
    initializeArray(array);
    
    cout << "\n--- РЕЗУЛЬТАТЫ ОБРАБОТКИ ---" << endl;
    printArray("Исходный массив", array);
    
    printDiagonalInfo(array);
    printAboveDiagonal(array);
    
    try {
        int min_above_diagonal = findMinAboveDiagonal(array);
        cout << "\nМИНИМАЛЬНЫЙ ЭЛЕМЕНТ СРЕДИ ЭЛЕМЕНТОВ ВЫШЕ ГЛАВНОЙ ДИАГОНАЛИ: " 
             << min_above_diagonal << endl;
    } catch (const exception& e) {
        cout << "\nОШИБКА: " << e.what() << endl;
    }
    
    cout << "\n--- ДОПОЛНИТЕЛЬНАЯ ИНФОРМАЦИЯ ---" << endl;
    cout << "Размер матрицы: " << M << "x" << N << endl;
    cout << "Область поиска: элементы, у которых номер столбца > номера строки" << endl;
}

bool showMainMenu() {
    cout << "\n================================================" << endl;
    cout << "                 ГЛАВНОЕ МЕНУ" << endl;
    cout << "================================================" << endl;
    cout << "1 - Выполнить задание с новыми данными" << endl;
    cout << "2 - Выйти из программы" << endl;
    cout << "================================================" << endl;
    
    int choice;
    do {
        cout << "Выберите действие (1-2): ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }
        if (choice != 1 && choice != 2) {
            cout << "Пожалуйста, введите 1 или 2!" << endl;
        }
    } while (choice != 1 && choice != 2);
    
    return choice == 1;
}