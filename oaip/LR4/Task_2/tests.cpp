#include <gtest/gtest.h>
#include <stdexcept>
#include "matrix_utils.h"

TEST(FindMinAboveDiagonalTest, MinAtBeginning) {
    int matrix[M][N] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };
    int result = findMinAboveDiagonal(matrix);
    EXPECT_EQ(result, 2);
}

TEST(FindMinAboveDiagonalTest, MinInMiddle) {
    int matrix[M][N] = {
        {10, 15, 20, 25, 30},
        {35, 10, 7, 18, 22},    // Минимум выше диагонали = 7 (элемент [1][2])
        {40, 45, 8, 16, 21},
        {50, 55, 60, 11, 19},
        {65, 70, 75, 80, 9}
    };
    int result = findMinAboveDiagonal(matrix);
    EXPECT_EQ(result, 7);
}

TEST(FindMinAboveDiagonalTest, AllElementsSame) {
    int matrix[M][N] = {
        {1, 5, 5, 5, 5},
        {2, 2, 5, 5, 5},
        {3, 3, 3, 5, 5},
        {4, 4, 4, 4, 5},
        {5, 5, 5, 5, 5}
    };
    int result = findMinAboveDiagonal(matrix);
    EXPECT_EQ(result, 5);
}

TEST(FindMinAboveDiagonalTest, NegativeNumbers) {
    int matrix[M][N] = {
        {1, -5, 3, -8, 2},
        {4, 2, -2, 1, 9},
        {6, 8, 3, -1, 5},
        {2, 6, 9, 7, -3},
        {5, 4, 2, 6, 8}
    };
    int result = findMinAboveDiagonal(matrix);
    EXPECT_EQ(result, -8);
}

TEST(FindMinAboveDiagonalTest, MinAtEnd) {
    int matrix[M][N] = {
        {10, 8, 7, 6, 1},      // Минимум выше диагонали = 1 (элемент [0][4])
        {9, 9, 5, 4, 3},
        {8, 7, 8, 3, 2},
        {7, 6, 5, 7, 4},
        {6, 5, 4, 3, 5}
    };
    int result = findMinAboveDiagonal(matrix);
    EXPECT_EQ(result, 1);
}

TEST(FindMinAboveDiagonalTest, OnlyOneElementAboveDiagonal) {
    int matrix[M][N] = {
        {1, 5, 2, 3, 4},      // Элементы выше диагонали: 5, 2, 3, 4, 2, 3, 4, 3, 4, 4
        {1, 2, 2, 3, 4},      // Минимум = 2
        {1, 2, 3, 3, 4},
        {1, 2, 3, 4, 4},
        {1, 2, 3, 4, 5}
    };
    int result = findMinAboveDiagonal(matrix);
    EXPECT_EQ(result, 2);
}

TEST(FindMinAboveDiagonalTest, LargeNumbers) {
    int matrix[M][N] = {
        {1000, 500, 2000, 800, 1200},
        {300, 2000, 700, 1800, 400},
        {600, 900, 3000, 400, 1100},
        {200, 600, 1900, 4000, 300},
        {700, 800, 1200, 1600, 5000}
    };
    int result = findMinAboveDiagonal(matrix);
    EXPECT_EQ(result, 300);
}

TEST(FindMinAboveDiagonalTest, SingleElementAboveDiagonal) {
    int matrix[M][N] = {
        {1, 5, 2, 3, 4},
        {1, 2, 2, 3, 4},
        {1, 2, 3, 3, 4},
        {1, 2, 3, 4, 4},
        {1, 2, 3, 4, 5}
    };
    int result = findMinAboveDiagonal(matrix);
    EXPECT_EQ(result, 2);
}

TEST(FindMinAboveDiagonalTest, AllNegativeAboveDiagonal) {
    int matrix[M][N] = {
        {1, -5, -3, -8, -2},
        {4, 2, -7, -1, -9},
        {6, 8, 3, -4, -6},
        {2, 6, 9, 4, -10},
        {5, 4, 2, 6, 5}
    };
    int result = findMinAboveDiagonal(matrix);
    EXPECT_EQ(result, -10);
}

TEST(FindMinAboveDiagonalTest, MixedPositiveNegative) {
    int matrix[M][N] = {
        {10, -5, 15, -8, 12},
        {4, 20, -2, 18, -7},
        {6, 8, 25, -1, 11},
        {2, 6, 9, 30, -3},
        {5, 4, 2, 6, 35}
    };
    int result = findMinAboveDiagonal(matrix);
    EXPECT_EQ(result, -8);
}

TEST(FindMinAboveDiagonalTest, BoundaryConditions) {
    int matrix[M][N] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };
    int result = findMinAboveDiagonal(matrix);
    EXPECT_EQ(result, 2);
}

TEST(FindMinAboveDiagonalTest, EmptyAboveDiagonal) {
    int matrix[M][N] = {
        {1, 0, 0, 0, 0},
        {0, 2, 0, 0, 0},
        {0, 0, 3, 0, 0},
        {0, 0, 0, 4, 0},
        {0, 0, 0, 0, 5}
    };
    int result = findMinAboveDiagonal(matrix);
    EXPECT_EQ(result, 0);
}

TEST(FindMinAboveDiagonalTest, AllZeros) {
    int matrix[M][N] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    int result = findMinAboveDiagonal(matrix);
    EXPECT_EQ(result, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}