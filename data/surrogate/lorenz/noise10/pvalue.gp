
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
set xrange [0:6]
set xtics 1
p "signi" u 1:8 not w lp pt 2 ps 2
pause -1 "Hit Return to continue..."
