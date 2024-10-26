#include <pthread.h>   
#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#define MAX 10 // producers and consumers can produce and consume upto MAX
#define BUFLEN 7 
#define NUMTHREAD 2      /* number of threads */
void *consumer(void *id);
void *producer(void *id);

char buffer[BUFLEN];
char source[BUFLEN]; // from this array producer will store it's production into buffer
int pCount = 0;
int cCount = 0;
int buflen;


// initializing pthread mutex and condition variables

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty  = PTHREAD_COND_INITIALIZER;
pthread_cond_t full  = PTHREAD_COND_INITIALIZER;
int thread_id[NUMTHREAD]  = {0, 1};
int i = 0; 
int j = 0;

int main() 
{
   
    int i;
    /* define the type to be pthread */
    pthread_t thread[NUMTHREAD];

    strcpy(source, "abcdef"); 
    buflen = strlen(source);
    /* create 2 threads*/
    /* create one consumer and one producer */
    /* define the properties of multi threads for both threads  */
    //Write Code Here

    pthread_create(&thread[0], NULL, producer, (void *)&thread_id[0]);
    pthread_create(&thread[1], NULL, consumer, (void *)&thread_id[1]);


    for (i = 0; i < NUMTHREAD; i++) {
        pthread_join(thread[i], NULL);
    }

    return 0;
}

void *producer(void *id) 
{

    /*
   1. Producer stores the values in the buffer (Here copies values from source[] to buffer[]).
   2. Use mutex and thread communication (wait(), sleep() etc.) for the critical section.
   3. Print which producer is storing which values using which thread inside the critical section.
   4. Producer can produce up to MAX
   */
   //Write code here


    while (i < MAX) {
        pthread_mutex_lock(&count_mutex);
        
        while ((pCount + 1) % BUFLEN == cCount) {
            pthread_cond_wait(&full, &count_mutex);
        }

        char product = source[i % buflen];
        buffer[pCount % BUFLEN] = product;
        printf("%d produced  %c  by Thread  %d\n", pCount, product, *(int *)id);
        pCount++;
        pthread_cond_signal(&nonEmpty);
        pthread_mutex_unlock(&count_mutex);
        sleep(1);
        i++; 
    }

}

void *consumer(void *id) 
{
    /*
   1. Consumer takes out the value from the buffer and makes it empty.
   2. Use mutex and thread communication (wait(), sleep() etc.) for critical section
   3. Print which consumer is taking which values using which thread inside the critical section.
   4. Consumer can consume up to MAX
   */
   //Write code here


    while (j < MAX) {
        pthread_mutex_lock(&count_mutex);
        
        while (pCount == cCount) {
            pthread_cond_wait(&nonEmpty, &count_mutex);
        }

        char consumed = buffer[cCount % BUFLEN];
        printf("%d consumed  %c  by Thread  %d\n", cCount, consumed, *(int *)id);
        cCount++;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&count_mutex);
        sleep(1); 
        j++;
    }
}


