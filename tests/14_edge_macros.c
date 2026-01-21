#include <stdio.h>

// Edge case: Complex macro definitions and usage
// Test that macros are preserved and not interfered with by renaming

#define SQUARE(x) ((x) * (x))
#define MAX3(a, b, c) ((a) > (b) ? ((a) > (c) ? (a) : (c)) : ((b) > (c) ? (b) : (c)))
#define STR(x) #x
#define CONCAT(a, b) a##b
#define PRINT_INT(x) printf("Value: %d\n", x)
#define IF(cond) if(cond)

// Macro with local variable-like names (should NOT be renamed)
#define SWAP(a, b) do { int temp = (a); (a) = (b); (b) = temp; } while(0)

// Macro that looks like a function
#define MIN(x, y) ((x) < (y) ? (x) : (y))

int main() {
    int x = 0;
    int y = 0;
    int result = 0;
    
    // Test 1: Simple macro
    x = 5;
    result = SQUARE(x);
    printf("Test 1: %d\n", result);
    
    // Test 2: Macro with expression
    result = SQUARE(x + 1);
    printf("Test 2: %d\n", result);
    
    // Test 3: Macro with multiple parameters
    result = MAX3(10, 20, 15);
    printf("Test 3: %d\n", result);
    
    // Test 4: Stringification macro
    printf("Test 4: %s\n", STR(Hello));
    
    // Test 5: Token concatenation macro
    int var1 = 100;
    int var2 = 200;
    printf("Test 5: %d %d\n", var1, var2);
    
    // Test 6: Macro as statement
    PRINT_INT(42);
    
    // Test 7: Macro with control flow
    x = 10;
    IF(x > 5) {
        printf("Test 7: x is greater than 5\n");
    }
    
    // Test 8: Macro with do-while(0) pattern
    x = 10;
    y = 20;
    SWAP(x, y);
    printf("Test 8: x=%d, y=%d\n", x, y);
    
    // Test 9: Nested macro calls
    result = SQUARE(SQUARE(2));
    printf("Test 9: %d\n", result);
    
    // Test 10: Macro with MIN function
    result = MIN(10, 20);
    printf("Test 10: %d\n", result);
    
    // Test 11: Macro with side effects (should evaluate twice)
    x = 5;
    result = SQUARE(x++);
    printf("Test 11: result=%d, x=%d\n", result, x);
    
    // Test 12: Macro in expression
    x = 3;
    y = 4;
    result = SQUARE(x) + SQUARE(y);
    printf("Test 12: %d\n", result);
    
    // Test 13: Macro with comparison
    x = 10;
    y = 20;
    result = (x > y) ? x : y;
    printf("Test 13: %d\n", result);
    
    // Test 14: Multiple SWAP calls
    int a = 1, b = 2, c = 3;
    SWAP(a, b);
    SWAP(b, c);
    printf("Test 14: a=%d, b=%d, c=%d\n", a, b, c);
    
    // Test 15: Macro with complex expression
    result = MAX3(SQUARE(3), SQUARE(4), SQUARE(5));
    printf("Test 15: %d\n", result);
    
    // Test 16: Macro used in conditional
    x = 15;
    if (MAX3(x, 10, 20) > 10) {
        printf("Test 16: Max is greater than 10\n");
    }
    
    // Test 17: Macro with local variables (names should not be renamed)
    x = 100;
    y = 200;
    SWAP(x, y);
    printf("Test 17: x=%d, y=%d\n", x, y);
    
    // Test 18: Macro in loop
    for (x = 0; x < 3; x++) {
        printf("Test 18: %d\n", SQUARE(x));
    }
    
    // Test 19: Macro with array
    int arr[3] = {1, 2, 3};
    result = SQUARE(arr[0]);
    printf("Test 19: %d\n", result);
    
    // Test 20: Macro with pointer
    int *ptr = &x;
    x = 5;
    result = SQUARE(*ptr);
    printf("Test 20: %d\n", result);
    
    return 0;
}