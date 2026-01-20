#include <gtest/gtest.h>
#include "matrix_functions.h"
#include <iostream>

using namespace std;

class MatrixTest : public ::testing::Test {
protected:
    void SetUp() override {
        
        matrix3x3 = new int*[3];
        for (int i = 0; i < 3; i++) {
            matrix3x3[i] = new int[3];
        }
        matrix3x3[0][0] = 1; matrix3x3[0][1] = 2; matrix3x3[0][2] = 3;
        matrix3x3[1][0] = 4; matrix3x3[1][1] = 6; matrix3x3[1][2] = 5;
        matrix3x3[2][0] = 7; matrix3x3[2][1] = 8; matrix3x3[2][2] = 10;

        
        matrixNoEven = new int*[2];
        for (int i = 0; i < 2; i++) {
            matrixNoEven[i] = new int[2];
        }
        matrixNoEven[0][0] = 1; matrixNoEven[0][1] = 2;
        matrixNoEven[1][0] = 3; matrixNoEven[1][1] = 5;

        
        matrix2x3 = new int*[2];
        for (int i = 0; i < 2; i++) {
            matrix2x3[i] = new int[3];
        }
        matrix2x3[0][0] = 2; matrix2x3[0][1] = 4; matrix2x3[0][2] = 6;
        matrix2x3[1][0] = 8; matrix2x3[1][1] = 10; matrix2x3[1][2] = 12;
    }

    void TearDown() override {
        for (int i = 0; i < 3; i++) delete[] matrix3x3[i];
        delete[] matrix3x3;
        
        for (int i = 0; i < 2; i++) delete[] matrixNoEven[i];
        delete[] matrixNoEven;
        
        for (int i = 0; i < 2; i++) delete[] matrix2x3[i];
        delete[] matrix2x3;
    }

    int** matrix3x3;
    int** matrixNoEven;
    int** matrix2x3;
};


TEST_F(MatrixTest, BasicInputTest) {
    int size;
    int* result = createEvenDiagonalArray(matrix3x3, 3, 3, size);
    
    EXPECT_EQ(size, 2);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result[0], 6);
    EXPECT_EQ(result[1], 10);
    
    long long product = calculateProduct(result, size);
    EXPECT_EQ(product, 60);
    
    delete[] result;
}


TEST_F(MatrixTest, NoEvenElementsOnDiagonal) {
    int size;
    int* result = createEvenDiagonalArray(matrixNoEven, 2, 2, size);
    
    EXPECT_EQ(size, 0);
    EXPECT_EQ(result, nullptr);
    
    long long product = calculateProduct(result, size);
    EXPECT_EQ(product, 0);
}


TEST_F(MatrixTest, RectangularMatrix) {
    int size;
    int* result = createEvenDiagonalArray(matrix2x3, 2, 3, size);
    
    EXPECT_EQ(size, 2);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 10);
    
    long long product = calculateProduct(result, size);
    EXPECT_EQ(product, 20);
    
    delete[] result;
}


TEST(ProductFunctionTest, SingleElement) {
    int arr[] = {5};
    long long product = calculateProduct(arr, 1);
    EXPECT_EQ(product, 5);
}


TEST(ProductFunctionTest, MultipleElements) {
    int arr[] = {2, 3, 4};
    long long product = calculateProduct(arr, 3);
    EXPECT_EQ(product, 24);
}


TEST(ProductFunctionTest, EmptyArray) {
    int* arr = nullptr;
    long long product = calculateProduct(arr, 0);
    EXPECT_EQ(product, 0);
}


TEST(ProductFunctionTest, WithZeroElement) {
    int arr[] = {2, 0, 4};
    long long product = calculateProduct(arr, 3);
    EXPECT_EQ(product, 0);
}