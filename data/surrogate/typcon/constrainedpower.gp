set terminal x11
set output
set logscale x
set xrange [5:*]
set yrange [0:1]
set ytics 0.1
set xlabel "N"
set ylabel "1-@^{\\^}{/Symbol b}"
p "stat" u 1:8 not w lp lt 2\
, "stat" u 1:9 not w lp lt 1\

pause -1  "Hit return to continue"
