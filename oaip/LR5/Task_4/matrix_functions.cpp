#include <iostream>
#include "matrix_functions.h"

using namespace std;

double** createMatrix(int rows, int cols) {
    double** matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
    }
    return matrix;
}

void deleteMatrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void reverseMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols / 2; j++) {
            double temp = matrix[i][j];
            matrix[i][j] = matrix[rows - 1 - i][cols - 1 - j];
            matrix[rows - 1 - i][cols - 1 - j] = temp;
        }
    }
    
    if (cols % 2 == 1) {
        int midCol = cols / 2;
        for (int i = 0; i < rows / 2; i++) {
            double temp = matrix[i][midCol];
            matrix[i][midCol] = matrix[rows - 1 - i][midCol];
            matrix[rows - 1 - i][midCol] = temp;
        }
    }
}

int countZeroElements(double** matrix, int rows, int cols) {
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0.0) {
                count++;
            }
        }
    }
    return count;
}