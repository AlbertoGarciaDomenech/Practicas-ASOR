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


// ej5 Practica 5
#define BUF_SIZE 500
#define N_PROC 3
int main(int argc, char *argv[]){
    struct addrinfo hints;
    struct addrinfo *result;
    int sfd, s;
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

    pid_t pid_list[N_PROC];
    int i = 0;
    for(i;i< N_PROC; i++){
        pid_t pid= fork();
        if(pid == 0){
            pid_list[i] == pid;
            while(1){
                char host[NI_MAXHOST];
                char serv[NI_MAXSERV];
                struct sockaddr_storage peer_addr;
                peer_addr_len = sizeof(struct sockaddr_storage);

                nread = recvfrom(sfd,buf,BUF_SIZE,0,(struct sockaddr *) &peer_addr, &peer_addr_len);
                if(nread == -1){
                    perror("Error recvfrom()\n");
                }
                s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST,serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
                if(s == 0){
                    printf("[Proc: %d] %d bytes de %s\n", getpid(), nread, host);      
                }
                else{
                        fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
                    }
                t = time(NULL);
                localt = localtime(&t);
                switch(buf[0]){
                    case 't':
                        nwrite = strftime(buf, BUF_SIZE,"%r",localt);
                        if(sendto(sfd,buf,nwrite,0,(struct sockaddr *) &peer_addr, peer_addr_len) != nwrite){
                            perror("error sendto\n");
                            exit(EXIT_FAILURE);
                        }
                        break;
                    case 'd':
                        nwrite = strftime(buf,BUF_SIZE,"%F", localt);
                        printf("%s",buf);
                        if(sendto(sfd,buf,nwrite,0,(struct sockaddr *) &peer_addr, peer_addr_len) != nwrite){
                            perror("error sendto\n");
                            exit(EXIT_FAILURE);
                        }
                        break;
                    case 'q':
                        printf("Cerrando servidor...\n");
                        return 0;
                        break;
                    default:
                        printf("Error, comando no reconocido%s\n",buf);
                        break;
                }
                
            }

            exit(0);
        }
    }
    for(i = 0; i < N_PROC; i++){
        wait(&pid_list[i]);
    }
    if(close(sfd) == -1){
        perror("Error close\n");

    }
    return 0;
}
