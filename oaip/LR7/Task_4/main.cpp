#include <iostream>

using namespace std;

const int PRIME_5 = 5;
const int PRIME_29 = 29;
const int PRIME_223 = 223;

int* bitwiseSubtract(const int* numbers);
int* bitwiseAdd(const int* numbers);
int* bitwiseNegate(const int* number_array);
int* bitwiseAbs(const int* number_array);
bool bitwiseGreater(const int* numbers);
bool bitwiseGreaterOrEqual(const int* numbers);

// Создание динамического массива - O(n)
int* createDynamicArray(int size_value, const int* input_values) {
    int* new_array = new int[size_value];                           // O(1)
    for (int index = 0; index < size_value; index++) {              // O(n) - цикл по n элементам
        new_array[index] = input_values[index];                     // O(1)
    }
    return new_array;
}

// Удаление динамического массива - O(1)
void deleteDynamicArray(const int* array_ptr) {
    delete[] array_ptr;
}

// Проверка на равенство нулю через побитовые операции - O(1)
bool isZero(const int* number_array) {
    return (number_array[0] | 0) == 0;
}

// Проверка на равенство двух чисел через побитовые операции - O(1)
bool isEqual(const int* numbers_array) {
    return (numbers_array[0] ^ numbers_array[1]) == 0;
}

// Побитовое сложение - O(k), где k - количество битов
int* bitwiseAdd(const int* numbers) {
    int first_number = numbers[0];
    int second_number = numbers[1];

    while (second_number != 0) {                   // O(k) - k = количество битов (максимум 32 для int)
        int carry_value = first_number & second_number;             // O(1)
        first_number = first_number ^ second_number;                // O(1)
        second_number = carry_value << 1;                           // O(1)
    }
    int* result_value = new int(first_number);                      // O(1)
    return result_value;
}

// Побитовое отрицание (получение -x) - O(k)
int* bitwiseNegate(const int* number_array) {
    int input_value = number_array[0];                              // O(1)
    int inverted_value = ~input_value;                              // O(1)
    int temp_values[] = {inverted_value, 1};
    int* temp_array = createDynamicArray(2, temp_values);           // O(1)
    int* result_value = bitwiseAdd(temp_array);                     // O(k) - вызов bitwiseAdd
    deleteDynamicArray(temp_array);                                 // O(1)
    return result_value;
}

// Вычитание a - b = a + (-b) - O(k)
int* bitwiseSubtract(const int* numbers) {
    int second_num_arr[] = {numbers[1]};
    int* second_num_dynamic = createDynamicArray(1, second_num_arr); // O(1)
    int* neg_second = bitwiseNegate(second_num_dynamic);            // O(k) - вызов bitwiseNegate
    
    int temp_values[] = {numbers[0], *neg_second};
    int* temp_array = createDynamicArray(2, temp_values);           // O(1)
    int* result_value = bitwiseAdd(temp_array);                     // O(k) - вызов bitwiseAdd
    
    deleteDynamicArray(second_num_dynamic);                         // O(1)
    delete neg_second;                                              // O(1)
    deleteDynamicArray(temp_array);                                 // O(1)
    return result_value;
}

// Абсолютное значение - O(k)
int* bitwiseAbs(const int* number_array) {
    int input_value = number_array[0];                              // O(1)
    int sign_mask = input_value >> 31;                              // O(1)
    
    int temp_values1[] = {input_value, sign_mask};
    int* temp_array1 = createDynamicArray(2, temp_values1);         // O(1)
    int* xor_result = new int(input_value ^ sign_mask);             // O(1)
    
    int temp_values2[] = {*xor_result, sign_mask};
    int* temp_array2 = createDynamicArray(2, temp_values2);         // O(1)
    int* result_value = bitwiseSubtract(temp_array2);               // O(k) - вызов bitwiseSubtract
    
    delete xor_result;                                              // O(1)
    deleteDynamicArray(temp_array1);                                // O(1)
    deleteDynamicArray(temp_array2);                                // O(1)
    return result_value;
}

// Побитовое сравнение a > b - O(1) - фиксированное количество операций
bool bitwiseGreater(const int* numbers) {
    int first_number = numbers[0];
    int second_number = numbers[1];
    
    // Сравнение знаков - O(1)
    int sign_first = (first_number >> 31) & 1;                      // O(1)
    int sign_second = (second_number >> 31) & 1;                    // O(1)
    
    if (sign_first != sign_second) {                                // O(1)
        return sign_second > sign_first;                            // O(1)
    }
    
    // Если знаки одинаковые, сравниваем побитово - O(1)
    for (int bit_index = 30; bit_index >= 0; bit_index--) {         // O(1) - фиксированно 31 итерация
        int bit_first = (first_number >> bit_index) & 1;            // O(1)
        int bit_second = (second_number >> bit_index) & 1;          // O(1)
        if (bit_first != bit_second) {                              // O(1)
            return bit_first > bit_second;                          // O(1)
        }
    }
    return false;                                                   // O(1)
}

// Побитовое сравнение a >= b - O(1)
bool bitwiseGreaterOrEqual(const int* numbers) {
    int equality_values[] = {numbers[0], numbers[1]};
    int* equality_array = createDynamicArray(2, equality_values);   // O(1)
    bool are_equal = isEqual(equality_array);                       // O(1)
    deleteDynamicArray(equality_array);                             // O(1)
    
    if (are_equal) {                                                // O(1)
        return true;                                                // O(1)
    }
    return bitwiseGreater(numbers);                                 // O(1) - вызов bitwiseGreater
}

// Проверка делимости на 5 через последнюю цифру - O(log n)
bool checkDivisibleBy5(const int* number_array) {
    int* abs_value_ptr = bitwiseAbs(number_array);                  // O(k) - вызов bitwiseAbs
    int input_number = *abs_value_ptr;
    
    // Получаем последнюю цифру через последовательное вычитание 10 - O(log n)
    int temp_value = input_number;
    while (true) {                                                  // O(log₁₀ n) - по количеству цифр
        int compare_values[] = {temp_value, 10};
        int* compare_array = createDynamicArray(2, compare_values); // O(1)
        bool is_greater_equal = bitwiseGreaterOrEqual(compare_array); // O(1) 
        deleteDynamicArray(compare_array);                          // O(1)
        
        if (!is_greater_equal) {                                    // O(1)
            break;                                                  // O(1)
        }
        
        int subtract_values[] = {temp_value, 10};
        int* subtract_array = createDynamicArray(2, subtract_values); // O(1)
        int* result_ptr = bitwiseSubtract(subtract_array);          // O(k) 
        temp_value = *result_ptr;
        delete result_ptr;                                          // O(1)
        deleteDynamicArray(subtract_array);                         // O(1)
    }
    
    int last_digit = temp_value;
    delete abs_value_ptr;                                           // O(1)
    
    int zero_check[] = {last_digit};
    int five_check[] = {last_digit, 5};
    int* zero_array = createDynamicArray(1, zero_check);            // O(1)
    int* five_array = createDynamicArray(2, five_check);            // O(1)
    
    bool result_flag = isZero(zero_array) || isEqual(five_array);   // O(1)
    
    deleteDynamicArray(zero_array);                                 // O(1)
    deleteDynamicArray(five_array);                                 // O(1)
    return result_flag;
}

bool checkDivisibleBy(const int* number_array, const int* divisor_array) {
    int* abs_value_ptr = bitwiseAbs(number_array);                  // O(k) 
    int input_number = *abs_value_ptr;
    int divisor_value = divisor_array[0];

    int zero_check[] = {input_number};
    int* zero_array = createDynamicArray(1, zero_check);            // O(1)
    if (isZero(zero_array)) {                                       // O(1)
        delete abs_value_ptr;                                       // O(1)
        deleteDynamicArray(zero_array);                             // O(1)
        return true;
    }
    
    int compare_values[] = {input_number, divisor_value};
    int* compare_array = createDynamicArray(2, compare_values);     // O(1)
    bool is_greater_equal = bitwiseGreaterOrEqual(compare_array);   // O(1) 
    
    if (!is_greater_equal) {
        delete abs_value_ptr;                                       // O(1)
        deleteDynamicArray(zero_array);                             // O(1)
        deleteDynamicArray(compare_array);                          // O(1)
        return false;
    }

    while (is_greater_equal) {                                      
        int subtract_values[] = {input_number, divisor_value};
        int* subtract_array = createDynamicArray(2, subtract_values); // O(1)
        int* result_ptr = bitwiseSubtract(subtract_array);          // O(k) - вызов bitwiseSubtract
        input_number = *result_ptr;
        delete result_ptr;                                          // O(1)
        deleteDynamicArray(subtract_array);                         // O(1)
        
        compare_values[0] = input_number;
        compare_values[1] = divisor_value;
        deleteDynamicArray(compare_array);                          // O(1)
        compare_array = createDynamicArray(2, compare_values);      // O(1)
        is_greater_equal = bitwiseGreaterOrEqual(compare_array);    // O(1) - вызов bitwiseGreaterOrEqual
    }

    delete abs_value_ptr;                                           // O(1)
    deleteDynamicArray(zero_array);                                 // O(1)
    deleteDynamicArray(compare_array);                              // O(1)
    
    int final_check[] = {input_number};
    int* final_array = createDynamicArray(1, final_check);          // O(1)
    bool is_divisible = isZero(final_array);                        // O(1)
    deleteDynamicArray(final_array);                                // O(1)
    return is_divisible;
}

// Проверка делимости на 29 - O(n/29)
bool checkDivisibleBy29(const int* number_array) {
    int divisor_values[] = {PRIME_29};
    int* divisor_array = createDynamicArray(1, divisor_values);     // O(1)
    bool result_flag = checkDivisibleBy(number_array, divisor_array); // O(n/29) - вызов checkDivisibleBy
    deleteDynamicArray(divisor_array);                              // O(1)
    return result_flag;
}

// Проверка делимости на 223 - O(n/223)
bool checkDivisibleBy223(const int* number_array) {
    int divisor_values[] = {PRIME_223};
    int* divisor_array = createDynamicArray(1, divisor_values);     // O(1)
    bool result_flag = checkDivisibleBy(number_array, divisor_array); // O(n/223) - вызов checkDivisibleBy
    deleteDynamicArray(divisor_array);                              // O(1)
    return result_flag;
}

// Функция для отображения контекстного меню - O(1)
void displayMenu() {
    cout << "==================================================\n";
    cout << "      ПРОВЕРКА ДЕЛИМОСТИ НА 5, 29, 223\n";
    cout << "==================================================\n";
    cout << "Суть задания:\n";
    cout << "- Проверить делимость числа на простые числа 5, 29, 223\n";
    cout << "Выполнила: Седельник Надежда\n\n";
}

// Проверка всех трех простых чисел - O(n)
void checkAllThreePrimes(const int* number_array) {
    cout << "Число " << number_array[0] << ":\n";

    cout << "  Делится на " << PRIME_5   << ": "
         << (checkDivisibleBy5(number_array)   ? "да" : "нет") << "\n";    // O(log n)

    cout << "  Делится на " << PRIME_29  << ": "
         << (checkDivisibleBy29(number_array)  ? "да" : "нет") << "\n";    // O(n/29)

    cout << "  Делится на " << PRIME_223 << ": "
         << (checkDivisibleBy223(number_array) ? "да" : "нет") << "\n\n";  // O(n/223)
}

int main() {
    displayMenu();  // O(1)

    cout << "Тестовые примеры:\n";
    int test_values[] = {0, 5, 10, 25, 29, 58, 145, 223, 446, 15};

    for (int test_index = 0; test_index < 10; test_index++) {       // O(10 * n) - 10 итераций
        int* number_array = createDynamicArray(1, &test_values[test_index]); // O(1)
        checkAllThreePrimes(number_array);                          // O(n) - вызов checkAllThreePrimes
        deleteDynamicArray(number_array);                           // O(1)
    }

    cout << "==================================================\n";

    char continue_flag;

    do {
        int user_number;
        cout << "Введите число для проверки: ";
        cin >> user_number;

        int* number_array = createDynamicArray(1, &user_number);    // O(1)
        checkAllThreePrimes(number_array);                          // O(n) 
        deleteDynamicArray(number_array);                           // O(1)

        cout << "Хотите проверить ещё одно число? (y/n): ";
        cin >> continue_flag;
        cout << "\n";

    } while (continue_flag == 'y' || continue_flag == 'Y');         // O(m * n) - m итераций

    cout << "Завершение работы.\n";
    return 0;
}
