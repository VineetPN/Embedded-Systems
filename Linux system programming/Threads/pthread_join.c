#include "header.h"
void * thread1(void *args){
    char *str = (char *)args;
    // while(1){
    //     printf("In thread 1 %s\n", str);
    // }
    printf("In thread 1 %s\n", str);
    sleep(5);
    return (void *) "Zhang jike";
}
int main(){
    pthread_t thread;
    int s;
    void *res;
    s = pthread_create(&thread, NULL, thread1, "Byabes");
    if(s != 0){
        perror("pthread_create:");
        return 1;
    }
    // while(1){
    //     printf(" In main thread\n");
    // }
    printf(" In main thread\n");
    pthread_join(thread, &res); // blocking function 

    printf("The player name is %s", (char *) res);
    
}