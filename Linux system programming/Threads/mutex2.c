#include "header.h"

int globData = 0;
pthread_mutex_t lock1, lock2;


void *thread1_func(void *args){
    pthread_mutex_lock(&lock1);
    printf("lock1 aquired\n");
    sleep(2);
    pthread_mutex_unlock(&lock1);
    pthread_mutex_lock(&lock2);
    printf("lock2 aquired\n");
    pthread_mutex_unlock(&lock2);
    sleep(2);
    return NULL;
}
void *thread2_func(void *args){
    pthread_mutex_lock(&lock2);
    printf("lock2 aquired\n");
    sleep(2);
    pthread_mutex_unlock(&lock2);
    pthread_mutex_lock(&lock1);
    printf("lock1 aquired\n");
    sleep(2);
    pthread_mutex_unlock(&lock1);
    return NULL;
}
int main(){

    pthread_t t1, t2;
    int s;
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    s = pthread_create(&t1, NULL, thread1_func, NULL);
    if(s != 0){
        perror("pthread_create_thread1");
    }
    s = pthread_create(&t2, NULL, thread2_func, NULL);
    if(s != 0){
        perror("pthread_create_thread2");
    }
    
    s = pthread_join(t1, NULL);
    if(s != 0){
        perror("join1");
    }
    s = pthread_join(t2, NULL);
    if(s != 0){
        perror("join2");
    }
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    printf("%d\n", globData);
    

}