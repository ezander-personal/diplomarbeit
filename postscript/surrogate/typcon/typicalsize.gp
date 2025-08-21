set terminal x11
set output
set logscale x
set xrange [5:*]
set yrange [0:0.1]
set ytics 0.01
set xlabel "N"
set ylabel "@^{\\^}{/Symbol a}"
p "stat" u 1:2 not w l lt 2\
, "stat" u 1:3 not w l lt 1\
, "stat" u 1:2:11 not w errorbars lt 1\
, "stat" u 1:3:10 not w errorbars lt 1\

pause -1  "Hit return to continue"
