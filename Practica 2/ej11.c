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

//ejer 11 Practica 2
int main(int argc, char *argv[]){
    struct stat buf;

    stat(argv[1],&buf);
    if((buf.st_mode & S_IFMT) == S_IFREG){
        char hard[strlen(argv[1])];
        strcpy(hard, argv[1]);
        strcat(hard, ".hard");
        link(argv[1],hard);
        char sym[strlen(argv[1])];
        strcpy(sym,argv[1]);
        strcat(sym,".sym");
        symlink(argv[1],sym);
    }

    return 0;
}