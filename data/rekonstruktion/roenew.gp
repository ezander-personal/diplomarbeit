set terminal x11
set output 
set nologscale
set autoscale
set parametric
set border 1+2+16
set xtics nomirror
set ytics mirror
set xlabel "X"
set ylabel "Y"
set zlabel "Z" offset -5,-12

set format x ""
set format z ""
set format y ""

set tics out

set ticslevel 1./6.

set size 1,1.5
set view 80,20,,1

sp "roessler" ev 1::::20000 u 2:3:4 not w l lt 1
pause -1 "Hit Return to continue..."
