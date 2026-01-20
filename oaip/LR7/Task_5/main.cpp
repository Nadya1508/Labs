#include <iostream>

using namespace std;

// O(n) - где n длина строки
bool readInt(const char* prompt, int& out) {
    cout << prompt;
    
    char buffer[100];
    cin >> buffer;
    
    if (buffer[0] == '\0') return false;
    
    int start = 0;
    if (buffer[0] == '-') {
        if (buffer[1] == '\0') return false;
        start = 1;
    }

    // O(n)
    for (int i = start; buffer[i] != '\0'; i++) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            return false;
        }
    }

    int value = 0;
    bool negative = (buffer[0] == '-');

    // O(n)
    for (int i = start; buffer[i] != '\0'; i++) {
        value = value * 10 + (buffer[i] - '0');
    }

    if (negative) value = -value;
    out = value;
    return true;
}

// O(k) - где k размер digits
void encodeBase3(int barrel, int* digits, int size) {
    // O(k)
    for (int i = 0; i < size; i++) {
        digits[i] = barrel % 3;
        barrel /= 3;
    }
}

// O(n) - где n размер digits
void printPlan(int* digits, int size) {
    cout << "План распределения рабов по бочкам:\n";
    // O(n)
    for (int i = 0; i < size; i++) {
        cout << "  Раб " << i + 1 << ": ";
        if (digits[i] == 0) cout << "не пить\n";
        else if (digits[i] == 1) cout << "пить в День 1\n";
        else cout << "пить в День 2\n";
    }
    cout << "\n";
}

// O(n) - где n размер digits
void printDayAssignments(int* digits, int size) {
    cout << "Рабы, пьющие в каждый день:\n";
    cout << "День 1: ";
    bool any = false;
    // O(n)
    for (int i = 0; i < size; i++) {
        if (digits[i] == 1) {
            cout << i + 1 << " ";
            any = true;
        }
    }
    if (!any) cout << "(никто)";
    cout << "\n";

    cout << "День 2: ";
    any = false;
    // O(n)
    for (int i = 0; i < size; i++) {
        if (digits[i] == 2) {
            cout << i + 1 << " ";
            any = true;
        }
    }
    if (!any) cout << "(никто)";
    cout << "\n\n";
}

// O(n) - где n размер died1 
int decodeBarrel(bool* died1, bool* died2, int size) {
    int barrel = 0;
    int power = 1;
    
    // O(n) 
    for (int i = 0; i < size; i++) {
        int digit = 0;
        if (died1[i]) 
            digit = 1;
        else if (died2[i]) 
            digit = 2;
        
        barrel += digit * power;
        power *= 3;
    }
    return barrel;
}

// O(n) - где n количество рабов
void getExperimentalResults(bool* died1, bool* died2, int size) {
    cout << "Введите результаты эксперимента:\n";
    
    // O(n)
    for (int i = 0; i < size; i++) {
        char response;
        cout << "Раб " << i + 1 << " умер в День 1? (y/n): ";
        cin >> response;
        died1[i] = (response == 'y' || response == 'Y');
        
        if (!died1[i]) {
            cout << "Раб " << i + 1 << " умер в День 2? (y/n): ";
            cin >> response;
            died2[i] = (response == 'y' || response == 'Y');
        } else {
            died2[i] = false;
        }
    }
    cout << "\n";
}

// Функция для проверки кодирования конкретной бочки O(n)
void testEncoding(int barrel, int slaves) {
    int* code = new int[slaves];
    for (int i = 0; i < slaves; i++) code[i] = 0;
    
    encodeBase3(barrel, code, slaves);
    
    cout << "Проверка кодирования бочки " << barrel << ":\n";
    cout << "Троичный код: ";
    for (int i = slaves - 1; i >= 0; i--) {
        cout << code[i];
    }
    cout << endl;
    
    printPlan(code, slaves);
    delete[] code;
}

// O(n)
void run_task5() {
    const int slaves = 5;
    const int maxBarrels = 240;
    
    cout << "=== Определение отравленной бочки ===\n\n";
    cout << "У Патриция 240 бочек вина и 5 рабов.\n";
    cout << "Недоброжелатель отравил одну из бочек.\n";
    cout << "Используем троичную систему для определения отравленной бочки.\n\n";
    
    testEncoding(103, slaves);
    testEncoding(127, slaves);
    
    int* code = new int[slaves]; // O(1) 
    bool* died1 = new bool[slaves]; // O(1)
    bool* died2 = new bool[slaves]; // O(1)
    
    // O(n)
    for (int i = 0; i < slaves; i++) {
        code[i] = 0;
        died1[i] = false;
        died2[i] = false;
    }
    
    cout << "Показываем план тестирования для всех 240 бочек:\n";
    cout << "Каждая бочка соответствует уникальной комбинации.\n\n";
    
    // Показываем пример кодирования для бочки 0
    encodeBase3(0, code, slaves);
    cout << "Пример: Бочка 0\n";
    printPlan(code, slaves);
    printDayAssignments(code, slaves);
    
    getExperimentalResults(died1, died2, slaves);
    
    // Декодируем номер бочки
    int poisonedBarrel = decodeBarrel(died1, died2, slaves);
    
    cout << "Результаты наблюдений:\n";
    // O(n)
    for (int i = 0; i < slaves; i++) {
        if (died1[i]) 
            cout << "  Раб " << i + 1 << " умер в День 1\n";
        else if (died2[i])
            cout << "  Раб " << i + 1 << " умер в День 2\n";
        else
            cout << "  Раб " << i + 1 << " выжил\n";
    }
    cout << "\n";
    
    cout << "Отравленная бочка: " << poisonedBarrel << "\n";
    
    if (poisonedBarrel >= 0 && poisonedBarrel <= maxBarrels) {
        cout << "Успех! Отравленная бочка найдена.\n";
    } else {
        cout << "Ошибка в данных! Получен некорректный номер бочки.\n";
    }
    
    // Освобождаем память O(1)
    delete[] code;
    delete[] died1;
    delete[] died2;
}

int main() {
    run_task5();
    return 0;
}
