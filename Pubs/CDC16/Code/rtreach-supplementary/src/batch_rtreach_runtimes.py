import subprocess
import os
from math import radians, degrees

# range of floats (range only allows ints)
# http://stackoverflow.com/questions/477486/python-decimal-range-step-value
# https://docs.python.org/2/tutorial/controlflow.html
#def drange(start, stop, step):
#	r = start
#	while r < stop:
#		yield r
#		r += step

DEBUG = 0;

RV_UNSAFE = 0;
RV_LMI_SAFE = 1;
RV_SIM_SAFE = 2;
RV_RTREACH_SAFE = 3;

#runtimes = [5, 20, 40, 50, 75, 100, 200, 500, 1000]; # runtimes from rtss2014 table
# all runtimes next
runtimes = [5, 20, 40, 50, 75, 100, 200, 500, 1000, 2000,3000,4500,6000]; # runtimes from rtss2014 table
#runtimes = [2000,3000,4500,6000];
#runtimes = [10, 20];
#runtimes = [100];

#num_samples = 5;
#num_samples = 12;
#num_samples = 14; # yields 44100
num_samples = 15; # value used in rtss paper on x86

x_min = -1.25;
#x_step = 0.05;
x_max = 1.25;
x_step = (x_max - x_min) / (num_samples - 1);

v_min = -1.2;
#v_step = 0.1;
v_max = 1.2;
v_step = (v_max - v_min) / (num_samples - 1);

#theta = radians(0);
#omega = radians(0);
theta_min = radians(-20);
theta_max = radians(20);
theta_step = (theta_max - theta_min) / (num_samples - 1);

omega_min = radians(-30);
omega_max = radians(30);
omega_step = (omega_max - omega_min) / (num_samples - 1);

print "test!"

x_vals = []
v_vals = []
theta_vals = []
omega_vals = []

# todo next: use num_samples + 1, this creates a slightly uneven scenario currently
# e.g., consider num_samples = 3
# let x_min = -1, x_max = 1
# x_step = (x_max - x_min) / num_samples = 1 - 1 = 2 / 3 = 2/3
# points taken are: -1, -1+2/3=-1/3, -1+4/3=1/3
# I guess other fix would be to take (x_max - x_min) / (num_samples-1)
# which would give:
# 1 - 1 = 2 / (3-2) = 2/2 = 1
# values are: -1, 0, 1, as desired
for i in range(0,num_samples):
	x_vals.append(x_min + i * x_step);
	v_vals.append(v_min + i * v_step);
	theta_vals.append(theta_min + i * theta_step);
	omega_vals.append(omega_min + i * omega_step);

print x_vals
print v_vals
print theta_vals
print omega_vals

x_iter = 0;
v_iter = 0;
theta_iter = 0;
omega_iter = 0;

for rt in runtimes:
	iters = 0;
	count_unsafe = 0;
	count_lmisafe = 0;
	count_simsafe = 0;
	count_rtsafe = 0;

	#for x in drange(x_min, x_max, x_step):
	for x in x_vals:
		v_iter = 0;
		#for v in drange(v_min, v_max, v_step):
		for v in v_vals:
			theta_iter = 0;
			#for theta in drange(theta_min, theta_max, theta_step):
			for theta in theta_vals:
				omega_iter = 0;
				#for omega in drange(omega_min, omega_max, omega_step):
				for omega in omega_vals:
					# rtreach(rt, state(1), state(2), state(3), state(4)) % this is the right order, rtreach(runtime, x, v, theta, omega)
					# call shell script: http://stackoverflow.com/questions/3777301/how-to-call-a-shell-script-from-python-code
					rtreach_call_args = ['./rtreach_arm', str(rt), str(x), str(v), str(theta), str(omega)];
					if DEBUG:
						print rtreach_call_args
					#subprocess.Popen('echo $PWD', shell=True)
					p = subprocess.Popen(rtreach_call_args, stdout=None, stderr=None, shell=False);
					#subprocess.Popen('./rtreach_arm'); # works with no args
					#print "start wait"
					retval = p.wait(); # wait for process to complete (to avoid starting lots of processes and messing up timing, etc.)
					#print "done wait"
					#retval = 0
					if DEBUG:
						print "rtreach: " + str( retval )

					if retval == RV_UNSAFE:
						count_unsafe = count_unsafe + 1;
					elif retval == RV_LMI_SAFE:
						count_lmisafe = count_lmisafe + 1;
					elif retval == RV_SIM_SAFE:
						count_simsafe = count_simsafe + 1;
					elif retval == RV_RTREACH_SAFE:
						count_rtsafe = count_rtsafe + 1;
					else:
						print "ERROR: unhandled return value"

					omega_iter = omega_iter + 1;
					iters = iters + 1;
					
				if omega_iter != num_samples:
					print "ERROR OMEGA"
				theta_iter = theta_iter + 1;
			if theta_iter != num_samples:
				print "ERROR THETA"
			v_iter = v_iter + 1;
		if v_iter != num_samples:
			print "ERROR V"
		x_iter = x_iter + 1;
	if not x_iter != num_samples:
		print "ERROR X"
		
	if iters != num_samples*num_samples*num_samples*num_samples:
		print "ERROR num samples bad"

	print os.linesep
	print "runtime: " + str( rt )
	print "total iter: " + str( iters )
	print "unsafe: " + str( count_unsafe )
	print "lmisafe: " + str( count_lmisafe )
	print "simsafe: " + str( count_simsafe )
	print "rtsafe: " + str( count_rtsafe )

	per_unsafe = count_unsafe / float(iters);
	per_lmisafe = count_lmisafe / float(iters);
	per_simsafe = count_simsafe / float(iters);
	per_rtsafe = count_rtsafe / float(iters);

	if count_lmisafe == 0:
		count_lmisafe = 1;

	per_improve = (count_rtsafe + count_lmisafe) / float(count_lmisafe);

	print "percent unsafe: " + str( per_unsafe )
	print "percent simsafe: " + str( per_simsafe )
	print "percent rtsafe: " + str( per_rtsafe )

#\textbf{Runtime (ms)} & \textbf{LMI} & \textbf{RealTime} & \textbf{Sim} & \textbf{Unrecov} & \textbf{Improve}\tabularnewline
#	5 & 5473  & 6180  & 1376  & 37596  & 213\% \tabularnewline
	print "TABLE ENTRY: "
	print str( rt ) + ' & ' + str( count_lmisafe ) + ' & ' + str( count_rtsafe ) + ' & ' + str( count_simsafe ) + ' & ' + str( count_unsafe ) + ' & ' + str( per_improve ) + " \\\\ "
