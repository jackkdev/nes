#version 400 core

in vec3 in_position;
in vec3 in_color;

out vec3 vertex_color;

uniform mat4 model;
uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(in_position.xy, 0.0f, 1.0f);
    vertex_color = in_color;
}