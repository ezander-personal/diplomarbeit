set title "Histogramm"
set xlabel "x"
set ylabel "n"
set terminal x11
set output 
set nologscale
set autoscale
set grid
set noparametric
set xrange [-1500:1000]
p "hs_regel" u 1:($2*0.5) smooth csplines not w l 1\
, "hs_regel1" u 1:2 smooth csplines not w l 2\
, "hs_regel2" u 1:2 smooth csplines not w l 2\

pause -1 "Hit Return to continue..."
