#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *convert(void *str) {

    char* name = (char*)str;
    int *n = malloc(4);
    int sum = 0;
    
    for (int i = 0; i < strlen(name); i++) {
        sum += name[i];
    }
    *n = sum;
    return (void*)n;
}

int main() {

    char user1[50], user2[50], user3[50];
    scanf("%s %s %s", user1, user2, user3);
    
    pthread_t pt_id1, pt_id2, pt_id3;
    
    pthread_create(&pt_id1, NULL, convert, user1);
    pthread_create(&pt_id2, NULL, convert, user2);
    pthread_create(&pt_id3, NULL, convert, user3);
    

    int *p1, *p2, *p3;
    pthread_join(pt_id1, (void**)&p1);
    pthread_join(pt_id2, (void**)&p2);
    pthread_join(pt_id3, (void**)&p3);
    

    // if (*p1 == *p2 and *p1 == *p3) printf("Youreka\n");
    if (*p1 == *p2 && *p1 == *p3) printf("Youreka\n");
    
    else if (*p1 == *p2 || *p1 == *p3 || *p2 == *p3) printf("Miracle\n");
    
    else printf("Hasta la vista\n");
    
    

    free(p1);
    free(p2);
    free(p3);
    
    return 0;
}

