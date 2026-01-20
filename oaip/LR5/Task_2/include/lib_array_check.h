#ifndef LIB_ARRAY_CHECK_H
#define LIB_ARRAY_CHECK_H

#define ARRAY_CHECK_API __attribute__((visibility("default")))

extern "C" {
    ARRAY_CHECK_API bool check_cos_positive_recursive(double* array, int start, int end);
    ARRAY_CHECK_API bool check_all_cos_positive(double* array, int n);
}

#endif