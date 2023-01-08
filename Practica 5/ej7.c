// PRACTICA 5 · Alberto García Doménech

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <stdbool.h>
#include <sys/wait.h>


// ej7 Practica 5

#define BUF_SIZE 500
int main(int argc, char *argv[]){
    struct addrinfo hints;
    struct addrinfo *result;
    int sfd, s;
    size_t len;
    ssize_t nread;
    char buf[BUF_SIZE];
    if(argc != 3){
        perror("Num arg incorrecto\n");
        exit(EXIT_FAILURE);
    }
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    s = getaddrinfo(argv[1],argv[2],&hints,&result);
    if(s != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    sfd = socket(result->ai_family, result->ai_socktype,0);
    if (sfd == -1){
        perror("Error socket\n");
        exit(EXIT_FAILURE);
    }
    s = connect(sfd,result->ai_addr,result->ai_addrlen);
    if(s == -1){
        perror("Error bind\n");
        exit(EXIT_FAILURE);
    }
    while(1){
        nread = read(0,buf,sizeof(buf));
        if(nread == 2 && buf[0] == 'Q'){
            close(sfd);
            exit(0);
        }
        send(sfd,buf,nread,0);
        recv(sfd,buf,nread,0);
        buf[nread] = '\0';
        printf("%s\n",buf);
    }
    close(sfd);
    return 0;
}

