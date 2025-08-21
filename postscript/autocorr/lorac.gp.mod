set title "auto-correlation"
set xlabel "{/Symbol t}"
set ylabel "A({/Symbol t})"
set terminal x11
set output 
set nologscale
set autoscale
set noparametric
set xzeroaxis 
set ytics ("0" 0)
set xrange [0:10]
set border 1+2
set xtics nomirror
set multiplot
p "lorac" u 1:2 not w l lt 1
set xtics ("{/Symbol t}_A" 2.50)
set grid
p "lorac" u 1:2 not w l lt 1
set nomultiplot
pause -1 "Hit Return to continue..."
