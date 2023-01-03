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

// ej13 Practica 3
volatile bool borrar = false;
static void myHandler(int signal){
    if(signal == SIGALRM){
    borrar = true;
    }
    if(signal == SIGUSR1){
        borrar = false;
    }
}
int main(int argc, char *argv[]){
    sigset_t set; //set de señales
    struct sigaction handler;
    sigfillset(&set); //llenado del set de todas las señales y borro las que quiero recibir
    sigdelset(&set,SIGUSR1);//si se recibe se para el borrado
    sigdelset(&set,SIGALRM);//se levanta la señal cuando se acabe el temporizador
    handler.sa_handler = myHandler;
    sigaction(SIGALRM,&handler,NULL);
    sigaction(SIGUSR1,&handler,NULL);

    alarm(atoi(argv[1]));
    sigsuspend(&set);
    if(borrar){
        char rm[3] = "rm ";
        strcat(rm, argv[0]);
        system(rm);
    }
    return 0;
}
