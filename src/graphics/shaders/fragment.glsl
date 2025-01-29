 #version 330 core
 in float new_distances;
 out vec4 FragColor;
 void main() {
    FragColor = vec4(new_distances, 1.0, 1.0, 1.0);
}