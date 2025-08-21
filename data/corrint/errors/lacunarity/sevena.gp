set terminal x11
set output
set border 1
set xtics nomirror   
set format y ""
set noytics    
set noxtics
set border 0
#set yrange [0:*]
set rmargin 7
set lmargin 7
set size 1,0.5
plot "sevena" not w l lw 3  
pause -1 "taste..."
