#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char **argv)
{
    if(argc !=2){
        return 1;
    }

    char* filename = argv[1];
    char filetype[32];
    struct stat data;

    stat(filename, &data);
    printf("Info sobre el fichero: %s", filename);
    puts("---------------");

    

    return 0;
}
