CC=	gcc
CFLAGS?= -std=c99 -pedantic -Wall -Wextra -O0 -g

.PHONY: all clean objs

all: $(SRC:%.c=%.exe) objs 

objs: $(OBJS:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean: $(wildcard *.exe) $(wildcard *.o)
	rm -rf $^
