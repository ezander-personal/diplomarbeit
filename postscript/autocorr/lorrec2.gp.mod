set title "reconstruction"
set xlabel ""
set ylabel ""
set terminal x11
set output 
set nologscale
set autoscale
set noparametric
set pointsize 0.01
set format x ""
set format y ""
set xlabel "x_i"
set ylabel "x_{i+{k_A}}"
p "lorrec2" u 2:3 not w p pt 1
pause -1 "Hit Return to continue..."
