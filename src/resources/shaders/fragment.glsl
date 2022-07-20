// FRAGMENT SHADER
#version 450 core
layout (location = 0) out vec4 color;
uniform vec3 u_color;

void main() {
    color = vec4(u_color, 1.0f); // RGBA
}
