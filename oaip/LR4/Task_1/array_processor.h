#ifndef ARRAY_PROCESSOR_H
#define ARRAY_PROCESSOR_H

// Прототипы функций
int* inputArray(int& size);
void printArray(int* arr, int size);
int findMin(int* arr, int size);
int findMax(int* arr, int size);
void removeMinMax(int*& arr, int& size);
int safeInput();

#endif