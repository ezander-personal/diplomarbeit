set title "auto-correlation"
set xlabel "tau"
set ylabel "C(tau)"
set terminal x11
set output 
set nologscale
set autoscale
set noparametric
set xzeroaxis 
set ytics ("0" 0)
set xrange [0:10]
p "lorac" u 1:2 not w l 1
pause -1 "Hit Return to continue..."
