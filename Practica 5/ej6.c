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

//ej6 Practica 5

#define BUF_SIZE 500

int main(int argc, char *argv[]){
   struct addrinfo hints;
   struct addrinfo *result;
   int sfd, s;
   //Declarar variable clisd
   int clisd;
   struct sockaddr_storage peer_addr;
   socklen_t peer_addr_len;
   char buf[BUF_SIZE];

    // Numero de argumentos = 3 -> recibimos puerto y host por arg
   if (argc != 3) {
       fprintf(stderr, "Usage: %s port\n", argv[0]);
       exit(EXIT_FAILURE);
   }
   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
   hints.ai_socktype = SOCK_STREAM; /* Datagram socket */ //CAMBIAR A SOCK_STREAM PARA TCP
   hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

   s = getaddrinfo(argv[1], argv[2], &hints, &result);
   if (s != 0) {
       fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
       exit(EXIT_FAILURE);
   }
   sfd = socket(result->ai_family, result->ai_socktype,0);
   if(sfd == -1){
       perror("Error socket\n");   
   }
   s = bind(sfd, result->ai_addr, result->ai_addrlen);
   if(s == -1){
       perror("errro bind\n");
       exit(EXIT_FAILURE);
   }
    s  = listen(sfd,5);
    if(s == -1){
        perror("Error listen\n");
        exit(EXIT_FAILURE);
    }
    while(1){
        char host[NI_MAXHOST], serv[NI_MAXSERV];
        peer_addr_len = sizeof(struct sockaddr_storage);
        //CAMBIAR RECVFROM A ACCEPT
        clisd = accept(sfd,(struct sockaddr *) &peer_addr, &peer_addr_len);
        if(clisd == -1){
            perror("Error accept\n");
            exit(EXIT_FAILURE);
        }
        s = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len,host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
        if(s==0){
            printf("Connected with %s\n",host);
        }
        else{
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
        }
        ssize_t c;
        while(c = recv(clisd,buf,BUF_SIZE,0)){
            send(clisd,buf,c,0);
        }
        if(close(clisd) == -1){
            perror("Error close clisd\n");
        }
        printf("Conexion finalizada\n");
   }  
   if(close(sfd) == -1){
       perror("Error close sfd\n");
   }
   printf("FIN\n");
   return 0;
}