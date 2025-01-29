#include "app/lbm.h"
#include "graphics/render.hpp"

int main() {
    printf("\x1B[32mStarting Initialization!\033[0m\n");
    int iter = 0;
    GLFWwindow* window = initialize_window();

    float* vertices = (float*) malloc(totalPoints * 2 * scale_sq *sizeof(float));
    float* distances = (float*) malloc(totalPoints * scale_sq * sizeof(float));
    initialize_test_points(vertices, distances);
    unsigned int shaderProgram = programInit();
    unsigned int vertex_buffer, distance_buffer, VAO;
    initializeRenderer(&VAO, &vertex_buffer, &distance_buffer, window);
    int i=19800;
    printf("(%f)\n", distances[i]);
    printf("(%f, %f)\n", vertices[2*i], vertices[2*i+1]);
    if (vertices == NULL || distances == NULL) {
        printf("Vertices or distances did not initialize properly!");
        exit(EXIT_FAILURE);
    }
    printf("\x1B[32mFinished Initialization!\033[0m\n");
    while (iter < 1000 && !glfwWindowShouldClose(window)) {
        // printf("\x1B[32mStarting Simulation!\033[0m\n");
        // main function goes here
        bufferData(vertices, distances, vertex_buffer, distance_buffer);
        render(VAO, window, shaderProgram);
        iter++;
    }

    free(vertices);
    free(distances);
    glfwTerminate();
}