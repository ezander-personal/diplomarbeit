set title "Noise"
set xlabel "i"
set ylabel "x"
set terminal x11
set output 
set nologscale
set autoscale
set grid
set noparametric
set xrange[0:300]
p "surro1" u 2 not w l 1
pause -1 "Hit Return to continue..."
