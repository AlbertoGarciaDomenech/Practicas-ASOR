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

// ej14 Practica 1
int main(){
    time_t tiempo = time(NULL);
    struct tm *ano = localtime(&tiempo);
    printf("Ano actual: %d\n",ano->tm_year + 1900);
    return 0;
}
