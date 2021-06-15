#version 400 core

in vec3 vertex_color;

out vec4 color;

void main() {
    color = vec4(vertex_color.xyz, 1.0f);
}