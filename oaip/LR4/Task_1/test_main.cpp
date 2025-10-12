#include <gtest/gtest.h>
#include "array_processor.h"

// Тест 1: Обычный случай - разные min и max
TEST(RemoveMinMaxTest, NormalCaseDifferentMinMax) {
    // Arrange
    int size = 6;
    int* arr = new int[size] {5, 2, 8, 1, 9, 3};
    
    // Act
    removeMinMax(arr, size);
    
    // Assert
    EXPECT_EQ(size, 4);
    
    // Проверяем что min (1) и max (9) удалены
    bool hasMin = false, hasMax = false;
    for (int i = 0; i < size; i++) {
        if (arr[i] == 1) hasMin = true;
        if (arr[i] == 9) hasMax = true;
    }
    EXPECT_FALSE(hasMin);
    EXPECT_FALSE(hasMax);
    
    delete[] arr;
}

// Тест 2: Несколько одинаковых min и max
TEST(RemoveMinMaxTest, MultipleMinMaxValues) {
    // Arrange
    int size = 8;
    int* arr = new int[size] {1, 2, 1, 3, 9, 4, 9, 5};
    
    // Act
    removeMinMax(arr, size);
    
    // Assert
    EXPECT_EQ(size, 4);
    
    // Должны остаться: 2, 3, 4, 5
    bool hasMin = false, hasMax = false;
    for (int i = 0; i < size; i++) {
        if (arr[i] == 1) hasMin = true;
        if (arr[i] == 9) hasMax = true;
    }
    EXPECT_FALSE(hasMin);
    EXPECT_FALSE(hasMax);
    
    delete[] arr;
}

// Тест 3: Все элементы одинаковы (min == max)
TEST(RemoveMinMaxTest, AllElementsSame) {
    // Arrange
    int size = 5;
    int* arr = new int[size] {7, 7, 7, 7, 7};
    
    // Act
    removeMinMax(arr, size);
    
    // Assert - массив должен стать пустым
    EXPECT_EQ(size, 0);
    EXPECT_EQ(arr, nullptr);
}

// Тест 4: Пустой массив
TEST(RemoveMinMaxTest, EmptyArray) {
    // Arrange
    int size = 0;
    int* arr = nullptr;
    
    // Act & Assert - не должно быть падения
    EXPECT_NO_THROW(removeMinMax(arr, size));
    EXPECT_EQ(size, 0);
    EXPECT_EQ(arr, nullptr);
}

// Тест 5: Массив из одного элемента
TEST(RemoveMinMaxTest, SingleElementArray) {
    // Arrange
    int size = 1;
    int* arr = new int[size] {42};
    
    // Act
    removeMinMax(arr, size);
    
    // Assert - массив должен стать пустым
    EXPECT_EQ(size, 0);
    EXPECT_EQ(arr, nullptr);
}

// Тест 6: Массив из двух разных элементов
TEST(RemoveMinMaxTest, TwoDifferentElements) {
    // Arrange
    int size = 2;
    int* arr = new int[size] {10, 20};
    
    // Act
    removeMinMax(arr, size);
    
    // Assert - оба удаляются, массив пустой
    EXPECT_EQ(size, 0);
    EXPECT_EQ(arr, nullptr);
}

// Тест 7: Только min и max элементы (без других)
TEST(RemoveMinMaxTest, OnlyMinMaxElements) {
    // Arrange
    int size = 4;
    int* arr = new int[size] {1, 1, 9, 9};
    
    // Act
    removeMinMax(arr, size);
    
    // Assert - все удаляются
    EXPECT_EQ(size, 0);
    EXPECT_EQ(arr, nullptr);
}

// Тест 8: Проверка сохранения порядка элементов
TEST(RemoveMinMaxTest, PreserveElementOrder) {
    // Arrange
    int size = 7;
    int* arr = new int[size] {5, 1, 3, 9, 2, 1, 4};
    
    // Act
    removeMinMax(arr, size);
    
    // Assert - порядок должен сохраниться: 5, 3, 2, 4
    EXPECT_EQ(size, 4);
    if (size >= 4) {
        EXPECT_EQ(arr[0], 5);
        EXPECT_EQ(arr[1], 3);
        EXPECT_EQ(arr[2], 2);
        EXPECT_EQ(arr[3], 4);
    }
    
    delete[] arr;
}

// Тесты для вспомогательных функций
TEST(UtilityFunctionsTest, FindMin) {
    int arr1[] = {5, 2, 8, 1, 9};
    EXPECT_EQ(findMin(arr1, 5), 1);
    
    int arr2[] = {-5, -2, -8, -1};
    EXPECT_EQ(findMin(arr2, 4), -8);
    
    int arr3[] = {42};
    EXPECT_EQ(findMin(arr3, 1), 42);
}

TEST(UtilityFunctionsTest, FindMax) {
    int arr1[] = {5, 2, 8, 1, 9};
    EXPECT_EQ(findMax(arr1, 5), 9);
    
    int arr2[] = {-5, -2, -8, -1};
    EXPECT_EQ(findMax(arr2, 4), -1);
    
    int arr3[] = {42};
    EXPECT_EQ(findMax(arr3, 1), 42);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}