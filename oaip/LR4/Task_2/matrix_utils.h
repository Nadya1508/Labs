#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

const int M = 5;
const int N = 5;

void showContextMenu();
int safeInputInt(const char* prompt);
void initializeArray(int arr[M][N]);
void printArray(const char* title, int arr[M][N]);
int findMinAboveDiagonal(int arr[M][N]);
void printAboveDiagonal(int arr[M][N]);
void printDiagonalInfo(int arr[M][N]);
void processTask();
bool showMainMenu();

#endif