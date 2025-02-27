#include "header.h"

int globData = 0;
pthread_mutex_t lock;


void *thread1_func(void *args){
    int locData = 0;
    for(int i = 0; i < 10000; i++){
        pthread_mutex_lock(&lock);
        locData = globData;
        locData++;
        globData = locData;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
void *thread2_func(void *args){
    int locData = 0;
    for(int i = 0; i < 10000; i++){
        pthread_mutex_lock(&lock);
        locData = globData;
        locData++;
        globData = locData;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
int main(){

    pthread_t t1, t2;
    int s;
    pthread_mutex_init(&lock, NULL);

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
    pthread_mutex_destroy(&lock);
    printf("%d\n", globData);
    

}