// PRACTICA 4 · Alberto García Doménech

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>


// ej1 Practica 4
int main(int argc, char *argv[]){
    if(argc != 5){
        perror("Error en num de argumentos\n");
        return -1;
    }
    int fd[2];
    pipe(fd);
    if(fork() == 0){ //hijo
    close(fd[1]);
    dup2(fd[0],0);
    char *args[] = {argv[3],argv[4],NULL};
    execvp(argv[3],args);
    close(fd[0]);
    } 
    else{ //padre
    close(fd[0]);
    dup2(fd[1],1);
    char *args[]={argv[1],argv[2],NULL};
    execvp(argv[1],args);
    close(fd[1]);
    }
    return 0;
}
