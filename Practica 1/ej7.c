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

//ej7 Practica 1
int main(){
    //primer arg de pathconf es la ruta o fichero(abierto), con "." le pasamos el dir actual
    printf("Maximo de enlaces: %d\nMaximo tam ruta: %d\nMaximo tam nombre fichero: %d\n",pathconf(".",_PC_LINK_MAX),pathconf(".",_PC_PATH_MAX),pathconf(".",_SC_OPEN_MAX));
    return 0;
}
