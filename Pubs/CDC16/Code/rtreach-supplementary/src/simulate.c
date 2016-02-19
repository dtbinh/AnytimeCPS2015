#include <stdio.h>
#include "simulate.h"

void simulate(REAL startPoint[NUM_DIMS],
			  REAL stepSize,
			  bool (*shouldStop)(REAL state[NUM_DIMS], REAL simTime, void* p),
			  void* param)
{
    // Simulate the system one stepSize at a time until shouldStop decides it should stop simulating.
    // The simulation happens using Euler's method
    // param will hold the value of the timeToSafe
	REAL point[NUM_DIMS];

	for (int d = 0; d < NUM_DIMS; ++d) {
		point[d] = startPoint[d];
        }

	HyperRectangle rect;
//	REAL time = stepSize; // was 0.0f
	REAL time = 0.0f;

	while (true)
	{
		if (shouldStop(point, time, param)) {
			DEBUG_PRINT("Quitting simulation: time: %f, stepSize: %f\n\r", time, stepSize);
			break;
		}

		for (int d = 0; d < NUM_DIMS; ++d) {
			rect.dims[d].min = rect.dims[d].max = point[d];
		}

		// euler's method

		for (int d = 0; d < NUM_DIMS; ++d)
		{
			REAL der = get_derivative_bounds(&rect, 2*d);

			point[d] += stepSize * der;
		}

		time += stepSize;
	}
}
