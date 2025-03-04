/*
    Author: Vineet
    This code implements a client which will send a message to the message queue 
    and then gets back the message from the server with some appended text
    This code shows the usage of process synchronization as well to avoid the race conditions.
*/


#include "header.h"
#define PERMISSIONS (0666 | IPC_CREAT)
typedef struct msgBuf
{
    long id; 
    char msg[100];
}buffer;

int main(){
    int id;
    buffer buff;
    struct sembuf v;

    //messageQ
    buff.id = 4;
    strcpy(buff.msg, "This is client 1");
    //key for msgQ
    key_t key = ftok("client", 65);
    if(key < 0){
        perror("ftok");
    }
    //key for sem
    key_t semKey = ftok("client_sem", 120);
    if(semKey < 0){
        perror("ftok");
    }
    id = msgget(key, 0666 | IPC_CREAT);
    if(id < 0){
        perror("msgget");
    }

    if(msgsnd(id, &buff, sizeof(buff.msg), 0) < 0) {
        perror("msgsnd");
    }
    //setval 1
    //check for semop

    int semid = semget(semKey, 4, PERMISSIONS);
    if(semid < 0){
        perror("semget");
    }

    //semaphore
    v.sem_num = 2;
    v.sem_op = -1;
    v.sem_flg = 0;
    semop(semid, &v, 1);
    ssize_t size = msgrcv(id, &buff, sizeof(buff.msg), 4, 0);
    if(size < 0){
        perror("msgrcv");
    }
    printf("returned msg = %s\n", buff.msg);
    return 0;
}