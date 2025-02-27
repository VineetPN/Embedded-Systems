#include "header.h"
void * thread1(void *args){
    char *str = (char *)args;
    // while(1){
    //     printf("In thread 1 %s\n", str);
    // }
    printf("In thread 1 %s\n", str);
    sleep(5);
     printf("Exiting thread 1 %s\n", str);
    pthread_exit(0);
}
int main(){
    pthread_t thread;
    int s;
    s = pthread_create(&thread, NULL, thread1, "Byabes");
    if(s != 0){
        perror("pthread_create:");
        return 1;
    }
    // while(1){
    //     printf(" In main thread\n");
    // }
    printf(" In main thread\n");
    sleep(10);
    
}