set title "singular vectors"
set xlabel "k"
set ylabel "c_{1,k}"
set terminal x11
set output 
set nologscale
set autoscale
set xrange [0:8]
set yrange [-1:1]
set grid
set noparametric
#set size ratio 1
p "lorsvd.v" u 1:2 not w lp pt 2 ps 2
pause -1 "Hit Return to continue..."
