#include <stdio.h>

// Edge case: Preprocessor directives
// Test that preprocessor directives are handled correctly

#define VALUE 100
#define ADD(x, y) ((x) + (y))
#define MULTI_LINE \
    This is a \
    multi-line macro

#ifdef VALUE
    #define DEFINED 1
#else
    #define DEFINED 0
#endif

#ifndef UNDEFINED
    #define NOT_DEFINED 1
#endif

#if DEFINED
    #define CONDITIONAL 1
#else
    #define CONDITIONAL 0
#endif

#if VALUE > 50
    #define BIG_VALUE 1
#else
    #define BIG_VALUE 0
#endif

#undef VALUE
#ifdef VALUE
    #define VALUE_UNDEFINED 0
#else
    #define VALUE_UNDEFINED 1
#endif

#define VALUE 200

#pragma GCC diagnostic ignored "-Wunused-variable"

int main() {
    int x = 0;
    int result = 0;
    
    // Test 1: Simple macro
    x = VALUE;
    printf("Test 1: %d\n", x);
    
    // Test 2: Macro with arguments
    result = ADD(10, 20);
    printf("Test 2: %d\n", result);
    
    // Test 3: Nested macro usage
    result = ADD(VALUE, 50);
    printf("Test 3: %d\n", result);
    
    // Test 4: Conditional compilation
    x = DEFINED;
    printf("Test 4: %d\n", x);
    
    // Test 5: #ifndef
    x = NOT_DEFINED;
    printf("Test 5: %d\n", x);
    
    // Test 6: #if with expression
    x = CONDITIONAL;
    printf("Test 6: %d\n", x);
    
    // Test 7: #if with comparison
    x = BIG_VALUE;
    printf("Test 7: %d\n", x);
    
    // Test 8: Line continuation in macro
    // Note: MULTI_LINE is just a string, not executable
    printf("Test 8: Macro defined\n");
    
    // Test 9: #undef result
    x = VALUE_UNDEFINED;
    printf("Test 9: %d\n", x);
    
    // Test 10: Redefine
    x = VALUE;
    printf("Test 10: %d\n", x);
    
    // Test 11: Multiple includes (same file)
    // This tests that #include is preserved
    printf("Test 11: Include preserved\n");
    
    // Test 12: #pragma
    int unused_var = 0;
    printf("Test 12: Pragma preserved\n");
    
    // Test 13: #error (commented out to allow compilation)
    // #error This would cause compilation error
    
    // Test 14: #warning (commented out)
    // #warning This is a warning
    
    return 0;
}