set terminal x11
set output
set logscale x
set xrange [5:*]
set yrange [0:1]
set ytics 0.1
set xlabel "N"
set ylabel "1-@^{\\^}{/Symbol b}"
#p "stat" u 1:6 sm csplines not w l lt 1\
#, "stat" u 1:7 sm csplines not w l lt 2\
#, "stat" u 1:7:10 not w errorbars 2\
#, "stat" u 1:6:10 not w errorbars 1\

p "stat" u 1:6 not w lp lt 2\
, "stat" u 1:7 not w lp lt 1\

pause -1  "Hit return to continue"
