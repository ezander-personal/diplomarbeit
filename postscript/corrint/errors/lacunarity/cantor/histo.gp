set title "Histogramm"
set xlabel "x"
set ylabel "n"
set terminal x11
set output 
set nologscale
set autoscale
set noparametric
p "histoa" u 1:2 not w l lt 1 ,\
"histob" u 1:2 not w l lt 2
pause -1 "Hit Return to continue..."
