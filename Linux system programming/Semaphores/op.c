#include "header.h"
int main(void){
    key_t key = ftok("sem1", 68);
    int id;
    struct sembuf v;

    id = semget(key, 5, IPC_CREAT|0666);
    if(id < 0){
        perror("semget");
        return 1;
    }
    printf("id = %d\n", id);
    v.sem_num = 4;
    v.sem_op = -1;
    v.sem_flg = 0;
    printf("Before\n");
    semop(id, &v, 1);
    printf("After\n");
    
}