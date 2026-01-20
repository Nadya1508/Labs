#include <gtest/gtest.h>
#include "array_functions.h"

class ArrayProcessingTest : public ::testing::Test {
protected:
    void SetUp() override {
        testArray = new int*[3];
        for(int i = 0; i < 3; i++) {
            testArray[i] = new int[3];
        }
        
        testArray[0][0] = 1; testArray[0][1] = 3; testArray[0][2] = 5;  
        testArray[1][0] = 2; testArray[1][1] = 7; testArray[1][2] = 4;  
        testArray[2][0] = 6; testArray[2][1] = 9; testArray[2][2] = 8;  
    }
    
    void TearDown() override {
        for(int i = 0; i < 3; i++) {
            delete[] testArray[i];
        }
        delete[] testArray;
    }
    
    int** testArray;
};

TEST_F(ArrayProcessingTest, BasicInputTest) {
    int resultSize = 0;
    int* result = createFilteredArray(testArray, 3, 3, resultSize);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(resultSize, 3);
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 7);
    EXPECT_EQ(result[2], 9);
    
    double average = calculateAverage(result, resultSize);
    EXPECT_DOUBLE_EQ(average, (3.0 + 7.0 + 9.0) / 3.0);
    
    freeMemory(result);
}

TEST_F(ArrayProcessingTest, NoMatchingElementsTest) {
    int** testArray2 = new int*[2];
    for(int i = 0; i < 2; i++) {
        testArray2[i] = new int[2];
    }
    
    testArray2[0][0] = 1; testArray2[0][1] = 2;  
    testArray2[1][0] = 3; testArray2[1][1] = 4;  
    
    int resultSize = 0;
    int* result = createFilteredArray(testArray2, 2, 2, resultSize);
    
    EXPECT_EQ(resultSize, 0);
    EXPECT_EQ(result, nullptr);
    
    freeMemory(testArray2, 2);
}

TEST_F(ArrayProcessingTest, AllElementsMatchTest) {
    int** testArray3 = new int*[2];
    for(int i = 0; i < 2; i++) {
        testArray3[i] = new int[2];
    }
    
    testArray3[0][0] = 1; testArray3[0][1] = 3;  
    testArray3[1][0] = 5; testArray3[1][1] = 7;  
    
    int resultSize = 0;
    int* result = createFilteredArray(testArray3, 2, 2, resultSize);
    
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(resultSize, 2);
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 7);
    
    freeMemory(result);
    freeMemory(testArray3, 2);
}

TEST(CalculateAverageTest, AverageCalculation) {
    int testArray[] = {1, 3, 5, 7};
    double average = calculateAverage(testArray, 4);
    EXPECT_DOUBLE_EQ(average, 4.0);
    
    double emptyAverage = calculateAverage(nullptr, 0);
    EXPECT_DOUBLE_EQ(emptyAverage, 0.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}