#include <stdio.h>

int main() {
    char *s1 = "Normal String";
    char *s2 = "String with \"quotes\" inside";
    char *s3 = "String with // comments inside";
    char *s4 = "String with /* multi-line */ inside";
    char *s5 = "String with \
    continued line";
    
    printf("%s\n%s\n%s\n", s1, s2, s3);
    return 0;
}
