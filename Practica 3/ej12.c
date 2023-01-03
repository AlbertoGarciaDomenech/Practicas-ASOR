// PRACTICA 3 · Alberto García Doménech

#include <unistd.h>
#include <sys/resource.h>
#include <stdio.h>
#include <sched.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdbool.h>


// ej12 Practica 3
volatile int numInt = 0;
volatile int numTstp = 0;
static void myHandler(int signal){
    if(signal == SIGINT){numInt++;}
    if(signal == SIGTSTP){numTstp++;}
}
int main(){
    struct sigaction sig_handler;
    sig_handler.sa_handler = myHandler;
    if(sigaction(SIGINT, &sig_handler, NULL) == -1){
        perror("sigaction SIGINT error");
    }
    if(sigaction(SIGTSTP, &sig_handler, NULL) == -1){
        perror("sigaction SIGTSTP error");
    }
    while(numInt + numTstp < 10){
        printf("Se han recibido %d SIGINT y %d SIGTSTP\n",numInt,numTstp);
        }
    printf("Numero de SIGINT recibidos : %d\nNumero de SIGTSTP recibidos: %d\n",numInt,numTstp);

    return 0;
}