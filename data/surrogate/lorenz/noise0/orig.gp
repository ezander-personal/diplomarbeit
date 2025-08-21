set title "time series"
set xlabel "t"
set ylabel "x"
set terminal x11
set output 
set nologscale
set autoscale
set grid
set noparametric
set xrange [0:10]
p "timeseries" u 1:2 not w l lt 1
pause -1 "Hit Return to continue..."
