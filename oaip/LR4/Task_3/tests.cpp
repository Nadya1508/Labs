#include <gtest/gtest.h>
#include <cmath>

using namespace std;

double dotProduct(double** matrix, int row1, int row2, int n);
bool isOrthonormal(double** matrix, int n);

double** createTestMatrix(int n, double** source = nullptr) {
    double** matrix = new double*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[n];
        if (source) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = source[i][j];
            }
        }
    }
    return matrix;
}

void deleteTestMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Тест для единичной матрицы (ортогональна и нормирована)
TEST(OrthonormalTest, IdentityMatrix) {
    int n = 3;
    double** matrix = createTestMatrix(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
    
    EXPECT_TRUE(isOrthonormal(matrix, n));
    deleteTestMatrix(matrix, n);
}

// Тест для ортонормированной матрицы поворота
TEST(OrthonormalTest, RotationMatrix) {
    int n = 2;
    double** matrix = createTestMatrix(n);
    
    // Матрица поворота на 45 градусов
    double cos45 = 0.70710678118; 
    double sin45 = 0.70710678118; 
    
    matrix[0][0] = cos45;
    matrix[0][1] = -sin45;
    matrix[1][0] = sin45;
    matrix[1][1] = cos45;
    
    EXPECT_TRUE(isOrthonormal(matrix, n));
    deleteTestMatrix(matrix, n);
}

// Тест для неортогональной матрицы
TEST(OrthonormalTest, NonOrthogonalMatrix) {
    int n = 2;
    double** matrix = createTestMatrix(n);
    
    matrix[0][0] = 1.0;
    matrix[0][1] = 1.0;
    matrix[1][0] = 1.0;
    matrix[1][1] = 1.0;
    
    EXPECT_FALSE(isOrthonormal(matrix, n));
    deleteTestMatrix(matrix, n);
}

// Тест для ненормированной матрицы
TEST(OrthonormalTest, NonNormalizedMatrix) {
    int n = 2;
    double** matrix = createTestMatrix(n);
    
    matrix[0][0] = 2.0;
    matrix[0][1] = 0.0;
    matrix[1][0] = 0.0;
    matrix[1][1] = 2.0;
    
    EXPECT_FALSE(isOrthonormal(matrix, n));
    deleteTestMatrix(matrix, n);
}

// Тест для матрицы с неквадратными размерами (должна работать для любых n)
TEST(OrthonormalTest, LargeIdentityMatrix) {
    int n = 5;
    double** matrix = createTestMatrix(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
    
    EXPECT_TRUE(isOrthonormal(matrix, n));
    deleteTestMatrix(matrix, n);
}

// Тест для функции скалярного произведения
TEST(DotProductTest, BasicTest) {
    int n = 3;
    double** matrix = createTestMatrix(n);
    
    matrix[0][0] = 1.0;
    matrix[0][1] = 2.0;
    matrix[0][2] = 3.0;
    
    matrix[1][0] = 4.0;
    matrix[1][1] = 5.0;
    matrix[1][2] = 6.0;
    
    double dot = dotProduct(matrix, 0, 1, n);
    EXPECT_NEAR(dot, 32.0, 1e-10); // 1*4 + 2*5 + 3*6 = 32
    
    deleteTestMatrix(matrix, n);
}

// Тест для ортогональных но не нормированных векторов
TEST(OrthonormalTest, OrthogonalButNotNormalized) {
    int n = 2;
    double** matrix = createTestMatrix(n);
    
    matrix[0][0] = 2.0;
    matrix[0][1] = 0.0;
    matrix[1][0] = 0.0;
    matrix[1][1] = 3.0;
    
    EXPECT_FALSE(isOrthonormal(matrix, n));
    deleteTestMatrix(matrix, n);
}