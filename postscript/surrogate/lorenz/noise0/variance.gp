set title "pvalues"
set xlabel "d"
#set ylabel "{(D_2-@^{-}{D_2})/{/Symbol s}_{D_2}}"
set ylabel "normalisierte Korrelationsdimension"
set terminal x11
set output 
set nologscale
set autoscale
#set grid
set noparametric
#set yrange [-4:2]
#set ytics 0.2
set xrange [0:6]
set xtics 1

p "dim1d" u (1):(($1-1.09750)/0.000171011) not w p 2\
, "dim2d" u (2):(($1-2.03399)/0.004692110) not w p 2\
, "dim3d" u (3):(($1-3.02650)/0.018612000) not w p 2\
, "dim4d" u (4):(($1-4.00258)/0.044072100) not w p 2\
, "dim5d" u (5):(($1-4.87683)/0.093052300) not w p 2\
, "signi" u 1:(($6-$4)/$5) not w p pt 6 ps 2 \


#1	1.09718	1.09782	1.0975	0.000171011	1.09744	0.350854623386501	0.725697415289152
#2	2.02347	2.04319	2.03399	0.00469211	1.75025	60.4717280711663	0.0
#3	2.98276	3.05974	3.0265	0.018612	1.92194	59.3466580700623	0.0
#4	3.9111	4.08239	4.00258	0.0440721	2.01741	45.0436897719873	0.0
#5	4.68313	5.09127	4.87683	0.0930523	2.07219	30.1404693919441	1.43007625461906e-199



pause -1 "Hit Return to continue..."
