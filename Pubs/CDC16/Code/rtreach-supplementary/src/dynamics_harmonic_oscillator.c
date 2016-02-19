#include "dynamics.h"
#include "util.h"
#include <math.h>

#ifdef DYNAMICS_HARMONIC_OSCILLATOR

double get_derivative_bounds(HyperRectangle* rect, int faceIndex)
{
	int dim = faceIndex / 2;
	bool isMin = (faceIndex % 2) == 0;

	// x' = y
	// y' = -x
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
		if (isMin)
			rv = fmin(-rect->dims[0].max, -rect->dims[0].min);
		else
			rv = fmax(-rect->dims[0].max, -rect->dims[0].min);
	}
	else
		error_exit("dimension index out of bounds in getDerivativeBounds");

	return rv;
}

#endif
