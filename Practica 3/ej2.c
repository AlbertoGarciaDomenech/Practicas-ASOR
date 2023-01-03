// PRACTICA 3 · Alberto García Doménech

#include <unistd.h>
#include <sys/resource.h>
#include <stdio.h>
#include <sched.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdbool.h>

// ej2 Practica 3
int main(){

    char *policy;
    int prioProces = getpriority(PRIO_PROCESS,0);
    int poliProces = sched_getscheduler(getpid());

    policy = (poliProces == SCHED_RR) ? "SCHED_RR" : ((poliProces == SCHED_FIFO) ? "SHCED_FIFO" : "SCHED_OTHER");

    printf("%d\n%s\nMin/Max(%d,%d)\n",prioProces,policy,sched_get_priority_min(poliProces),sched_get_priority_max(poliProces));
    return 0;
}
