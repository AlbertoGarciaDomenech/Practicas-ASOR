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

//ej5 Practica 1
int main(){
struct utsname buf;
if(uname(&buf) == 0){
    printf("Sysname: %s\nNodename: %s\nRelease: %s\nVersion: %s\nMachine: %s\n",buf.sysname,buf.nodename,buf.release,buf.version,buf.machine);
}
return 0;
}