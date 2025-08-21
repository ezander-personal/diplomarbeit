set title "correlation-dimension"
set xlabel "d"
set ylabel "p"
set terminal x11
set output 
set nologscale
set autoscale
set noparametric
p "signi" u 1:8 not w p 2

pause -1 "Hit Return to continue..."
