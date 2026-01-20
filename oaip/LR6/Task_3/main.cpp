#include <iostream>
#include <cmath>
#include <gtest/gtest.h>

using namespace std;

class StringConverter {
private:
    int stringLength(const char* str) const {
        if (!str) return 0;
        int length = 0;
        while (str[length] != '\0') {
            length++;
        }
        return length;
    }

    void stringReverse(char* str) const {
        if (!str) return;
        
        int len = stringLength(str);
        for (int i = 0; i < len / 2; i++) {
            char temp = str[i];
            str[i] = str[len - i - 1];
            str[len - i - 1] = temp;
        }
    }

    bool isDigit(char c) const {
        return c >= '0' && c <= '9';
    }

    bool isWhitespace(char c) const {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

    char* allocateString(int length) const {
        if (length <= 0) return nullptr;
        char* result = new char[length + 1];
        for (int i = 0; i <= length; i++) {
            result[i] = '\0';
        }
        return result;
    }

    int countDigits(int number) const {
        if (number == 0) return 1;
        int count = 0;
        int n = number < 0 ? -number : number;
        while (n > 0) {
            count++;
            n /= 10;
        }
        return count;
    }

public:
    StringConverter() = default;
    ~StringConverter() = default;

    void deallocateString(char* str) const {
        if (str) {
            delete[] str;
        }
    }

    bool validateNumericString(const char* str) const {
        if (!str || stringLength(str) == 0) return false;
        
        int i = 0;
        bool has_digit = false;
        bool has_dot = false;
        
        while (isWhitespace(str[i])) i++;
        
        if (str[i] == '+' || str[i] == '-') i++;
        
        while (str[i] != '\0' && !isWhitespace(str[i])) {
            if (isDigit(str[i])) {
                has_digit = true;
            } else if (str[i] == '.') {
                if (has_dot) return false;
                has_dot = true;
            } else {
                return false;
            }
            i++;
        }
        
        while (isWhitespace(str[i])) i++;
        
        return has_digit && str[i] == '\0';
    }

    char** splitString(const char* str, char delimiter, int& count) const {
        if (!str) {
            count = 0;
            return nullptr;
        }
        
        count = 1;
        int len = stringLength(str);
        for (int i = 0; i < len; i++) {
            if (str[i] == delimiter) count++;
        }
        
        char** result = new char*[count];
        int start = 0, result_index = 0;
        
        for (int i = 0; i <= len; i++) {
            if (str[i] == delimiter || str[i] == '\0') {
                int substr_len = i - start;
                result[result_index] = allocateString(substr_len);
                
                for (int j = 0; j < substr_len; j++) {
                    result[result_index][j] = str[start + j];
                }
                
                start = i + 1;
                result_index++;
            }
        }
        
        return result;
    }
    
    void deallocateStringArray(char** arr, int count) const {
        if (!arr) return;
        for (int i = 0; i < count; i++) {
            deallocateString(arr[i]);
        }
        delete[] arr;
    }

    char* intToStringDynamic(int number) const {
        if (number == 0) {
            char* result = allocateString(1);
            result[0] = '0';
            return result;
        }
        
        bool is_negative = number < 0;
        int num_digits = countDigits(number);
        int buffer_size = num_digits + (is_negative ? 1 : 0);
        
        char* buffer = allocateString(buffer_size);
        if (!buffer) return nullptr;
        
        int i = 0;
        int n = is_negative ? -number : number;
        
        while (n > 0) {
            buffer[i++] = '0' + (n % 10);
            n /= 10;
        }
        
        if (is_negative) {
            buffer[i++] = '-';
        }
        
        buffer[i] = '\0';
        stringReverse(buffer);
        return buffer;
    }

    char* intToString(int number, char* buffer) const {
        if (!buffer) return nullptr;
        
        if (number == -2147483647 - 1) {
            const char* min_val = "-2147483648";
            int len = stringLength(min_val);
            for (int j = 0; j <= len; j++) {
                buffer[j] = min_val[j];
            }
            return buffer;
        }
        
        if (number == 0) {
            buffer[0] = '0';
            buffer[1] = '\0';
            return buffer;
        }
        
        int i = 0;
        bool is_negative = number < 0;
        int n = is_negative ? -number : number;
        
        while (n != 0) {
            buffer[i++] = '0' + (n % 10);
            n /= 10;
        }
        
        if (is_negative) {
            buffer[i++] = '-';
        }
        
        buffer[i] = '\0';
        stringReverse(buffer);
        return buffer;
    }

    int stringToInt(const char* str) const {
        if (!str || !validateNumericString(str)) {
            return 0;
        }
        
        int result = 0;
        int i = 0;
        bool is_negative = false;
        
        while (isWhitespace(str[i])) i++;
        
        if (str[i] == '-') {
            is_negative = true;
            i++;
        } else if (str[i] == '+') {
            i++;
        }
        
        while (isDigit(str[i])) {
            result = result * 10 + (str[i] - '0');
            i++;
        }
        
        return is_negative ? -result : result;
    }

    char* doubleToStringDynamic(double number, int precision = 6) const {
        if (number == 0.0) {
            char* result = allocateString(precision + 2);
            result[0] = '0';
            result[1] = '.';
            for (int i = 0; i < precision; i++) {
                result[2 + i] = '0';
            }
            return result;
        }
        
        bool is_negative = number < 0;
        double abs_number = is_negative ? -number : number;
        
        int int_part = static_cast<int>(abs_number);
        double fractional = abs_number - int_part;
        
        char* int_str = intToStringDynamic(int_part);
        int int_len = stringLength(int_str);
        
        int buffer_size = int_len + 1 + precision + (is_negative ? 1 : 0);
        char* buffer = allocateString(buffer_size);
        
        int i = 0;
        
        if (is_negative) {
            buffer[i++] = '-';
        }
        
        for (int j = 0; j < int_len; j++) {
            buffer[i++] = int_str[j];
        }
        
        buffer[i++] = '.';
        
        for (int j = 0; j < precision; j++) {
            fractional *= 10;
            int digit = static_cast<int>(fractional);
            buffer[i++] = '0' + digit;
            fractional -= digit;
        }
        
        buffer[i] = '\0';
        deallocateString(int_str);
        return buffer;
    }

    char* doubleToString(double number, char* buffer, int precision = 6) const {
        if (!buffer) return nullptr;
        
        if (number == 0.0) {
            buffer[0] = '0';
            buffer[1] = '.';
            for (int i = 0; i < precision; i++) {
                buffer[2 + i] = '0';
            }
            buffer[2 + precision] = '\0';
            return buffer;
        }
        
        int i = 0;
        bool is_negative = number < 0;
        double abs_number = is_negative ? -number : number;
        
        int int_part = static_cast<int>(abs_number);
        double fractional = abs_number - int_part;
        
        char int_buffer[20];
        intToString(int_part, int_buffer);
        int int_len = stringLength(int_buffer);
        
        if (is_negative) {
            buffer[i++] = '-';
        }
        
        for (int j = 0; j < int_len; j++) {
            buffer[i++] = int_buffer[j];
        }
        
        buffer[i++] = '.';
        
        for (int j = 0; j < precision; j++) {
            fractional *= 10;
            int digit = static_cast<int>(fractional);
            buffer[i++] = '0' + digit;
            fractional -= digit;
        }
        
        buffer[i] = '\0';
        return buffer;
    }

    double stringToDouble(const char* str) const {
        if (!str || !validateNumericString(str)) {
            return 0.0;
        }
        
        double result = 0.0;
        int i = 0;
        bool is_negative = false;
        bool after_decimal = false;
        double decimal_place = 0.1;
        
        while (isWhitespace(str[i])) i++;
        
        if (str[i] == '-') {
            is_negative = true;
            i++;
        } else if (str[i] == '+') {
            i++;
        }
        
        while (str[i] != '\0' && !isWhitespace(str[i])) {
            if (str[i] == '.') {
                after_decimal = true;
            } else if (isDigit(str[i])) {
                if (after_decimal) {
                    result += (str[i] - '0') * decimal_place;
                    decimal_place *= 0.1;
                } else {
                    result = result * 10.0 + (str[i] - '0');
                }
            }
            i++;
        }
        
        return is_negative ? -result : result;
    }

    void displayMenu() const {
        cout << "\n===============================================\n";
        cout << "          ЛАБОРАТОРНАЯ РАБОТА 6\n";
        cout << "   ПРЕОБРАЗОВАНИЕ ЧИСЕЛ И СТРОК\n";
        cout << "===============================================\n";
        cout << "Выполнила: Седельник Надежда\n";
        cout << "Вариант: 8\n";
        cout << "===============================================\n";
        cout << "СУТЬ ЗАДАНИЯ:\n";
        cout << "1. Реализовать преобразование целых чисел в строки и обратно\n";
        cout << "2. Реализовать преобразование вещественных чисел в строки и обратно\n";
        cout << "3. Работать со строками как с массивами char\n";
        cout << "4. Использовать одномерные и двумерные массивы символов\n";
        cout << "5. Обрабатывать неверный пользовательский ввод\n";
        cout << "6. Не использовать стандартные функции работы со строками\n";
        cout << "7. Реализовать модульное тестирование с Google Tests\n";
        cout << "8. Использовать CMake с санитайзерами и линтером\n";
        cout << "===============================================\n";
        cout << "ФУНКЦИОНАЛ ПРОГРАММЫ:\n";
        cout << "- intToString() - целое число в строку\n";
        cout << "- stringToInt() - строка в целое число\n";
        cout << "- doubleToString() - вещественное число в строку\n";
        cout << "- stringToDouble() - строка в вещественное число\n";
        cout << "- splitString() - разделение строки на подстроки\n";
        cout << "- validateNumericString() - проверка числовой строки\n";
        cout << "===============================================\n";
    }

    void runDemo() const {
        displayMenu();
        
        cout << "\n=== ДЕМОНСТРАЦИЯ РАБОТЫ ===\n";
        
        cout << "\n1. ПРЕОБРАЗОВАНИЕ ЦЕЛЫХ ЧИСЕЛ:\n";
        char buffer[50];
        cout << "   intToString(123, buffer) = " << intToString(123, buffer) << endl;
        cout << "   intToString(-456, buffer) = " << intToString(-456, buffer) << endl;
        cout << "   stringToInt(\"789\") = " << stringToInt("789") << endl;
        cout << "   stringToInt(\"-123\") = " << stringToInt("-123") << endl;
        
        cout << "\n2. ПРЕОБРАЗОВАНИЕ ВЕЩЕСТВЕННЫХ ЧИСЕЛ:\n";
        cout << "   doubleToString(3.14159, buffer, 2) = " << doubleToString(3.14159, buffer, 2) << endl;
        cout << "   doubleToString(-2.718, buffer, 3) = " << doubleToString(-2.718, buffer, 3) << endl;
        cout << "   stringToDouble(\"3.14\") = " << stringToDouble("3.14") << endl;
        cout << "   stringToDouble(\"-45.67\") = " << stringToDouble("-45.67") << endl;
        
        cout << "\n3. РАБОТА С ДИНАМИЧЕСКИМИ МАССИВАМИ:\n";
        char* dynamicInt = intToStringDynamic(12345);
        cout << "   intToStringDynamic(12345) = " << dynamicInt << endl;
        deallocateString(dynamicInt);
        
        char* dynamicDouble = doubleToStringDynamic(3.1415926535, 4);
        cout << "   doubleToStringDynamic(3.14159, 4) = " << dynamicDouble << endl;
        deallocateString(dynamicDouble);
        
        cout << "\n4. РАБОТА С ДВУМЕРНЫМИ МАССИВАМИ:\n";
        int count = 0;
        char** splitResult = splitString("apple,banana,cherry", ',', count);
        cout << "   splitString(\"apple,banana,cherry\", ',', count):\n";
        for (int i = 0; i < count; i++) {
            cout << "      [" << i << "] = \"" << splitResult[i] << "\"\n";
        }
        deallocateStringArray(splitResult, count);
        
        cout << "\n5. ОБРАБОТКА ОШИБОЧНОГО ВВОДА:\n";
        cout << "   stringToInt(\"abc\") = " << stringToInt("abc") << " (неверный ввод)\n";
        cout << "   stringToDouble(\"xyz\") = " << stringToDouble("xyz") << " (неверный ввод)\n";
        cout << "   stringToInt(\"123.45\") = " << stringToInt("123.45") << " (целое число с точкой)\n";
        
        cout << "\n===============================================\n";
        cout << "Демонстрация завершена успешно!\n";
        cout << "===============================================\n";
    }
};

class StringConverterTest : public ::testing::Test {
protected:
    StringConverter converter;
};

TEST_F(StringConverterTest, IntToStringPositive) {
    char buffer[20];
    EXPECT_STREQ(converter.intToString(123, buffer), "123");
}

TEST_F(StringConverterTest, IntToStringNegative) {
    char buffer[20];
    EXPECT_STREQ(converter.intToString(-456, buffer), "-456");
}

TEST_F(StringConverterTest, IntToStringZero) {
    char buffer[20];
    EXPECT_STREQ(converter.intToString(0, buffer), "0");
}

TEST_F(StringConverterTest, StringToIntPositive) {
    EXPECT_EQ(converter.stringToInt("123"), 123);
}

TEST_F(StringConverterTest, StringToIntNegative) {
    EXPECT_EQ(converter.stringToInt("-456"), -456);
}

TEST_F(StringConverterTest, StringToIntInvalid) {
    EXPECT_EQ(converter.stringToInt("abc"), 0);
}

TEST_F(StringConverterTest, DoubleToStringPositive) {
    char buffer[30];
    EXPECT_STREQ(converter.doubleToString(3.14159, buffer, 2), "3.14");
}

TEST_F(StringConverterTest, DoubleToStringNegative) {
    char buffer[30];
    EXPECT_STREQ(converter.doubleToString(-2.5, buffer, 1), "-2.5");
}

TEST_F(StringConverterTest, StringToDoublePositive) {
    EXPECT_DOUBLE_EQ(converter.stringToDouble("3.14"), 3.14);
}

TEST_F(StringConverterTest, SplitStringBasic) {
    int count = 0;
    char** result = converter.splitString("one,two,three", ',', count);
    EXPECT_EQ(count, 3);
    EXPECT_STREQ(result[0], "one");
    EXPECT_STREQ(result[1], "two");
    EXPECT_STREQ(result[2], "three");
    converter.deallocateStringArray(result, count);
}

// 2 краевых случая
TEST_F(StringConverterTest, EdgeCaseVeryLargeNumber) {
    char buffer[30];
    EXPECT_STREQ(converter.intToString(999999999, buffer), "999999999");
}

TEST_F(StringConverterTest, EdgeCaseVerySmallNumber) {
    char buffer[30];
    EXPECT_STREQ(converter.intToString(-999999999, buffer), "-999999999");
}

int main(int argc, char **argv) {
    if (argc > 1) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

    StringConverter converter;
    converter.runDemo();
    return 0;
}