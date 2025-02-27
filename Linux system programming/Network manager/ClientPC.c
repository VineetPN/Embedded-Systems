/*
arg[0] -> filename
arg[1] -> IPAddress
arg[2] -> Port number

*/


#include "header.h"

void error(const char*);

int main(int argc, char *argv[]){
    

    if(argc < 3){
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(1);
    }
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    int portNo = atoi(argv[2]);
    char buffer[255];
    int retVal;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNo);
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    while(1){
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);
        send(sockfd, buffer, strlen(buffer), 0);
        if(retVal < 0){
            error("Error during send");
        }
        bzero(buffer, 255);
        retVal = recv(sockfd, buffer, sizeof(buffer), 0);
        if(retVal < 0){
            error("Error during send");
        }
        printf("Server: %s\n", buffer);
        if(strcmp(buffer, "Bye") == 0){
            break;
        }
    }
    
    close(sockfd);
    return 0;


}

void error(const char* msg){
    perror(msg);
    exit(1);
}