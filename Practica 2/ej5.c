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

//ejer5 Practica 2

int main(){

    if(open("ejercicio5.txt", O_CREAT, 00645) == -1){
        printf("Hubo un error\n");
    }
    else{close("fichero5.txt");}

    return 0;
}

