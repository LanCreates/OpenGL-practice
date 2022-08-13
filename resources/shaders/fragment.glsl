// FRAGMENT SHADER
#version 450 core

struct other_data {
    vec3 color;
};

out vec4 out_color;
in other_data things;

uniform float time;

void main() {
    out_color = vec4(
        things.color + 0.2*sin(time*1.5) + 0.4,
        1.0f
    ); // RGBA
}
