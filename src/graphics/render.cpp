#include "render.hpp"
extern "C" {
	#include "shader_constants.h"
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void error_callback(int error, const char* description) {
	std::cout << "\x1B[31mError " << error << ":\033[0m " << description << '\n';
}

// Initializes the window, GLFW, and Glad.
GLFWwindow* initialize_window() {
	if(!glfwInit()) {
		std::cout << "Initialization failed" << '\n';
	} else {
		std::cout << "Window initialization successful" << '\n';
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	// glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	// glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(resX, resY, "LBM Awesome", NULL, NULL);
	if (!window) {
		std::cout << "Window failed to create" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetErrorCallback(error_callback);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
	glfwSetTime(0.0);

	return window;
}

unsigned int programInit() {
    const char *vertex = (char*) src_graphics_shaders_vertex_glsl;
    const char *fragment = (char*) src_graphics_shaders_fragment_glsl;

    // vertex shader

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex, NULL);
    glCompileShader(vertexShader);

    int success;
	char log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    glGetProgramInfoLog(vertexShader, 512, NULL, log);
    printf("Vertex shader info log: %s\n", log);
	if (!success) {
		fprintf(stderr, "Vertex shader failed to compile!\n");
		glDeleteShader(vertexShader);
	}

    // Fragment shader

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment, NULL);
    glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    glGetProgramInfoLog(fragmentShader, 512, NULL, log);
    printf("Fragment shader info log: %s\n", log);
	if (!success) {
		fprintf(stderr, "Fragment shader failed to compile.\n");
		glDeleteShader(fragmentShader);
	}

    // Shader program

    unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindAttribLocation(shaderProgram, 0, "vertices");
	glBindAttribLocation(shaderProgram, 0, "colors");
	glLinkProgram(shaderProgram);

    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    glGetProgramInfoLog(shaderProgram, 512, NULL, log);
    printf("Program info log: %s\n", log);
	if (!success) {
		fprintf(stderr, "Shader program failed to link.\n");
		glDeleteShader(shaderProgram);
	}

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void initializeRenderer(unsigned int* VAO, unsigned int* vertex_buffer, unsigned int* dist_buffer, GLFWwindow* window) {
	printf("Initializing the renderer...\n");
	// VBO and VAO Initialization
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, vertex_buffer);
	glGenBuffers(1, dist_buffer);
	glBindVertexArray(*VAO);
}

void bufferData(float* vertices, float* distances, unsigned int vertex_buffer, unsigned int dist_buffer) {
	// printf("Buffering new data...\n");

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, totalPoints * 2 * sizeof(float), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//delete[] vertices;

	glBindBuffer(GL_ARRAY_BUFFER, dist_buffer);
	glBufferData(GL_ARRAY_BUFFER, totalPoints * sizeof(float), distances, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, (void*)0); // careful here
	glEnableVertexAttribArray(1);
	//delete[] colors;
}

// this needs to be entirely reworked later on
// ---------------------------------------------
// void save(float* colorData, int iter) {
// 	#define RGB_CHANNEL_COUNT 3
// 	#define FILENAME_LEN 10
// 	printf("Saving image data...");

// 	char filename[FILENAME_LEN];
// 	sprintf(filename, "img_%d.ppm", iter);
// 	FILE* file = fopen(filename, "wb");
// 	fprintf(file, "P6\n%d %d 255\n", resX, resY);

// 	// convert color data from (0, 1) scale to (0, 255)
// 	// unsigned char* newColorData = (unsigned char*)malloc(3 * totalPoints*sizeof(int));
// 	for (int i = 0; i < totalPoints*3; i++) {
// 		fputc((int)(colorData[i] * 255), file);
// 	}
// 	// stbi_write_png(filename, resX, resY, RGB_CHANNEL_COUNT, newColorData, resX*sizeof(unsigned char));
// }

void render(unsigned int VAO, GLFWwindow* window, unsigned int shaderProgram) {
	// printf("Rendering the set...\n");
	// Wireframe Mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, totalPoints * 2);

	glfwSwapBuffers(window);
	glfwPollEvents();
}