#include "pendulum.h"

#include "face_lift.h"
#include "util.h"
#include "simulate.h"
#include <stdio.h>

static FILE* f_initial;
static FILE* f_intermediate;
static FILE* f_final;

void close_files(bool closeInitial)
{
	if (closeInitial && f_initial)
		fclose(f_initial);

	if (f_intermediate)
		fclose(f_intermediate);

	if (f_final)
		fclose(f_final);
}

void open_files(bool openInitial)
{
	if (openInitial)
		f_initial = fopen("initial.gnuplot.txt", "w");

	f_intermediate = fopen("intermediate.gnuplot.txt", "w");
	f_final = fopen("final.gnuplot.txt", "w");

	if (!f_initial || !f_intermediate || !f_final)
	{
		close_files(true);

		error_exit("error opening files");
	}
}

void restartedComputation()
{
	// close and open the files to clear them
	close_files(false);
	open_files(false);
}

// styleIndex: 0 = init, 1 = intermediate, 2 = final
void hyperrectangle_to_file(FILE* fout, HyperRectangle* r, int styleIndex)
{
	if (fout)
	{
		int X_DIM = 0;
		int Y_DIM = 1;

		const char* styleStr[] =
		{
			"set label ' Init' at %f, %f point pointtype 3 lc rgb 'blue' tc rgb 'blue'",
			"set obj rect from %f, %f to %f, %f fc rgbcolor 'dark-green' fs solid 0.2 noborder\n",
			"set obj rect from %f, %f to %f, %f fc rgbcolor 'red' fs solid 0.3 noborder\n",
		};

		fprintf(fout, styleStr[styleIndex], r->dims[X_DIM].min, r->dims[Y_DIM].min,
				r->dims[X_DIM].max, r->dims[Y_DIM].max);
	}
}

// called on states reached during the computation
bool intermediateState(HyperRectangle* r)
{
	bool allowed = true;

	hyperrectangle_to_file(f_intermediate, r,1);

	return allowed;
}

REAL potential(REAL pos, REAL vel, REAL theta, REAL omega)
{
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

	hyperrectangle_to_file(f_final, rect,2);
	printf("--->  potential of final state = %f\n", maxPotential);

	return maxPotential < 1;
}

bool shouldStop(REAL state[NUM_DIMS], REAL simTime, void* p)
{
	bool rv = false;
	REAL pot = potential(state[0], state[1], state[2], state[3]);
	REAL maxTime = 2.0;

	if (pot < 1)
	{
		rv = true;

		REAL* stopTime = (REAL*)p;
		*stopTime = simTime;
	}

	if (simTime >= maxTime)
	{
		rv = true;

		REAL* stopTime = (REAL*)p;
		*stopTime = -1;
	}

	return rv;
}

bool runReachability(REAL* start, REAL simTime, REAL wallTimeMs, REAL startMs)
{
	LiftingSettings set;

	for (int d = 0; d < NUM_DIMS; ++d)
	{
		set.init.dims[d].min = start[d];
		set.init.dims[d].max = start[d];
	}

	set.reachTime = simTime;
	set.maxRuntimeMilliseconds = wallTimeMs;

	set.initialStepSize = set.reachTime / 10;
	set.maxRectWidthBeforeError = 100;

	set.reachedAtFinalTime = finalState;
	set.reachedAtIntermediateTime = intermediateState;
	set.restartedComputation = restartedComputation;

	open_files(true);
	hyperrectangle_to_file(f_initial, &set.init, 0);

	bool safe =  face_lifting_iterative_improvement(startMs, &set);
	close_files(true);

	return safe;
}

REAL getSimulatedSafeTime(REAL start[4])
{
	REAL stepSize = 0.02;
	REAL rv = 0;

	simulate(start, stepSize, shouldStop, (void*)&rv);

	printf("time until simulation reaches safe state = %f\n", rv);

	return rv;
}

int isSafe(int runtimeMs, REAL state[NUM_DIMS])
{
	int rv = 0;
	int startMs = milliseconds();

	REAL timeToSafe = getSimulatedSafeTime(state);

	if (timeToSafe < 0)
		printf("simulation is never safe, no need to run\n");
	else
	{
		REAL reachTime = timeToSafe * 1.25;
		printf("running reachabiltiy for time = %f\n", reachTime);
		rv = runReachability(state, reachTime, runtimeMs, startMs);
	}

	return rv;
}
