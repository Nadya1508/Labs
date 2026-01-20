#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H

int** create2DArray(int rows, int cols);
void fillArray(int** array, int rows, int cols);
void printArray(int** array, int rows, int cols);
int* createFilteredArray(int** sourceArray, int rows, int cols, int& resultSize);
double calculateAverage(int* array, int size);
void freeMemory(int** array, int rows);
void freeMemory(int* array);

void showContextMenu();
void clearInputBuffer();
void runProgram();

#endif