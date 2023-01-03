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

//ej6 Practica 1
int main(){
    printf("Maximo de argumentos: %d\nMaximo hijos: %d\nMaximo ficheros abiertos: %d\n",sysconf(_SC_ARG_MAX),sysconf(_SC_CHILD_MAX),sysconf(_SC_OPEN_MAX));
    return 0;
}