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


static REAL g = 9.8;
static REAL m = 1/9.8;
static int  L = 1;
static REAL k = 200;
static REAL I = 300;
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

//	// sample all the corners
//	REAL points[16][4] =
//	{
//		{rect->dims[0].min, rect->dims[1].min, rect->dims[2].min, rect->dims[3].min},
//		{rect->dims[0].min, rect->dims[1].min, rect->dims[2].min, rect->dims[3].max},
//		{rect->dims[0].min, rect->dims[1].min, rect->dims[2].max, rect->dims[3].min},
//		{rect->dims[0].min, rect->dims[1].min, rect->dims[2].max, rect->dims[3].max},
//
//		{rect->dims[0].min, rect->dims[1].max, rect->dims[2].min, rect->dims[3].min},
//		{rect->dims[0].min, rect->dims[1].max, rect->dims[2].min, rect->dims[3].max},
//		{rect->dims[0].min, rect->dims[1].max, rect->dims[2].max, rect->dims[3].min},
//		{rect->dims[0].min, rect->dims[1].max, rect->dims[2].max, rect->dims[3].max},
//
//		{rect->dims[0].max, rect->dims[1].min, rect->dims[2].min, rect->dims[3].min},
//		{rect->dims[0].max, rect->dims[1].min, rect->dims[2].min, rect->dims[3].max},
//		{rect->dims[0].max, rect->dims[1].min, rect->dims[2].max, rect->dims[3].min},
//		{rect->dims[0].max, rect->dims[1].min, rect->dims[2].max, rect->dims[3].max},
//
//		{rect->dims[0].max, rect->dims[1].max, rect->dims[2].min, rect->dims[3].min},
//		{rect->dims[0].max, rect->dims[1].max, rect->dims[2].min, rect->dims[3].max},
//		{rect->dims[0].max, rect->dims[1].max, rect->dims[2].max, rect->dims[3].min},
//		{rect->dims[0].max, rect->dims[1].max, rect->dims[2].max, rect->dims[3].max},
//	};

    REAL c  = k/J;
    REAL a  = -m*g*L/I;
    REAL b  = -k/I;
    REAL d  = 1/J;
	REAL rv = 0;
    REAL m1, M1, m2, M2, m3, M3, m4, M4, ul, uu;
    
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
    // lower and upper bounds on u
    ul = 0.1;
    uu = 0.9;
    
    if (dim == 0) { //  x1
        rv = M2;
    }
    else if (dim == 1){ // x2
        
        REAL x1  = acos(-b/a); // \in [0,pi]
        REAL x0  = x1 - PI/2;
        REAL fx0 = b*x0 + a*sin(x0);
        REAL fm1 = b*m1 + a*sin(m1);
        REAL fM1 = b*M1 + a*sin(M1);
        if (fabs(b/a) > 1) {
            // f'(x) = b*x1+a*sin(x1) does not become 0
            REAL df = b+a*cos(m1);
            if (df <= 0) { // so always <0
                rv = -b*M3 + fm1;
            }
            else {
                rv = -b*M3 + fM1;
            }
        }
        else if (M1 <= x0)
            rv = -b*M3 + fM1;
        else if (m1 <= x0 && M1 >= x0)
            rv = -b*M3 + fx0;
        else if (m1 >= x0 && M1 <= x1)
            rv = -b*M3 + fm1;
        else if (m1 <= x1 && M1 > x1) {
            if (fm1 >= fM1)
                rv = -b*M3 + fm1;
            else
                rv = -b*M3 + fM1;
        }
        else if (m1 >= x1 && M1 <= PI) {
            rv = -b*M3 + fM1;
        }
        else {
            printf("CRAP!!! rv = %f, x0=%f, x1=%f, m1=%f, M1=%f \n", rv , x0, x1, m1, M1);
        }
        
    }
    else if (dim == 2) { // x3
        rv = M4;
    }
    else if (dim==3) {
        rv = c*(M1-m3) + d*uu;
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
            REAL minDerNew = 0;// = get_derivative_bounds_new(&rect, 2*d);

			if (minDerOld != minDerNew)
			{
				printf("iteration %d, dim=%d: min der mismatch for rect = \n", i, d);
				println(&rect);

				printf("old = %f\n", minDerOld);
				printf("new = %f\n", minDerNew);

				exit(1);
			}

			// check max ders

            REAL maxDerOld = 0; //= get_derivative_bounds(&rect, 2*d + 1);
            REAL maxDerNew = 0;// = get_derivative_bounds_new(&rect, 2*d + 1);

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
