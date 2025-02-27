#include "header.h"
typedef struct Manis{
    int id;
    char *item;
}food;
void * thread1_Func(void *args){
    food *f1 = malloc(sizeof(food));
    f1 = (food *)args;
    

    sleep(5);
    return (void*) f1;
}
int main(){
    pthread_t thread;
    int s;
    food *f2;
    food *f1 = malloc(sizeof(food));
    f1->id = 4;
    f1->item = "Paneer Biriyani";
    s = pthread_create(&thread, NULL, thread1_Func, (void*) f1);
    if(s != 0){
        perror("pthread_create:");
        return 1;
    }
    pthread_join(thread, (void**) &f2);
    printf("Item number is = %d and item is %s\n", f2->id, f2->item);
}