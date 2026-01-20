#include "matrix_functions.h"

int* createEvenDiagonalArray(int** matrix, int n, int k, int& resultSize) {
    resultSize = 0;
    int minDim = (n < k) ? n : k;
    
    for (int i = 0; i < minDim; i++) {
        if (matrix[i][i] % 2 == 0) {
            resultSize++;
        }
    }
    
    int* resultArray = nullptr;
    if (resultSize > 0) {
        resultArray = new int[resultSize];
        int index = 0;
        for (int i = 0; i < minDim; i++) {
            if (matrix[i][i] % 2 == 0) {
                resultArray[index++] = matrix[i][i];
            }
        }
    }
    
    return resultArray;
}

long long calculateProduct(int* array, int size) {
    if (size == 0 || array == nullptr) {
        return 0;
    }
    
    long long product = 1;
    for (int i = 0; i < size; i++) {
        product *= array[i];
    }
    return product;
}