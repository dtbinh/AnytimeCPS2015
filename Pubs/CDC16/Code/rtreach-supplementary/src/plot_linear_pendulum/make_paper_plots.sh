#!/bin/bash

# this bash script makes the data for the plots reach_large, reach_mid, and reach_small for the paper.


cd ..



if ! make x86_plot_linear_pendulum; then
 echo 'Compile Error'
 exit 1
fi

# large
if ! (./rtreach_plots.exe -3 0.725 -0.1 0.85 0 0); then
  echo 'Running Rtreach Failed'
  exit 1
fi

if ! cp -v *.gnuplot.txt plot_linear_pendulum/large_files; then
  echo 'copying gnuplot.txt failed'
  exit 1
fi

# med
./rtreach_plots.exe -5 0.725 -0.1 0.85 0 0
cp *.gnuplot.txt plot_linear_pendulum/med_files

# small
./rtreach_plots.exe -7 0.725 -0.1 0.85 0 0
cp *.gnuplot.txt plot_linear_pendulum/small_files

# use custom .plot file for correct titles and such
cd plot_linear_pendulum/large_files
gnuplot < plot_large.gnuplot
cp *.png ..

# use custom .plot file for correct titles and such
cd ../med_files
gnuplot < plot_med.gnuplot
cp *.png ..

# use custom .plot file for correct titles and such
cd ../small_files
gnuplot < plot_small.gnuplot
cp *.png ..


