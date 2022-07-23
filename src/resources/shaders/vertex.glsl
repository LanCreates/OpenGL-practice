// VERTEX SHADER
#version 450 core 
layout (location = 0) in vec2 position; 
layout (location = 1) in vec3 transformer;

uniform vec2 u_transformer;
out vec3 color_data;

void main() {
    gl_Position = vec4(position.x, //*u_transformer.x, 
                       position.y, //*u_transformer.y,
                       0.0f, 1.0f);
    color_data = transformer;
}
