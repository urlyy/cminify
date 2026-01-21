
#include <stdio.h>

struct Point {
    int x;
    int y;
};

int main() {
    struct Point p;
    p.x = 10;
    p.y = 20;
    
    // Local variable with same name as struct member
    int x = 5;
    
    // Should print 15 (10 + 5)
    // If bug exists: p.x might be renamed to p.a (invalid) or x renamed to a but p.x stays x (correct)
    // Wait, if 'x' is in scope, logic renames 'x' to 'a'.
    // If it incorrectly renames p.x -> p.a, compilation will fail (Point has no member 'a').
    printf("%d\n", p.x + x);
    
    return 0;
}
