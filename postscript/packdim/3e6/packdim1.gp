set title "packdim"
set xlabel "x"
set ylabel "P(x|x_1)"
set terminal x11
set output 
set nologscale
set autoscale
set noparametric

#set format y ""
set border 1+2
set xtics nomirror
set ytics nomirror
set ytics 0.0001

p "packdim" u 1:3 not w l 1
pause -1 "Hit Return to continue..."
