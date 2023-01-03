// PRACTICA 1 · Alberto García Doménech

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <time.h>
#include <sys/time.h>

//ej13 Practica 1
int main(){
    int i = 0;
    struct timeval tOriginal, tFinal;
    gettimeofday(&tOriginal,NULL);
    for(i; i < 1000000;i++){
    }
    gettimeofday(&tFinal,NULL);
    printf("tiempo en microsegundos que ha tardado: %d\n", ((tFinal.tv_sec*1000000 + tFinal.tv_usec) - (tOriginal.tv_sec*1000000 + tOriginal.tv_usec)));
    return 0;
}
