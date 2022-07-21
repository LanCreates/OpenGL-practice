// VERTEX SHADER
#version 450 core 
layout (location = 0) in vec2 position; 
uniform vec2 u_transformer;

void main() {
    gl_Position = vec4(position.x*u_transformer.x, 
                       position.y*u_transformer.y,
                       0.0f, 1.0f);
}
