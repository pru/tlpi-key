CC=	gcc
CFLAGS?= -std=c99

SRC= $(wildcard *.c)

.PHONY: all clean

all: $(SRC:%.c=%.exe)

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean: $(wildcard *.exe)
	rm -rf $^
