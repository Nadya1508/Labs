#include <gtest/gtest.h>
#include "matrix_functions.h"

class MatrixTest : public ::testing::Test {
protected:
    void SetUp() override {
        matrix2x2 = createMatrix(2, 2);
        matrix2x2[0][0] = 1.1;
        matrix2x2[0][1] = 2.2;
        matrix2x2[1][0] = 3.3;
        matrix2x2[1][1] = 4.4;
        
        matrix3x3 = createMatrix(3, 3);
        matrix3x3[0][0] = 1.0;
        matrix3x3[0][1] = 0.0;  
        matrix3x3[0][2] = 3.0;
        matrix3x3[1][0] = 4.0;
        matrix3x3[1][1] = 5.0;
        matrix3x3[1][2] = 0.0;  
        matrix3x3[2][0] = 7.0;
        matrix3x3[2][1] = 8.0;
        matrix3x3[2][2] = 9.0;
        
        matrix1x1 = createMatrix(1, 1);
        matrix1x1[0][0] = 0.0;  
        
        matrix2x3 = createMatrix(2, 3);
        matrix2x3[0][0] = 1.0;
        matrix2x3[0][1] = 0.0;  
        matrix2x3[0][2] = 3.0;
        matrix2x3[1][0] = 0.0;  
        matrix2x3[1][1] = 5.0;
        matrix2x3[1][2] = 6.0;
    }
    
    void TearDown() override {
        if (matrix2x2) deleteMatrix(matrix2x2, 2);
        if (matrix3x3) deleteMatrix(matrix3x3, 3);
        if (matrix1x1) deleteMatrix(matrix1x1, 1);
        if (matrix2x3) deleteMatrix(matrix2x3, 2);
    }
    
    double** matrix2x2 = nullptr;
    double** matrix3x3 = nullptr;
    double** matrix1x1 = nullptr;
    double** matrix2x3 = nullptr;
};

TEST_F(MatrixTest, CreateMatrixValidDimensions) {
    double** testMatrix = createMatrix(2, 3);
    ASSERT_NE(testMatrix, nullptr);
    deleteMatrix(testMatrix, 2);
}

TEST_F(MatrixTest, CountZeroElementsNoZeros) {
    EXPECT_EQ(countZeroElements(matrix2x2, 2, 2), 0);
}

TEST_F(MatrixTest, CountZeroElementsWithZeros) {
    EXPECT_EQ(countZeroElements(matrix3x3, 3, 3), 2);
}

TEST_F(MatrixTest, ReverseMatrixSquare) {
    reverseMatrix(matrix2x2, 2, 2);
    
    EXPECT_DOUBLE_EQ(matrix2x2[0][0], 4.4);
    EXPECT_DOUBLE_EQ(matrix2x2[0][1], 3.3);
    EXPECT_DOUBLE_EQ(matrix2x2[1][0], 2.2);
    EXPECT_DOUBLE_EQ(matrix2x2[1][1], 1.1);
}

TEST_F(MatrixTest, SingleElementMatrix) {
    EXPECT_EQ(countZeroElements(matrix1x1, 1, 1), 1);
    
    reverseMatrix(matrix1x1, 1, 1);
    EXPECT_DOUBLE_EQ(matrix1x1[0][0], 0.0);
}

TEST_F(MatrixTest, AllZeroElements) {
    double** allZeros = createMatrix(2, 2);
    allZeros[0][0] = 0.0; allZeros[0][1] = 0.0;
    allZeros[1][0] = 0.0; allZeros[1][1] = 0.0;
    
    EXPECT_EQ(countZeroElements(allZeros, 2, 2), 4);
    
    reverseMatrix(allZeros, 2, 2);
    EXPECT_DOUBLE_EQ(allZeros[0][0], 0.0);
    EXPECT_DOUBLE_EQ(allZeros[1][1], 0.0);
    
    deleteMatrix(allZeros, 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}