/*
    Author: Vineet
    This code implements a server which will read the messages from the message queue 
    and then append a text to that recieved message and reutrn it back to the client
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
    struct sembuf v;
    buffer buff;
    int msgid;
    int result;
    
    //key for msgQ
    key_t key = ftok("client", 65);
    if(key < 0){
        perror("ftok");
    }
    // key for semaphore
    key_t semKey = ftok("client_sem", 120);
    if(semKey < 0){
        perror("semKey");
    }


    id = msgget(key, PERMISSIONS);
    if(id < 0){
        perror("msgget");
    }
    int semid = semget(semKey, 4, PERMISSIONS);
    if(semid < 0){
        perror("semget");
    }

    ssize_t size = msgrcv(id, &buff, sizeof(buff.msg), 4, 0);
        if(size < 0){
            perror("msgrcv");
        }
        printf("Sent by Client; %s\n", buff.msg);
        msgid = buff.id;
        char msg[size + 1];
        strncpy(msg, buff.msg, size);
        msg[size] = '\0';

        printf("msg = %s\n", msg);

        strcat(msg, " - Zupa");
        buff.id = msgid;
        strcpy(buff.msg, msg);
        if(msgsnd(id, &buff, sizeof(buff.msg), 0) < 0)
        {
            perror("msgsnd server");
        }
        result = semctl(semid, 2, SETVAL, 1);

    
    return 0;
}