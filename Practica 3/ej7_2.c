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
//version execvp
int main(int argc, char *argv[]){
    if(argc < 2){
    perror("Insufficient arguments\n");
    return 1;
    }
    execvp(argv[1],argv + 1);
    printf("El comando terminó de ejecutarse\n");
    return 0;
}