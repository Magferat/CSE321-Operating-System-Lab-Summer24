#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<pthread.h>


int count=1;

void* open_th(void* p){
    for(int i=1;i<=5;i++)
    {
        printf("thread-%d prints %d\n",* (int*)p+1,count);
        count++;
    }
    pthread_exit(NULL);
    


}
int main(){

    pthread_t threads[5];
    int i; 
    for(i=0;i<5;i++){
        pthread_create(&threads[i],NULL,open_th,&i);
        pthread_join(threads[i],NULL);
    }
    return 0;
}
