// Stanley Bak
// 4-2014
// Simulate Header

#ifndef SIMULATE_H_
#define SIMULATE_H_

#include "dynamics.h"
#include "geometry.h"
#include "main.h"
#include <stdbool.h>

// simulate dynamics using Eurler's method
void simulate(REAL point[NUM_DIMS],
			  REAL stepSize,
			  bool (*shouldStop)(REAL state[NUM_DIMS], REAL simTime, void* p),
			  void* param);

#endif
