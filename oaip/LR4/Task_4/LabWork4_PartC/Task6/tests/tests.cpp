#include <gtest/gtest.h>
#include "magic_square.h"

// Тест создания магического квадрата 3x3
TEST(MagicSquareTest, Create3x3) {
    MagicSquare square(3);
    EXPECT_TRUE(square.isMagicSquare());
    EXPECT_EQ(square.getMagicSum(), 15);
}

// Тест создания магического квадрата 4x4
TEST(MagicSquareTest, Create4x4) {
    MagicSquare square(4);
    EXPECT_TRUE(square.isMagicSquare());
    EXPECT_EQ(square.getMagicSum(), 34);
}

// Тест создания магического квадрата 5x5
TEST(MagicSquareTest, Create5x5) {
    MagicSquare square(5);
    EXPECT_TRUE(square.isMagicSquare());
    EXPECT_EQ(square.getMagicSum(), 65);
}

// Тест магической суммы
TEST(MagicSquareTest, MagicSum) {
    MagicSquare square(3);
    int expected_sum = 3 * (3 * 3 + 1) / 2;
    EXPECT_EQ(square.getMagicSum(), expected_sum);
}

// Тест размера
TEST(MagicSquareTest, Size) {
    MagicSquare square(7);
    EXPECT_EQ(square.getSize(), 7);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}