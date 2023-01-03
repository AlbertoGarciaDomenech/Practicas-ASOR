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


//ejer15 Practica 2
int main(int argc, char *argv[]){

    char fichero[strlen(argv[1])];
    strcpy(fichero,argv[1]);
    int fd = open(fichero,O_RDWR);
    if((lockf(fd,F_LOCK,0) == 0)){
        printf("esperamos primeros 10 sec. Tiempo actual:%d\n",time(NULL));
        int i = 0;
        for(i;i<10;i++){printf("%d\n",i+1);sleep(1);}
        printf("%d\n",time(NULL));
        lockf(fd,F_ULOCK,0);
        printf("volvemos a esperar 10 sec\n");
        i = 0;
        for(i;i<10;i++){printf("%d\n",i+1);sleep(1);}
        }
    else{
        perror("ERROR cerrojo\n");
    }

    printf("fin\n");


    return 0;
}
