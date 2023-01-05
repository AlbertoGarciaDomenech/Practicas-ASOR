// PRACTICA 5 · Alberto García Doménech

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

//ej1 Practica 5
int main(int argc, char *argv[]){

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s;

    if(argc != 2){
        perror("Num incorrecto args\n");
        return -1;
    }
    memset(&hints,0,sizeof(struct addrinfo));     //inicializar hints a 0
    hints.ai_family = AF_UNSPEC;
    s = getaddrinfo(argv[1],NULL,&hints,&result);
    if(s!=0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    for(rp = result; rp != NULL; rp = rp->ai_next){
        char buf[NI_MAXHOST];
        getnameinfo(rp->ai_addr,rp->ai_addrlen,buf,sizeof(buf),NULL,0,NI_NUMERICHOST);
        printf("%s\t%d\t%d\n",buf,rp->ai_family,rp->ai_socktype);
    }
    return 0;
}