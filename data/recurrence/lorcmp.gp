set xlabel "{/Symbol t}"
set terminal x11
set output 
set nologscale
set autoscale
set noparametric
set xzeroaxis 
set noytics
set border 1+2
set xtics nomirror
set multiplot
set xrange [0:5]
set ytics ("0" 0, " " 1.82, " " 500)
p "../autocorr/lorac" u 1:2 not w l lt 1
p "../redundancy/lormut" u 1:2 not w l lt 2
p "lorrct" u 1:2 not w l lt 3
set xtics ("{/Symbol t}_A" 2.50, "{/Symbol t}_R" 0.162)
set grid
p "../autocorr/lorac" u 1:2  not w l lt 3
p "../redundancy/lormut" u 1:2 not w l lt 4
p "lorrct" u 1:2 not w l lt 5

set nomultiplot
pause -1 "Hit Return to continue..."
