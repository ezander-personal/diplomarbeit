#
# include standard makefile definitions
#

include ../Makefile.inc

#
#
#

LIBNAME=../..//lib/libalg.a

PROGRAMS=$(wildcard *.cc)
HEADERS=$(subst .cc,.h,$(PROGRAMS))
LIBOBJS=$(subst .cc,.o,$(PROGRAMS))

CPPFLAGS+= -I$(WORK)/cxx  -DALGORITHM

# 
# phony targets
#

.PHONY: all clean cleanall depend
.SILENT: clean cleanall

all: .depend headers $(LIBNAME)

clean: 
	$(RM) *.o *~

distclean:
	$(RM) *.o *~ .depend

depend:
	$(MAKEDEPEND)
 

# 
# modules
#

$(LIBNAME): $(LIBOBJS)
	$(RM) $(LIBNAME)
	$(AR) $(LIBNAME) $(LIBOBJS)
	$(RANLIB) $(LIBNAME)
	$(INSTALL) $(LIBNAME) lib

.depend:
	$(MAKEDEPEND)

headers: $(HEADERS)

$(HEADERS) : %.h : %.cc
	touch -r $< $@


# include dependendy file if one exists

#include .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif



