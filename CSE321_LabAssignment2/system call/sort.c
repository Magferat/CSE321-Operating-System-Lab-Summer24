#include <stdio.h>
#include <stdlib.h>


void swap(int *j1, int *j2);
void bubble_sort(int num[], int n);


int main(int argc, char *argv[]) {

    int n = argc - 1;
    int given[n];

    for (int i = 1; i < argc; i++) {
        given[i - 1] = atoi(argv[i]);
    }
    
    bubble_sort(given, n);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", given[i]);
    }
    printf("\n");

    return 0;
}

void bubble_sort(int num[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (num[j] < num[j + 1]) {
                swap(&num[j], &num[j + 1]);
            }
        }
    }
}

void swap(int *j1, int *j2) {
    int temp = *j1;
    *j1 = *j2;
    *j2 = temp;
}

