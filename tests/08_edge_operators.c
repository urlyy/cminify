#include <stdio.h>

// Edge case: Operators and whitespace handling
// Test that removing whitespace doesn't change operator semantics

int main() {
    int a = 10;
    int b = 20;
    int result = 0;
    
    // Test 1: Increment/Decrement with spaces
    // a ++ should become a++ when minified (not a ++)
    a = 5;
    result = a++;
    printf("Post-increment: %d\n", result);
    
    // Test 2: Pre-increment
    a = 5;
    result = ++a;
    printf("Pre-increment: %d\n", result);
    
    // Test 3: Multiple operators
    a = 10;
    result = a + + + + b;  // a + (+ (+ (+ b))) = 10 + 20 = 30
    printf("Multiple plus: %d\n", result);
    
    // Test 4: Minus minus
    a = 10;
    b = 5;
    result = a - - b;  // a - (-b) = 10 - (-5) = 15
    printf("Minus minus: %d\n", result);
    
    // Test 5: Arrow operator
    struct Point {
        int x;
        int y;
    } p;
    struct Point *ptr = &p;
    ptr->x = 100;
    result = ptr->x;
    printf("Arrow operator: %d\n", result);
    
    // Test 6: Conditional operator
    a = 10;
    result = (a > 5) ? 100 : 200;
    printf("Conditional: %d\n", result);
    
    // Test 7: Bitwise operators
    a = 5;  // 101
    b = 3;  // 011
    result = a & b;  // 001 = 1
    printf("Bitwise AND: %d\n", result);
    
    result = a | b;  // 111 = 7
    printf("Bitwise OR: %d\n", result);
    
    result = a ^ b;  // 110 = 6
    printf("Bitwise XOR: %d\n", result);
    
    // Test 8: Shift operators
    a = 8;
    result = a << 2;  // 32
    printf("Left shift: %d\n", result);
    
    result = a >> 1;  // 4
    printf("Right shift: %d\n", result);
    
    // Test 9: Comma operator
    a = 0;
    result = (a = 5, a + 10);  // 15
    printf("Comma operator: %d\n", result);
    
    // Test 10: Sizeof operator
    result = sizeof(int);
    printf("Sizeof: %d\n", result);
    
    return 0;
}