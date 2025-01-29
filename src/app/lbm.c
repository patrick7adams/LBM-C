#include "lbm.h"

void initialize_test_points(float* vertices, float* distances) {
    for (int i = 0; i < totalPoints; i++) {
        vertices[2*i] = ((float)(i%resX)+1.0f) / (0.5f*resX) - 1.0f;
        vertices[2*i+1] = ((float)(i/resX)+1.0f) / (0.5f*resY) - 1.0f;
        distances[i] = (float) (i%2);
    }
}

void initialize_walls(int* walls) {
    // figure out wall processing here eventually, for now just create a square in the middle
    for (int i = 0; i < resX; i++) {
        for (int k = 0; k < resY; k++) {
            if (abs(i-resX/2) < 10 && abs(k-resY/2) < 10) {
                walls[i*resY+k] = 1;
            } else {
                walls[i*resY+k] = 0;
            } 
        }
    }
}

void initialize(int* walls, float* directional_densities) {
    initialize_walls(walls);
    int flow_direction = 2;
    for (int i = 0; i < resX; i++) {
        for (int k = 0; k < resY; k++) {
            directional_densities[i*resY*9 + k*9 + flow_direction] = 2.3;
        }
    }
}

void run_lbm(float* distances) {
    // define and initialize all state variables here
    float* directional_densities = (float*) malloc(totalPoints * 9 * sizeof(float));
    float* directional_densities_eq = (float*) malloc(totalPoints * 9 * sizeof(float));
    float* directional_densities_old = (float*) malloc(totalPoints * 9 * sizeof(float));
    memset(directional_densities, 1.0f, totalPoints * 9 * sizeof(float));
    float* densities = (float*) malloc(totalPoints * sizeof(float));
    float* ux = (float*) malloc(totalPoints * sizeof(float));
    float* uy = (float*) malloc(totalPoints * sizeof(float));
    int* walls = (int*) malloc(totalPoints * sizeof(int));

    initialize(walls, directional_densities);
    while (t < num_iterations) {
        step_lbm(directional_densities, directional_densities_eq, directional_densities_old, \ 
        densities, ux, uy, walls);




        t++;
    }
}

void step_lbm(
    float* directional_densities, float* directional_densities_eq, \
float* directional_densities_old, float* densities, float* ux, float* uy, float* walls)  {

}

void streaming_step(float* old_directional_densities, float* directional_densities) {

}

void srt_bgk_collision_step() {

}