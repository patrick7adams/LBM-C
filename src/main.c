#include "app/lbm.h"
#include "graphics/render.hpp"
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("\x1B[32mStarting Initialization!\033[0m\n");
    int iter = 0;
    GLFWwindow* window = initialize_window();

    float* vertices = (float*) malloc(totalPoints * 2 * sizeof(float));
    float* distances = (float*) malloc(totalPoints * sizeof(float));
    initialize_test_points(vertices, distances);
    unsigned int shaderProgram = programInit();
    unsigned int vertex_buffer, distance_buffer, VAO;
    initializeRenderer(&VAO, &vertex_buffer, &distance_buffer, window);
    int i=19800;
    printf("(%f)\n", distances[i]);
    printf("(%f, %f)\n", vertices[2*i], vertices[2*i+1]);

    float* directional_densities = (float*) malloc(totalPoints * 9 * sizeof(float));
    float* directional_densities_bndry = (float*) malloc(totalPoints * 9 * sizeof(float));
    float* directional_densities_old = (float*) malloc(totalPoints * 9 * sizeof(float));
    srand(time(NULL));
    for (int i = 0; i < totalPoints*9; i++) {
        directional_densities[i] = 1.0f + 0.4f * ((float) rand() / RAND_MAX);
    }
    float* densities = (float*) malloc(totalPoints * sizeof(float));
    float* ux = (float*) malloc(totalPoints * sizeof(float));
    float* uy = (float*) malloc(totalPoints * sizeof(float));
    int* walls = (int*) malloc(totalPoints * sizeof(int));

    initialize(walls, directional_densities);

    if (vertices == NULL || distances == NULL) {
        printf("Vertices or distances did not initialize properly!");
        exit(EXIT_FAILURE);
    }
    printf("\x1B[32mFinished Initialization!\033[0m\n");
    while (iter < 3000 && !glfwWindowShouldClose(window)) {
        // printf("\x1B[32mStarting Simulation!\033[0m\n");
        // main function goes here
        // print_point(directional_densities, 1, 1, iter);
        step_lbm(directional_densities, directional_densities_bndry, directional_densities_old, \ 
        densities, ux, uy, walls);
        // print_point(directional_densities, 1, 1, iter);
        // printf("%d - density: %f\n", iter, densities[1*resY+1]);
        plot_lbm(distances, ux, uy);
        // printf("distances - %f\n", distances[1*resX+1]);
        float max_dist = -100.0f;
        for(int i = 0; i < totalPoints; i++) {
            if (distances[i] > max_dist) {
                max_dist = distances[i];
            }
        }
        float scale_factor = 1.0f / max_dist;
        for(int i = 0; i < totalPoints; i++) {
            distances[i] *= scale_factor;
        }
        bufferData(vertices, distances, vertex_buffer, distance_buffer);
        render(VAO, window, shaderProgram);
        // usleep(1000000/60);
        iter++;
    }

    free(vertices);
    free(distances);
    glfwTerminate();
}