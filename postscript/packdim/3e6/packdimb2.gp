set title "packdim"
set xlabel "x"
set ylabel "P(x|x_1,x_2)"
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

p "packdimb" u 1:4 not w l lt 1
pause -1 "Hit Return to continue..."
