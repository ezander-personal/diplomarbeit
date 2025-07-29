#
# set variables and flags 
#


#SUBDIRS=nr nmath/nmath util alg clm
SUBDIRS=nr util alg clm others
MYSUBDIRS=util alg clm



NUM1:=$(shell number1)
NUM2:=$(shell number2)
TARFILE:=src.tar
GZFILE:=src$(NUM2).tgz


# 
# phony targets
#

.PHONY: all clean cleanobj cleanall backup depend bin tar disk backup $(SUBDIRS)
.IGNORE: $(PROGRAMS)
.SILENT: clean cleanobj cleanall backup disk

all: 
	@for i in $(SUBDIRS) ; \
	do \
	(cd $$i; $(MAKE) ) \
	done
	@echo ; echo ; echo "_____ToDo_____" ; echo ; cat ToDo ; echo ; echo "______________" ; echo ;

clean: 
	@for i in $(SUBDIRS) ; \
	do \
	(cd $$i; $(MAKE) clean) \
	done
	$(RM) *~

myclean: 
	@for i in $(MYSUBDIRS) ; \
	do \
	(cd $$i; $(MAKE) clean) \
	done
	$(RM) *~

distclean:
	@for i in $(SUBDIRS) ; \
	do \
	(cd $$i; $(MAKE) distclean) \
	done
	$(RM) *~

depend:
	@for i in $(SUBDIRS) ; \
	do \
	(cd $$i; $(MAKE) depend) \
	done

tar:
	tar cf $(TARFILE)
	tar rf $(TARFILE)  Makefile Makefile.inc ToDo number* .number$(NUM1) .tsa_dir_dem
	tar rf $(TARFILE)  alg/*.cc alg/*.h alg/Makefile 
	tar rf $(TARFILE)  clm/*.cc clm/Makefile 
	tar rf $(TARFILE)  util/*.h util/*.cc util/Makefile 
	tar rf $(TARFILE)  nr/include/*.h nr/src/*.c nr/src/*.cc nr/Makefile
	tar rf $(TARFILE)  others/*.cc others/Makefile
	gzip -f -c $(TARFILE) > $(GZFILE)
	@mv .number$(NUM1) .number$(NUM2)

backup: disk


disk:	tar
	mcopy -n $(GZFILE) a:$(GZFILE)
	rm $(GZFILE)

bin:
	cp $(PROGRAMS) gp /home/zandere/bin/

 


