#include <stdio.h>

#define MAX_SIZE 100

// Function with arguments to test renaming
int add(int first_arg, int second_arg) {
    return first_arg + second_arg;
}

int g_global = 10; // Should not be renamed
static int s_internal = 99; // Should be renamed to something like 'a' in global scope map

int main() {
    int local_var = 42;
    int accumulator = 0;
    
    // Test scope shadowing
    {
        int local_var = 100; // Shadowed variable
        accumulator += local_var;
        printf("Inner local: %d\n", local_var);
    }
    
    accumulator += local_var;
    
    // Complex expression
    int result = add(local_var, g_global);
    
    char *str = "Do not rename local_var inside string";
    
    printf("Result: %d, Accumulator: %d\n", result, accumulator);
    
    return 0;
}
