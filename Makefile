SUBDIRS=	4 util

.PHONY:	all clean

all:  
	for A in $(SUBDIRS); do make -f $(PWD)/Makefile.exe -C $$A all; done

clean:
	for A in $(SUBDIRS); do make -f $(PWD)/Makefile.exe -C $$A clean; done
