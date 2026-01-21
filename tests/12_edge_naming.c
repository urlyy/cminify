#include <stdio.h>

// Edge case: Variable naming conventions
// Test that various naming styles are handled correctly

int main() {
    int result = 0;
    
    // Test 1: Underscore prefix
    int _private = 10;
    printf("Test 1: %d\n", _private);
    
    // Test 2: Underscore suffix
    int temp_ = 20;
    printf("Test 2: %d\n", temp_);
    
    // Test 3: Multiple underscores
    int __double_underscore__ = 30;
    printf("Test 3: %d\n", __double_underscore__);
    
    // Test 4: All underscores
    int ___ = 40;
    printf("Test 4: %d\n", ___);
    
    // Test 5: Mixed case
    int CamelCase = 50;
    printf("Test 5: %d\n", CamelCase);
    
    // Test 6: snake_case
    int snake_case = 60;
    printf("Test 6: %d\n", snake_case);
    
    // Test 7: Numbers in name
    int var123 = 70;
    printf("Test 7: %d\n", var123);
    
    // Test 8: Leading underscore with number
    int _123var = 80;
    printf("Test 8: %d\n", _123var);
    
    // Test 9: Very long name
    int this_is_a_very_long_variable_name_that_should_be_renamed_to_something_shorter = 90;
    printf("Test 9: %d\n", this_is_a_very_long_variable_name_that_should_be_renamed_to_something_shorter);
    
    // Test 10: Single character names (should remain or be renamed consistently)
    int x = 100;
    int y = 200;
    result = x + y;
    printf("Test 10: %d\n", result);
    
    // Test 11: Names that look like keywords but aren't
    int integer = 110;
    printf("Test 11: %d\n", integer);
    
    // Test 12: Names with Hungarian notation
    int iCount = 120;
    printf("Test 12: %d\n", iCount);
    
    // Test 13: Names with double underscore in middle
    int middle__underscore = 130;
    printf("Test 13: %d\n", middle__underscore);
    
    // Test 14: Uppercase with underscores (constant style)
    int CONSTANT_VALUE = 140;
    printf("Test 14: %d\n", CONSTANT_VALUE);
    
    // Test 15: Function with long parameter names
    int add_numbers(int first_number, int second_number) {
        return first_number + second_number;
    }
    result = add_numbers(10, 20);
    printf("Test 15: %d\n", result);
    
    // Test 16: Variable name starting with underscore and capital
    int _Capital = 150;
    printf("Test 16: %d\n", _Capital);
    
    // Test 17: Variable with many consecutive underscores
    int many____underscores = 160;
    printf("Test 17: %d\n", many____underscores);
    
    // Test 18: Scoped variable with underscore prefix
    {
        int _local = 170;
        printf("Test 18: %d\n", _local);
    }
    
    // Test 19: Similar names that shouldn't conflict
    int variable = 180;
    int variable_ = 190;
    int _variable = 200;
    printf("Test 19: %d %d %d\n", variable, variable_, _variable);
    
    // Test 20: Names with digits at end
    int var1 = 210;
    int var2 = 220;
    result = var1 + var2;
    printf("Test 20: %d\n", result);
    
    return 0;
}