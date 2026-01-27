.PHONY: default rebuild pdf clean

# Everything that was normally here is now in latexmkrc... 

all: pdf

rebuild: clean pdf

pdf:
	latexmk
clean:
	latexmk -C
