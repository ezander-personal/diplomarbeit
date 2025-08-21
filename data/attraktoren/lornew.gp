set terminal x11
set output 
set nologscale
set autoscale
set parametric
set border 1+2+16
set xtics nomirror -15,5,15
set noytics
set ytics mirror
set ztics 10,10,50
set xlabel "x"
set ylabel "y"
set y2label "y2"
set zlabel "z"
set ticslevel 8.2/(42.8-8.2)
set format x ""
set format z ""
set format y ""

set tics out

set zrange [0:60]
set ticslevel 0

set label "x" at 10,0,0
set label "y" at 0,10,0
set label "z" at 0,0,10
set nolabel

set size 1,1.3

sp "lorenz" ev 1::::10000 u 2:3:4 not w l lt 1
pause -1 "Hit Return to continue..."
