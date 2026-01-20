#include <iostream>
using namespace std;

int getStringLength(const char* str) {
    int length = 0;
    while (str[length] != '\0') length++;  // O(n)
    return length;
}

bool isValidBinary(const char* binaryStr) {
    if (!binaryStr) return false;
    for (int i = 0; binaryStr[i] != '\0'; i++)  // O(n)
        if (binaryStr[i] != '0' && binaryStr[i] != '1') return false;
    return true;
}

void clearInputBuffer() {
    while (cin.get() != '\n');  // O(n)
}


char* inputBinaryNumber() {
    const int BUFFER_SIZE = 512;
    char* buffer = new char[BUFFER_SIZE];
    cout << "Введите двоичное число: ";
    cin.getline(buffer, BUFFER_SIZE);

    int length = getStringLength(buffer);  // O(n)
    char* result = new char[length + 1];

    for (int i = 0; i <= length; i++)  // O(n)
        result[i] = buffer[i];

    delete[] buffer;
    return result;
}

char* convertToOnesComplement(const char* naturalNum) {
    int length = getStringLength(naturalNum);  // O(n)
    char* onesComplement = new char[length + 1];

    for (int i = 0; i <= length; i++)  // O(n)
        onesComplement[i] = naturalNum[i];

    if (onesComplement[0] == '1') {
        for (int i = 1; i < length; i++) {  // O(n)
            onesComplement[i] = (onesComplement[i] == '0') ? '1' : '0';
        }
    }
    return onesComplement;
}

char* convertToTwosComplement(const char* onesComplement) {
    int length = getStringLength(onesComplement);  // O(n)
    char* twosComplement = new char[length + 1];

    for (int i = 0; i <= length; i++)  // O(n)
        twosComplement[i] = onesComplement[i];

    if (twosComplement[0] == '1') {
        int carry = 1;
        for (int i = length - 1; i >= 1 && carry > 0; i--) {  // O(n)
            if (twosComplement[i] == '0') {
                twosComplement[i] = '1';
                carry = 0;
            } else {
                twosComplement[i] = '0';
            }
        }
    }
    return twosComplement;
}


void extendNumber(char*& number, int newLength) {
    int oldLength = getStringLength(number);  // O(n)
    if (oldLength == newLength) return;
    
    char signBit = number[0];
    char* extendedNumber = new char[newLength + 1];
    
    int difference = newLength - oldLength;
    for (int i = 0; i < difference; i++)  // O(n)
        extendedNumber[i] = signBit;
        
    for (int i = 0; i <= oldLength; i++)  // O(n)
        extendedNumber[i + difference] = number[i];
        
    delete[] number;
    number = extendedNumber;
}

void alignBinaryNumbers(char* &num1, char* &num2) {
    int len1 = getStringLength(num1);  // O(n)
    int len2 = getStringLength(num2);  // O(n)
    int maxLength = (len1 > len2) ? len1 : len2;
    
    extendNumber(num1, maxLength);  // O(n)
    extendNumber(num2, maxLength);  // O(n)
}


char* addOnesComplement(const char* num1, const char* num2) {
    int length = getStringLength(num1);  // O(n)
    char* result = new char[length + 2];

    int carry = 0;
    result[length + 1] = '\0';

    for (int i = length - 1; i >= 0; i--) {  // O(n)
        int bit1 = num1[i] - '0';
        int bit2 = num2[i] - '0';
        int sum = bit1 + bit2 + carry;
        result[i + 1] = (sum % 2) + '0';
        carry = sum / 2;
    }

    result[0] = carry + '0';
    return result;
}

char* handleCyclicCarry(char* additionResult) {
    int length = getStringLength(additionResult);  // O(n)

    if (additionResult[0] == '1') {
        char* correctedResult = new char[length];
        
        for (int i = 1; i < length; i++)  // O(n)
            correctedResult[i - 1] = additionResult[i];
        correctedResult[length - 1] = '\0';

        int carry = 1;
        for (int i = length - 2; i >= 0 && carry > 0; i--) {  // O(n)
            if (correctedResult[i] == '0') {
                correctedResult[i] = '1';
                carry = 0;
            } else {
                correctedResult[i] = '0';
            }
        }

        delete[] additionResult;
        return correctedResult;
    }

    return additionResult;
}


void performBinaryAddition() {
    char* input1 = inputBinaryNumber();  // O(n)
    char* input2 = inputBinaryNumber();  // O(n)
    
    if (!isValidBinary(input1) || !isValidBinary(input2)) {  // O(n)
        cout << "Ошибка: Введено не двоичное число!\n";
        delete[] input1;
        delete[] input2;
        return;
    }

    int len1 = getStringLength(input1);  // O(n)
    int len2 = getStringLength(input2);  // O(n)
    char* original1 = new char[len1 + 1];
    char* original2 = new char[len2 + 1];
    
    for (int i = 0; i <= len1; i++) original1[i] = input1[i];  // O(n)
    for (int i = 0; i <= len2; i++) original2[i] = input2[i];  // O(n)

    cout << "\n=== Процесс сложения ===\n";
    
    alignBinaryNumbers(input1, input2);  // O(n)
    
    cout << "После выравнивания:\n";
    cout << "Число 1: " << input1 << "\n";
    cout << "Число 2: " << input2 << "\n";

    char* onesComplement1 = convertToOnesComplement(input1);  // O(n)
    char* onesComplement2 = convertToOnesComplement(input2);  // O(n)
    
    cout << "\nВ обратном коде:\n";
    cout << "Число 1: " << onesComplement1 << "\n";
    cout << "Число 2: " << onesComplement2 << "\n";

    char* rawSum = addOnesComplement(onesComplement1, onesComplement2);  // O(n)
    cout << "\nСумма в обратном коде: " << rawSum << "\n";

    char* correctedSum = handleCyclicCarry(rawSum);  // O(n)
    if (correctedSum != rawSum) {
        cout << "После циклического переноса: " << correctedSum << "\n";
    }

    char* finalResult = convertToTwosComplement(correctedSum);  // O(n)
    cout << "Результат в дополнительном коде: " << finalResult << "\n";

    cout << "\n=== Итог ===\n";
    cout << original1 << " + " << original2 << " = " << finalResult << "\n";

    delete[] input1;
    delete[] input2;
    delete[] original1;
    delete[] original2;
    delete[] onesComplement1;
    delete[] onesComplement2;
    delete[] correctedSum;
    delete[] finalResult;
}


int main() {
    int choice;
    
    do {
        cout << "\n=== Сложение двоичных чисел ===\n";
        cout << "Выполнила: Седельник Надежда\n";
        cout << "Вариант: 8\n";
        cout << "1. Сложить два числа\n";
        cout << "2. Выход\n";
        cout << "Выберите опцию: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1:
                performBinaryAddition();
                break;
            case 2:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
                break;
        }
    } while (choice != 2);

    return 0;
}
