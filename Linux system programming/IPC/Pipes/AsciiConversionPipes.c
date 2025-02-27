#include "header.h"
void Convert2Capital(char out[]){
    int n =  10;
    for(int i = 0; i < n; i++){
        out[i] = out[i] - 32;
    }
}
int main(void){
    int fd1[2];
    int fd2[2];
    char inp[10] = {0};
    char out[10] = {0};

    int retVal1, retVal2;
    retVal1 = pipe(fd1);
    retVal2 = pipe(fd2);

    scanf("%s", inp);
    if(fork() == 0){
        if(read(fd1[0], out, sizeof(out)) < 0) perror("read2");
        printf("%s recvd from the first pipe\n", out);

        Convert2Capital(out);
        if(write(fd2[1], out, strlen(out) + 1) < 0) perror("write1");
        printf("%s is sent via pipe2\n", out);
    }
    else {
        char o[10] = {0};
        if(write(fd1[1], inp, strlen(inp) + 1) < 0) perror("write1");
        printf("%s is sent\n", inp);

        if(read(fd2[0], o, sizeof(o)) < 0) perror("read2");
        printf("%s recvd from the second pipe", o);
        
    }
}