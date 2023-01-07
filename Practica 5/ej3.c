// PRACTICA 5 · Alberto García Doménech

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>

// ej3 Practica 5 
#define BUF_SIZE 500
int main(int argc, char *argv[]){
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;
    size_t len;
    ssize_t nread;
    char buf[BUF_SIZE];
    if(argc != 4){
        perror("Num arg incorrecto\n");
        exit(EXIT_FAILURE);
    }
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    s = getaddrinfo(argv[1],argv[2],&hints,&rp);
    if(s != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    sfd = socket(rp->ai_family, rp->ai_socktype,0);
    if (sfd == -1){
        perror("Error socket\n");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_storage server_addr;
    socklen_t server_len = sizeof(struct sockaddr_storage);
    sendto(sfd,argv[3],2,0,(struct sockaddr *) rp->ai_addr,rp->ai_addrlen);

    nread = recvfrom(sfd,buf,BUF_SIZE,0,(struct sockaddr*) &argv, &server_len);
    if (nread == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    buf[nread] = '\0';
    printf("Received %ld bytes: %s\n", (long) nread, buf);
    
    exit(EXIT_SUCCESS);


    return 0;
}