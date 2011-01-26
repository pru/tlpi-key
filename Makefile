SUBDIRS=	4 util

.PHONY:	all clean

all:  
	for A in $(SUBDIRS); do make -f $(PWD)/Makefile.inc -C $$A all; done

clean:
	for A in $(SUBDIRS); do make -f $(PWD)/Makefile.inc -C $$A clean; done
