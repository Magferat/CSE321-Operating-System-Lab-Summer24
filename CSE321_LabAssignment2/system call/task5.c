#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    pid_t child_pid, g_child_pid1, g_child_pid2, g_child_pid3;

    printf("1. Parent process ID : %d\n", getpid());
    child_pid = fork();
    
    if (child_pid == 0) {

        printf("2. Child process ID : %d\n", getpid());
        g_child_pid1 = fork();
        
        if (g_child_pid1 == 0) {
            printf("3. Grandchild process ID : %d\n", getpid());
            exit(EXIT_SUCCESS);
        }

        g_child_pid2 = fork();
        
        if (g_child_pid2 == 0) {
            printf("4. Grandchild process ID : %d\n", getpid());
            exit(EXIT_SUCCESS);
        }

        g_child_pid3 = fork();
       
        if (g_child_pid3 == 0) {
            printf("5. Grandchild process ID : %d\n", getpid());
            exit(EXIT_SUCCESS);
        }

	
        exit(EXIT_SUCCESS);
    } 

	wait(NULL);
    return 0;
}

