#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    printf("Enter a, b: ");
    scanf("%d %d", &a, &b);

    if (a > b) {
        printf("%d\n", a - b);
    } else if (a < b) {
        printf("%d\n", a + b);
    } else {
        printf("%d\n", a * b);
    }

    return 0;
}

