
#
# set variables and flags 
#


include ../Makefile.inc

LIBNAME=libnr.a
LIBINSTALL=../../lib/libnr.a

LIBOBJS=$(subst src/,,$(subst .c,.o,$(wildcard src/*.c))) $(subst src/,,$(subst .cc,.o,$(wildcard src/*.cc)))

VPATH=./src:./include

DBXFLAGS=

# 
# phony targets
#

.PHONY: all clean distclean depend
.SILENT: clean cleanall

all: .depend $(LIBNAME)

clean: 
	$(RM) *.o $(LIBNAME)

distclean:
	$(RM) *.o  .depend

depend:
	$(CPP) -M src/*.c src/*.cc $(CPPFLAGS)> .depend

.depend:
	$(CPP) -M src/*.c src/*.cc $(CPPFLAGS)> .depend
 

# 
# modules
#

#$(LIBNAME): $(LIBOBJS)

$(LIBNAME): $(LIBOBJS) 
	$(RM) $(LIBNAME)
	$(AR) $(LIBNAME) $(LIBOBJS) 
	$(RANLIB) $(LIBNAME)
	$(INSTALL) $(LIBNAME) $(LIBINSTALL)


# 
# include dependendy file if one exists
#

ifeq (.depend,$(wildcard .depend))
include .depend
endif



