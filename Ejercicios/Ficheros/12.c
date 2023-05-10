#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <signal.h>
#include <link.h>
#include <fcntl.h>


/*Recorre el dir: /var/spool/works/ y Los envía a otro programa que los ejectuta
-> LANZAR TRABAJO: Escribe un nuevo fichero en el 
dir compartido, que se inspecciona periódicamente

-------PROCESOS DEL PROGRAMA SPOOLER----------
1) Se recorre el dir y se comprueba si hay entradas nuevas
    - El main pone un temporizador que ejecutará esto 1vez/sec
2) 
*/

//VGlobales
#define BUFSIZE 4096
char* spool_path= "/var/spool/works/";


void recorrer_directorio(char* dir_path){
    char buffer[BUFSIZE];
    DIR* dir;
    struct dirent* entrada;
    //abrimos el fichero
    dir = opendir(dir_path);
    
    //mientras haya entradas, las leemos en la variable entradas
    while((entrada=readdir(dir))!=NULL){
        //Obviamos si la entradas es '.' o '..'
        if((strcmp(entrada->d_name, ".")==0)||(strcmp(entrada->d_name, "..")==0)){
            continue;
        }
        
        sprintf(buffer,"%s/%s",dir, entrada->d_name); 
        //Buffer con formato 'dirname/filename'
        procesar_fichero(buffer); //Procesamos el fichero
        }
        // Cierra el directorio 
        closedir(dir);
    }

void procesar_fichero(char* filename)
{
    /*Por cada fichero encontrado en el directorio se debe ejecutar el programa 
    /bin/ejecutor, al que se le pasará por su entrada estándar el contenido del fichero.*/
    
    int fd;
    switch (fork())
    {
    case -1:
        /* error */
        perror("fork"); exit(1);
        break;

    case 0:
        //proceso hijo ejecuta el programa
        close(0);
        if((fd=open(filename,O_RDONLY))<0){
            perror("open()"); exit(2);}
            execlp("ejecutor",NULL);
            perror("execlp()");
    default:
        wait(NULL);
    }
    
    unlink(filename);
}

//Controlador de la alarma
void handler (int sig)
{   
    //Bucle de la alarma
    recorrer_directorio(spool_path);
    signal(SIGALRM,handler); // Volver a montar la señal
    alarm(1);
}

int main(int argc , char *argv[]){
    //timer
    signal(SIGALRM,handler);
    alarm(1); //Se invoca al signal(SIGALARM cada 1 sec)

}

