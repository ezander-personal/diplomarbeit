set title "reconstruction"
set xlabel ""
set ylabel ""
set terminal x11
set output 
set nologscale
set autoscale
set parametric
set pointsize 0.01
set border 1+2+16

set noxtics
set noytics
set noztics
#set xlabel "X"
#set ylabel "Y"
#set zlabel "Z" -5,-12
set format x ""
set format z ""
set format y ""

#set tics out

#set zrange [0:60]
#set ticslevel 0

#set label "x" at 10,0,0
#set label "y" at 0,10,0
#set label "z" at 0,0,10
#set nolabel

#set size 1,1.3


sp "lorrec" ev 2 u 2:3:4 not w p pt 1
pause -1 "Hit Return to continue..."

