#include "car.h"
#include "main.h"
#include "face_lift.h"
#include "util.h"
#include "simulate.h"
#include <stdio.h>


bool intermediateState(HyperRectangle* r)
{
    // [HA] User provided funct. Checks whether the rectangle r (which is the reachable region) contains unsafe states
    // Called on states reached during the computation
    // This hard-codes the unsafe set in the bounds below

	bool allowed = true;
	const REAL FIFTEEN_DEGREES_IN_RADIANS = 0.2618;

	// check if the constraints are satisfied

	if (r->dims[0].min < -1 || r->dims[0].max > 1) // position limits
		allowed = false;
	else if (r->dims[1].min < -1 || r->dims[1].max > 1) // velocity limits
		allowed = false;
	else if (r->dims[2].min < -FIFTEEN_DEGREES_IN_RADIANS || r->dims[2].max > FIFTEEN_DEGREES_IN_RADIANS)
		allowed = false;

	return allowed;
}

REAL potential(REAL pos, REAL vel, REAL theta, REAL omega)
{
    // [HA] User-provided function. Computes x'Px, where P defines the recoverable ellipsoid
	REAL state[] = {pos, theta, vel, omega};

	REAL P_lmi[4][4] = {
			{1.0520,    1.2082,    0.2580,    0.1988},
			{1.2082,   33.9334,    4.6631,    4.0269},
			{0.2580,    4.6631,    2.2108,    1.0090},
			{0.1988,    4.0269,    1.0090,    0.8424}
	};

	// X^t * P * x

	REAL xTransposeTimesP[4] = {0, 0, 0, 0};

	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
			xTransposeTimesP[row] += P_lmi[col][row] * state[col];
	}

	REAL rv = 0;

	for (int row = 0; row < 4; ++row)
		rv += xTransposeTimesP[row] * state[row];

	return rv;
}

bool finalState(HyperRectangle* rect)
{
    // [HA] user-provided fnt. Checks whether all points in the rectangle rect is inside the recoverable region, which
    // is an ellipsoid defined by matrix P
    // This is done by checking whether all 16 vertices of the rectangle are in the ellipsoid
	REAL points[16][4] =
	{
		{rect->dims[0].min, rect->dims[1].min, rect->dims[2].min, rect->dims[3].min},
		{rect->dims[0].min, rect->dims[1].min, rect->dims[2].min, rect->dims[3].max},
		{rect->dims[0].min, rect->dims[1].min, rect->dims[2].max, rect->dims[3].min},
		{rect->dims[0].min, rect->dims[1].min, rect->dims[2].max, rect->dims[3].max},

		{rect->dims[0].min, rect->dims[1].max, rect->dims[2].min, rect->dims[3].min},
		{rect->dims[0].min, rect->dims[1].max, rect->dims[2].min, rect->dims[3].max},
		{rect->dims[0].min, rect->dims[1].max, rect->dims[2].max, rect->dims[3].min},
		{rect->dims[0].min, rect->dims[1].max, rect->dims[2].max, rect->dims[3].max},

		{rect->dims[0].max, rect->dims[1].min, rect->dims[2].min, rect->dims[3].min},
		{rect->dims[0].max, rect->dims[1].min, rect->dims[2].min, rect->dims[3].max},
		{rect->dims[0].max, rect->dims[1].min, rect->dims[2].max, rect->dims[3].min},
		{rect->dims[0].max, rect->dims[1].min, rect->dims[2].max, rect->dims[3].max},

		{rect->dims[0].max, rect->dims[1].max, rect->dims[2].min, rect->dims[3].min},
		{rect->dims[0].max, rect->dims[1].max, rect->dims[2].min, rect->dims[3].max},
		{rect->dims[0].max, rect->dims[1].max, rect->dims[2].max, rect->dims[3].min},
		{rect->dims[0].max, rect->dims[1].max, rect->dims[2].max, rect->dims[3].max},
	};

	REAL maxPotential = potential(points[0][0], points[0][1], points[0][2], points[0][3]);

	for (int i = 1; i < 16; ++i)
	{
		REAL p = potential(points[i][0], points[i][1], points[i][2], points[i][3]);

		if (p > maxPotential)
			maxPotential = p;
	}

	DEBUG_PRINT("--->  potential of final state = %f\n", maxPotential);

	return maxPotential < 1;
}

bool shouldStop(REAL state[NUM_DIMS], REAL simTime, void* p)
{
    // [HA]
    // simTime is the current (simulation) time, i.e. state = x(simTime)
    // p holds the value of timeToSafe and is an output
	bool rv = false;
	REAL pot = potential(state[0], state[1], state[2], state[3]);
	REAL maxTime = 2.0f;

	DEBUG_PRINT("\n\r\n\rpot: %f\n\rmaxTime: %f\n\r", pot, maxTime);

	if (pot < 1)
	{
		rv = true;
//		rv = (bool)1;
//		rv = false;

        // [HA] pretty contorted: pointer stopTime is made to point to the same memory address as p,
        // then is used to place the value simTime in there. This way p points to the value simTime,
        // and that is taken to be timeToSafe by the caller of this function.
		REAL* stopTime = (REAL*)p;
		DEBUG_PRINT("p from pointer: %p\n\r", (REAL *)p);
		*stopTime = simTime; // should set *p = simTime?
//		*p = simTime;
//		*p = maxTime;

		DEBUG_PRINT("\n\r\n\rp: %p\n\rstopTime: %f\n\rrv: %d\n\r", (REAL*)p, *stopTime, rv);
		if (rv) {
			DEBUG_PRINT("RV TRUE\n\r");
		}
	}

	if (simTime >= maxTime)
	{
        // [HA] So the caller has been simulating for a while (upto maxtime) without being told to stop by this fnt
        // stopTime is set to -1 indicating that safe set was never entered.
        // rv = true to indicate the caller should stop.
        // This logic really belongs in caller, not here.
		rv = true;

		REAL* stopTime = (REAL*)p;
		*stopTime = -1;
	}

	return rv;
}

HyperRectangle runReachability(REAL start[][2], REAL simTime, REAL wallTimeMs, REAL startMs)
{
	LiftingSettings set;

	for (int d = 0; d < NUM_DIMS; ++d)
	{
		set.init.dims[d].min = start[d][0];
		set.init.dims[d].max = start[d][1];
	}

	set.reachTime = simTime;
	set.maxRuntimeMilliseconds = wallTimeMs;

    // [HA] initial reachTimeStepSize is 10% the desired reach  horizon
	REAL iss = set.reachTime;
//	iss = iss / 10.0f; // problem with division?
	iss = iss * 0.10f;

	DEBUG_PRINT("\n\rsimTime: %f\n\rreachTime: %f\n\r\n\r", simTime, set.reachTime);

	set.initialStepSize = iss; //set.reachTime / 10.0f;
	set.maxRectWidthBeforeError = 100;

	set.reachedAtFinalTime = finalState;
	set.reachedAtIntermediateTime = intermediateState;
	set.restartedComputation = 0; //restartedComputation;

	HyperRectangle reachSet = face_lifting_iterative_improvement(startMs, &set);
//    printf("\n\n====== Reach set \n");
//    				println(&reachSet);
    return reachSet;
}

REAL getSimulatedSafeTime(REAL start[4])
{
    // [HA] Returns the time to enter safe set from vector start
    // It does so by forward simulating the system from start
	REAL stepSize = 0.02f;
	REAL rv = 0.0f;

	simulate(start, stepSize, shouldStop, (void*)&rv); // TODO: look here

	DEBUG_PRINT("time until simulation reaches safe state = %f\n", rv);

	return rv;
}
