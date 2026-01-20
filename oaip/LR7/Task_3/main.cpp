#include <iostream>

using namespace std;

// Функция для создания динамического массива - O(1)
char* createDynamicArray(const int* size) {
    return new char[*size];  // O(1)
}

// Функция для удаления динамического массива - O(1)
void deleteDynamicArray(char* arr) {
    if (arr != nullptr) {  // O(1)
        delete[] arr;  // O(1)
    }
}

// Функция проверки символа - O(1)
bool isValidDigit(const char* digit, const int* base) {
    if (*digit >= '0' && *digit <= '9') {  // O(1)
        return (*digit - '0') < *base;  // O(1)
    }
    if (*digit >= 'A' && *digit <= 'Z') {  // O(1)
        return (*digit - 'A' + 10) < *base;  // O(1)
    }
    if (*digit >= 'a' && *digit <= 'z') {  // O(1)
        return (*digit - 'a' + 10) < *base;  // O(1)
    }
    return false;  // O(1)
}

// Функция преобразования символа в число - O(1)
int digitToValue(const char* digit) {
    if (*digit >= '0' && *digit <= '9') return *digit - '0';  // O(1)
    if (*digit >= 'A' && *digit <= 'Z') return *digit - 'A' + 10;  // O(1)
    if (*digit >= 'a' && *digit <= 'z') return *digit - 'a' + 10;  // O(1)
    return -1;  // O(1)
}

// Функция преобразования числа в символ - O(1)
char valueToDigit(const int* value) {
    if (*value >= 0 && *value <= 9) return '0' + *value;  // O(1)
    return 'A' + (*value - 10);  // O(1)
}

// Функция проверки числа - O(n)
bool isValidNumber(char* number, const int* base) {
    if (number[0] == '\0') return false;  // O(1)

    int start = (number[0] == '-') ? 1 : 0;  // O(1)
    if (number[start] == '\0') return false;  // O(1)

    for (int i = start; number[i] != '\0'; i++) { // O(n) 
        if (!isValidDigit(&number[i], base)) return false;  // O(1)
    }
    return true;  // O(1)
}

// Функция определения длины строки - O(n)
int* stringLength(const char* str) {
    int* len = new int(0);  // O(1)
    while (str[*len] != '\0') { // O(n) 
        (*len)++;  // O(1)
    }
    return len;  // O(1)
}

// Функция сравнения двух чисел без знака - O(n)
int compareUnsigned(const char* a, const char* b) {
    int* lenAPtr = stringLength(a);  // O(n)
    int* lenBPtr = stringLength(b);  // O(n)
    int lenA = *lenAPtr;  // O(1)
    int lenB = *lenBPtr;  // O(1)
    delete lenAPtr;  // O(1)
    delete lenBPtr;  // O(1)

    if (lenA > lenB) return 1;  // O(1)
    if (lenA < lenB) return -1;  // O(1)
    
    for (int i = 0; i < lenA; i++) { // O(n)
        int valA = digitToValue(&a[i]);  // O(1)
        int valB = digitToValue(&b[i]);  // O(1)
        if (valA > valB) return 1;  // O(1)
        if (valA < valB) return -1;  // O(1)
    }
    return 0;  // O(1)
}

// Функция сложения двух неотрицательных чисел - O(n)
char* addUnsigned(const char* a, const char* b, const int* base) {
    int* lenAPtr = stringLength(a);  // O(n)
    int* lenBPtr = stringLength(b);  // O(n)
    int lenA = *lenAPtr;  // O(1)
    int lenB = *lenBPtr;  // O(1)
    delete lenAPtr;  // O(1)
    delete lenBPtr;  // O(1)

    int maxLen = (lenA > lenB) ? lenA : lenB;  // O(1)
    int* sizePtr = new int(maxLen + 3);  // O(1)
    char* result = createDynamicArray(sizePtr);  // O(1)
    delete sizePtr;  // O(1)

    int carry = 0;  // O(1)
    int index = 0;  // O(1)
    int i = lenA - 1, j = lenB - 1;  // O(1)

    while (i >= 0 || j >= 0 || carry > 0) { // O(n) - цикл по max(lenA, lenB)
        int digit1 = (i >= 0) ? digitToValue(&a[i]) : 0;  // O(1)
        int digit2 = (j >= 0) ? digitToValue(&b[j]) : 0;  // O(1)
        
        int sum = digit1 + digit2 + carry;  // O(1)
        carry = sum / *base;  // O(1)
        int digit = sum % *base;  // O(1)
        
        result[index++] = valueToDigit(&digit);  // O(1)
        i--;  // O(1)
        j--;  // O(1)
    }

    result[index] = '\0';  // O(1)

    // Переворачиваем результат - O(n)
    for (int k = 0, m = index - 1; k < m; k++, m--) { // O(n) - цикл по половине длины
        char temp = result[k];  // O(1)
        result[k] = result[m];  // O(1)
        result[m] = temp;  // O(1)
    }

    return result;  // O(1)
}

// Функция вычитания (a >= b, оба неотрицательные) - O(n)
char* subtractUnsigned(const char* a, const char* b, const int* base) {
    int* lenAPtr = stringLength(a);  // O(n)
    int* lenBPtr = stringLength(b);  // O(n)
    int lenA = *lenAPtr;  // O(1)
    int lenB = *lenBPtr;  // O(1)
    delete lenAPtr;  // O(1)
    delete lenBPtr;  // O(1)

    int* sizePtr = new int(lenA + 2);  // O(1)
    char* result = createDynamicArray(sizePtr);  // O(1)
    delete sizePtr;  // O(1)

    int borrow = 0;  // O(1)
    int index = 0;  // O(1)
    int i = lenA - 1, j = lenB - 1;  // O(1)

    while (i >= 0 || j >= 0) { // O(n) 
        int digit1 = (i >= 0) ? digitToValue(&a[i]) : 0;  // O(1)
        int digit2 = (j >= 0) ? digitToValue(&b[j]) : 0;  // O(1)
        
        int diff = digit1 - digit2 - borrow;  // O(1)
        if (diff < 0) {  // O(1)
            diff += *base;  // O(1)
            borrow = 1;  // O(1)
        } else {  // O(1)
            borrow = 0;  // O(1)
        }
        
        result[index++] = valueToDigit(&diff);  // O(1)
        i--;  // O(1)
        j--;  // O(1)
    }

    // Убираем ведущие нули - O(n)
    while (index > 1 && result[index - 1] == '0') { // O(n) 
        index--;  // O(1)
    }

    result[index] = '\0';  // O(1)

    // Переворачиваем результат - O(n)
    for (int k = 0, m = index - 1; k < m; k++, m--) { // O(n) 
        char temp = result[k];  // O(1)
        result[k] = result[m];  // O(1)
        result[m] = temp;  // O(1)
    }

    return result;  // O(1)
}

// Функция сложения - O(n)
char* addNumbers(char* a, char* b, const int* base) {
    bool aNeg = (a[0] == '-');  // O(1)
    bool bNeg = (b[0] == '-');  // O(1)
    const char* absA = aNeg ? a + 1 : a;  // O(1)
    const char* absB = bNeg ? b + 1 : b;  // O(1)

    // Оба положительные - O(n)
    if (!aNeg && !bNeg) {  // O(1)
        return addUnsigned(absA, absB, base);  // O(n)
    }
    
    // Оба отрицательные - O(n)
    if (aNeg && bNeg) {  // O(1)
        char* result = addUnsigned(absA, absB, base);  // O(n)
        int* lenPtr = stringLength(result);  // O(n)
        int len = *lenPtr;  // O(1)
        delete lenPtr;  // O(1)
        
        char* finalResult = createDynamicArray(new int(len + 2));  // O(1)
        finalResult[0] = '-';  // O(1)
        for (int i = 0; i <= len; i++) { // O(n) 
            finalResult[i + 1] = result[i];  // O(1)
        }
        deleteDynamicArray(result);  // O(1)
        return finalResult;  // O(1)
    }
    
    // Разные знаки: a + b = a - (-b) или (-a) + b = b - a - O(n)
    if (aNeg && !bNeg) {  // O(1)
        // -a + b = b - a
        int cmp = compareUnsigned(absA, absB);  // O(n)
        if (cmp == 0) {  // O(1)
            char* result = createDynamicArray(new int(2));  // O(1)
            result[0] = '0';  // O(1)
            result[1] = '\0';  // O(1)
            return result;  // O(1)
        } else if (cmp > 0) {  // O(1)
            // |a| > |b|, результат отрицательный - O(n)
            char* result = subtractUnsigned(absA, absB, base);  // O(n)
            int* lenPtr = stringLength(result);  // O(n)
            int len = *lenPtr;  // O(1)
            delete lenPtr;  // O(1)
            
            char* finalResult = createDynamicArray(new int(len + 2));  // O(1)
            finalResult[0] = '-';  // O(1)
            for (int i = 0; i <= len; i++) { // O(n) 
                finalResult[i + 1] = result[i];  // O(1)
            }
            deleteDynamicArray(result);  // O(1)
            return finalResult;  // O(1)
        } else {  // O(1)
            // |a| < |b|, результат положительный - O(n)
            return subtractUnsigned(absB, absA, base);  // O(n)
        }
    } else { // !aNeg && bNeg - O(n)
        // a + (-b) = a - b
        int cmp = compareUnsigned(absA, absB);  // O(n)
        if (cmp == 0) {  // O(1)
            char* result = createDynamicArray(new int(2));  // O(1)
            result[0] = '0';  // O(1)
            result[1] = '\0';  // O(1)
            return result;  // O(1)
        } else if (cmp > 0) {  // O(1)
            // |a| > |b|, результат положительный - O(n)
            return subtractUnsigned(absA, absB, base);  // O(n)
        } else {  // O(1)
            // |a| < |b|, результат отрицательный - O(n)
            char* result = subtractUnsigned(absB, absA, base);  // O(n)
            int* lenPtr = stringLength(result);  // O(n)
            int len = *lenPtr;  // O(1)
            delete lenPtr;  // O(1)
            
            char* finalResult = createDynamicArray(new int(len + 2));  // O(1)
            finalResult[0] = '-';  // O(1)
            for (int i = 0; i <= len; i++) { // O(n) - копирование результата
                finalResult[i + 1] = result[i];  // O(1)
            }
            deleteDynamicArray(result);  // O(1)
            return finalResult;  // O(1)
        }
    }
}

// Функция вычитания - O(n)
char* subtractNumbers(char* a, char* b, const int* base) {
    bool aNeg = (a[0] == '-');  // O(1)
    bool bNeg = (b[0] == '-');  // O(1)
    const char* absA = aNeg ? a + 1 : a;  // O(1)
    const char* absB = bNeg ? b + 1 : b;  // O(1)

    // a - b (оба положительные) - O(n)
    if (!aNeg && !bNeg) {  // O(1)
        int cmp = compareUnsigned(absA, absB);  // O(n)
        if (cmp == 0) {  // O(1)
            char* result = createDynamicArray(new int(2));  // O(1)
            result[0] = '0';  // O(1)
            result[1] = '\0';  // O(1)
            return result;  // O(1)
        } else if (cmp > 0) {  // O(1)
            return subtractUnsigned(absA, absB, base);  // O(n)
        } else {  // O(1)
            char* result = subtractUnsigned(absB, absA, base);  // O(n)
            int* lenPtr = stringLength(result);  // O(n)
            int len = *lenPtr;  // O(1)
            delete lenPtr;  // O(1)
            
            char* finalResult = createDynamicArray(new int(len + 2));  // O(1)
            finalResult[0] = '-';  // O(1)
            for (int i = 0; i <= len; i++) { // O(n) 
                finalResult[i + 1] = result[i];  // O(1)
            }
            deleteDynamicArray(result);  // O(1)
            return finalResult;  // O(1)
        }
    }
    
    // -a - b = -(a + b) - O(n)
    if (aNeg && !bNeg) {  // O(1)
        char* result = addUnsigned(absA, absB, base);  // O(n)
        int* lenPtr = stringLength(result);  // O(n)
        int len = *lenPtr;  // O(1)
        delete lenPtr;  // O(1)
        
        char* finalResult = createDynamicArray(new int(len + 2));  // O(1)
        finalResult[0] = '-';  // O(1)
        for (int i = 0; i <= len; i++) { // O(n) 
            finalResult[i + 1] = result[i];  // O(1)
        }
        deleteDynamicArray(result);  // O(1)
        return finalResult;  // O(1)
    }
    
    // a - (-b) = a + b - O(n)
    if (!aNeg && bNeg) {  // O(1)
        return addUnsigned(absA, absB, base);  // O(n)
    }
    
    // -a - (-b) = -a + b = b - a - O(n)
    if (aNeg && bNeg) {  // O(1)
        int cmp = compareUnsigned(absA, absB);  // O(n)
        if (cmp == 0) {  // O(1)
            char* result = createDynamicArray(new int(2));  // O(1)
            result[0] = '0';  // O(1)
            result[1] = '\0';  // O(1)
            return result;  // O(1)
        } else if (cmp > 0) {  // O(1)
            // |a| > |b|, результат отрицательный - O(n)
            char* result = subtractUnsigned(absA, absB, base);  // O(n)
            int* lenPtr = stringLength(result);  // O(n)
            int len = *lenPtr;  // O(1)
            delete lenPtr;  // O(1)
            
            char* finalResult = createDynamicArray(new int(len + 2));  // O(1)
            finalResult[0] = '-';  // O(1)
            for (int i = 0; i <= len; i++) { // O(n) 
                finalResult[i + 1] = result[i];  // O(1)
            }
            deleteDynamicArray(result);  // O(1)
            return finalResult;  // O(1)
        } else {  // O(1)
            // |a| < |b|, результат положительный - O(n)
            return subtractUnsigned(absB, absA, base);  // O(n)
        }
    }
    
    return nullptr;  // O(1) 
}

// Функция ввода числа - O(n)
char* inputNumber(const int* base) {
    int* sizePtr = new int(100);  // O(1)
    char* buffer = createDynamicArray(sizePtr);  // O(1)
    delete sizePtr;  // O(1)

    while (true) { // O(k) 
        cout << "Введите число: ";  // O(1)
        cin >> buffer;  // O(1)

        if (isValidNumber(buffer, base)) {  // O(n)
            int* lenPtr = stringLength(buffer);  // O(n)
            int len = *lenPtr;  // O(1)
            int* copySizePtr = new int(len + 1);  // O(1)
            char* number = createDynamicArray(copySizePtr);  // O(1)
            delete copySizePtr;  // O(1)

            for (int idx = 0; idx <= len; idx++) { // O(n) 
                number[idx] = buffer[idx];  // O(1)
            }
            deleteDynamicArray(buffer);  // O(1)
            delete lenPtr;  // O(1)
            return number;  // O(1)
        }
        cout << "Ошибка: число невалидно для системы счисления с основанием " << *base << "!\n";  // O(1)
    }
}

// Функция вывода меню - O(1)
void printMenu(const char* title) {
    cout << "\n" << title << "\n";  // O(1)
    cout << "=== КАЛЬКУЛЯТОР СИСТЕМ СЧИСЛЕНИЯ ===\n";  // O(1)
    cout << "Выполнила: Седельник Надежда\n";  // O(1)
}

int main() {
    char* title = createDynamicArray(new int(50));  // O(1)
    for (int idx = 0; idx < 49; idx++) title[idx] = '=';  // O(1) 
    title[49] = '\0';  // O(1)

    printMenu(title);  // O(1)
    deleteDynamicArray(title);  // O(1)

    int* base = new int;  // O(1)

    cout << "Введите основание системы счисления (2-36): ";  // O(1)
    cin >> *base;  // O(1)

    if (*base < 2 || *base > 36) {  // O(1)
        cout << "Ошибка: основание должно быть от 2 до 36!\n";  // O(1)
        delete base;  // O(1)
        return 1;  // O(1)
    }

    cout << "\n--- Ввод первого числа ---\n";  // O(1)
    char* num1 = inputNumber(base);  // O(n)

    cout << "\n--- Ввод второго числа ---\n";  // O(1)
    char* num2 = inputNumber(base);  // O(n)

    cout << "\n--- Результаты ---\n";  // O(1)
    char* sumResult = addNumbers(num1, num2, base);  // O(n)
    char* subResult = subtractNumbers(num1, num2, base);  // O(n)

    cout << num1 << " + " << num2 << " = " << sumResult << "\n";  // O(1)
    cout << num1 << " - " << num2 << " = " << subResult << "\n";  // O(1)

    deleteDynamicArray(num1);  // O(1)
    deleteDynamicArray(num2);  // O(1)
    deleteDynamicArray(sumResult);  // O(1)
    deleteDynamicArray(subResult);  // O(1)
    delete base;  // O(1)

    return 0;  // O(1)
}
