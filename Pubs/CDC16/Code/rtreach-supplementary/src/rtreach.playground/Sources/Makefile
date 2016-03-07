
CC = gcc
CC_arm = arm-linux-gnueabi-gcc
CC_arm_noos = arm-none-eabi-gcc
FLAGS = -std=gnu99 -O3 -Wall 
LIBS = -lm
FLAGS_ARM = -static
GNUPLOT = gnuplot
RTREACH_CORE = face_lift.c geometry.c interval.c simulate.c util.c
RTREACH_EXAMPLES =  dynamics_arm.c
# RTREACH_EXAMPLES = dynamics_pendulum.c
# RTREACH_EXAMPLES = dynamics_converging_oscillator.c dynamics_harmonic_oscillator.c dynamics_vanderpol.c dynamics_pendulum.c dynamics_pendulum_nonlinear.c

# using static on arm to enable double comparisons...:http://stackoverflow.com/questions/25756939/gnu-c-atof-strtof-and-strtod-fail-debian-for-beagleboard

# TODO: detect the architecture/os and pick compiler based on that...

all: x86

arm:
	$(CC) $(FLAGS) $(FLAGS_ARM) main.c $(RTREACH_CORE) $(RTREACH_EXAMPLES) pendulum.c $(LIBS) -o rtreach_arm -DLINEAR_PENDULUM

arm_noos:
	$(CC_arm_noos) $(FLAGS) $(FLAGS_ARM) main.c $(RTREACH_CORE) $(RTREACH_EXAMPLES) pendulum.c $(LIBS) -o rtreach_arm_noos -DLINEAR_PENDULUM

x86:
	$(CC) $(FLAGS) main.c $(RTREACH_CORE) $(RTREACH_EXAMPLES) pendulum.c $(LIBS) -o rtreach -DLINEAR_PENDULUM

clean:
	rm -f rtreachcar rtreacharm

mpccar: clean
	$(CC) $(FLAGS) mpcmain.c $(RTREACH_CORE) $(RTREACH_EXAMPLES) car.c $(LIBS) -o rtreachcar -DLINEAR_PENDULUM

mpcarm: clean
	$(CC) $(FLAGS) mpcmain.c $(RTREACH_CORE) $(RTREACH_EXAMPLES) arm.c $(LIBS) -o rtreacharm -DMANIPULATOR_ARM

x86_nonlinear:
	$(CC) $(FLAGS) main.c $(RTREACH_CORE) $(RTREACH_EXAMPLES) pendulum.c $(LIBS) -o rtreach -DNONLINEAR_PENDULUM
# for nonlinear pendulum, use -DNONLINEAR_PENDULUM instead of -DLINEAR_PENDULUM

x86_plot_linear_pendulum:
	$(CC) $(FLAGS) main_plots.c $(RTREACH_CORE) $(RTREACH_EXAMPLES) pendulum_plots.c $(LIBS) -o rtreach_plots.exe -DLINEAR_PENDULUM
    
x86_plot_nonlinear_pendulum:
	$(CC) $(FLAGS) main_plots.c $(RTREACH_CORE) $(RTREACH_EXAMPLES) pendulum_plots.c $(LIBS) -o rtreach_plots.exe -DNONLINEAR_PENDULUM
