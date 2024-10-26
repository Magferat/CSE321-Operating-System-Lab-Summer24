#include <stdio.h>
#include <string.h>

int main() {
    char email[100], domain[100];
    char *pointer;
    char old_d[] = "@kaaj.com";
    char new_d[] = "@sheba.xyz";

    printf("Email: ");
    scanf("%s", email);

    pointer = strchr(email, '@');
    strcpy(domain, pointer);

    if (strcmp(domain, old_d) == 0) {
        printf("Email address is outdated");
    }
    else if (strcmp(domain, new_d) == 0) {
        printf("Email address is okay");
    }

    return 0;
}
