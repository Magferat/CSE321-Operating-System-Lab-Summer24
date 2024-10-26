#include <stdio.h>
#include <math.h>


int check_perfect(int num) {


    int sum = 0;
    int i = 1;


    while (i*i <= num) {
        if (num%i == 0) {
            if (i != num) {
                sum += i;
            }
            if (i != num/i && num/i != num) {
                sum += num/i;
            }
        }
        i = i+1;
    }
    
    if (sum == num) {
        return 1;
    } else {
        return 0;
    }
 
}

int main() {
    int lower_bound, upper_bound;

    printf("lower bound: ");
    scanf("%d", &lower_bound);
    printf("upper bound: ");
    scanf("%d", &upper_bound);

    for (int i = lower_bound; i <= upper_bound; i++) {
        if (check_perfect(i) == 1) printf("%d\n", i);
    }

    return 0;
}

