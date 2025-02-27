#include "header.h"
int main(){
    key_t key = ftok("write", 65);
    struct sembuf v;
    int id;
    int fd = open("data1", O_WRONLY|O_CREAT|O_APPEND, 0664);
    

    id = semget(key, 5, IPC_CREAT|0664);
    v.sem_num = 1;
    v.sem_op = 0;
    v.sem_flg = 0;

    
    printf("Here I am\n");
    
    for(char ch = 'a'; ch <= 'z'; ch++){
        semop(id, &v, 1);
        semctl(id, 2, SETVAL, 1);
        write(fd, &ch, 1);
        sleep(1);
        semctl(id, 2, SETVAL, 0);
    }
    
    printf("Done\n");


    return 0;
}