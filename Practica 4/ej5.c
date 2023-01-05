// PRACTICA 4 · Alberto García Doménech

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>

#define MAX_BUFFER 256

// ej5 Practica 4
int main(int argc, char *argv[]){

    fd_set readfds; //conjunto de descriptores de lectura
    char buf[MAX_BUFFER];
    int readFrom;
    int tuberia1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
    int tuberia2 = open("tuberia2", O_RDONLY | O_NONBLOCK);

    FD_ZERO(&readfds);//limpiamos set
    FD_SET(tuberia1,&readfds);
    FD_SET(tuberia2,&readfds);//añadimos descriptores de las tuberias al set de descriptores de lectura


    while(1){
        readFrom = select(((tuberia1 > tuberia2) ? tuberia1 : tuberia2)+1,&readfds,NULL,NULL,NULL);
        if(readFrom == -1){
            perror("Error seleccionando de las tuberias\n"); return -1;
        }
        else{
            if(FD_ISSET(tuberia1,&readfds)){
                if(read(tuberia1,buf,MAX_BUFFER) == 0){
                    close(tuberia1);
                    tuberia1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
                }
                else{

                    printf("Leido desde tuberia 1\nDatos:\n%s\n",buf);
                }
            }
            else if(FD_ISSET(tuberia2, &readfds)){
                if(read(tuberia2,buf,MAX_BUFFER) == 0){
                close(tuberia2);
                tuberia2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
                }
                else{
                    printf("Leido desde tuberia 2\nDatos:\n%s\n");
                }
            }

        }
    }


    return 0;
}