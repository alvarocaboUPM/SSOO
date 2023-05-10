#include <stdio.h>	/* setbuf, printf */
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //PID operations

/*
Escribir un programa que cree N procesos hijo, tomando N del primer 
argumento de la línea de mandato. 
Cada pareja de hijos consecutivos i e i+1 se deben comunicar entre sí con un pipe
unidireccional hijo i --> hijo i+1. 
El último hijo debe comunicarse mediante pipe unidireccional con
el primer hijo (último hijo → primer hijo)
*/
int main(int argc, char *argv[]){
    int pid,ent,sal,i,n;
    char c;
    int pp[2];
    n= atoi(argv[1]);

    if (pipe(pp) < 0){
            perror("Error al crear el pipe\n");
            return 0;
            }
            
    ent = pp[0];
    sal = pp[1];
    write(sal, &c, 1); /* se escribe el testigo en el primer pipe */
    
    for(i=0; i<n; i++){
        if (i != n-1)
            if (pipe(pp) < 0){
            perror("Error al crear el pipe\n");
            return 0;
            }

        pid = fork();
        switch(pid){
        case -1: /* error */
            perror("Error en el fork \n");
            return 0;
        case 0: 
            /* proceso hijo */
            if (i != n-1){
                close(sal);
                sal = dup (pp[1]);
                close(pp[0]);
                close(pp[1]);
                printf("Leido en hijo n%i\n",i);
                }
            i = n;
            break;
        default:
            /* proceso padre */
            if (i == n-1) 
               /* último proceso */
                return 0;
            else{
                close(ent);
                close(pp[1]);
                ent = pp[0];
            }
            printf("Escrito en padre n%i\n",i);
            break;
            }
    }
}