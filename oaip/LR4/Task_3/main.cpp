#include <iostream>
#include "matrix_utils.h"

using namespace std;

void showMenu() {
    cout << "\n================================================" << endl;
    cout << "               ГЛАВНОЕ МЕНЮ" << endl;
    cout << "================================================" << endl;
    cout << "1 - Проверить новую матрицу" << endl;
    cout << "2 - Показать информацию о задании" << endl;
    cout << "3 - Выйти из программы" << endl;
    cout << "================================================" << endl;
    cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    showTaskInfo();
    
    int choice;
    do {
        showMenu();
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }
        
        switch (choice) {
            case 1: {
                int n;
                cout << "Введите размер матрицы N: ";
                while (!(cin >> n) || n <= 0) {
                    cout << "Ошибка! Введите положительное целое число: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                
                double** matrix = createMatrix(n);
                inputMatrix(matrix, n);
                
                cout << "\n--- РЕЗУЛЬТАТЫ ---" << endl;
                printMatrix(matrix, n);
                
                bool isOrthonormalResult = isOrthonormal(matrix, n);
                cout << "\nМатрица " << (isOrthonormalResult ? "ЯВЛЯЕТСЯ" : "НЕ ЯВЛЯЕТСЯ") 
                     << " ортонормированной" << endl;
                
                clearMatrix(matrix, n);
                break;
            }
                
            case 2:
                showTaskInfo();
                break;
                
            case 3:
                cout << "Выход из программы..." << endl;
                break;
                
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
        }
        
    } while (choice != 3);
    
    return 0;
}