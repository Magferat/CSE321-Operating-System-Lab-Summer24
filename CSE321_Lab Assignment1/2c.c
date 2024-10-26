#include <stdio.h>
#include <string.h>
#include <ctype.h>

void check_pass(char password[]);

int main() {
    char password[100];

    printf("Enter the password: ");
    scanf("%s", password);

    check_pass(password);

    return 0;
}

void check_pass(char password[]) {

    int digit = 0, upper = 0, lower = 0, special = 0;

    for (int i = 0; i < strlen(password); i++) {
        if (islower(password[i]))lower = 1;
        if (isupper(password[i]))upper = 1;
        if (isdigit(password[i]))digit = 1;
        if (strchr("_$#@", password[i]))special = 1;
    }

    if (digit && lower && upper && special) printf("OK ");
    else {
        if (!digit) printf("Digit missing, ");
        if (!upper) {
            printf("Uppercase character missing, ");
        }
        if (!lower) {
            printf("Lowercase character missing, ");
        }
        if (!special) {
            printf("Special character missing, ");
        }
    }
}
