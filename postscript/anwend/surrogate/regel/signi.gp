
set title "correlation-dimension"
set xlabel "d"
set ylabel "S"
set terminal x11
set output 
set nologscale
set autoscale
set noparametric
p "signi" u 1:7 not w p pt 2

pause -1 "Hit Return to continue..."
