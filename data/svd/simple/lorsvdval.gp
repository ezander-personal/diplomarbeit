set title "singular values"
set xlabel "i"
set ylabel "ln({/Symbol s}_i/{/Symbol s}_1)"
set terminal x11
set output 
set nologscale
set autoscale
set xrange [1:7]
set noparametric
set grid
set xtics nomirror 1
set ytics nomirror 2
p "lorsvd.w" u 1:3 not w lp pt 2 ps 2

pause -1 "Hit Return to continue..."
