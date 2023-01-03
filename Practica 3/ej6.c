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

//ej6 Practica 3
int main(){

    if(fork() == 0){ //hijo
    sleep(10);
    setsid();
    chdir("/temp");
    printf("HIJO\nPID: %d\nPPID: %d\nPGID: %d\nSID: %d\n",getpid(),getppid(),getpgrp(),getsid(getpid()));
    // exit(0);
    }
    else{ //padre
    printf("PADRE\nPID: %d\nPPID: %d\nPGID: %d\nSID: %d\n",getpid(),getppid(),getpgrp(),getsid(getpid()));

    }

    return 0;
}
