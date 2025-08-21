set title "time series"
set xlabel "t"
set ylabel "v"
set terminal x11
set output 
set nologscale
set autoscale
set noparametric
set border 1+2
set xtics nomirror
set ytics nomirror
set xrange [0:150]
set pointsize 0.01
p "timeseries" u 1:2 not w p pt 1
pause -1 "Hit Return to continue..."
