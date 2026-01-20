#include "../include/lib_array_check.h"
#include <cmath>
#include <iostream>

bool check_cos_positive_recursive(double* array, int start, int end) {
    if (array == nullptr) {
        return false;
    }
    
    if (start < 0 || end < 0 || start > end) {
        return false;
    }
    
    int length = end - start + 1;
      
    if (length == 1) {
        return cos(array[start]) > 0;
    }
    if (length == 2) {
        return (cos(array[start]) > 0) && (cos(array[end]) > 0);
    }
    
    int split_index = start + length / 3;
    
    bool first_third = check_cos_positive_recursive(array, start, split_index - 1);
    bool remaining_part = check_cos_positive_recursive(array, split_index, end);
    
    return first_third && remaining_part;
}

bool check_all_cos_positive(double* array, int n) {
    if (n <= 0 || array == nullptr) {
        return false;
    }
    return check_cos_positive_recursive(array, 0, n - 1);
}