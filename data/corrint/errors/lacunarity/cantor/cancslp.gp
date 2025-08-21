set title "correlation dimension"
set xlabel "ln r"
set ylabel "D_2"
set terminal x11
set output 
set nologscale
set autoscale
set noparametric
set grid
p "canacslp" u 1:2 not w linesp lt 2,\
"canbcslp" u 1:2 not w linesp lt 4


pause -1 "Hit Return to continue..."
