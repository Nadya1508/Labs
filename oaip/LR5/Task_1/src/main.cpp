#include <iostream>
#include "matrix_ops.h"

int main() {
    bool continueProgram = true;
    
    while (continueProgram) {
        printMainMenu();
        
        try {
            int k = getValidatedInput();
            MatrixOperations ops(k);
            ops.printResults();
            
        } catch (const char* error_msg) {
            std::cout << "Ошибка: " << error_msg << std::endl;
        }
        
        continueProgram = askToContinue();
    }
    
    std::cout << "\nПрограмма завершена.\n";
    return 0;
}