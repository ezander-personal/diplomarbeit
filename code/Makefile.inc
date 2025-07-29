

ifeq (../.tsa_dir,$(wildcard ../.tsa_dir))
include ../.tsa_dir
else
ifeq (../../.tsa_dir,$(wildcard ../../.tsa_dir))
include ../../.tsa_dir
else
WORK=$(HOME)/work/cxx
endif
endif


# commands

CC=g++
CXX=g++
CP=cp -u
RM=rm -f
AR=ar -rc
MV= mv
RANLIB=ranlib
INSTALL=install -c -m 600
INSTALLBIN=install -c -m 700 
MAKEDEPEND=$(CPP) -MM *.cc $(CPPFLAGS)> .depend

F77=g77
.f.o:
	$(F77) -c $(FFLAGS) $<

# includes

#NINCLUDES=-I$(WORK)/src -I$(WORK)/src/nmath/include -I$(WORK)/src/nr/include
NINCLUDES=-I$(WORK)/src -I$(WORK)/src/nr/include
XINCLUDES=-I$(OPENWINHOME)/include 
LINCLUDES=-I$(WORK)/src/alg -I$(WORK)/src/util
# libraries

ALGLIB=$(WORK)/lib/libalg.a
UTILLIB=$(WORK)/lib/libutil.a
NRLIB=$(WORK)/lib/libnr.a

#NLIBS= -lnmath -lnr -lm -lf2c
NLIBS= -lnr -lm
NLIBDIRS=
#$(LLIBDIRS) 
XLIBS=  -lxview -lolgx -lX11 -lsspkg
XLIBDIRS=  $(OPENWINHOME)/lib
LLIBS= -lalg -lutil
LLIBDIRS= -L$(WORK)/lib

LOADLIBES= $(NLIBDIRS) $(LLIBDIRS) $(LLIBS) $(NLIBS)

# compiler flags 
CFLAGS= -m486 -O2 -ffast-math
CXXFLAGS= -m486 -ffast-math -O2 -pipe -Wall -Wcast-qual -fno-strength-reduce -fomit-frame-pointer -Wstrict-prototypes -Wformat $(DBXFLAGS)
#CXXFLAGS= -m486 -ffast-math -pipe -Wall -Wcast-qual $(DBXFLAGS)
CPPFLAGS=$(NINCLUDES) $(LINCLUDES)
LDFLAGS=

# debug flags
DBXFLAGS= -ggdb
#DBXFLAGS=



















