CC=	gcc

.PHONY:	all exe-4

all: exe-4

exe-4: tee_4-1

tee_4-1:	4-1.c
	$(CC) $^ -o $@

