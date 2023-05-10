#include <stdio.h>	/* setbuf, printf */
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //PID operations

#define n 100
int main(char** argv, int argc){
    int pipe_fd[2];
    int pid,i;
    pipe(pipe_fd);
    char* text="Pito bonito";

    for(i=0; i<n; i++){
        switch (pid=fork())
        {
        case 0:
            //Hijo lee
            close(pipe_fd[1]);
            read(pipe_fd[0], text, strlen(text));
            close(pipe_fd[0]);
            puts("HIJO LEE");
            exit(0);
        
        default:
            close(pipe_fd[0]);
            write(pipe_fd[1], text, strlen(text));
            close(pipe_fd[1]);
            puts("PADRE ESCRIBE");
        }
    }
        return 0;
}