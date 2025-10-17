#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H


bool isOrthonormal(double** matrix, int n);


double dotProduct(double** matrix, int row1, int row2, int n);

double** createMatrix(int n);


void inputMatrix(double** matrix, int n);


void printMatrix(double** matrix, int n);


void showTaskInfo();


void clearMatrix(double** matrix, int n);

#endif