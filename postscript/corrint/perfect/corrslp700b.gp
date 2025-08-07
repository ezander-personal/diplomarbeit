set title "correlation dimension"
set xlabel "ln r"
#set ylabel "d{ln C(r)} / d{ ln r}"
set ylabel "D_2"
set terminal x11
set output 
set nologscale
set autoscale
set grid
set noparametric
set xrange [-7:0]
set multiplot
p "corrslp700" u 1:2 not w linesp 1,\
"corrslp700" u 1:3 not w linesp 1,\
"corrslp700" u 1:4 not w linesp 1,\
"corrslp700" u 1:5 not w linesp 1,\
"corrslp700" u 1:6 not w linesp 1,\
"corrslp700" u 1:7 not w linesp 1,\
"corrslp700" u 1:8 not w linesp 1,\
"corrslp700" u 1:9 not w linesp 1
set xtics ("r_{min}" -5.7, "r_{max}" -3.3)
#set noytics
set grid
replot
set nomultiplot
pause -1 "Hit Return to continue..."
