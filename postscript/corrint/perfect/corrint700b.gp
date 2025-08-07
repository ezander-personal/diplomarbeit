set title "correlation integral"
set xlabel "ln r"
set ylabel "ln C"
set terminal x11
set output 
set nologscale
set autoscale
set noparametric
set grid
set xrange [-7:0]
p "corrint700" u 1:2 not w linesp 1,\
"corrint700" u 1:3 not w linesp 1,\
"corrint700" u 1:4 not w linesp 1,\
"corrint700" u 1:5 not w linesp 1,\
"corrint700" u 1:6 not w linesp 1,\
"corrint700" u 1:7 not w linesp 1,\
"corrint700" u 1:8 not w linesp 1,\
"corrint700" u 1:9 not w linesp 1
pause -1 "Hit Return to continue..."
