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

// ej15 Practica 1
int main(){
    time_t tiempo = time(NULL);
    struct tm *ano = localtime(&tiempo);
    char buffer[200];
    strftime(buffer, sizeof(buffer),"%A %d de %B de %Y, %H:%M", ano);
    printf("%s\n",buffer);
    return 0;
}
