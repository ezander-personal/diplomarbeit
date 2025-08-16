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
set xrange [0:8]
set ytics ("0" 0, " " 1.302, " " 500)
#set noytics
#set key top right title "Hallo" box 2
p "../autocorr/roeac" u 1:2 not w l lt 1
#set ytics ("0" 0, "" 2)
p "../redundancy/roemut" u 1:2 not w l lt 2
p "roerct" u 1:2 not w l lt 3
#set xtics ("{/Symbol t}_A" 1.29, "{/Symbol t}_R" 1.16)
set grid
#set key title "A" nobox 1

p "../autocorr/roeac" u 1:2  not w l lt 3
p "../redundancy/roemut" u 1:2 not w l lt 4
p "roerct" u 1:2 not w l lt 5
set nomultiplot

pause -1 "Hit Return to continue..."
