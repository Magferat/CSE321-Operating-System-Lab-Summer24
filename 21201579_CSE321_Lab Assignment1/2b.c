#include <stdio.h>
#include <string.h>

int main() {
    FILE *f1_pointer, *f2_pointer;
    char sentence[200];
    char *result_s[100];
    char *word;
    int i = 0;

    f1_pointer = fopen("2b_input.txt", "r");
    f2_pointer = fopen("2b_output.txt", "w");


    fgets(sentence, sizeof(sentence), f1_pointer);

    word = strtok(sentence, " ");
    while (word != NULL) {
        result_s[i] = word;
        word = strtok(NULL, " ");
        i++;
    }

    for (int j = 0; j < i; j++) {

          fprintf(f2_pointer, "%s ", result_s[j]);
    }

    fclose(f1_pointer);
    fclose(f2_pointer);

    return 0;
}
