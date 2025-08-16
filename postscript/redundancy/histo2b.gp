set title "Histogramm Rand"
set xlabel "x"
set ylabel "n"
set terminal x11
set output 
set nologscale
set autoscale
set grid
set noparametric
p "histo2" u 1:2 not w l 1\
, "histo2" u 1:2 not w i 1
pause -1 "Hit Return to continue..."
