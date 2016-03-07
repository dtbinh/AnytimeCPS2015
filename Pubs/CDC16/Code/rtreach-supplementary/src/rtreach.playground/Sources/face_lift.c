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

REAL restrict_state(REAL angle, int dim)
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
    REAL prevders[NUM_FACES];
    REAL ders[NUM_FACES];
	// initially, estimate nebWidth based on the derivative in the center of the rectangle we care about

    for (int f = 0; f < NUM_FACES; ++f) {
		nebWidth[f] = 0;
        prevders[f] = 0;
    }

    
	bool needRecompute = true;
	REAL minNebCrossTime;
    HyperRectangle initialRect = *rect;
    
	while (needRecompute)
	{
		needRecompute = false;
		minNebCrossTime = DBL_MAX;

		for (int f = 0; f < NUM_FACES; ++f)
		{
            //[HA] Faces are indexed as follows: along dimension d (d=0,1,...), faces are 2*d and 2*d+1. The implicit casting to integer gives d from f.
            // E.g. dimension 0 has faces 0 and 1, dimension 1 has faces 2 and 3, dimension 2 has faces 4 and 5, etc.
			int dim = f / 2;
            
            //[HA] A face is either a 'min' face, meaning it lower bounds the rectangle, or a 'max' face,
            // meaning it upper bounds the rectangle. Knowing which is which matters when we are trying to
            // determine whether the face's neighborhood is inside the rectangle or outside it.
            // The first of the faces along a dimension is the 'min' face (and so that's the face with even index), the other is the 'max' face
            /* This illustrates the indexing scheme in 2 dimensions
                    3
                  ------
                 |      |
             0   |      |  1
                 |      |
                  ------
                    2
             */
			bool isMin = (f % 2) == 0;

			HyperRectangle faceNebRect;

			// make candidate neighborhood
			make_neighborhood_rect(&faceNebRect, f, &bloatedRect, rect, nebWidth[f]);

			// test derivative inside neighborhood
            // function defined in dynamics_*.c. This is a signed quantity
			REAL der = get_derivative_bounds(&faceNebRect, f);

			if (der > MAX_DER) {
				der = MAX_DER;
                        }
			else if (der < MIN_DER) {
				der = MIN_DER;
                        }

			REAL prevNebWidth = nebWidth[f];
			REAL newNebWidth = der * stepSize;
            REAL prevder = prevders[f];
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
                DEBUG_PRINT("\tRecompute: face %d, isMin=%d, prevGrewOut=%d, grewOut=%d\n",
                            f,  isMin,  prevGrewOutward, grewOutward);

            }

			// 2nd condition to recompute, der doubled (which means neb width is twice what it was before)
            //[HA] modified this from commented version
            //      max face: both derivatives drive outward (are +ve) and new one is faster, or both drive inward (are -ve) and new one is slower
            if (  (!isMin && prevNebWidth > 0 && newNebWidth > 2 *prevNebWidth)|| (!isMin && prevNebWidth <0 && newNebWidth < 2*prevNebWidth)) {
                needRecompute = true;
                DEBUG_PRINT("\tRecompute: max face %d, prevder = %f, curder = %f, prevNhbd=%.14f, newNhbdWidth = %.14f\n",
                            f,  prevder, der, prevNebWidth, newNebWidth);
            }
                // min face: both derivatives drive outward (are -ve) and new one is faster, or both drive inward (are +ve) and new one is slower
            else if ((isMin && prevNebWidth <0 && newNebWidth < 2*prevNebWidth)) {
                needRecompute = true;
                DEBUG_PRINT("\tRecompute: min face %d, outward prevder = %f, curder = %f, prevNhbd=%.9f, newNhbdWidth = %.9f\n",
                            f,  prevder, der, prevNebWidth, newNebWidth);
            }
            else if ((isMin && prevNebWidth>0 && newNebWidth < 2*prevNebWidth)) {
                needRecompute = true;
                DEBUG_PRINT("\tRecompute: min face %d, inward prevder = %f, curder = %f, prevNhbd=%f, newNhbdWidth = %f, diff=%.14f\n",
                            f,  prevder, der, prevNebWidth, newNebWidth, prevder - der);

            }
//			if (fabs(newNebWidth) > 2 * fabs(prevNebWidth)) {
//				needRecompute = true;
//                        }

			// adjust bloated rect only if we are requiring a later recomputation
			if (needRecompute)
			{
                //[HA] Nhbd recomputation is done iteratively. First, nhbd N0 = face F. We maximize derivative over the face and obtain the max DF.
                // We use DF to build a nhbd N1 of face F of width DF*stepSize. If max derivative over N1, DN1, is larger than 2*DF, then we need
                // to re-compute because a point starting in N0 might pick up speed and exit N1 (which, remember, was computed bvased on DN0).
                // So we compute N2 of width DN1*stepSize, maximize derivative over that to obtain DN2. And repeat until there's no need to re-compute (or we
                // hit a pre-set maximum width for the nhbd beyond which it is "ridiculous" to keep increasing its size).
                
                // extending the face by stepSize*der , where der is the max derivative we just computed inside the current nhbd.
				nebWidth[f] = newNebWidth;
                if (isMin && nebWidth[f] < 0) {
                    REAL newmin = rect->dims[dim].min + nebWidth[f];
                    newmin = restrict_state(newmin, dim);
                    bloatedRect.dims[dim].min = newmin;
                }
                else if (!isMin && nebWidth[f] > 0) {
                    REAL newmax = rect->dims[dim].max + nebWidth[f];
                    newmax = restrict_state(newmax, dim);
					bloatedRect.dims[dim].max = newmax;
                }
			}
			else
			{
				// might be the last iteration, compute min time to cross face
				// clamp derivative if it changed direction
				// this means along the face it's inward, but in the neighborhood it's outward
                if ((der < 0 && prevNebWidth > 0) || (der > 0 && prevNebWidth < 0)) {
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
            prevders[f]  = der;
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
        REAL lowerbound = restrict_state(ders[2*d] * timeToElapse, d);
		rect->dims[d].min += lowerbound;
        REAL upperbound = restrict_state(ders[2*d+1] * timeToElapse, d);
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
    // In case no computation yields precise enough results, returnn this empty guy
    HyperRectangle shitRect;
    for (int d=0; d<NUM_DIMS; d++) {
        shitRect.dims[d].min = shitRect.dims[d].max = 1234;
    }
    
    
#ifdef DEBUG
    printf("Initial set is ");
    println(&settings->init);
    printf("\n\n");

    FILE* reachfile;
    reachfile = fopen("reachset.m", "w");
    if (reachfile== NULL)
        error_exit("whata da fuck!");
    
    fprintf(reachfile, "reachy = [\n");
#endif
    
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
                trackedRect = shitRect;
			}
            else {
                reachTimeRemaining -= timeElapsed;
#ifdef DEBUG
                fprintf(reachfile, "%f,%f, %f, %f,  %f, %f,  %f, %f, %f; \n",
                        trackedRect.dims[0].min, trackedRect.dims[0].max,
                        trackedRect.dims[1].min, trackedRect.dims[1].max,
                        trackedRect.dims[2].min, trackedRect.dims[2].max,
                        trackedRect.dims[3].min, trackedRect.dims[3].max,
                        timeElapsed);
#endif
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
    fprintf(reachfile, "\n];");
    fclose(reachfile);
    

	DEBUG_PRINT("Nb of stepSize reductions at quit: %d\n\r", iter);

    return trackedRect;
//	return rv;
}
