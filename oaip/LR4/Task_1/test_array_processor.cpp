#include <gtest/gtest.h>
#include "array_processor.h"

TEST(ArrayProcessorTest, FindMinMax) {
    int arr[] = {5, 2, 8, 1, 9, 3};
    int size = 6;
    
    EXPECT_EQ(findMin(arr, size), 1);
    EXPECT_EQ(findMax(arr, size), 9);
}

TEST(ArrayProcessorTest, RemoveMinMax) {
    int arr[] = {5, 2, 8, 1, 9, 1, 3, 9}; 
    int size = 8;
    
    removeMinMax(arr, size);
    
    
    EXPECT_EQ(size, 4);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 8);
    EXPECT_EQ(arr[3], 3);
}

TEST(ArrayProcessorTest, RemoveMinMaxCorrect) {
    int arr[] = {4, 1, 7, 1, 9, 9, 3}; 
    int size = 7;
    
    removeMinMax(arr, size);
    
    
    EXPECT_EQ(size, 3);
    EXPECT_EQ(arr[0], 4);
    EXPECT_EQ(arr[1], 7);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayProcessorTest, AllElementsSame) {
    int arr[] = {5, 5, 5, 5};
    int size = 4;
    
    removeMinMax(arr, size);
    
    EXPECT_EQ(size, 0); 
}

TEST(ArrayProcessorTest, EmptyArray) {
    int arr[MAX_SIZE] = {};
    int size = 0;
    
    removeMinMax(arr, size);
    
    EXPECT_EQ(size, 0); 
}

TEST(ArrayProcessorTest, SingleElement) {
    int arr[] = {7};
    int size = 1;
    
    removeMinMax(arr, size);
    
    EXPECT_EQ(size, 0); 
}

TEST(ArrayProcessorTest, OnlyMinAndMax) {
    int arr[] = {1, 10, 1, 10, 1}; 
    int size = 5;
    
    removeMinMax(arr, size);
    
    EXPECT_EQ(size, 0); 
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}