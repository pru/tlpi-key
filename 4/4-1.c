/*
 * Copyright 2011 Prudhvi Krishna Surapaneni. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list
 *       of conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 *    THIS SOFTWARE IS PROVIDED BY PRUDHVI KRISHNA SURAPANENI  ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *    WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 *    FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL PRUDHVI KRISHNA SURAPANENI OR
 *    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *    ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *    ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *    The views and conclusions contained in the software and documentation are those of the
 *    authors and should not be interpreted as representing official policies, either expressed
 *    or implied, of Prudhvi Krishna Surapaneni.
 *
 **/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <unistd.h>

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
