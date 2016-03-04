#include "main.h"
#include "dynamics.h"
#include "util.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "dynamics_arm.h"

#ifdef DYNAMICS_ARM

#define NUM_DIMS (4)

// a saturated controlled inverted pendulum
// X' = AX + Bu, with u = KX, u between -4.95 and 4.95
// where X = [pos_error velocity angle angular_vel]^T

static REAL m = 1;
static REAL g = 9.8;
static int  L = 1;
static int  k = 200;
static REAL I = 1;
static REAL J = 1;
static const REAL PI = 3.14;

int numDerivativeBoundsCalls = 0;


REAL get_derivative_bounds(HyperRectangle* rect, int faceIndex)
{
    //[HA] user-defined function
    // This only maximizes the derivative of the ith state variable, where i = dim = faceIndex /2
    // This is equivalent to maximizing the projection of the gradient onto the ith dimension
	++numDerivativeBoundsCalls;
    
    // [HA] ?? why is dim = faceIndex/2 (and why not just pass dimension)
	int dim = faceIndex / 2;
	// bool isMin = (faceIndex % 2) == 0;

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

    REAL c  = k/J;
    REAL a  = -m*g*L/I;
	REAL rv = 0;
    REAL m1, M1, m2, M2, m3, M3, m4, M4;
    
    int ii=0;
    m1 = rect->dims[ii].min;
    M1 = rect->dims[ii].max;
    ii++;
    m2 = rect->dims[ii].min;
    M2 = rect->dims[ii].max;
    ii++;
    m3 = rect->dims[ii].min;
    M3 = rect->dims[ii].max;
    ii++;
    m4 = rect->dims[ii].min;
    M4 = rect->dims[ii].max;
    
    if (dim == 0) { //  x1
        rv = M1;
    }
    else if (dim == 1){ // x2
        if (a >= -1) {
            rv = M1 + a*sin(M1);
        }
        else {
            REAL x1 = acos(-1/a); // \in [0,pi]
            REAL x0 = x1 - PI/2;
            REAL fx0 = x0 + a*sin(x0);
            REAL fm1, fM1;
            if (M1 <= x0)
                rv = M1 + a*sin(M1);
            else if (m1 <= x0 && M1 >= x0)
                rv = fx0;
            else if (m1 >= x0 && M1 <= x1)
                rv = m1+a*sin(m1);
            else if (m1 <= x1 && M1 > x1) {
                fm1 = m1 + a*sin(m1);
                fM1 = M1 + a*sin(M1);
                if (fm1 >= fM1)
                    rv = fm1;
                else
                    rv = fM1;
            }
            else if (m1 >= x1) {
                rv = M1 + a*sin(M1);
            }
            else {
                printf("CRAP!!!");
            }
            
        }
    }
    else if (dim == 2) {
        rv = M4;
    }
    else if (dim==3) {
        rv = c*(M1-m3);
    }

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
            REAL minDerNew;// = get_derivative_bounds_new(&rect, 2*d);

			if (minDerOld != minDerNew)
			{
				printf("iteration %d, dim=%d: min der mismatch for rect = \n", i, d);
				println(&rect);

				printf("old = %f\n", minDerOld);
				printf("new = %f\n", minDerNew);

				exit(1);
			}

			// check max ders

            REAL maxDerOld; //= get_derivative_bounds(&rect, 2*d + 1);
            REAL maxDerNew;// = get_derivative_bounds_new(&rect, 2*d + 1);

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
