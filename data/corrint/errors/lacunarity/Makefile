all: mkcantor sevena sevenb sixa sixb three sevena.eps sevenb.eps

mkcantor: mkcantor.cc

sevena: mkcantor
	./mkcantor 4 1100011 > sevena

sevenb: mkcantor
	./mkcantor 4 1010101 > sevenb

sixa: mkcantor
	./mkcantor 4 110011 > sixa

sixb: mkcantor
	./mkcantor 4 101101 > sixb

three: mkcantor
	./mkcantor 4 101 > three

sevena.eps: sevena sevena.gp
	gp2eps sevena.gp

sevenb.eps: sevenb sevenb.gp
	gp2eps sevenb.gp

clean:
	rm -f mkcantor sevena sevenb sixa sixb three sevena.eps sevenb.eps

