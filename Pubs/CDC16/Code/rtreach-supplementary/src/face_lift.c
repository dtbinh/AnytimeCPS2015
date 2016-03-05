// Stanley Bak
// 4-2014

#include <stdio.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>

#include "main.h"
#include "face_lift.h"
#include "util.h"

static const REAL PI = 3.1416;

// make a face's neighborhood of a given width
void make_neighborhood_rect(HyperRectangle* out, int f,
		HyperRectangle* bloatedRect, HyperRectangle* originalRect, REAL nebWidth)
{
    //[HA] this returns a nhbd of face f that has width nebWidth.
    // Except along dim d, the nhbd equals bloatedRect. Along d, it extends from the face of _originalRect_ (the non-bloated one) up to width nebWidth along the d axis.
	*out = *bloatedRect;
	bool isMin = (f % 2) == 0;
	int d = f / 2;

	// flatten
	if (isMin)
	{
		out->dims[d].min = originalRect->dims[d].min;
		out->dims[d].max = originalRect->dims[d].min;
	}
	else
	{
		out->dims[d].min = originalRect->dims[d].max;
		out->dims[d].max = originalRect->dims[d].max;
	}

	// swap if nebWidth was negative
	if (nebWidth < 0)
		out->dims[d].min += nebWidth;
	else
		out->dims[d].max += nebWidth;
}


REAL restrict_angle(REAL angle, int dim)
{
    // Restrict angle to the range [-PI, PI]
    REAL ra = angle;
    if (0){//(dim <= 1) {
        if (angle <= PI && angle >= -PI) {
            ra = angle;
        }
        else if (angle > PI) {
            // angle = pi + k*pi + r*pi, k integer, 0<= r <1
            REAL rp = fmod(angle, PI);
            REAL r = rp/PI;
            int m = (angle - rp)/PI - 1;
            if (m % 2 ==0) {
                ra = -(1-r)*PI;
            }
            else {
                ra = r*PI;
            }
        }
        else {
            // angle = -pi -k*pi - r*pi
            REAL rp = fmod(-angle, PI);
            REAL r = rp / PI;
            int m = (-angle - rp)/PI -1 ;
            if (m % 2 == 0) {
                ra = (1-r)*PI;
            }
            else {
                ra = -r*PI;
            }
        }
        printf("Restricted angle %f to %f\n", angle, ra);
    }

    return ra;
}
// necessary to guarantee loop termination
const REAL MAX_DER = 99999;
const REAL MIN_DER = -99999;

// do a single face lifting operation
// [HA] (i.e. for a single stepSize)
// et (error tracker) is set if you want to track the sources of errors, can be null
// returns time elapsed
REAL lift_single_rect(HyperRectangle* rect, REAL stepSize, REAL timeRemaining)
{
  #ifdef DEBUG
	static int debugNumCalls = 0;
	++debugNumCalls;
	//HyperRectangle debug_initialRect = *rect;
  #endif

	////////////////////////////////////////////////
	// estimate the widths of the neighborhoods   //
	// construct bloated rect (for neighborhoods) //

	HyperRectangle bloatedRect = *rect;
	REAL nebWidth[NUM_FACES];

	// initially, estimate nebWidth based on the derivative in the center of the rectangle we care about

    for (int f = 0; f < NUM_FACES; ++f) {
		nebWidth[f] = 0;
    }

	bool needRecompute = true;
	REAL minNebCrossTime;
	REAL ders[NUM_FACES];

    HyperRectangle initialRect = *rect;
    
	while (needRecompute)
	{
		needRecompute = false;
		minNebCrossTime = DBL_MAX;

		for (int f = 0; f < NUM_FACES; ++f)
		{
			int dim = f / 2;
            //[HA] A face is either a 'min' face, meaning it lower bounds the rectangle, or a 'max' face,
            // meaning it upper bounds the rectangle. Knowing which is which matters when we are trying to
            // determine whether the face's neighborhood is inside the rectangle or outside it.
            // Apparently faces with even index are min faces. But look at this: is this really the numbering scheme?
            /*
                    3?
                  ------
                 |      |
             2?  |      |  1
                 |      |
                  ------
                    0
             */
			bool isMin = (f % 2) == 0;
            //DEBUG_PRINT("\tFace %d, dim %d, isMin = %d\n", f, dim, isMin);

			HyperRectangle faceNebRect;

			// make candidate neighborhood
			make_neighborhood_rect(&faceNebRect, f, &bloatedRect, rect, nebWidth[f]);

			// test derivative inside neighborhood
            // function defined in dynamics_*.c
			REAL der = get_derivative_bounds(&faceNebRect, f);

			if (der > MAX_DER) {
				der = MAX_DER;
                        }
			else if (der < MIN_DER) {
				der = MIN_DER;
                        }

			REAL prevNebWidth = nebWidth[f];
			REAL newNebWidth = der * stepSize;

			bool grewOutward = (isMin && newNebWidth < 0) || (!isMin && newNebWidth > 0);
			bool prevGrewOutward = (isMin && prevNebWidth < 0) || (!isMin && prevNebWidth > 0);

			// prevent flipping from outward face to inward face
			if (!grewOutward && prevGrewOutward)
			{
				newNebWidth = 0;
				der = 0;
			}

			// if flipping from inward to outward
			if (!prevGrewOutward && grewOutward) {
				needRecompute = true;
                        }

			// 2nd condition to recompute, der doubled (which means neb width is twice what it was before)
			if (fabs(newNebWidth) > 2 * fabs(prevNebWidth)) {
				needRecompute = true;
                        }

			// adjust bloated rect only if we are requiring a later recomputation
			if (needRecompute)
			{
//                DEBUG_PRINT("\tNeed to recompute\n");
                //[HA] Nhbd recomputation is done iteratively. First, nhbd N0 = face F. We maximize derivative over the face and obtain the max DF.
                // We use DF to build a nhbd N1 of face F of width DF*stepSize. If max derivative over N1, DN1, is larger than 2*DF, then we need
                // to re-compute because a point starting in N0 might pick up speed and exit N1 (which, remember, was computed bvased on DN0).
                // So we compute N2 of width DN1*stepSize, max derivative over that to obtain DN2. And repeat until there's no need to re-compute (or we
                // hit a pre-determined max nb of iterations or something).
                
                // extending the face by stepSize*der , where der is the max derivative we just computed inside the current nhbd.
				nebWidth[f] = newNebWidth;

                if (isMin && nebWidth[f] < 0) {
                    REAL newmin = rect->dims[dim].min + nebWidth[f];
                    newmin = restrict_angle(newmin, dim);
                    bloatedRect.dims[dim].min = newmin;
                }
                else if (!isMin && nebWidth[f] > 0) {
                    REAL newmax = rect->dims[dim].max + nebWidth[f];
                    newmax = restrict_angle(newmax, dim);
					bloatedRect.dims[dim].max = newmax;
                }
			}
			else
			{
				// might be the last iteration, compute min time to cross face
				// clamp derivative if it changed direction
				// this means along the face it's inward, but in the neighborhood it's outward
				if (der < 0 && prevNebWidth > 0) {
					der = 0;
                }
				else if (der > 0 && prevNebWidth < 0) {
					der = 0;
                }

				if (der != 0)
				{
                    //[HA] this is how much reach time will actually elapse if we use this der value along this face.
                    // crossTime will be less than stepSize if der > prev der, but it will always be at least stepSize/2.
                    // That's because if der > 2*prev der (which is what would cause crossTime to be less than stepSize/2), needToRecompute = true and we
                    // recompute smaller nhbds.
					REAL crossTime = prevNebWidth / der;

					if (crossTime < minNebCrossTime) {
						minNebCrossTime = crossTime;
                                        }
				}

				ders[f] = der;
//                DEBUG_PRINT("\tders[%d] = %f\n", f, der);
			}
		} // ends for each fce
	} // ends while need to recompute
    

    //[HA] If we've reached here, this means we didn't need to re-compute, so we have a good minNebCrossTime.
	if (minNebCrossTime * 2 < stepSize)
	{
		//sanity check
		error_exit("minNebCrossTime is less than half of step size.");
	}
	////////////////////////////////////////
	// lift each face by the minimum time //

	REAL timeToElapse = minNebCrossTime;

	// subtract a tiny amount time due to multiplication / division rounding
	timeToElapse = timeToElapse * 99999 / 100000;

	if (timeRemaining < timeToElapse) {
		timeToElapse = timeRemaining;
        }

	// do the lifting
	for (int d = 0; d < NUM_DIMS; ++d)
	{
        REAL lowerbound = restrict_angle(ders[2*d] * timeToElapse, d);
		rect->dims[d].min += lowerbound;
        REAL upperbound = restrict_angle(ders[2*d+1] * timeToElapse, d);
		rect->dims[d].max += upperbound;
	}
    
//    if (!hyperrectangle_contains(rect, &initialRect, true) ) {
//        printf("Lifted rectangle does not contain input rectangle.\nLifted:");
//        println(rect);
//        printf("\nInitial:");
//        println(&initialRect);
//        error_exit("Bye\n");
//    }

	if (!hyperrectangle_contains(&bloatedRect, rect, true))
	{
		//printf("error occurred when debugNumCalls = %d\n", debugNumCalls);
		//printf("rect = ");
		//println(&debug_initialRect);

		error_exit("lifted rect is outside of bloated rect");
	}

	return timeToElapse;
}

// generate a split rectangle
void generateSplitRectangle(HyperRectangle* rectToSplit, HyperRectangle* out,
		int iteratorVal, int splitDimensions[NUM_DIMS])
{
	for (int dimIndex = 0; dimIndex < NUM_DIMS; ++dimIndex)
	{
		int mask = splitDimensions[dimIndex];
		int splitNum = iteratorVal % mask;
		iteratorVal /= mask;

		REAL width = interval_width(&rectToSplit->dims[dimIndex]) / splitDimensions[dimIndex];

		// assign the current dimension
		out->dims[dimIndex].min = rectToSplit->dims[dimIndex].min + splitNum * width;
		out->dims[dimIndex].max = out->dims[dimIndex].min + width;
	}
}

///////////////// below is from header file ///////////////

HyperRectangle face_lifting_iterative_improvement(int startMs, LiftingSettings* settings)
{
    // startMs: when this code started running
	bool lastIterationSafe = false;

	set_error_print_params(settings);

	REAL stepSize = settings->initialStepSize;

	int iter = 0; // number of iterations

    HyperRectangle trackedRect;
    
    printf("Initial set is ");
    println(&settings->init);
    printf("\n\n");
    
	while (true)
	{
		iter++;
		bool safe = true; // until proven otherwise

		// if we've cut the step size way too far where floating point error may be a factor
		if (stepSize < 0.0000001)
		{
			DEBUG_PRINT("Quitting from step size too small: stepSize: %0.10f at iteration: %d\n\r", stepSize, iter);
			break;
		}

		if (settings->restartedComputation) {
			settings->restartedComputation();
                }

		REAL reachTimeRemaining = settings->reachTime;
		trackedRect = settings->init;
//		HyperRectangle hull;
        

		// compute reachability up to split time
		while (safe && reachTimeRemaining > 0)
		{
            // [HA] commenting this out as it doesn't seem hull is used for anything
			//if (settings->reachedAtIntermediateTime) {
			//	hull = trackedRect;
            //}

			// debug changed so error tracker is always passed in (see note)
			REAL timeElapsed = lift_single_rect(&trackedRect, stepSize, reachTimeRemaining);

			// if we're not even close to the desired step size
            REAL hrwidth = hyperrectange_max_width(&trackedRect);
			if (hrwidth > settings->maxRectWidthBeforeError)
			{
				DEBUG_PRINT("Width %f exceeds maxRectWidthBeforeError at reach time %f, iter = %d, rect = ",
						hrwidth, settings->reachTime - reachTimeRemaining, iter);
				#if DEBUG
				println(&trackedRect);
				#endif
				// step size is too large, make it smaller and recompute
				safe = false;
			}
            // [HA]Commenting out this else since for our application, we don't have an unsafe set when computing the reach sets.
            // We just want the reach set and so don't want to interrupt anything.
//			else if (settings->reachedAtIntermediateTime)
//			{
//				hyperrectangle_grow_to_convex_hull(&hull, &trackedRect);
//
//				safe = safe && settings->reachedAtIntermediateTime(&hull);
//			}
            
            //[HA] ran out of time, so check whether it entered the recoverable region before declaring failure
            // This too is commented out since we don't have a recoverable region in our application
//			if (timeElapsed == reachTimeRemaining && settings->reachedAtFinalTime)
//				safe = safe && settings->reachedAtFinalTime(&trackedRect);

			reachTimeRemaining -= timeElapsed;
		}

		int now = milliseconds();
		int elapsedTotal = now - startMs;

		DEBUG_PRINT("%dms: ran reachability wiht stepSize = %f\n",	elapsedTotal, stepSize);

		if (settings->maxRuntimeMilliseconds > 0)
		{
			int remaining = settings->maxRuntimeMilliseconds - elapsedTotal;

			if (remaining < 0)
			{
				// we've exceeded our time, use the result from the last iteration
				// note in a real system you would have an interrupt or something to cut off computation
				DEBUG_PRINT("Quitting from runtime maxed out\n\r");
				break;
			}
		}
		else
		{
			// if max runtime was negative, this means we want to split a fixed number of times
            //[HA] no clue what this is doing,
			if (settings->maxRuntimeMilliseconds++ == 0)
			{
				DEBUG_PRINT("Splitting\n\r");
				break;
			}
		}

		lastIterationSafe = safe;

		// apply error-reducing strategy
		stepSize /= 2;
	}

	DEBUG_PRINT("Nb of stepSize reductions at quit: %d\n\r", iter);

    return trackedRect;
//	return rv;
}
