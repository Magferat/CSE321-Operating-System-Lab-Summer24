#include <stdio.h>
#include <string.h>

int main() {
    char given[100];

    printf("Enter a string: ");
    scanf("%s", given);

    int len = strlen(given);
    char right_s[len];
    int k = 0;

    for (int j = len - 1; j >= 0; j--) {
        right_s[k] = given[j];
        k++;
    }

    if (strcmp(given, right_s) == 0) {
        printf("palindrome\n", given);
    } else {
        printf("not a palindrome.\n", given);
    }

    return 0;
}
