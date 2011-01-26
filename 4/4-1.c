#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>

#define BUF_SIZE 4*1024

int main(int argc, char * argv[]) {
    int stin = open("/dev/stdin", O_RDONLY);
    int stout = open("/dev/stdout", O_WRONLY);
    int outfilefd,append = 0,flags = 0;
    int opt; 
    while(( opt = getopt(argc, argv, "a")) != -1) {
        switch(opt) {
            case 'a':
                append = 1;
        }
    }

    flags = append?(O_WRONLY|O_APPEND):(O_CREAT|O_WRONLY|O_TRUNC);
    
    outfilefd = open(argv[optind],flags,S_IRUSR|S_IWUSR);

    if(stout < 0 || stin < 0 || outfilefd < 0) {
         perror("open");
         return -1;
    }
    else {
        char * buf = (char *)calloc(sizeof(char)*BUF_SIZE,1);
        int rv = 0;
        while ((rv = read(stin, buf, BUF_SIZE)) > 0) {
            write(stout, buf, rv);
            write(outfilefd, buf,rv);
        }
        free(buf);
        close(outfilefd);
        close(stout);
        close(stin);
    }
}
