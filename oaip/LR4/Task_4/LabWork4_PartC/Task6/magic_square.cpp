#include "magic_square.h"
#include <iostream>
#include <cmath>

using namespace std;

MagicSquare::MagicSquare(int n) : size(n) {
    square = new int*[size];
    for (int i = 0; i < size; i++) {
        square[i] = new int[size];
        for (int j = 0; j < size; j++) {
            square[i][j] = 0;
        }
    }
    
    if (n % 2 == 1) {
        createOddMagicSquare();
    } else if (n % 4 == 0) {
        createDoublyEvenMagicSquare();
    } else {
        createSinglyEvenMagicSquare();
    }
}

MagicSquare::~MagicSquare() {
    for (int i = 0; i < size; i++) {
        delete[] square[i];
    }
    delete[] square;
}

void MagicSquare::createOddMagicSquare() {
    int i = 0;
    int j = size / 2;
    int num = 1;
    
    while (num <= size * size) {
        square[i][j] = num++;
        
        int new_i = (i - 1 + size) % size;
        int new_j = (j + 1) % size;
        
        if (square[new_i][new_j] != 0) {
            i = (i + 1) % size;
        } else {
            i = new_i;
            j = new_j;
        }
    }
}

void MagicSquare::createDoublyEvenMagicSquare() {
    int num = 1;
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            square[i][j] = num++;
        }
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((i % 4 == j % 4) || ((i % 4) + (j % 4) == 3)) {
                square[i][j] = size * size + 1 - square[i][j];
            }
        }
    }
}

void MagicSquare::createSinglyEvenMagicSquare() {
    int k = size / 2;
    
    int** temp_square = new int*[size];
    for (int i = 0; i < size; i++) {
        temp_square[i] = new int[size];
        for (int j = 0; j < size; j++) {
            temp_square[i][j] = 0;
        }
    }
    
    int temp_i = 0;
    int temp_j = k / 2;
    int num = 1;
    
    while (num <= size * size) {
        temp_square[temp_i][temp_j] = num++;
        
        int new_i = (temp_i - 1 + size) % size;
        int new_j = (temp_j + 1) % size;
        
        if (temp_square[new_i][new_j] != 0) {
            temp_i = (temp_i + 1) % size;
        } else {
            temp_i = new_i;
            temp_j = new_j;
        }
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            square[i][j] = temp_square[i][j];
        }
    }
    
    for (int i = 0; i < size; i++) {
        delete[] temp_square[i];
    }
    delete[] temp_square;
}

bool MagicSquare::isMagicSquare() const {
    int magic_sum = size * (size * size + 1) / 2;
    
    for (int i = 0; i < size; i++) {
        int row_sum = 0;
        for (int j = 0; j < size; j++) {
            row_sum += square[i][j];
        }
        if (row_sum != magic_sum) return false;
    }
    
    for (int j = 0; j < size; j++) {
        int col_sum = 0;
        for (int i = 0; i < size; i++) {
            col_sum += square[i][j];
        }
        if (col_sum != magic_sum) return false;
    }
    
    
    int diag1_sum = 0;
    for (int i = 0; i < size; i++) {
        diag1_sum += square[i][i];
    }
    if (diag1_sum != magic_sum) return false;
    
    
    int diag2_sum = 0;
    for (int i = 0; i < size; i++) {
        diag2_sum += square[i][size - 1 - i];
    }
    if (diag2_sum != magic_sum) return false;
    
    return true;
}


void MagicSquare::printSquare() const {
    cout << "\n";
    cout << "========================================\n";
    cout << "        МАГИЧЕСКИЙ КВАДРАТ " << size << "x" << size << "\n";
    cout << "    Магическая сумма: " << getMagicSum() << "\n";
    cout << "========================================\n\n";
    
    
    int max_num = size * size;
    int width = 0;
    while (max_num > 0) {
        width++;
        max_num /= 10;
    }
    
    
    cout << "+";
    for (int j = 0; j < size; j++) {
        for (int w = 0; w < width + 2; w++) cout << "-";
        cout << "+";
    }
    cout << "\n";
    
    
    for (int i = 0; i < size; i++) {
        cout << "|";
        for (int j = 0; j < size; j++) {
            
            int num = square[i][j];
            int digits = 0;
            int temp = num;
            while (temp > 0) {
                digits++;
                temp /= 10;
            }
            if (num == 0) digits = 1;
            
            for (int s = 0; s < width - digits + 1; s++) {
                cout << " ";
            }
            cout << num << " |";
        }
        cout << "\n";
        
        if (i < size - 1) {
            cout << "+";
            for (int j = 0; j < size; j++) {
                for (int w = 0; w < width + 2; w++) cout << "-";
                cout << "+";
            }
            cout << "\n";
        }
    }
    
    cout << "+";
    for (int j = 0; j < size; j++) {
        for (int w = 0; w < width + 2; w++) cout << "-";
        cout << "+";
    }
    cout << "\n\n";
}

int MagicSquare::getMagicSum() const {
    return size * (size * size + 1) / 2;
}

void showContextMenu() {
    cout << "\n==========================================\n";
    cout << "           КОНТЕКСТНОЕ МЕНЮ             \n";
    cout << "==========================================\n";
    cout << " Задание: Построение магического        \n";
    cout << "           квадрата                     \n";
    cout << " Студент: Седельник Надежда            \n";
    cout << " Группа: 553503                        \n";
    cout << "==========================================\n\n";
}

void showInstructions() {
    cout << "\nИНСТРУКЦИЯ ПО ИСПОЛЬЗОВАНИЮ:\n";
    cout << "-----------------------------\n";
    cout << "- Введите порядок магического квадрата (n > 1)\n";
    cout << "- Программа создаст магический квадрат nxn\n";
    cout << "- Все числа от 1 до n^2 используются ровно один раз\n";
    cout << "- Суммы строк, столбцов и диагоналей равны\n";
    cout << "- Магическая сумма = n * (n^2 + 1) / 2\n";
    cout << "- Для выхода введите 0\n\n";
}

int getValidatedInput(const char* prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= minVal && value <= maxVal) {
                clearInputBuffer();
                return value;
            } else {
                cout << "Ошибка: число должно быть от " << minVal << " до " << maxVal << endl;
            }
        } else {
            cout << "Ошибка: введите целое число." << endl;
        }
        clearInputBuffer();
    }
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void printMainMenu() {
    cout << "ГЛАВНОЕ МЕНЮ:\n";
    cout << "1 - Создать магический квадрат\n";
    cout << "2 - Проверить магичность квадрата\n";
    cout << "3 - Показать квадрат\n";
    cout << "0 - Выход\n";
    cout << "Выберите действие: ";
}