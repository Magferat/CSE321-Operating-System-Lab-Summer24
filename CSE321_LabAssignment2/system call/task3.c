#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int pipefds[2];
    if (pipe(pipefds) != 0) printf("Pipe erorr");	

    pid_t a, b, c;
    int total = 0;
    pid_t initial_p = getpid();
    write(pipefds[1], &total, sizeof(4));
    

    a = fork();
    b = fork();
    c = fork();
    
    pid_t current_p = getpid();
    printf("Parent : %d, Child : %d\n", getppid(), getpid());
    
    if (current_p != initial_p && current_p % 2 != 0){
        	fork();
        	// printf("inside if, Parent : %d, Child : %d\n", getppid(), getpid());
    }


    read(pipefds[0], &total, sizeof(4));
    total++;
    write(pipefds[1], &total, sizeof(4));
    close(pipefds[1]);

    wait(NULL);
    wait(NULL);
    wait(NULL);
	 
  
  if (getpid() == initial_p){
        read(pipefds[0], &total, sizeof(4));
        close(pipefds[0]);
        printf("Total: %d\n", total);
    }

    return 0;
}


