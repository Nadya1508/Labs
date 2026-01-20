#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H

double** createMatrix(int rows, int cols);

void deleteMatrix(double** matrix, int rows);

void reverseMatrix(double** matrix, int rows, int cols);

int countZeroElements(double** matrix, int rows, int cols);

#endif