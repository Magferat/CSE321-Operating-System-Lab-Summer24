#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void* open_th(void* arg) {

    int num = *((int*)arg);
    printf("thread-%d running\n", num);
    sleep(1);    
    printf("thread-%d closed\n", num);

}

int main() {

    pthread_t threads[5];
    int th_args[5];
    for (int i = 0; i < 5; i++) {
	    th_args[i] = 1+i;
        pthread_create(&threads[i], NULL, open_th, &th_args[i]) ;
        pthread_join(threads[i], NULL);
        
    }
    
    return 0;
}

