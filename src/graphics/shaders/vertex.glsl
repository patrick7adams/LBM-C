 #version 330 core
 layout (location = 0) in vec2 vertices;
 layout (location = 1) in float distances;
 out float new_distances;
 
 void main() {
    gl_Position = vec4(vertices, 0.0, 1.0);
    new_distances = distances;
}