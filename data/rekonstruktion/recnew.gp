set terminal x11
set output 
set nologscale
set autoscale
set parametric
set border 1+2+16
set xtics nomirror
set ytics mirror
set xlabel "v_i"
set ylabel "v_{i+k}"
set zlabel "v_{i+2k}" offset -5,-12

set format x ""
set format z ""
set format y ""

set tics out

set ticslevel 0

set size 1,1.3
!set view 80,20,,1

sp "rects" ev 1::::20000 u 2:3:4 not w l lt 1
pause -1 "Hit Return to continue..."
