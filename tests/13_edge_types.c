#include <stdio.h>

// Edge case: Complex type declarations
// Test that pointers, arrays, and function pointers are handled correctly

// Helper function prototypes for function pointer tests
int add(int a, int b);
int subtract(int a, int b);

int main() {
    int result = 0;
    
    // Test 1: Simple pointer
    int *ptr = NULL;
    int value = 10;
    ptr = &value;
    printf("Test 1: %d\n", *ptr);
    
    // Test 2: Pointer to pointer
    int **ptr_to_ptr = &ptr;
    printf("Test 2: %d\n", **ptr_to_ptr);
    
    // Test 3: Multiple pointers in one declaration
    int *p1;
    int *p2;
    int a = 20;
    int b = 30;
    p1 = &a;
    p2 = &b;
    printf("Test 3: %d %d\n", *p1, *p2);
    
    // Test 4: Const pointer
    const int *const_ptr = &value;
    printf("Test 4: %d\n", *const_ptr);
    
    // Test 5: Array
    int arr[5] = {1, 2, 3, 4, 5};
    printf("Test 5: %d\n", arr[0]);
    
    // Test 6: Array of pointers
    int *arr_of_ptrs[3];
    int x = 10;
    int y = 20;
    int z = 30;
    arr_of_ptrs[0] = &x;
    arr_of_ptrs[1] = &y;
    arr_of_ptrs[2] = &z;
    printf("Test 6: %d\n", *arr_of_ptrs[0]);
    
    // Test 7: Pointer to array
    int (*ptr_to_arr)[5] = &arr;
    printf("Test 7: %d\n", (*ptr_to_arr)[0]);
    
    // Test 8: Function pointer
    int (*func_ptr)(int, int);
    func_ptr = add;
    result = func_ptr(5, 10);
    printf("Test 8: %d\n", result);
    
    // Test 9: Array of function pointers
    int (*func_arr[2])(int, int);
    func_arr[0] = add;
    func_arr[1] = subtract;
    result = func_arr[0](10, 5) + func_arr[1](10, 5);
    printf("Test 9: %d\n", result);
    
    // Test 10: Pointer to function pointer
    int (**ptr_to_func_ptr)(int, int) = &func_ptr;
    result = (*ptr_to_func_ptr)(3, 7);
    printf("Test 10: %d\n", result);
    
    // Test 11: Void pointer
    void *void_ptr = &value;
    printf("Test 11: %d\n", *(int *)void_ptr);
    
    // Test 12: Const pointer vs pointer to const
    int const *ptr_to_const = &value;  // pointer to const int
    int *const const_ptr_to_int = &value;  // const pointer to int
    printf("Test 12: %d %d\n", *ptr_to_const, *const_ptr_to_int);
    
    // Test 13: Multi-dimensional array
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
    printf("Test 13: %d\n", matrix[0][0]);
    
    // Test 14: Pointer to multi-dimensional array
    int (*ptr_to_matrix)[2][3] = &matrix;
    printf("Test 14: %d\n", (*ptr_to_matrix)[0][0]);
    
    // Test 15: Array with const elements
    const int const_arr[3] = {10, 20, 30};
    printf("Test 15: %d\n", const_arr[0]);
    
    // Test 16: Typedef with pointer
    typedef int* IntPtr;
    IntPtr typedef_ptr = &value;
    printf("Test 16: %d\n", *typedef_ptr);
    
    // Test 17: Struct pointer
    struct Point {
        int x;
        int y;
    } point;
    struct Point *point_ptr = &point;
    point_ptr->x = 100;
    printf("Test 17: %d\n", point_ptr->x);
    
    // Test 18: Array of struct pointers
    struct Point *point_ptrs[2];
    struct Point p1 = {10, 20};
    struct Point p2 = {30, 40};
    point_ptrs[0] = &p1;
    point_ptrs[1] = &p2;
    printf("Test 18: %d\n", point_ptrs[0]->x);
    
    // Test 19: Pointer with restrict keyword
    int *restrict restrict_ptr = &value;
    printf("Test 19: %d\n", *restrict_ptr);
    
    // Test 20: Volatile pointer
    volatile int *volatile_ptr = &value;
    printf("Test 20: %d\n", *volatile_ptr);
    
    return 0;
}

// Helper functions for function pointer tests
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}