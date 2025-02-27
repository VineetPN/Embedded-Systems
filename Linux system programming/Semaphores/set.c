#include "header.h"
int main(int argc, char** argv){
    if(argc != 3){
        printf("Wrong input\n");
        return 1;
    }
    key_t key = ftok("Sem1", 68);
    int id;

    id = semget(key, 5, IPC_CREAT|0666);
    if(id < 0){
        perror("semget");
        return 1;
    }
    printf("id = %d\n", id);
    int r;
    r = semctl(id, atoi(argv[1]), SETVAL, atoi(argv[2]));
    if(r < 0){
        perror("semctl");
        return 1;
    }
    printf("Value at %d semaphore = %d\n", atoi(argv[1]), r);
}