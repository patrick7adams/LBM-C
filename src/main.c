#include "app/lbm.h"
#include "graphics/render.hpp"

int main() {
    printf("\x1B[32mStarting Initialization!\033[0m\n");
    int iter = 0;
    GLFWwindow* window = initialize_window();

    unsigned int* vertices = (unsigned int*) malloc(totalPoints * 2 * sizeof(unsigned int));
    float* distances = (float*) malloc(totalPoints * sizeof(float));
    initialize_test_points(vertices, distances);
    int i = 501;
    printf("(%d, %d)\n", vertices[i*2], vertices[i*2+1]);
    printf("%f\n", distances[i]);
    unsigned int shaderProgram = programInit();
    unsigned int vertex_buffer, distance_buffer, VAO;
    initializeRenderer(&VAO, &vertex_buffer, &distance_buffer, window);
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