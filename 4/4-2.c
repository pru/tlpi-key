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
