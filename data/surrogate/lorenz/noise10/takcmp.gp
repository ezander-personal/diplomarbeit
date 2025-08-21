set title "correlation-dimension"
set xlabel "d"
set ylabel "D2"
set terminal x11
set output 
set nologscale
set autoscale
set grid
set noparametric
p "takdim" u 1:2 not w linesp lt 1\
, "surtdim1" u 1:2 not w linesp lt 2\
, "surtdim2" u 1:2 not w linesp lt 2
pause -1 "Hit Return to continue..."
