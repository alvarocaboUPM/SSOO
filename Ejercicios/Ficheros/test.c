#include "stdlib.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int fd[2];
int i;

void sumar(){
    write(fd[1], &i, sizeof(int));
}
int main(int argc, char const *argv[])
{
    struct sigaction signal;

    sigemptyset(&signal.sa_mask);
    signal.sa_flags = 0;
    signal.sa_handler = sumar;

    return 0;
}
