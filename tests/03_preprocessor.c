#include <stdio.h>

#define PI 3.14159
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#ifdef PI
    #define EXISTS 1
#else
    #define EXISTS 0
#endif

int main() {
    float r = 5.0;
    float area = PI * r * r;
    printf("Area: %f\n", area);
    return 0;
}
