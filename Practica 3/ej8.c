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


//ej8 Practica 3
int main(int argc, char *argv[]) {

    if(fork() == 0){
        sleep(1);
        setsid();
        chdir("/temp");
        int fichSalida = open("/tmp/dameon.out",  O_RDWR | O_CREAT | O_TRUNC, 0666);
        int fichErr = open("/tmp/daemon.err",  O_RDWR | O_CREAT | O_TRUNC, 0666);
        int fichEntr = open("/dev/null/", O_RDWR | O_CREAT | O_TRUNC, 0666);
        dup2(fichSalida,1);
        dup2(fichErr,2);
        dup2(fichEntr,0);
        if (execvp(argv[1],argv + 1) == -1){
            perror("error ejecucion\n");
        }
    }
    else{

    }

    return 0;
}