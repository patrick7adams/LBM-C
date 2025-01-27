#include "lbm.h"

void initialize_test_points(unsigned int* vertices, float* distances) {
    for (int i = 0; i < totalPoints; i++) {
        vertices[2*i] = i%resX;
        vertices[2*i+1] = i/resX;
        distances[i] = (float) (i%2);
    }
}