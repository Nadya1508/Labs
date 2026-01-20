#include <iostream>

using namespace std;

void clearInputBuffer() {
    while (cin.get() != '\n') { // O(k) - зависит от размера буфера
        continue;
    }
}

 //Сложность: O(1)
void printMenu() {
    cout << "\n=== Конвертер обратного кода в естественную форму ===\n";
    cout << "Выполнила: Седельник Надежда\n";
    cout << "Вариант: 8\n";
    cout << "1. Конвертировать число\n";
    cout << "2. Выход\n";
    cout << "Выберите опцию: ";
}

//Сложность: O(n)
bool isValidReverseCode(const char* reverseCodeArray) { // O(1) - динамический массив
    if (reverseCodeArray == nullptr) { // O(1)
        return false;
    }
    
    if (reverseCodeArray[0] != '0' && reverseCodeArray[0] != '1') { // O(1)
        return false;
    }
    
    for (int i = 0; reverseCodeArray[i] != '\0'; ++i) { // O(n) - цикл по всем элементам
        if (reverseCodeArray[i] != '0' && reverseCodeArray[i] != '1') { // O(1)
            return false;
        }
    }
    
    return true;
}

 //Сложность: O(n)
int stringLength(const char* strArray) { // O(1) - динамический массив
    if (strArray == nullptr) { // O(1)
        return 0;
    }
    
    int length = 0; // O(1)
    while (strArray[length] != '\0') { // O(n) 
        ++length; // O(1)
    }
    return length;
}

//Сложность: O(n)
int reverseCodeToDecimal(const char* reverseCodeArray) { // O(1) - динамический массив
    if (reverseCodeArray == nullptr) { // O(1)
        return 0;
    }

    int length = stringLength(reverseCodeArray); // O(n)
    
    if (reverseCodeArray[0] == '0') { // O(1) - положительное число
        int decimal = 0; // O(1)
        int power = 1; // O(1)
        
        for (int i = length - 1; i >= 1; --i) { // O(n) - обработка каждого бита
            if (reverseCodeArray[i] == '1') { // O(1)
                decimal += power; // O(1)
            }
            power *= 2; // O(1)
        }
        return decimal; // O(1)
    }
    else { // O(1) - отрицательное число
        int decimal = 0; // O(1)
        int power = 1; // O(1)

        for (int i = length - 1; i >= 1; --i) { // O(n) - обработка каждого бита
            if (reverseCodeArray[i] == '0') { // O(1) - ИНВЕРСИЯ: 0 становится 1
                decimal += power; // O(1)
            }
            power *= 2; // O(1)
        }
        
        return -decimal; // O(1) - для обратного кода
    }
}

 //Сложность: O(n)
char* inputReverseCodeNumber() { // O(1)
    const int BUFFER_SIZE = 1000; // O(1)
    char* buffer = new char[BUFFER_SIZE]; // O(1) 
    
    cout << "Введите число в обратном коде (только 0 и 1): "; // O(1)
    cin.getline(buffer, BUFFER_SIZE); // O(n) 
    
    int length = stringLength(buffer); // O(n)
    char* number = new char[length + 1]; // O(1) 
    for (int i = 0; i <= length; i++) { // O(n) 
        number[i] = buffer[i]; // O(1)
    }
    
    delete[] buffer; // O(1)
    return number; // O(1)
}

void printConversionResult(const char* reverseCodeArray, int decimal) { // O(1) - динамический массив
    cout << "Обратный код: " << reverseCodeArray << " -> Десятичное: " << decimal << endl; // O(n)
}


void convertNumber() { // O(1)
    char* inputArray = inputReverseCodeNumber(); // O(n) 

    if (!isValidReverseCode(inputArray)) { // O(n)
        cout << "Ошибка: Неверный формат обратного кода!\n"; // O(1)
        delete[] inputArray; // O(1)
        clearInputBuffer(); // O(k)
        return;
    }
    
    int decimal = reverseCodeToDecimal(inputArray); // O(n)
    
    printConversionResult(inputArray, decimal); // O(n)
    
    delete[] inputArray; // O(1)
}

int main() {
    int choice = 0;
    
    do {
        printMenu(); // O(1)
        cin >> choice; // O(1)
        clearInputBuffer(); // O(k) - очистка буфера
        
        switch (choice) { // O(1)
            case 1:
                convertNumber(); // O(n)
                break;
            case 2:
                cout << "Выход из программы.\n"; // O(1)
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n"; // O(1)
                break;
        }
    } while (choice != 2); // O(m) - цикл выполняется m раз
    
    return 0;
}
