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


// ej4 Practica 5
#define BUF_SIZE 500
int main(int argc, char *argv[]){
    struct addrinfo hints;
    struct addrinfo *result;
    int sfd, s;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t nread;
    int nwrite;
    char buf[BUF_SIZE];
    struct tm *localt;
    time_t t;

    if(argc != 3){
        perror("Num incorrecto de args\n");
        exit(EXIT_FAILURE);
    }
    memset(&hints,0,sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC; //allow ipv4 & ipv6
    hints.ai_socktype = SOCK_DGRAM;//UDP
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(argv[1],argv[2],&hints,&result);
    if(s != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    sfd = socket(result -> ai_family, result->ai_socktype, 0);
    if(sfd == -1){
        perror("Error socket\n");
        exit(EXIT_FAILURE);
    }
    s = bind(sfd, result->ai_addr, result->ai_addrlen);
    if(s == -1){
        perror("Error bind\n");
        exit(EXIT_FAILURE);
    }
    //conexion establecida
    while(1){
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(0,&readfds);
        FD_SET(sfd,&readfds);
        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];
        bool client = false;

        int r = select(sfd + 1, &readfds,NULL,NULL,NULL);//sfd > 0

        if(r == -1){
            perror("Select error\n");
            exit(EXIT_FAILURE);
        }
        if(FD_ISSET(0,&readfds)){
            //read from stdin
            client = false;
            nread = read(0,buf,2);
            buf[1] = '\0';
            if(nread == -1){
                perror("Error read\n");
            }
        }
        else if(FD_ISSET(sfd,&readfds)){
            //read from socket
            client = true;
            peer_addr_len = sizeof(struct sockaddr_storage);
            nread = recvfrom(sfd,buf,BUF_SIZE,0,(struct sockaddr *) &peer_addr, &peer_addr_len);
            if(nread == -1){
                perror("Error recvfrom()\n");
            }
            s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST,serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
            if(s == 0){
                    printf("%ld bytes de %s:%s\n", (long) nread, host, serv);
            }
            else{
                    fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
                }
        }

        t = time(NULL);
        localt = localtime(&t);
            printf("%c",buf[0]);
        switch(buf[0]){
            case 'd':
                nwrite = strftime(buf,BUF_SIZE,"%F", localt);
                if(client){
                    if(sendto(sfd,buf,nwrite,0,(struct sockaddr *) &peer_addr, peer_addr_len) != nwrite){
                        perror("error sendto\n");
                        exit(EXIT_FAILURE);
                    }
                }
                else{
                    printf("%s\n",buf);
                }
                break;
            case 't':
                //nwrite = strftime(buf, sizeof(buf),"%r",localt);
                nwrite = strftime(buf,BUF_SIZE,"%F", localt);
                if(client){
                        if(sendto(sfd,buf,nwrite,0,(struct sockaddr *) &peer_addr, peer_addr_len) != nwrite){
                        perror("error sendto\n");
                        exit(EXIT_FAILURE);
                    }
                else{
                        printf("%s\n",buf);
                }
                }
                break;
            case 'q':
                printf("Cerrando servidor...\n");
                return 0;
                break;
            default:
                printf("Error, comando no reconocido:\n%s\n",buf);
                break;
        }
    }
    if(close(sfd) == -1){
        perror("Error close\n");       
    }
    return 0;
}