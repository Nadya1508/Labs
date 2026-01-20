#include <iostream>
#include <cctype>

#ifdef TEST_MODE
#include <gtest/gtest.h>
#endif

class TextProcessor {
private:
    bool isConsonant(const char* character) const {
        char ch = character[0];
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        if (!std::isalpha(static_cast<unsigned char>(ch))) return false;
        const char vowels[] = {'a','e','i','o','u','y','\0'};
        for (int i = 0; vowels[i] != '\0'; i++) {
            if (ch == vowels[i]) return false;
        }
        return true;
    }

    bool isDelimiter(const char* character) const {
        return character[0] == ' ' || character[0] == '\t' || 
               character[0] == '\n' || character[0] == '\0';
    }

    void stringCopy(char* dest, const char* src, const int* size) const {
        for (int i = 0; i < *size; i++) {
            dest[i] = src[i];
        }
        dest[*size] = '\0';
    }

    int stringLength(const char* str) const {
        int len = 0;
        while (str[len] != '\0') {
            len++;
        }
        return len;
    }

public:
    char* text;
    int size;

    TextProcessor(const char* inputText) {
        if (inputText && inputText[0] != '\0') {
            size = stringLength(inputText);
            text = new char[size + 1];
            int tempSize = size;
            stringCopy(text, inputText, &tempSize);
        } else {
            text = new char[1];
            text[0] = '\0';
            size = 0;
        }
    }

    ~TextProcessor() {
        delete[] text;
    }

    char* removeWordsByLength(const char* inputText, const int* textSize, int targetLength) const {
        if (!inputText || targetLength <= 0) {
            char* result = new char[*textSize + 1];
            stringCopy(result, inputText, textSize);
            return result;
        }

        char* result = new char[*textSize + 1];
        result[0] = '\0';
        
        int resultIndex = 0;
        int textIndex = 0;
        bool firstWord = true;
        
        while (textIndex <= *textSize) {
            int wordStart = textIndex;
            while (textIndex <= *textSize && isDelimiter(&inputText[textIndex])) {
                textIndex++;
            }
            if (textIndex > *textSize) break;
            
            wordStart = textIndex;
            
            while (textIndex <= *textSize && !isDelimiter(&inputText[textIndex])) {
                textIndex++;
            }
            int wordEnd = textIndex;

            char firstChar = '\0';
            int letterCount = 0;
            bool hasLetters = false;
            
            for (int i = wordStart; i < wordEnd; i++) {
                if (std::isalpha(static_cast<unsigned char>(inputText[i]))) {
                    letterCount++;
                    hasLetters = true;
                    if (firstChar == '\0') {
                        firstChar = inputText[i];
                    }
                }
            }
            
            bool shouldRemove = hasLetters && 
                              (letterCount == targetLength) && 
                              (firstChar != '\0') && 
                              isConsonant(&firstChar);
            
            if (!shouldRemove) {
                if (!firstWord && resultIndex > 0) {
                    result[resultIndex++] = ' ';
                }
                
                for (int i = wordStart; i < wordEnd; i++) {
                    result[resultIndex++] = inputText[i];
                }
                firstWord = false;
            }
        }
        
        result[resultIndex] = '\0';
        return result;
    }

    char* processText(int targetLength) const {
        return removeWordsByLength(text, &size, targetLength);
    }
};

int safeInputInt(const char* prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка! Пожалуйста, введите целое число.\n";
        } else {
            std::cin.ignore(10000, '\n');
            break;
        }
    }
    return value;
}

void safeInputText(char*& buffer, int& size) {
    const int BUFFER_SIZE = 1000;
    char temp[BUFFER_SIZE];
    std::cout << "Введите текст: ";
    std::cin.getline(temp, BUFFER_SIZE);
    
    if (std::strlen(temp) == 0) {
        std::cout << "Текст не может быть пустым. Пожалуйста, введите текст: ";
        std::cin.getline(temp, BUFFER_SIZE);
    }
    
    size = std::strlen(temp);
    buffer = new char[size + 1];
    std::strcpy(buffer, temp);
}

void showContextMenu() {
    std::cout << "\n==============================================\n";
    std::cout << " ЛАБОРАТОРНАЯ РАБОТА №6\n";
    std::cout << " Тема: Удаление слов заданной длины,\n";
    std::cout << "       начинающихся с согласных букв\n";
    std::cout << " Выполнила: Седельник Надежда, группа 553503\n";
    std::cout << "==============================================\n\n";
}

void runTask() {
    char* inputText = nullptr;
    int textSize = 0;
    safeInputText(inputText, textSize);
    
    TextProcessor processor(inputText);
    delete[] inputText;

    std::cout << "\nИсходный текст: " << processor.text << std::endl;
    int targetLength = safeInputInt("Введите длину слов для удаления: ");
    
    if (targetLength <= 0) {
        std::cout << "Ошибка: длина должна быть положительным числом!\n";
        return;
    }
    
    char* result = processor.processText(targetLength);
    std::cout << "\nРезультат: " << result << std::endl;
    delete[] result;
}

void showMainMenu() {
    int choice = 0;
    while (choice != 3) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Выполнить задание\n";
        std::cout << "2. Описание работы\n";
        std::cout << "3. Выход\n";
        std::cout << "Выберите пункт: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Неверный ввод! Пожалуйста, введите число 1-3.\n";
            continue;
        }
        std::cin.ignore(10000, '\n');
        
        switch (choice) {
            case 1: runTask(); break;
            case 2: showContextMenu(); break;
            case 3: std::cout << "Выход из программы...\n"; break;
            default: std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}

#ifndef TEST_MODE
int main() {
    showContextMenu();
    showMainMenu();
    return 0;
}
#endif

#ifdef TEST_MODE

TEST(TextProcessorTest, RemoveThreeLetterConsonantWords) {
    TextProcessor processor("cat dog bus apple");
    char* result = processor.processText(3);
    EXPECT_STREQ("apple", result);
    delete[] result;
}

TEST(TextProcessorTest, RemoveFiveLetterConsonantWords) {
    TextProcessor processor("hello world test program");
    char* result = processor.processText(5);
    EXPECT_STREQ("test program", result);
    delete[] result;
}

TEST(TextProcessorTest, NoWordsToRemove) {
    TextProcessor processor("apple orange egg");
    char* result = processor.processText(3);
    EXPECT_STREQ("apple orange egg", result);
    delete[] result;
}

TEST(TextProcessorTest, MixedCase) {
    TextProcessor processor("Cat Bat car Dog");
    char* result = processor.processText(3);
    EXPECT_STREQ("", result);
    delete[] result;
}

TEST(TextProcessorTest, AllWordsRemoved) {
    TextProcessor processor("bat cat rat");
    char* result = processor.processText(3);
    EXPECT_STREQ("", result);
    delete[] result;
}

TEST(TextProcessorTest, WithPunctuation) {
    TextProcessor processor("cat, dog! bat? apple.");
    char* result = processor.processText(3);
    EXPECT_STREQ("apple.", result);
    delete[] result;
}

TEST(TextProcessorTest, MultipleSpaces) {
    TextProcessor processor("cat   dog   bat   apple");
    char* result = processor.processText(3);
    EXPECT_STREQ("apple", result);
    delete[] result;
}

TEST(TextProcessorTest, DifferentLengths) {
    TextProcessor processor("big small tiny huge");
    char* result = processor.processText(4);
    EXPECT_STREQ("big small", result);
    delete[] result;
}

TEST(TextProcessorTest, EmptyString) {
    TextProcessor processor("");
    char* result = processor.processText(3);
    EXPECT_STREQ("", result);
    delete[] result;
}

TEST(TextProcessorTest, InvalidLength) {
    TextProcessor processor("test string");
    char* result = processor.processText(0);
    EXPECT_STREQ("test string", result);
    delete[] result;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif