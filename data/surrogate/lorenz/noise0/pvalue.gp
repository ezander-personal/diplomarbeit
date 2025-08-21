
set title "pvalues"
set xlabel "d"
set ylabel "p"
set terminal x11
set output 
set nologscale
set autoscale
set grid
set noparametric
set yrange [0:1]
set ytics 0.2
p "signi" u 1:8 not w linesp pt 2 ps 2
pause -1 "Hit Return to continue..."
