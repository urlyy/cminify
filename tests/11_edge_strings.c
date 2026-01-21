#include <stdio.h>

// Edge case: Strings and character literals
// Test that string content is preserved and escape sequences are handled correctly

int main() {
    char *str = NULL;
    char ch = 0;
    int len = 0;
    
    // Test 1: Simple string
    str = "Hello, World!";
    printf("Test 1: %s\n", str);
    
    // Test 2: String with escaped quotes
    str = "She said \"Hello\"";
    printf("Test 2: %s\n", str);
    
    // Test 3: String with escaped backslash
    str = "Path: C:\\Users\\test";
    printf("Test 3: %s\n", str);
    
    // Test 4: String with newline escape
    str = "Line1\nLine2";
    printf("Test 4: %s\n", str);
    
    // Test 5: String with tab escape
    str = "Column1\tColumn2";
    printf("Test 5: %s\n", str);
    
    // Test 6: Empty string
    str = "";
    printf("Test 6: '%s'\n", str);
    
    // Test 7: String with special characters
    str = "Special: \a\b\f\r\t\v";
    printf("Test 7: %s\n", str);
    
    // Test 8: Octal escape sequence
    str = "Octal: \101\102\103";  // ABC
    printf("Test 8: %s\n", str);
    
    // Test 9: Hex escape sequence
    str = "Hex: \x41\x42\x43";  // ABC
    printf("Test 9: %s\n", str);
    
    // Test 10: String with question mark escape
    str = "Question: \?";
    printf("Test 10: %s\n", str);
    
    // Test 11: Single quote escape in string
    str = "It\'s a test";
    printf("Test 11: %s\n", str);
    
    // Test 12: Character literal
    ch = 'A';
    printf("Test 12: %c\n", ch);
    
    // Test 13: Character with escape
    ch = '\'';
    printf("Test 13: %c\n", ch);
    
    // Test 14: Character with backslash
    ch = '\\';
    printf("Test 14: %c\n", ch);
    
    // Test 15: Character with newline escape
    ch = '\n';
    printf("Test 15: newline char\n");
    
    // Test 16: String with null character
    str = "Null\0character";
    printf("Test 16: %s\n", str);
    
    // Test 17: String concatenation (adjacent strings)
    str = "Hello" " " "World";
    printf("Test 17: %s\n", str);
    
    // Test 18: String with comment-like content
    str = "This is NOT // a comment";
    printf("Test 18: %s\n", str);
    
    // Test 19: String with multi-line comment-like content
    str = "This is NOT /* a comment */";
    printf("Test 19: %s\n", str);
    
    // Test 20: String with percent signs (for printf)
    str = "Percent: %%";
    printf("Test 20: %s\n", str);
    
    return 0;
}