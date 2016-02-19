#include "main.h"
#include "dynamics.h"
#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef DYNAMICS_PENDULUM

// a saturated controlled inverted pendulum
// X' = AX + Bu, with u = KX, u between -4.95 and 4.95
// where X = [pos_error velocity angle angular_vel]^T

static const REAL A[4][4] =
{
	{0, 1, 0, 0},
	{0, -10.95, -2.75, 0.0043},
	{0, 0, 0, 1},
	{0, 24.92, 28.58, -0.044},
};

// true if >= 0
static const bool A_sgn[4][4] =
{
	{true, true, true, true},
	{true, false, false, true},
	{true, true, true, true},
	{true, true, true, false},
};

static const REAL B[4] = {0, 1.94, 0, -4.44}; // transposed

// true if >= 0
static const bool B_sgn[4] = {true, true, true, false};

// saftry controller from paper: static const REAL K[4] = {6, 20, 60, 16};

// from lmi solving:
static const REAL K[4] = {0.4072    ,  7.2373 , 18.6269 , 3.6725};

// true if >= 0
static const bool K_sgn[4] = {true, true, true, true};

int numDerivativeBoundsCalls = 0;

REAL eval_dim_old(int dim, REAL state[4])
{
	REAL rv = 0;

	// do the AX part
	for (int i = 0; i < 4; ++i)
		rv += A[dim][i] * state[i];

	// do the Bu part
	REAL u = 0;

	// u = KX
	for (int i = 0; i < 4; ++i)
		u += K[i] * state[i];

	// input saturation
	if (u < -4.95)
		u = -4.95;
	else if (u > 4.95)
		u = 4.95;

	// B*u
	rv += B[dim] * u;

	return rv;
}

REAL get_derivative_bounds(HyperRectangle* rect, int faceIndex)
{
	++numDerivativeBoundsCalls;

	int dim = faceIndex / 2;
	bool isMin = (faceIndex % 2) == 0;

	// sample all the corners
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

	REAL rv = 0;

	if (dim >= 4)
		error_exit("dimension index out of bounds in getDerivativeBounds");

	rv = eval_dim_old(dim, points[0]);

	for (int i = 1; i < 16; ++i)
	{
		REAL val = eval_dim_old(dim, points[i]);

		if (isMin && val < rv)
		{
			rv = val;
		}
		else if (!isMin && val > rv)
			rv = val;
	}

	return rv;
}

REAL get_derivative_bounds_new(HyperRectangle* rect, int faceIndex)
{
	++numDerivativeBoundsCalls;

	int dim = faceIndex / 2;
	bool isMin = (faceIndex % 2) == 0;

	REAL rv = 0;

	// do the AX part
	for (int i = 0; i < 4; ++i)
	{
		REAL val = 0;

		if (!isMin == A_sgn[dim][i])
			val = rect->dims[i].max * A[dim][i];
		else
			val = rect->dims[i].min * A[dim][i];

		rv += val;
		//rv += A[dim][i] * state[i];
	}

	if (faceIndex == 2)
	{
		printf("after ax = %f\n", rv);

		REAL debugAx = 0;

		for (int i = 0; i < 4; ++i)
			debugAx += A[dim][i] * rect->dims[i].min;

		printf("debugAx = %f\n", debugAx);
	}

	// do the Bu part
	// Bu = BKX
	REAL u = 0;
	bool maximizingU = true;

	if (!B_sgn[dim])
		maximizingU = false;

	// u = KX
	for (int i = 0; i < 4; ++i)
	{
		if (K_sgn[i] == maximizingU)
			u += K[i] * rect->dims[i].max;
		else
			u += K[i] * rect->dims[i].min;
	}

	// input saturation
	if (u < -4.95)
		u = -4.95;
	else if (u > 4.95)
		u = 4.95;

	// B*u
	rv += B[dim] * u;


	return rv;
}

// test function for comparing between optimized dynamics and original dynamics
void test_dynamics()
{
	HyperRectangle rect;

	srand(500);

	for (int i = 0; i < 100000; ++i)
	{
		for (int d = 0; d < NUM_DIMS; ++d)
		{
			REAL start = (((rand() % 100) / 100.0) - 0.5);

			rect.dims[d].min = start;
			rect.dims[d].max = start + 0.3;
		}

		for (int d = 0; d < NUM_DIMS; ++d)
		{
			REAL minDerOld = get_derivative_bounds(&rect, 2*d);
			REAL minDerNew = get_derivative_bounds_new(&rect, 2*d);

			if (minDerOld != minDerNew)
			{
				printf("iteration %d, dim=%d: min der mismatch for rect = \n", i, d);
				println(&rect);

				printf("old = %f\n", minDerOld);
				printf("new = %f\n", minDerNew);

				exit(1);
			}

			// check max ders

			REAL maxDerOld = get_derivative_bounds(&rect, 2*d + 1);
			REAL maxDerNew = get_derivative_bounds_new(&rect, 2*d + 1);

			if (maxDerOld != maxDerNew)
			{
				printf("iteration %d, dim=%d: max der mismatch for rect = \n", i, d);
				println(&rect);
				exit(1);
			}
		}
	}

	printf("done testing dynamics! exiting...");
	exit(1);
}

#endif
