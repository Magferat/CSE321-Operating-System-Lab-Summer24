#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
/*
This program provides a possible solution using mutex and semaphore.
use 5 Farmers and 5 ShopOwners to demonstrate the solution.
*/

#define MaxCrops 5 // Maximum crops a Farmer can produce or a Shopowner can take
#define warehouseSize 5 // Size of the warehouse
sem_t empty;
sem_t full;
int in = 0;
int out = 0;
char crops[warehouseSize] = {'R', 'W', 'P', 'S', 'M'}; // indicating room for different crops
char warehouse[warehouseSize] = {'N', 'N', 'N', 'N', 'N'}; // initially all the room is empty

pthread_mutex_t mutex;

void condition(int id, const char* role) {
    pthread_mutex_lock(&mutex);
    printf("%s%d: ", role, id);
    for (int j = 0; j < warehouseSize; j++) {
        printf("%c", warehouse[j]);
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
}

void *Farmer(void *far) {
    
     /*
    1.Farmer harvest crops and put them in particular room. For example, room 0 for Rice(R).
    2.use mutex and semaphore for critical section.
    3.print which farmer is keeping which crops in which room inside the critical section.
    4.print the whole warehouse buffer outside of the critical section
   */

    int farmerId = *((int *)far);
    for (int i = 0; i < MaxCrops; i++) {
        char crop = crops[i % 5]; 
        sem_wait(&empty); 
        pthread_mutex_lock(&mutex); 
        warehouse[in] = crop;
        printf("Farmer %d: Insert crops %c at %d\n", farmerId, crop, in);
        in = (in + 1) % warehouseSize;

        pthread_mutex_unlock(&mutex); 
        sem_post(&full);
    }

    condition(farmerId, "Farmer");
}

void *ShopOwner(void *sho) {
    /*
   1.Shop owner takes crops and makes that particular room empty.
   2.use mutex and semaphore for critical section.
   3.print which shop owner is taking which crops from which room inside the critical section.
   4.print the whole warehouse buffer outside of the critical section
   */

    int shopOwnerId = *((int *)sho);
    for (int i = 0; i < MaxCrops; i++) {
        sem_wait(&full); 
        pthread_mutex_lock(&mutex); 

        char crop = warehouse[out];
        printf("Shop owner %d: Remove crops %c from %d\n", shopOwnerId, crop, out);
        warehouse[out] = 'N'; 
        out = (out + 1) % warehouseSize; 

        pthread_mutex_unlock(&mutex); 
        sem_post(&empty); 
    }

    condition(shopOwnerId, "ShopOwner");
}

int main() {
    /*initializing thread,mutex,semaphore
    */
    pthread_t Far[5], Sho[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, warehouseSize); // When the warehouse is full thread will wait
    sem_init(&full, 0, 0); // When the warehouse is empty thread will wait

    int a[5] = {1, 2, 3, 4, 5}; // Just used for numbering the Farmer and ShopOwner

    /*create 5 thread for Farmer 5 thread for ShopOwner
    -------------------------------------------------
    -------------------------------------------------
    */
    for (int i = 0; i < 5; i++) {
        pthread_create(&Far[i], NULL, Farmer, (void *)&a[i]);
        pthread_create(&Sho[i], NULL, ShopOwner, (void *)&a[i]);
    }


    for (int i = 0; i < 5; i++) {
        pthread_join(Far[i], NULL);
        pthread_join(Sho[i], NULL);
    }

    // Closing or destroying mutex and semaphore
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

