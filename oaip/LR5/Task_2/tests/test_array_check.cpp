#include <gtest/gtest.h>
#include <dlfcn.h>

typedef bool (*check_all_cos_positive_func)(double*, int);

class ArrayCheckTest : public ::testing::Test {
protected:
    void* library_handle;
    check_all_cos_positive_func check_all_cos_positive;
    
    void SetUp() override {
        library_handle = dlopen("./libarraycheck.dylib", RTLD_LAZY);
        ASSERT_TRUE(library_handle != nullptr) << "Ошибка загрузки библиотеки: " << dlerror();
        
        check_all_cos_positive = (check_all_cos_positive_func)dlsym(library_handle, "check_all_cos_positive");
        ASSERT_TRUE(check_all_cos_positive != nullptr) << "Ошибка получения функции: " << dlerror();
    }
    
    void TearDown() override {
        if (library_handle) {
            dlclose(library_handle);
        }
    }
};

TEST_F(ArrayCheckTest, AllPositiveCos) {
    double test_array[] = {0.5, 1.0, 0.8};
    EXPECT_TRUE(check_all_cos_positive(test_array, 3));
}

TEST_F(ArrayCheckTest, SomeNegativeCos) {
    double test_array[] = {0.5, 3.14, 0.8};
    EXPECT_FALSE(check_all_cos_positive(test_array, 3));
}

TEST_F(ArrayCheckTest, SingleElementPositive) {
    double test_array[] = {0.1};
    EXPECT_TRUE(check_all_cos_positive(test_array, 1));
}

TEST_F(ArrayCheckTest, SingleElementNegative) {
    double test_array[] = {3.14};
    EXPECT_FALSE(check_all_cos_positive(test_array, 1));
}

TEST_F(ArrayCheckTest, TwoElementsBothPositive) {
    double test_array[] = {0.5, 1.0};
    EXPECT_TRUE(check_all_cos_positive(test_array, 2));
}

TEST_F(ArrayCheckTest, TwoElementsOneNegative) {
    double test_array[] = {0.5, 3.14};
    EXPECT_FALSE(check_all_cos_positive(test_array, 2));
}

TEST_F(ArrayCheckTest, SizeSixExample) {
    double test_array[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6};
    EXPECT_TRUE(check_all_cos_positive(test_array, 6));
}

TEST_F(ArrayCheckTest, NullArray) {
    EXPECT_FALSE(check_all_cos_positive(nullptr, 5));
}

TEST_F(ArrayCheckTest, ZeroSize) {
    double test_array[] = {0.1};
    EXPECT_FALSE(check_all_cos_positive(test_array, 0));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}