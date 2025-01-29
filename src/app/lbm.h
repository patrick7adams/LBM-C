#ifndef __LBM__
#define __LBM__

#include <stdlib.h>
#include <math.h>
#include "constants.h"

// lbm-related constants (for D2Q9 schema)
const float probabilities[9] = {4.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f};
const int dx[9] = {0, 1, 0, -1, 0, 1, -1, -1, 1};
const int dy[9] = {0, 0, 1, 0, -1, 1, 1, -1, -1};
const int t = 0;
const int num_iterations = 10000;
const float relaxation_time = 0.53f;
const float viscosity = 1.0f/relaxation_time;



void initialize_test_points(float* vertices, float* distances);


#endif