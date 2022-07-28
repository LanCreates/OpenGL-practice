// FRAGMENT SHADER
#version 450 core
layout (location = 0) out vec4 color;
in vec3 color_data;

uniform vec3 color_transformer;

void main() {
    color = vec4(color_data*color_transformer, 1.0f); // RGBA
}
