set title "Histogramm"
set xlabel "x"
set ylabel "n"
set terminal x11
set output 
set nologscale
set autoscale
set grid
set noparametric
set multiplot
p "histo1" u 1:2 not w l 1,\
"histo1" u 1:2 not w i 1
p "histo2" u 1:2 not w l 2,\
"histo2" u 1:2 not w i 2
set nomultiplot
pause -1 "Hit Return to continue..."
