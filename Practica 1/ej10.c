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

//ej10 Practica 1
int main(){
    struct passwd *p = getpwuid(getuid());
    printf("UID real: %d\nUID efectivo: %d\n",getuid(), geteuid());
    //nombre usuario, dir home, desc usuario
    printf("Nombre usuario: %s\nDirectorio home: %s\nDescripcion usuario: %s\n",p->pw_name, p->pw_dir, p->pw_gecos );

return 0;
}