// PRACTICA 2 · Alberto García Doménech

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
//ejer12 Practica 2
int main(int argc, char *argv[]){

    char f[strlen(argv[1])];
    strcpy(f,argv[1]);
    int i = 0;
    int fd = open(f,O_RDWR);
    dup2(fd,1);
    for(i;i<10;i++){
        printf("frase %d\n", i);
    }
    close(fd);
    return 0;
}
