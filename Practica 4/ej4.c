// PRACTICA 4 · Alberto García Doménech

//ej4 Practica 4

int main(int argc, char *argv[]){
    int fd = open("tuberiaNombre",O_WRONLY);
    int i = 0;
    write(fd,argv[1],strlen(argv[1]));
    close(fd);
    return 0;
}