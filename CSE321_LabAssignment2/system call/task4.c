#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>



int main(int argc, char *argv[]) {
   
    int n = argc - 1;
    char *given_num[n];
    for (int i = 0; i <= n ; i++) {
        given_num[i] = argv[i];
    }
    
    given_num[n] = NULL;
    pid_t pid = fork();

    if (pid == 0) execv("./sort", given_num);
    
    else {
        wait(NULL);
        execv("./oddeven", given_num);
    }

    return 0;
}

