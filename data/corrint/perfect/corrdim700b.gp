set title "correlation-dimension"
set xlabel "d"
set ylabel "D_2"
set terminal x11
set output 
set nologscale
set autoscale
set grid
set noparametric
set yrange [1:2.2]
p "corrdim700" u 1:2 not w linesp lt 1
pause -1 "Hit Return to continue..."
