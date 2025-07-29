#include standard makefile

include ../Makefile.inc



# set some variables

PROGRAMS=lower upper uplow testfloat psm

CPPFLAGS+= -DALGORITHM
BINDIR=$(HOME)/bin
CC=g++

# some declarations

.PHONY: all clean cleanall depend
.SILENT: clean cleanall



#phony targets

all: .depend $(PROGRAMS) install

install:
	@$(CP) $(PROGRAMS) $(BINDIR)

clean: 
	$(RM) *.o *~ $(PROGRAMS)

distclean:
	$(RM) *.o *~ $(PROGRAMS) .depend

depend:
	$(MAKEDEPEND)
 


# the real targets


$(PROGRAMS) : % : %.o

.depend:
	$(MAKEDEPEND)




# include dependendy file if one exists

ifeq (.depend,$(wildcard .depend))
include .depend
endif



