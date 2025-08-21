set terminal x11
set output
set hidden
set ticslevel 0
set view 20,20
set format x ""
set format y ""
set format z ""
!set noztics
set border 1+2+4+8+16+32+64+256+512
set zrange [0:100]
set xlabel "i" offset 0,1
set ylabel "j" offset -4,0
set zlabel "P_{X_{/Symbol t}}" offset 4,6

splot "density1" matrix not w l lt 0
pause -1 "press any key"
