#include <iostream>
#include "matrix_utils.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    
    showContextMenu();
    
    cout << "Начало работы с программой обработки матриц." << endl;
    cout << "Программа найдет минимальный элемент СРЕДИ элементов, расположенных ВЫШЕ главной диагонали." << endl;
    
    bool continueProgram = true;
    while (continueProgram) {
        processTask();
        continueProgram = showMainMenu();
    }
    
    cout << "\n Завершение работы программы." << endl;
    return 0;
}