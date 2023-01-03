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

//ej5 Practica 3
int main(){
    printf("PID: %d\nPPID: %d\nPGID: %d\nSID: %d\n",getpid(),getppid(),getpgrp(),getsid(getpid()));
    return 0;
}
