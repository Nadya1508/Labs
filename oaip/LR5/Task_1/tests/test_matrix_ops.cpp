#include <gtest/gtest.h>
#include "matrix_ops.h"

TEST(MatrixOperationsTest, MinimumSizeMatrix) {
    MatrixOperations ops(1);
    
    EXPECT_DOUBLE_EQ(ops.getMatrixCValue(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(ops.getMatrixDValue(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(ops.sumMainDiagonalC(), 0.0);
    EXPECT_DOUBLE_EQ(ops.sumSecondaryDiagonalC(), 0.0);
    EXPECT_DOUBLE_EQ(ops.sumMainDiagonalD(), 0.0);
    EXPECT_DOUBLE_EQ(ops.sumSecondaryDiagonalD(), 0.0);
}

TEST(MatrixOperationsTest, BoundaryConditionJ8J9) {
    MatrixOperations ops(10);
    
    EXPECT_DOUBLE_EQ(ops.getMatrixDValue(3, 8), 3*3 + 8*8);
    EXPECT_DOUBLE_EQ(ops.getMatrixDValue(3, 9), (3*3 + 9*9)/2.0);
    
    double sumD_main = ops.sumMainDiagonalD();
    double sumD_secondary = ops.sumSecondaryDiagonalD();
    EXPECT_GT(sumD_main, 0);
    EXPECT_GT(sumD_secondary, 0);
}

TEST(MatrixOperationsTest, Basic3x3Matrix) {
    MatrixOperations ops(3);
    
    EXPECT_NEAR(ops.getMatrixCValue(1, 1), (1.0 + 1.0) / 3.0, 0.0001);
    EXPECT_NEAR(ops.getMatrixCValue(2, 2), (4.0 + 4.0) / 5.0, 0.0001);
    EXPECT_DOUBLE_EQ(ops.getMatrixDValue(1, 1), 1.0 + 1.0);
    EXPECT_DOUBLE_EQ(ops.getMatrixDValue(2, 2), 4.0 + 4.0);
    
    double sumC_main = ops.sumMainDiagonalC();
    double sumD_main = ops.sumMainDiagonalD();
    
    EXPECT_GT(sumC_main, 0);
    EXPECT_GT(sumD_main, 0);
    EXPECT_EQ(ops.getSize(), 3);
}

TEST(MatrixOperationsTest, SizeValidation) {
    EXPECT_TRUE(MatrixOperations::isValidSize(1));
    EXPECT_TRUE(MatrixOperations::isValidSize(500));
    EXPECT_TRUE(MatrixOperations::isValidSize(1000));
    EXPECT_FALSE(MatrixOperations::isValidSize(0));
    EXPECT_FALSE(MatrixOperations::isValidSize(-1));
    EXPECT_FALSE(MatrixOperations::isValidSize(1001));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}