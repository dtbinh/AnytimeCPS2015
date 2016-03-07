// Stanley Bak
// Pendulum Real-time reach check header

#ifndef CAR_H_
#define CAR_H_

#include <stdbool.h>
#include "geometry.h"
#include "main.h"

// return the potential of the lmi-outputted function for a given state
REAL potential(REAL pos, REAL vel, REAL theta, REAL omega);

// check if the passed-in state is provably safe
int isSafe(int runtimeMs, REAL state[NUM_DIMS]);

// run reachability for a given wall timer (or iterations if negative)
HyperRectangle runReachability(REAL start[][2], REAL simTime, REAL wallTimeMs, REAL startMs);

#endif
