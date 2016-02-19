set terminal png font arial 16 size 500, 600
set output "reach_large.png"

set title "Step=0.0091, Time= 3ms" font "arial,20"
set xlabel "Position"
set ylabel "Velocity"

# ranges for pendulum
set xrange [-0.2:0.6]
set yrange [0.4:1]

load "intermediate.gnuplot.txt"
load "final.gnuplot.txt"
load "initial.gnuplot.txt"

plot \
   1/0 lw 4 lc rgb 'blue' with lines t 'Initial', \
   1/0 lw 4 lc rgb 'dark-green' with lines t 'Intermediate', \
   1/0 lw 4 lc rgb 'red' with lines t 'Final'
