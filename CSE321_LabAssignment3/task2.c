#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h> 
#include <sys/shm.h>

struct msg {
    long int type;
    char txt[6];
};


int main() {
    printf("Please enter the workspace name:\n");
    char input[100];
    scanf("%s", input);
    
    if (strcmp(input, "cse321") != 0) printf("Invalid workspace name\n");
    
    else {
        int msg_id;
        struct msg send;
        
        msg_id = msgget((key_t)12, 0666 | IPC_CREAT);
        
        send.type = 2;
        strncpy(send.txt, input, sizeof(send.txt));
        
        msgsnd(msg_id, (void *)&send, sizeof(send.txt), 0);
        printf("Workspace name sent to otp generator from log in: %s\n", send.txt);
        
        pid_t otp = fork();
        if (otp == 0) {
            struct msg received;
            msg_id = msgget((key_t)12, 0666 | IPC_CREAT);
            
            msgrcv(msg_id, (void *)&received, sizeof(received.txt), 2, IPC_NOWAIT);
            printf("OTP generator received workspace name from log in: %s\n", received.txt);
            
            pid_t pid = getpid();
            char store[50];
            struct msg child_write;
            child_write.type = 5;
            sprintf(store, "%d", pid);
            strncpy(child_write.txt, store, sizeof(child_write.txt));
            
            send.type = 8;
            strncpy(send.txt, store, sizeof(send.txt));
            msgsnd(msg_id, (void *)&send, sizeof(send.txt), 0);
            printf("OTP sent to log in from OTP generator: %s\n", send.txt);
            
            msgsnd(msg_id, (void *)&child_write, sizeof(child_write.txt), 0);
            printf("OTP sent to mail from OTP generator: %s\n", child_write.txt);
            
            pid_t mail = fork();
            if (mail == 0) {
                struct msg mailr;
                msg_id = msgget((key_t)12, 0666 | IPC_CREAT);
                
                msgrcv(msg_id, (void *)&mailr, sizeof(mailr.txt), 5, IPC_NOWAIT);
                printf("Mail received OTP from OTP generator: %s\n", mailr.txt);
                
                send.type = 9;
                strncpy(send.txt, store, sizeof(send.txt));
                msgsnd(msg_id, (void *)&send, sizeof(send.txt), 0);
                printf("OTP sent to log in from mail: %s\n", send.txt);
            } 
            else {
                wait(NULL);
            }
        } 
        else {
            wait(NULL);
            
            msgrcv(msg_id, (void *)&send, sizeof(send), 8, IPC_NOWAIT);
            printf("Log in received OTP from OTP generator: %s\n", send.txt);
            char rotp[50];
            strncpy(rotp, send.txt, sizeof(rotp));
            
            msgrcv(msg_id, (void *)&send, sizeof(send), 9, IPC_NOWAIT);
            printf("Log in received OTP from mail: %s\n", send.txt);
            char rmail[50];
            strncpy(rmail, send.txt, sizeof(rmail));
            
            if (strcmp(rotp, rmail) == 0)printf("OTP Verified\n");
            
            else {
                printf("OTP Incorrect\n");
            }
            
            msgctl(msg_id, IPC_RMID, NULL);
        }
    }
    
    return 0;
}

