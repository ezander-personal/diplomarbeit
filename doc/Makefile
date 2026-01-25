.PHONY: arbeit all gliederung bib view print ps backup tar disk clean

#
# normal targets section
#

arbeit: clean pdf ps


#
# commands section
#

pdf:
	TEXINPUTS=".//:" latexmk -pdf gliederung

ps:
	TEXINPUTS=".//:" latexmk gliederung

clean:
	latexmk -C gliederung
