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

//ej3 Practica 1
int main(){
    int i = 0;
    for(i; i < 255; i++){
        printf("Error %d: %s\n",i,strerror(i));
}
return 0;
}
