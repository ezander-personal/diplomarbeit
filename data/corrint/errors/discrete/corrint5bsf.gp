set title "correlation integral"
set xlabel "ln r"
set ylabel "ln C(r)"
set terminal x11
set output 
set nologscale
set autoscale
set grid
set noparametric
set xrange[-6:0]
p "corrint5sf" u 1:2 not w linesp lt 1,\
"corrint5sf" u 1:3 not w linesp lt 1,\
"corrint5sf" u 1:4 not w linesp lt 1,\
"corrint5sf" u 1:5 not w linesp lt 1,\
"corrint5sf" u 1:6 not w linesp lt 1,\
"corrint5sf" u 1:7 not w linesp lt 1,\
"corrint5sf" u 1:8 not w linesp lt 1,\
"corrint5sf" u 1:9 not w linesp lt 1
pause -1 "Hit Return to continue..."
