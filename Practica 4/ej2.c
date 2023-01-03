// PRACTICA 4 · Alberto García Doménech

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

// ej2 Practica 4 
int main(int argc, char*argv[]){
    int p_h[2];
    int h_p[2];
    if(pipe(h_p) == -1){perror("Error abriendo tuberia h_p\n");return -1;}
    if(pipe(p_h) == -1){perror("Error abriendo tuberia p_h\n");return -1;}
    if(fork() == 0){//hijo
        close(p_h[1]); //cerramos escritura pipe padre a hijo
        close(h_p[0]); //cerramos lectura pipe hijo a padre
        int numMssg = 0;
        while(numMssg < 10){
            char mensaje[200];
            char c;
            c =  'l';
            if(read(p_h[0],mensaje,200) == -1) {perror("Error leyendo en p_h\n");}
            printf("Mensaje num %d: %s\n",numMssg+1, mensaje);
            sleep(1);
            c = (numMssg < 10) ? 'l' : 'q';
            if(write(h_p[1],&c,1) == -1) {perror("Error escritura h_p\n");}
            numMssg++;
        }
        close(p_h[1]);
        close(h_p[0]);

    }
    else{//padre
        close(p_h[0]);//cerramos lectura pipe padre a hijo
        close(h_p[1]);//cerramos escritura pipe hijo a padre
        char c[1] = "l";
        char mensaje[200] = "";
        scanf("%s", mensaje);
        if(write(p_h[1],mensaje,strlen(mensaje)) == -1){perror("Error escritura p_h\n");}
        if(read(h_p[0],c,1) == -1){perror("Error lectura h_p\n");}
        while(c[0] != 'q'){
            scanf("%s", mensaje);
            write(p_h[1],mensaje,strlen(mensaje));
            read(h_p[0],c,1);            
        }
        close(p_h[1]);
        close(h_p[0]);

    }
    printf("Procedimiento finalizado\n");

    return 0;
}