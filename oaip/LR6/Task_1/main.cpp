#include <iostream>
#include <gtest/gtest.h>

class FloatNumberExtractor {
private:
    static const int MAX_STRING_LENGTH = 80;

    static bool isDigitCharacter(char* character_ptr) {
        return *character_ptr >= '0' && *character_ptr <= '9';
    }

    static int getStringLength(char* string_ptr) {
        if (string_ptr == nullptr) return 0;
        int length = 0;
        while (string_ptr[length] != '\0') {
            length++;
        }
        return length;
    }

    static bool isValidFloatCharacter(char* character_ptr) {
        return isDigitCharacter(character_ptr) || 
               *character_ptr == '.' || *character_ptr == ',' || 
               *character_ptr == '+' || *character_ptr == '-' || 
               *character_ptr == 'e' || *character_ptr == 'E';
    }

    static bool isValidFloatNumber(char* string_ptr, int start_idx, int end_idx) {
        if (start_idx >= end_idx) return false;
        
        bool has_digit = false;
        bool has_decimal = false;
        bool has_exponent = false;
        bool need_digit_after_exp = false;
        
        for (int i = start_idx; i < end_idx; ++i) {
            char* current_char = &string_ptr[i];
            
            if (isDigitCharacter(current_char)) {
                has_digit = true;
                if (need_digit_after_exp) {
                    need_digit_after_exp = false;
                }
            }
            else if (*current_char == '.' || *current_char == ',') {
                if (has_decimal || has_exponent) return false;
                has_decimal = true;
            }
            else if (*current_char == 'e' || *current_char == 'E') {
                if (has_exponent || !has_digit) return false;
                has_exponent = true;
                need_digit_after_exp = true;
            }
            else if (*current_char == '+' || *current_char == '-') {
                if (i != start_idx && (string_ptr[i-1] != 'e' && string_ptr[i-1] != 'E')) {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        
        return has_digit && !need_digit_after_exp;
    }

public:
    static void displayContextMenu(char* menu_title) {
        if (menu_title != nullptr) {
            std::cout << "========================================\n";
            std::cout << "          КОНТЕКСТНОЕ МЕНЮ\n";
            std::cout << "========================================\n";
        }
        std::cout << "Суть задания: Из строки, состоящей из букв, цифр,\n";
        std::cout << "запятых, точек, знаков + и -, выделить подстроку,\n";
        std::cout << "задающую вещественное число с плавающей точкой.\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Выполнила: Седельник Надежда\n";
        std::cout << "Вариант: 8\n";
        std::cout << "- Строки до 80 символов\n";
        std::cout << "- Использование getchar()\n";
        std::cout << "- Обработка неверного ввода\n";
        std::cout << "========================================\n\n";
    }

    static char* readUserInput(int* max_len_ptr) {
        char* input_buffer = new char[*max_len_ptr + 1];
        std::cout << "Введите строку (максимум " << *max_len_ptr << " символов): ";
        
        int input_char;
        int char_count = 0;
        
        while ((input_char = getchar()) != '\n' && input_char != EOF) {
            if (char_count < *max_len_ptr) {
                input_buffer[char_count++] = static_cast<char>(input_char);
            } else {
                while ((input_char = getchar()) != '\n' && input_char != EOF) {}
                std::cout << "Предупреждение: ввод обрезан до " << *max_len_ptr << " символов\n";
                break;
            }
        }
        
        if (char_count == 0) {
            std::cout << "Ошибка: введена пустая строка\n";
            delete[] input_buffer;
            return nullptr;
        }
        
        input_buffer[char_count] = '\0';
        return input_buffer;
    }

    static char* findFloatNumber(char* input_string) {
        if (input_string == nullptr || input_string[0] == '\0') {
            return nullptr;
        }
        
        int str_len = getStringLength(input_string);
        int best_start = 0;
        int best_len = 0;
        
        for (int i = 0; i < str_len; ++i) {
            char* current_char = &input_string[i];
            if (isValidFloatCharacter(current_char)) {
                int j = i;
                
                while (j < str_len && isValidFloatCharacter(&input_string[j])) {
                    j++;
                }
                
                if (isValidFloatNumber(input_string, i, j)) {
                    int current_len = j - i;
                    if (current_len > best_len) {
                        best_len = current_len;
                        best_start = i;
                    }
                }
                
                i = j - 1;  
            }
        }
        
        if (best_len == 0) {
            return nullptr;
        }
        
        char* result = new char[best_len + 1];
        for (int i = 0; i < best_len; ++i) {
            result[i] = input_string[best_start + i];
        }
        result[best_len] = '\0';
        
        return result;
    }

    static void displayResults(char* original_str, char* result_str) {
        std::cout << "\n=== РЕЗУЛЬТАТЫ ===\n";
        std::cout << "Исходный текст: \"" << original_str << "\"\n";
        
        if (result_str != nullptr) {
            std::cout << "Найдено вещественное число: \"" << result_str << "\"\n";
        } else {
            std::cout << "Вещественное число не найдено в строке.\n";
        }
        std::cout << "==================\n";
    }

    static void cleanupMemory(char** ptr_array, int array_size) {
        for (int i = 0; i < array_size; ++i) {
            if (ptr_array[i] != nullptr) {
                delete[] ptr_array[i];
                ptr_array[i] = nullptr;
            }
        }
    }

    static void executeProgram(char* program_name) {
        displayContextMenu(program_name);
        
        int max_length = MAX_STRING_LENGTH;
        char* user_input = readUserInput(&max_length);
        
        if (user_input == nullptr) {
            std::cout << "Программа завершена из-за ошибки ввода.\n";
            return;
        }
        
        char* found_number = findFloatNumber(user_input);
        
        displayResults(user_input, found_number);
        
        char* memory_ptrs[] = {user_input, found_number};
        cleanupMemory(memory_ptrs, 2);
        
        std::cout << "\nНажмите Enter для выхода...";
        std::cin.get();
    }
};

class FloatNumberExtractorTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(FloatNumberExtractorTest, ExtractSimpleFloat) {
    char test_str[] = "abc123.45def";
    char* result = FloatNumberExtractor::findFloatNumber(test_str);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "123.45");
    delete[] result;
}

TEST_F(FloatNumberExtractorTest, ExtractNegativeFloat) {
    char test_str[] = "value -123.45 end";
    char* result = FloatNumberExtractor::findFloatNumber(test_str);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "-123.45");
    delete[] result;
}

TEST_F(FloatNumberExtractorTest, ExtractFloatWithExponent) {
    char test_str[] = "number 1.23e-4 text";
    char* result = FloatNumberExtractor::findFloatNumber(test_str);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "1.23e-4");
    delete[] result;
}

TEST_F(FloatNumberExtractorTest, ExtractFloatWithComma) {
    char test_str[] = "price 123,45$";
    char* result = FloatNumberExtractor::findFloatNumber(test_str);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "123,45");
    delete[] result;
}

TEST_F(FloatNumberExtractorTest, ExtractPositiveFloatWithPlus) {
    char test_str[] = "value +99.99 units";
    char* result = FloatNumberExtractor::findFloatNumber(test_str);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "+99.99");
    delete[] result;
}

TEST_F(FloatNumberExtractorTest, ExtractIntegerNumber) {
    char test_str[] = "number 123 text";
    char* result = FloatNumberExtractor::findFloatNumber(test_str);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "123");
    delete[] result;
}

TEST_F(FloatNumberExtractorTest, ExtractMultipleNumbersLongest) {
    char test_str[] = "12.34 and 567.890";
    char* result = FloatNumberExtractor::findFloatNumber(test_str);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "567.890");
    delete[] result;
}

TEST_F(FloatNumberExtractorTest, NoFloatNumberInString) {
    char test_str[] = "hello world text";
    char* result = FloatNumberExtractor::findFloatNumber(test_str);
    EXPECT_EQ(result, nullptr);
}

TEST_F(FloatNumberExtractorTest, EmptyInputString) {
    char test_str[] = "";
    char* result = FloatNumberExtractor::findFloatNumber(test_str);
    EXPECT_EQ(result, nullptr);
}

TEST_F(FloatNumberExtractorTest, InvalidFloatPatternMultipleDots) {
    char test_str[] = "12.34.56 invalid";
    char* result = FloatNumberExtractor::findFloatNumber(test_str);
    EXPECT_EQ(result, nullptr);
}

TEST_F(FloatNumberExtractorTest, OnlySpecialCharacters) {
    char test_str[] = "+-.,eE";
    char* result = FloatNumberExtractor::findFloatNumber(test_str);
    EXPECT_EQ(result, nullptr);
}

TEST_F(FloatNumberExtractorTest, FloatWithExponentAtEnd) {
    char test_str[] = "number 1.23e text";
    char* result = FloatNumberExtractor::findFloatNumber(test_str);
    EXPECT_EQ(result, nullptr);
}

int main(int argc, char** argv) {
    char* program_name = new char[50];
    const char* name = "Извлечение вещественных чисел";
    int i = 0;
    while (name[i] != '\0' && i < 49) {
        program_name[i] = name[i];
        i++;
    }
    program_name[i] = '\0';

    if (argc > 1 && std::string(argv[1]) == "--tests") {
        ::testing::InitGoogleTest(&argc, argv);
        int test_result = RUN_ALL_TESTS();
        delete[] program_name;
        return test_result;
    }
    
    FloatNumberExtractor::executeProgram(program_name);
    delete[] program_name;
    return 0;
}