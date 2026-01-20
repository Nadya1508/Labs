#include <gtest/gtest.h>
#include "array_utils.h"

TEST(Array3DTest, ConstructorTest) {
    Array3D arr(3);
    EXPECT_EQ(arr.getSize(), 3);
}

TEST(Array3DTest, SetGetTest) {
    Array3D arr(2);
    arr.setValue(0, 0, 0, 42);
    EXPECT_EQ(arr.getValue(0, 0, 0), 42);
}

TEST(Array3DTest, DiagonalSumTest) {
    Array3D arr(2);

    arr.setValue(0, 0, 0, 10);
    arr.setValue(0, 0, 1, 1);
    arr.setValue(0, 1, 0, 2);
    arr.setValue(0, 1, 1, 3);
    arr.setValue(1, 0, 0, 4);
    arr.setValue(1, 0, 1, 5);
    arr.setValue(1, 1, 0, 6);
    arr.setValue(1, 1, 1, 20);

    EXPECT_EQ(arr.findMaxDiagonalSum(), 30);
}

TEST(Array3DTest, SingleElementTest) {
    Array3D arr(1);
    arr.setValue(0, 0, 0, 100);
    EXPECT_EQ(arr.findMaxDiagonalSum(), 100);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}