set title "correlation-dimension"
set xlabel "d"
set ylabel "D_2"
set terminal x11
set output 
set nologscale
set autoscale
set noparametric
set yrange [0:12]
set ytics 2
set xrange [0.5:8.5]
p "td_surro1" u 1:2 not w p pt 1,\
"td_surro2" u 1:2 not w p pt 1,\
"td_surro3" u 1:2 not w p pt 1,\
"td_surro4" u 1:2 not w p pt 1,\
"td_surro5" u 1:2 not w p pt 1,\
"td_surro6" u 1:2 not w p pt 1,\
"td_surro7" u 1:2 not w p pt 1,\
"td_surro8" u 1:2 not w p pt 1,\
"td_surro9" u 1:2 not w p pt 1,\
"td_surro10" u 1:2 not w p pt 1,\
"td_surro11" u 1:2 not w p pt 1,\
"td_surro12" u 1:2 not w p pt 1,\
"td_surro13" u 1:2 not w p pt 1,\
"td_surro14" u 1:2 not w p pt 1,\
"td_surro15" u 1:2 not w p pt 1,\
"td_surro16" u 1:2 not w p pt 1,\
"td_surro17" u 1:2 not w p pt 1,\
"td_surro18" u 1:2 not w p pt 1,\
"td_surro19" u 1:2 not w p pt 1,\
"td_r_3" u 1:2 not w p pt 2

pause -1 "Hit Return to continue..."
