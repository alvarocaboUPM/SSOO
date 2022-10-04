#define DATA_SIZE 2048
#define N 5000
char buffer[DATA_SIZE];
int fd, i;

int main(int argc, char* argv[]){
    fd = open(argv[1], 'O_RDWR');
    for (i = 0 ; i < N; i++)
    write(fd, buffer, DATA_SIZE);
    lseek(fd, 0, 'SEEK_SET');
    for (i = 0 ; i < N; i++)
    read(fd, buffer, DATA_SIZE);
    Close(fd);
}
