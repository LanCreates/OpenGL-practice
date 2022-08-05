// FRAGMENT SHADER
#version 450 core
out vec4 out_color;
in vec3 color_data;

uniform float time;

void main() {
    out_color = vec4(
        color_data + 0.2*sin(time*1.5) + 0.4,
        1.0f
    ); // RGBA
}
