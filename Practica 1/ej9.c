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

// ej9 Practica 1
int main(){
    printf("UID real: %d\nUID efectivo: %d\n",getuid(), geteuid());
return 0;
}