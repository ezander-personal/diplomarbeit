#include standard makefile

include ../Makefile.inc



# set some variables


CPPFLAGS+= -DUTILITY

LIBNAME=../../lib/libutil.a
LIBOBJS= $(subst .cc,.o,$(wildcard *.cc))



# some declarations

.PHONY: all clean cleanall depend
.SILENT: clean cleanall



#phony targets

all: .depend $(LIBNAME)

clean: 
	$(RM) *.o *~ 

distclean:
	$(RM) *.o *~ .depend

depend:
	$(MAKEDEPEND)
 


# the real targets

$(LIBNAME): $(LIBOBJS)
	$(RM) $(LIBNAME)
	$(AR) $(LIBNAME) $(LIBOBJS)
	$(RANLIB) $(LIBNAME)
	$(INSTALL) $(LIBNAME) lib


.depend:
	$(MAKEDEPEND)




# include dependendy file if one exists

ifeq (.depend,$(wildcard .depend))
include .depend
endif



