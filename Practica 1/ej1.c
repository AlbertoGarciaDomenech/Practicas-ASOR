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

// ej 1&2 Practica 1
int main(){
if(setuid(0) == -1){
    printf("Error %d: %s\n",errno,strerror(errno));

    switch(errno){
        case EAGAIN:
            perror("EAGAIN The uid does not match the current uid and  uid  brings  process over its RLIMIT_NPROC resource limit.\n");
              break;
        case EPERM:
            perror("EPERM  The  user is not privileged (Linux: does not have the CAP_SETUID capability) and uid does not match the real UID  or  saved  set- user-ID of the calling process\n");
              break;
        default:
        perror("NO");
    }
}
else{
    printf("todo bien mi pana\n");
}

return 1;
}