#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    int fd;
    long offset;
    if ( argc < 2)
        return -1;

    fd = open(argv[1], O_CREAT|O_RDWR, S_IRUSR | S_IWUSR);
    if( fd < 0 )
        return -1;

    offset = strtol(argv[2], NULL, 0);
    if(lseek(fd, offset, SEEK_SET) == -1)
        perror("lseek");
    else
        write(fd, "1",1);
    close(fd);
}
