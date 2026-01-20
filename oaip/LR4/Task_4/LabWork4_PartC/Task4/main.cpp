#include <iostream>
#include "array_utils.h"

int main() {
    Array3D* array3D = nullptr;
    int choice;
    
    std::cout << "ПРОГРАММА ДЛЯ РАБОТЫ  3D МАССИВАМИ" << std::endl;
    std::cout << "========================================" << std::endl;
    
    do {
        printMenu();
        
        if (!(std::cin >> choice)) {
            std::cout << "Ошибка: введите число от 0 до 4." << std::endl;
            clearInputBuffer();
            continue;
        }
        
        switch (choice) {
            case 1: {
                int size = getValidatedInput("Введите размер массива (n): ", 1, 10);
                if (array3D) delete array3D;
                array3D = new Array3D(size);
                array3D->fillRandom();
                std::cout << "Массив " << size << "x" << size << "x" << size << " создан и заполнен случайными числами." << std::endl;
                break;
            }
            
            case 2: {
                int size = getValidatedInput("Введите размер массива (n): ", 1, 10);
                if (array3D) delete array3D;
                array3D = new Array3D(size);
                array3D->fillFromInput();
                std::cout << "Массив " << size << "x" << size << "x" << size << " создан и заполнен вручную." << std::endl;
                break;
            }
            
            case 3: {
                if (array3D) {
                    int maxSum = array3D->findMaxDiagonalSum();
                    std::cout << "Максимальная сумма на диагонали: " << maxSum << std::endl;
                } else {
                    std::cout << "Ошибка: массив не создан. Сначала создайте массив." << std::endl;
                }
                break;
            }
            
            case 4: {
                if (array3D) {
                    delete array3D;
                    array3D = nullptr;
                    std::cout << "Массив удален." << std::endl;
                } else {
                    std::cout << "Массив уже удален." << std::endl;
                }
                break;
            }
            
            case 0: {
                std::cout << "Завершение работы программы." << std::endl;
                break;
            }
            
            default: {
                std::cout << "Ошибка: неверный выбор. Введите число от 0 до 4." << std::endl;
                break;
            }
        }
        
    } while (choice != 0);
    
    if (array3D) delete array3D;
    return 0;
}