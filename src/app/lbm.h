#ifndef __LBM__
#define __LBM__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "constants.h"
#include <sys/time.h>

// lbm-related constants (for D2Q9 schema)
const float probabilities[9] = {4.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f, 1.0f/36.0f};
const int dx[9] = {0, 1, 0, -1, 0, 1, -1, -1, 1};
const int dy[9] = {0, 0, 1, 0, -1, 1, 1, -1, -1};
const int num_iterations = 10000;
const float relaxation_time = 0.53f;
const float viscosity = 1.0f/relaxation_time;



void initialize_test_points(float* vertices, float* distances);
void print_point(float* directional_densities, int x, int y, int iter);
void initialize_walls(int* walls);
void initialize(int* walls, float* directional_densities);
void step_lbm(float* directional_densities, float* directional_densities_tmp, float* densities, float* ux, float* uy, int* walls);
void streaming_step(float* directional_densities_tmp, float* directional_densities);
void srt_bgk_collision_step(float* directional_densities, float* directional_densities_tmp, float* densities, float* ux, float* uy, int* walls);
void plot_lbm(float* distances, float* ux, float* uy);

#endif