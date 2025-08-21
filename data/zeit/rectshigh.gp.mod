
set title "reconstruction"
set xlabel "v_i"
set ylabel "v_{i+200}"
set terminal x11
set output 
set nologscale
set autoscale
set noparametric

set format x ""
set format y ""
set format z ""

set pointsize 0.01
set size 1,1.3

p "rectshigh" ev 4 u 2:3 not w p pt 1
pause -1 "Hit Return to continue..."
