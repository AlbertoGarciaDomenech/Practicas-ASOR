// PRACTICA 2 · Alberto García Doménech

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

// ejer9 Practica 2
int main(int argc, char *argv[]){

    struct stat buf;
    char *modo;
    char buf1[100000];
    char* directory = getcwd(buf1,sizeof(buf1));
    if(argc == 2){
        strcat(directory,"/");
        strcat(directory, argv[1]);
    }
    int fd = open(argv[1],O_RDONLY);
    fstat(fd,&buf);
    switch(buf.st_mode & S_IFMT) {
        case S_IFSOCK:modo="socket";break;
        case S_IFLNK:modo="Symbolic link";break;
        case S_IFREG:modo="Regular File";break;
        case S_IFBLK:modo="Block device";break;
        case S_IFDIR:modo="Directory";break;
        case S_IFCHR:modo="Character device";break;
        case S_IFIFO:modo="FIFO";break;
    }
    printf("%s\n",modo);
    printf("Major: %d\nMinor: %d\nInodo: %d\nTipo fichero: %s\nHora de ultimo acceso:%s", major(buf.st_dev),minor(buf.st_dev),buf.st_ino,modo,ctime(&buf.st_atime));
    close(fd);

    return 0;
}
