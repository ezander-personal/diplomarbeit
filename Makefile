TEXFILES=$(wildcard *.tex)
BIBFILES=$(wildcard *.bbl)

NUM1:=$(shell number1)
NUM2:=$(shell number2)
TARFILE:=tex.tar
GZFILE:=tex$(NUM2).tgz

RM=rm -f


.PHONY: arbeit all gliederung bib view print ps backup tar disk clean

#
# normal targets section
#

arbeit: view gliederung pslist

all: view gliederung bib gliederung2 gliederung3



#
# commands section
#

gliederung:
	latex gliederung

gliederung2:
	latex gliederung

gliederung3:
	latex gliederung


bib:
	bibtex gliederung

view:
	runxdvi

print:
	lpr gliederung

split:
	dvips gliederung	
	dsplit gliederung.ps 

#
#
#

nops:
	@rm -f style/psyesno.sty
	@ln -s psno.sty style/psyesno.sty

ps:
	@rm -f style/psyesno.sty
	@ln -s psyes.sty style/psyesno.sty

showps:
	@if `cmp style/psyesno.sty style/psyes.sty > /dev/null`; then echo "True PostScript output."; else echo "Dummy PostScript output."; fi

pslist: gliederung.aux
	@grep psdo gliederung.aux | cut -d"{" -f 2 | cut -d "}" -f 1 > pslist

#
# backup section
#

backup:	disk

tar:
	tar cf $(TARFILE)
	tar rf $(TARFILE)  Makefile settexvars runxdvi number* .number*
	tar rf $(TARFILE)  *.tex style/* bst/* bib/*
	gzip -f -c $(TARFILE) > $(GZFILE)
	@mv .number$(NUM1) .number$(NUM2)

disk:	tar
	mcopy -n $(GZFILE) a:$(GZFILE)
	rm $(GZFILE)

psbackup: pslist
	tar cf allps 
	tar rfh allps `cat pslist` ./postscript/*.eps
	gzip -f -c allps > allps.tgz
	

#
# cleanup section
#

clean:
	$(RM) *.dvi *.ps  dsplit* *~  "#"*"#"

distclean:
	$(RM) *.aux *.bbl *.blg *.dvi *.log *.toc *.ps  dsplit* *~  "#"*"#"

