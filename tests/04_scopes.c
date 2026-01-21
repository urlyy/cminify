#include <stdio.h>

int global = 1;

int main() {
    int x = 1;
    printf("Outer: %d\n", x);
    {
        int x = 2; // Shadow
        printf("Inner 1: %d\n", x);
        {
            int x = 3; // Shadow again
            printf("Inner 2: %d\n", x);
        }
    }
    printf("Outer Again: %d\n", x);
    return 0;
}
