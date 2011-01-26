CC=	gcc

SRC= $(wildcard *.c)

.PHONY: all clean

all: $(SRC:%.c=%.exe)

%.exe: %.c
	$(CC) -o $@ $<

clean: $(wildcard *.exe)
	rm -rf $<
