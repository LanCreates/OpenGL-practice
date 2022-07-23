// FRAGMENT SHADER
#version 450 core
layout (location = 0) out vec4 color;

uniform vec3 changer;
in vec3 color_data;

void main() {
    color = vec4(color_data, 1.0f); // RGBA
}
