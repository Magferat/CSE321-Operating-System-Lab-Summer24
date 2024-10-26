#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 

int main()
{

    pid_t child =fork();
    if(child==0){
        
        pid_t grandchild = fork();
        if(grandchild==0){
            printf("I am grandchild\n");
            exit(EXIT_SUCCESS);
            
        }
        else {
            wait(NULL);
            printf("I am child\n");
            exit(EXIT_SUCCESS);
        }
    }
    else{
        wait(NULL);
        printf("I am parent\n");
    }
    
}
