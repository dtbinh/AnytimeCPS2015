#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "pendulum.h"
#include "util.h"

int main(int argc, char** argv)
{
	int rv = 0;

	if (argc != 7)
	{
		printf("Usage: rt_reach (milliseconds-runtime) (seconds-reachtime) (position) (velocity) (angle) (angular velocity)\n");
		printf("If milliseconds is negative, it will split a fixed number of times\n");
		rv = 1;
	}
	else
	{
		int ms = atoi(argv[1]);
        
		if (ms < 0)
			printf("splitting time step exactly %i times ", -ms);
		else
		{
			printf("Using time bound. Please note that the times will be inflated and noisy, "
				"because we're outputting the reach set to files on disk. Normally you wouldn't have this overhead.\n\n");
			printf("Running for %i ms ", ms);
		}
        
        double reachTime = atof(argv[2]);
        printf("Reach time is %f seconds\n", reachTime);

		// setttings for pendulum
		double startState[4] = {atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6])};

		printf("from state = [%f, %f, %f, %f]\n",
				startState[0], startState[1], startState[2], startState[3]);

		// state = {pos, vel, angle, angular_vel}
		// from startState = {-0.1, vel, 0, 0};
		// set velocity to 0.6 for a recoverable state inside the ellipse
		// set velocity to 0.7 for a recoverable state slightly outside of the ellipse
		// set velocity to 0.8 for a recoverable state outside of the ellipse
		// set velocity to 0.9 for an unrecoverable state

		printf("potential of start state = %f\n",
				potential(startState[0], startState[1], startState[2], startState[3]));
		fflush(stdout);

		//bool safe = isSafeTimed(ms, startState);
        bool safe = runReachability(startState, reachTime, ms, milliseconds());

		printf("finished computation, result = %s\n", safe ? "safe" : "unsafe");
	}

	return rv;
}
