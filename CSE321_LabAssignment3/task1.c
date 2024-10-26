#include <stdio.h>       
#include <stdlib.h>      
#include <string.h>      
#include <unistd.h>      
#include <sys/types.h>  
#include <sys/shm.h>     
#include <sys/ipc.h>     
#include <sys/wait.h>   

struct shared {
    char sel[100];  
    int b;          
};

int main() {
    
    int pipe_fds[2];
    char message[100];

    if (pipe(pipe_fds) == -1) {
	printf("Error");

    }

    int shm_id;
    struct shared *shared_mem;

    shm_id = shmget((key_t)101, sizeof(struct shared), 0666 | IPC_CREAT);
    
    
    shared_mem = (struct shared *)shmat(shm_id, NULL, 0);
   
    shared_mem->b = 1000; 

    printf("Provide Your Input From Given Options:\n1. Type a to Add Money\n2. Type w to Withdraw Money\n3. Type c to Check Balance\n");
    

    char user_selection[100];
    
    scanf("%s", user_selection);
    printf("Your selection: %s\n", user_selection);
    strcpy(shared_mem->sel, user_selection); 

    pid_t pid = fork();

    if (pid == 0) {

        close(pipe_fds[0]); 

        struct shared *child_shared_mem;
        child_shared_mem = (struct shared *)shmat(shm_id, NULL, 0);
        
        
        char selection[100];
        int amount;
        strcpy(selection, child_shared_mem->sel);

        if (strcmp(selection, "a") == 0) {        
            printf("Enter amount to be added:\n");
            scanf("%d", &amount); 
            
            if (amount > 0) {
            
                child_shared_mem->b += amount;
                printf("Balance added successfully\nUpdated balance after addition:\n%d\n", child_shared_mem->b);
            } 
            
            else printf("Adding failed, Invalid amount\n");  
        } 
        else if (strcmp(selection, "w") == 0) {
            printf("Enter amount to be withdrawn:\n");
            scanf("%d", &amount); 
            
            if (amount > 0 && amount <= child_shared_mem->b) {
            
                child_shared_mem->b -= amount; 
                printf("Balance withdrawn successfully\nUpdated balance after withdrawal:\n%d\n", child_shared_mem->b);
            } 
            
            else printf("Withdrawal failed, Invalid amount\n");
        } 
        else if (strcmp(selection, "c") == 0) printf("Current balance:\n%d\n", child_shared_mem->b);  
        
        else printf("Invalid selection\n"); 
    

        strcpy(message, "Thank you for using.\n"); 
        write(pipe_fds[1], message, strlen(message) + 1); 
        close(pipe_fds[1]); 
        

    } 
    else {

        int status;
        wait(&status); 

        close(pipe_fds[1]);
        read(pipe_fds[0], message, sizeof(message));
        
        printf("%s", message); 
        close(pipe_fds[0]); 
        

        
    }

    return 0; 
}

