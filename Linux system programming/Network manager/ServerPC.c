#include "header.h"
void error(const char*);

int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "No port number provided. Program terminated\n");
        exit(1);
    }

    int sockfd, newsockfd, portNo, n;
    char buffer[255];

    struct sockaddr_in serv_addr, clien_addr;
    socklen_t clilen; //32 bit data type 

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("Opening socket failed");
    }
    bzero((char*) &serv_addr, sizeof(serv_addr)); //adds the number of zeroes to the string of serv_addr
    portNo = atoi(argv[1]); //argv[1] shall contain the port number
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portNo); //host to network short
    
    if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
        error("binding failed");
    }
    listen(sockfd, 5);
    clilen = sizeof(clien_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &clien_addr, &clilen);
    if(newsockfd < 0){
        error("Accept failed");
    }

    while(1){
        bzero(buffer, 255);
        n = read(newsockfd, buffer, 255);
        if(n < 0){
            error("Error on reading");
        }
        printf("Client: %sI know you missed gym today", buffer);
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);
        n = write(newsockfd, buffer, strlen(buffer));
        if(n < 0){
            error("Error during write");
        }
        if(strcmp("Bye", buffer) == 0){
            break;
        }
    }
    close(newsockfd);
    close(sockfd);
    return 0;

}

void error(const char* msg){
    perror(msg);
    exit(1);
}