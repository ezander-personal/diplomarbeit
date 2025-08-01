set title "fourier spectrum"
set xlabel "f"
set ylabel "log P(f)"
set terminal x11
set output 
set nologscale
set autoscale
set xrange [0:10]
set noparametric
set border 1+2
set xtics nomirror
set ytics nomirror
p "fourier" u 1:2 not w l 1
pause -1 "Hit Return to continue..."
