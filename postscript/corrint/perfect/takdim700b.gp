set title "correlation-dimension"
set xlabel "d"
set ylabel "D_2"
set terminal x11
set output 
set nologscale
set autoscale
set grid
set noparametric
p "takdim700" u 1:2 not w linesp 1
pause -1 "Hit Return to continue..."
