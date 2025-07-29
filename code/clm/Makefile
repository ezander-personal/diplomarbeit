#include standard makefile

include ../Makefile.inc



# set some variables

PROGRAMS=$(subst .cc,,$(wildcard *.cc))

CPPFLAGS+= -DINTERFACE
BINDIR=../../bin/

# some declarations

.PHONY: all clean cleanall backup depend install
.IGNORE: $(PROGRAMS)
.SILENT: clean cleanall distclean backup disk



# phony targets

all: .depend $(PROGRAMS) install

install:
	@$(CP) $(PROGRAMS) $(BINDIR)
	@(strip $(BINDIR)* 2> /dev/null; echo "" )

clean: 
	$(RM) $(PROGRAMS) *.o

distclean:
	$(RM) $(PROGRAMS) .depend *.o *~

backup: 
	$(CP) *.cc *.h Makefile backup/

disk:
	mcopy -n *.cc *.h Makefile gp a:

depend:
	$(MAKEDEPEND)

 

# the real targets

$(PROGRAMS) : % : %.o $(UTILLIB) $(NRLIB)

.depend:
	$(MAKEDEPEND)



# include dependendy file if one exists

#include .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif



