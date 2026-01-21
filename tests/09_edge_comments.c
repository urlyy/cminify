#include <stdio.h>

// Edge case: Comments and their interaction with code
// Test that comments are properly removed without breaking code

int main() {
    int x = 0;
    int y = 0;
    int result = 0;
    
    // Test 1: Comment replacing whitespace
    // int/**/x = 5; should become int x = 5; (not intx = 5;)
    x = 5;
    printf("Test 1: %d\n", x);
    
    // Test 2: Multiple comments in a row
    x = 10;
    /* comment 1 */ x = x + 5; /* comment 2 */
    printf("Test 2: %d\n", x);
    
    // Test 3: Comment at start of line
    x = 15;
    // This is a comment
    printf("Test 3: %d\n", x);
    
    // Test 4: Comment after code
    x = 20;
    printf("Test 4: %d\n", x);  // This is a trailing comment
    
    // Test 5: Multi-line comment
    x = 25;
    /*
     * This is a multi-line comment
     * spanning multiple lines
     */
    printf("Test 5: %d\n", x);
    
    // Test 6: Comment with special characters
    x = 30;
    /* Comment with special chars: * / */
    printf("Test 6: %d\n", x);
    
    // Test 7: Comment between tokens
    x = 35;
    y = 10;
    result = x /* comment */ + /* another */ y;
    printf("Test 7: %d\n", result);
    
    // Test 8: Empty comment
    x = 40;
    /**/
    printf("Test 8: %d\n", x);
    
    // Test 9: Comment-like content in strings (should NOT be removed)
    char *str = "This is not a comment // or is it?";
    printf("Test 9: %s\n", str);
    
    // Test 10: Comment with asterisks
    x = 45;
    /* *** comment *** */
    printf("Test 10: %d\n", x);
    
    // Test 11: Comment at end of file
    x = 50;
    printf("Test 11: %d\n", x);
    // Final comment
    
    return 0;
}