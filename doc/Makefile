.PHONY: arbeit all gliederung bib view print ps backup tar disk clean

#
# normal targets section
#

arbeit: clean pdf ps


#
# commands section
#

pdf:
	TEXINPUTS=".//:" ./latexmk.pl -pdf gliederung

ps:
	TEXINPUTS=".//:" ./latexmk.pl gliederung

clean:
	./latexmk.pl -C gliederung
