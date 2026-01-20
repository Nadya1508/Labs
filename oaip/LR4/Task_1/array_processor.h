#ifndef ARRAY_PROCESSOR_H
#define ARRAY_PROCESSOR_H

const int MAX_SIZE = 100; 


void inputArray(int arr[], int& size);
void printArray(const int arr[], int size);
void removeMinMax(int arr[], int& size);
int findMin(const int arr[], int size);
int findMax(const int arr[], int size);


int safeInput();
void showContextMenu();
void showInstructions();

#endif