#include "lbm.h"

void print_point(float* directional_densities, int x, int y, int iter) {
    printf("%d - (", iter);
    for (int i = 0; i < 9; i++) {
        printf("%f, ", directional_densities[x*resX*9 + y*9 + i]);
    }
    printf(")\n");
}

void print_time(struct timeval* start, struct timeval* end, char* text) {
    double time_elapsed = ((*end).tv_sec - (*start).tv_sec) + ((*end).tv_usec - (*start).tv_usec) / 1000000.0;
    printf(text);
    printf("%f\n", time_elapsed);
}

void initialize_test_points(float* vertices, float* distances) {
    for (int i = 0; i < totalPoints; i++) {
        vertices[2*i] = ((float)(i%resX)+1.0f) / (0.5f*resX) - 1.0f;
        vertices[2*i+1] = ((float)(i/resX)+1.0f) / (0.5f*resY) - 1.0f;
        distances[i] = (float) (i%2);
    }
}

void initialize_walls(int* walls) {
    // figure out wall processing here eventually, for now just create a square in the middle
    for (int i = 0; i < resY; i++) {
        for (int k = 0; k < resX; k++) {
            // if (abs(i-resY/2) < 10 && abs(k-resX/2) < 10) {
            //     walls[i*resX+k] = 1;
            // } else {
            //     walls[i*resX+k] = 0;
            // } 
            if (sqrt((i-resY/2) * (i-resY/2) + (k-resX/2) * (k-resX/2)) < 20) {
                walls[i*resX+k] = 1;
            } else {
                walls[i*resX+k] = 0;
            } 
        }
    }
}

void initialize(int* walls, float* directional_densities) {
    initialize_walls(walls);
    int flow_direction = 2;
    for (int i = 0; i < resY; i++) {
        for (int k = 0; k < resX; k++) {
            directional_densities[i*resX*9 + k*9 + flow_direction] = 2.3 + 0.4f * ((float) rand() / RAND_MAX);
        }
    }
}

void step_lbm(
    float* directional_densities, float* directional_densities_bndry, \
float* directional_densities_old, float* densities, float* ux, float* uy, int* walls)  {
    struct timeval stream, collide, end;
    gettimeofday(&stream, NULL);
    streaming_step(directional_densities_old, directional_densities);
    gettimeofday(&collide, NULL);
    srt_bgk_collision_step(directional_densities, directional_densities_bndry, densities, ux, uy, walls);
    gettimeofday(&end, NULL);
    // print_time(&stream, &collide, "Stream time: ");
    // print_time(&collide, &end, "Collide time: ");
}

void streaming_step(float* old_directional_densities, float* directional_densities) {
    // ~0.0135 seconds to run
    for (int j = 0; j < resY; j++) {
        for (int k = 0; k < resX; k++) {
            for (int i = 0; i < 9; i++) {
                int jx = (j+dx[i]+resY)%resY;
                int kx = (k+dy[i]+resX)%resX;
                old_directional_densities[jx*resX*9 + kx*9+i] = directional_densities[j*resX*9 + k*9 + i];
            }
        }
    }
    memcpy(directional_densities, old_directional_densities, totalPoints*9*sizeof(float));
}

void srt_bgk_collision_step(float* directional_densities, float* directional_densities_bndry, float* densities, float* ux, float* uy, int* walls) {
    // ~0.019 seconds
    for (int j = 0; j < resY; j++) {
        for (int k = 0; k < resX; k++) {
            int index = j*resX+k;
            densities[index] = 0.0f;
            ux[index] = 0.0f;
            uy[index] = 0.0f;
            for (int i = 0; i < 9; i++) {
                densities[index] += directional_densities[index*9 + i];
                ux[index] += directional_densities[index*9 + i] * dx[i];
                uy[index] += directional_densities[index*9 + i] * dy[i];
            }
            ux[index] /= densities[index];
            uy[index] /= densities[index];
        }
    }
    // save all directional densities into tmp array
    // ~0.0009 seconds
    memcpy(directional_densities_bndry, directional_densities, resX*resY*9*sizeof(float));
    for (int j = 0; j < resY; j++) {
        for (int k = 0; k < resX; k++) {
            int index = j*resX+k;
            float tmp;
            if (walls[index]) {
                // flip around all density directions
                tmp = directional_densities_bndry[9*index + 1];
                directional_densities_bndry[9*index+1] = directional_densities_bndry[9*index+3];
                directional_densities_bndry[9*index+3] = tmp;
                tmp = directional_densities_bndry[9*index + 2];
                directional_densities_bndry[9*index+2] = directional_densities_bndry[9*index+4];
                directional_densities_bndry[9*index+4] = tmp;
                tmp = directional_densities_bndry[9*index + 5];
                directional_densities_bndry[9*index+5] = directional_densities_bndry[9*index+7];
                directional_densities_bndry[9*index+7] = tmp;
                tmp = directional_densities_bndry[9*index + 6];
                directional_densities_bndry[9*index+6] = directional_densities_bndry[9*index+8];
                directional_densities_bndry[9*index+8] = tmp;
                ux[index] = 0;
                uy[index] = 0;
                for (int i = 0; i < 9; i++) {
                    directional_densities[9*index+i] = directional_densities_bndry[9*index+i];
                }
                
            }
        }
    }
    // ~0.032 seconds
    for (int j = 0; j < resY; j++) {
        for (int k = 0; k < resX;  k++) {
            int index = j*resX+k;
            for (int i = 0; i < 9; i++) {
                float dp = dx[i]*ux[index] + dy[i]*uy[index];
                float abs_val = ux[index]*ux[index] + uy[index]*uy[index];
                float eq_number_density = densities[index] * probabilities[i] * (1.0f + 3.0f*dp + (9.0f/2.0f)*dp*dp - (3.0f/2.0f)*abs_val);
                float diff = eq_number_density - directional_densities[9*index+i];
                directional_densities[9*index+i] += viscosity * diff;
            }
        }
    }
}

void plot_lbm(float* distances, float* ux, float* uy) {
    for (int j = 0; j < resY; j++) {
        for (int k = 0; k < resX; k++) {
            int index = j*resX+k;
            distances[index] = sqrtf(ux[index]*ux[index] + uy[index]*uy[index]);
        }
    }
}