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

// ej7 Practica 3
//version system
int main(int argc, char *argv[]){
    if(argc < 2){
        perror("Insufficient arguments\n");
        return 1;
    }
    char comando[strlen(argv[1])];
    strcpy(comando,argv[1]);
    int i = 2;
    for(i; i < argc; i++){
        strcat(comando, " ");
        strcat(comando, argv[i]);
    }
    system(comando);
    printf("El comando terminó de ejecutarse\n");
    return 0;
}
