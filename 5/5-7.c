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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

struct some_struct {
	int x;
	int y;
};

int my_readv(int fd, const struct iovec *iov, int iovcnt) {
	int i = 0;
	int rc = 0;
	int rv = 0;
	while( i < iovcnt ) {
		rc = read(fd, iov[i].iov_base, iov[i].iov_len);
		rv+= rc;
		i++;
	}

	return rv;
}

int my_writev(int fd, const struct iovec *iov, int iovcnt) {
	int i = 0;
	int alloc_size = 0;
	void * buf;
	int written = 0;
	while( i < iovcnt ) {
		alloc_size += iov[i++].iov_len;
	}

	i = 0;
	buf = malloc(alloc_size);

	while( i < iovcnt ) {
		int toWrite = iov[i].iov_len;
		int wv = 0;
		
		while( (wv = write( fd, (char *)(buf+wv), toWrite - wv)) > 0 ) {
			written += wv;
		}
		i++;
	}
	return written;
}

void print_contents(const struct iovec *iov) {
	char * buf = (char *)(iov[0].iov_base);
	int * x = (int *)(iov[1].iov_base);
	struct some_struct * y = (struct some_struct *)(iov[2].iov_base);
	printf("char buf[10] = %s\n int x = %d,\n int y.x = %d,\n int y.y = %d\n", buf, *x, y->x, y->y);
}

int main(int argc, char * argv[]) {
	int fd;
	int rv1,rv2,wv1,wv2;
	struct iovec iov[3];
	char buf[10]; // first buf
	int x; // second buf
	struct some_struct y; // third buf

	iov[0].iov_base = buf;
	iov[0].iov_len = 10;
	iov[1].iov_base = &x;
	iov[1].iov_len = sizeof(x);
	iov[2].iov_base = &y;
	iov[2].iov_len = sizeof(struct some_struct);

	if( argc < 2 )
		return -1;
	fd = open(argv[1], O_RDWR);
	if( fd == -1 )
		return -1;

	rv1 = readv(fd, iov, 3);
	print_contents(iov);

	lseek(fd, 0, SEEK_SET);

	rv2 = my_readv(fd, iov, 3);
	print_contents(iov);
	printf("readv: rv1=(%d) vs my_readv: rv2=(%d)\n STATUS: %s\n",rv1,rv2, rv1==rv2?"PASS":"FAIL");
	
	lseek(fd, 0, SEEK_END);
	wv1 = writev(fd, iov, 3);

	wv2 = my_writev(fd, iov, 3);
	printf("writev: wv1=(%d) vs my_writev: wv2=(%d)\n STATUS: %s\n", wv1, wv2, wv1==wv2?"PASS":"FAIL");
	
	close(fd);
	return 0;
}
