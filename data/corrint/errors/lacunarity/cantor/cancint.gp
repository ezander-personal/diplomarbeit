set title "correlation integral"
set xlabel "ln r"
set ylabel "ln C(r)"
set terminal x11
set output 
set nologscale
set autoscale
set noparametric
set grid
p "canacint" ev 3 u 1:2  not w linesp lt 2,\
"canbcint" ev 3 u 1:2  not w linesp lt 4
pause -1 "Hit Return to continue..."
