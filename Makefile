SUBDIRS=	4 5 util

.PHONY:	all clean

all:  
	for A in $(SUBDIRS); do make -C $$A all; done

clean:
	for A in $(SUBDIRS); do make -C $$A clean; done
