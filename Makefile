.PHONY: arbeit all gliederung bib view print ps backup tar disk clean

#
# normal targets section
#

arbeit: clean pdf ps

all: arbeit pslist



#
# commands section
#

pdf:
	TEXINPUTS=".//:" ./latexmk.pl -pdf gliederung

ps:
	TEXINPUTS=".//:" ./latexmk.pl gliederung

clean:
	./latexmk.pl -C gliederung

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

