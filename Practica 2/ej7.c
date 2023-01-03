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

//ejer7 Practica 2
int main(){
    char *fich = "fichero7.txt";
    umask(0026);
    open(fich,O_CREAT,0676);
    close(fich);
    return 0;
}


