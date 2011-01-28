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

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
    int flags1,flags2;
    int fd1,fd2;
    off_t of1,of2;
    int rv = 0;
    fd1 = open("/dev/stdout",O_WRONLY);
    if( fd1 == -1 ) {
        perror("open");
        return -1;
    }

    fd2 = dup(fd1);
    if( fd2 == -1 ) {
        perror("dup");
        rv = -1;
    }

    of1 = lseek(fd1, 0, SEEK_CUR);
    of2 = lseek(fd2, 0, SEEK_CUR);
    
    printf("fd1:offset: %lu fd2:offset: %lu (%s)\n", of1, of2, of1==of2?"Equal":"Not Equal");

    flags1 = fcntl(fd1, F_GETFL);
    flags2 = fcntl(fd2, F_GETFL);

    printf("fd1:flags: %d fd2:flags: %d (%s)\n", flags1, flags2, flags1==flags2?"Equal":"Not Equal");

    close(fd1);
    return rv;
}
