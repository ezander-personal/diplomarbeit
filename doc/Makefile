.PHONY: arbeit all gliederung bib view print ps backup tar disk clean

#
# normal targets section
#

default: pdf

clear_first: clean pdf


#
# commands section
#

pdf:
	TEXINPUTS=".//:" latexmk -pdf gliederung

clean:
	latexmk -C gliederung
