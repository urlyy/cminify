// Test case: Verify that generated variable names don't conflict with function names
#include <stdio.h>

// Many user-defined functions to test collision avoidance
int func_a() { return 1; }
int func_b() { return 2; }
int func_c() { return 3; }
int func_d() { return 4; }

// Test that local variables won't be named after these functions
int test_function() {
    int var1 = 10;
    int var2 = 20;
    int var3 = 30;
    int var4 = 40;
    int var5 = 50;
    
    // Call the functions
    int result = func_a() + func_b() + func_c() + func_d();
    result += var1 + var2 + var3 + var4 + var5;
    
    return result;
}

int main() {
    int value = test_function();
    printf("Result: %d\n", value);
    return 0;
}
