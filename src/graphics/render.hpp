#ifndef RENDER_HPP
#define RENDER_HPP

extern "C" {
	#include "glad.h"
	#include "glfw3.h"
	#include "constants.h"
	#include <math.h>
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void error_callback(int error, const char* description);
GLFWwindow* initialize_window();
unsigned int programInit();
void initializeRenderer(unsigned int* VAO, unsigned int* vertex_buffer, unsigned int* dist_buffer, GLFWwindow* window);
void bufferData(float* vertices, float* distances, unsigned int vertex_buffer, unsigned int dist_buffer);
// void save(float* colorData, int iter);
void render(unsigned int VAO, GLFWwindow* window, unsigned int shaderProgram);
#endif