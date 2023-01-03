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

// ejer17 Practica 2
int main(int argc, char *argv[]){
    char directory[strlen(argv[1])];
    struct stat buf;
    struct dirent *entry;
    strcpy(directory,argv[1]);
    int size =0;
    stat(directory,&buf);
    if(S_ISDIR(buf.st_mode)){
        DIR *dir = opendir(directory);
        if(dir == NULL){
            perror("error abriendo dir\n");
            return -1;
        }
        while(entry = readdir(dir)){
            char pathname[strlen(directory) + 1 + strlen(entry->d_name)];
            strcpy(pathname, directory);
            strcat(pathname,"/");
            strcat(pathname,entry->d_name);
            // printf(pathname);
            if(lstat(pathname,&buf) == -1){
                perror("error");
            }
            else{
                if(S_ISDIR(buf.st_mode)){printf("%s/\n",entry->d_name);}
                else{
                    size += buf.st_size;
                    if(S_ISREG(buf.st_mode)){
                        printf(pathname);
                        if(buf.st_mode & S_IXUSR || buf.st_mode & S_IXGRP || buf.st_mode & S_IXOTH){
                        printf("*",pathname);
                        }
                        printf("\n");
                    }
                    if(S_ISLNK(buf.st_mode)){
                        char cLink[50];
                        readlink(pathname,cLink,100);
                        printf("%s -> %s \n",pathname, cLink);
                    }
                }
            }
        }
        printf("Tamano total de ficheros: %d kb\n", size/1000);
        close(directory);
    }

    return 0;
}