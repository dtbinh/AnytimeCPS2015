#include "main.h"
#include "dynamics.h"
#include "util.h"
#include <math.h>

#ifdef DYNAMICS_CONVERGING_OSCILLATOR


// x' = y - 0.5 x
// y' = -0.5y - x

REAL evalX(REAL x, REAL y)
{
	return y - 0.5*x;
}

REAL evalY(REAL x, REAL y)
{
	return -0.5*y - x;
}

REAL get_derivative_bounds(HyperRectangle* rect, int faceIndex)
{
	int dim = faceIndex / 2;
	bool isMin = (faceIndex % 2) == 0;

	// sample all the corners
	REAL points[4][2] =
	{
		{rect->dims[0].min, rect->dims[1].min},
		{rect->dims[0].min, rect->dims[1].max},
		{rect->dims[0].max, rect->dims[1].min},
		{rect->dims[0].max, rect->dims[1].max},
	};

	REAL rv = 0;

	if (dim == 0)
	{

		rv = evalX(points[0][0], points[0][1]);

		for (int i = 1; i < 4; ++i)
		{
			REAL val = evalX(points[i][0], points[i][1]);

			if (isMin && val < rv)
				rv = val;
			else if (!isMin && val > rv)
				rv = val;
		}
	}
	else if (dim == 1)
	{

		rv = evalY(points[0][0], points[0][1]);

		for (int i = 1; i < 4; ++i)
		{
			REAL val = evalY(points[i][0], points[i][1]);

			if (isMin && val < rv)
				rv = val;
			else if (!isMin && val > rv)
				rv = val;
		}
	}
	else
		error_exit("dimension index out of bounds in getDerivativeBounds");

	return rv;
}

#endif
