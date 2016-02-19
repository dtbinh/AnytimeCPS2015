#include "dynamics.h"
#include "util.h"

#include <math.h>

#ifdef DYNAMICS_VANDERPOL

double vanderpol_eval_y_der(double x, double y)
{
	// y' = (1-x^2)*y - x;

	return (1 - x * x) * y - x;
}

double get_derivative_bounds(HyperRectangle* rect, int faceIndex)
{
	int dim = faceIndex / 2;
	bool isMin = (faceIndex % 2) == 0;

	// x' = y
	// y' = (1-x^2)*y - x;
	// NOTE: I should be checking for local min/max here for correctness
	double rv = 0;

	if (dim == 0)
	{
		if (isMin)
			rv = rect->dims[1].min;
		else
			rv = rect->dims[1].max;
	}
	else if (dim == 1)
	{
		// sample all the corners, note that strictly speaking I also should check for local min/max points
		double points[4][2] =
		{
			{rect->dims[0].min, rect->dims[1].min},
			{rect->dims[0].min, rect->dims[1].max},
			{rect->dims[0].max, rect->dims[1].min},
			{rect->dims[0].max, rect->dims[1].max},
		};

		rv = vanderpol_eval_y_der(points[0][0], points[0][1]);

		for (int i = 1; i < sizeof(points) / sizeof(points[0]); ++i)
		{
			double val = vanderpol_eval_y_der(points[i][0], points[i][1]);

			if (isMin)
				rv = fmin(rv, val);
			else
				rv = fmax(rv, val);
		}
	}
	else
		error_exit("dimension index out of bounds in getDerivativeBounds");

	return rv;
}

#endif
