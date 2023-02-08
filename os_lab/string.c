#include <stdio.h>
#include <string.h>


int
main() {
    char* s = "abc";
    char a[12] = "abdc";
    // s[0] = 'X';
    printf("%s \n %ld \n", a, strlen(a));
}