/*
Aim: Child 1 should read 5 bytes of data and child 2 should read 5 bytes of data and parent should send 10 bytes of data
until the child one is reading bytes of data the child 2 mutex should be locked.
*/
#include "header.h"
#include "pthread.h"

pthread_mutex_t lock;

int main(){
    char str[10] = "1234567890";
    int fd[2];
    int s;

    s = pipe(fd);
    //fd[0] -> read end file desc.
    //fd[1] -> write end file desc.

    if(fork() == 0){
        //child 1
        char strchld1[5];
        pthread_mutex_lock(&lock);
            int s1 = read(fd[0], strchld1, sizeof(strchld1));
            if(s1 < 0){
                perror("read1");
            }
        pthread_mutex_unlock(&lock);
        printf("%s\n", strchld1);
    }
    else{
        //parent
        int s3 = write(fd[1], str, sizeof(str));
        if(s3 < 0){
            perror("write");
        }
        if(fork() == 0){
            char strchld2[5];
            //child2
            pthread_mutex_lock(&lock);
            int s2 = read(fd[0], strchld2, sizeof(strchld2));
            if(s2 < 0){
                perror("read2");
            }
            pthread_mutex_unlock(&lock);
            printf("%s\n", strchld2);
        }
        else{
            //parent
        }
    }
}