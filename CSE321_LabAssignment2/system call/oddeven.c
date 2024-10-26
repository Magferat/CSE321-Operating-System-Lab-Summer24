#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int n = argc - 1;
    int arr[n]; 

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]); 
    }
    
    for (int i = 0; i < n; i++) {
        int num = arr[i]; 
        if (num % 2 == 0) printf("%d : even\n", num);
        else printf("%d : odd\n", num);
    }

    return 0;
}

