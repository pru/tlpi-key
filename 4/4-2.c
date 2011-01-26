#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_LEN 4*1024

int main(int argc, const char * argv[]) {
    char * buf;
    int fd,wd,rv;
    if( argc < 2)
        return -1;
    else {
        fd = open(argv[1], O_RDONLY);
        wd = open(argv[2], O_CREAT|O_WRONLY, S_IRUSR | S_IWUSR);
        buf = (char *)calloc(BUF_LEN, 1);
        
        while((rv = read(fd,buf, BUF_LEN))) {
            write(wd,buf,rv);
        }
        
        close(wd);
        close(fd);
    }
}
