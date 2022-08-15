#include <iostream>
#include <string>
#include <cmath>
#include <array>

#include "glew.h"
#include "glfw3.h"

#include "callbacks.h"
#include "input.h"
#include "point.h"
#include "renderer.h"
#include "file.h"
#include "shader.h"
#include "vao.h"

const float 
    DEG_TO_RAD = 0.01745,
    RAD_TO_DEG = 57.2958;

const int 
    GSCR_H = 600,
    GSCR_W = 600;

GLFWwindow* g_window;
VAO gVAO1, gVAO2;
Renderer g_renderer(&g_window);
Shader_program g_shader_program;
Input g_input;

void loop() {
    g_shader_program.use_program();

    float transformer[4];
    while(not glfwWindowShouldClose(g_window)) {
        // Receive Input
        glfwPollEvents();

        // Render
        transformer[0] = glfwGetTime();
        transformer[1] = std::tan(transformer[0] + 180*RAD_TO_DEG);
        glBindVertexArray(transformer[1] < -0.6? gVAO2.get_ID(): gVAO1.get_ID());

        g_shader_program.send_floats("time", transformer, 1);
        g_renderer.render();
    }
}

void prepare() {
    // Getting all the data and read it
    std::array<float, 21> data;
    std::array<float, 21> data2;

    File_handler file;
    file.set_path("../data.txt");
    std::ifstream stream = file.get_stream();
    if(stream.is_open()) {
        int radius, ptr = 0;
        float angle, 
              r, g, b;

        while(ptr < data.size()) {
            stream >> radius >> angle >> r >> g >> b >> data[ptr + 5] >> data[ptr + 6];
            data[ptr] = Point2D::locate(radius, GSCR_H, angle, 'x');
            data[ptr + 1] = Point2D::locate(radius, GSCR_H, angle, 'y');
            data[ptr + 2] = r/255; data[ptr + 3] = g/255; data[ptr + 4] = b/255;
            ptr += 7;
        }
    } else {
        perror("Something went wrong!\n");
        return;
    }

    for(int i = 0; i < data2.size(); i++) {
        if(i % 7 < 3) { data2[i] = -data[i];
        } else { data2[i] = data[i];
        }
    }

    // Preparing buffers
    // [1]===================
    gVAO1.init(); gVAO1.bind();
    Buffer VBO(&data, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW);
    VBO.init(); VBO.bind();
    VBO.send_data();

    gVAO1.set_attrib_pointer(0, 2, 7, &VBO);
    gVAO1.set_attrib_pointer(2, 3, 7, &VBO);

    // [2]===================
    gVAO2.init(); gVAO2.bind();
    Buffer VBO2(&data2, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW);
    VBO2.init(); VBO2.bind();
    VBO2.send_data();
    
    gVAO2.set_attrib_pointer(0, 2, 7, &VBO2);
    gVAO2.set_attrib_pointer(2, 3, 7, &VBO2);

    g_shader_program.set_shader_source_path('V', "../resources/shaders/vertex.glsl");
    g_shader_program.set_shader_source_path('F', "../resources/shaders/fragment.glsl");
    g_shader_program.make_shader_program();
}

void initialize() {
    if(glfwInit() == GLFW_FALSE) {
        printf("Failed to initialize GLFW");
        return;
    }

    g_window = glfwCreateWindow(GSCR_H, GSCR_W, "Title", NULL, NULL);
    glfwMakeContextCurrent(g_window);
    glfwSetFramebufferSizeCallback(g_window, callback::framebuffer_size);

    unsigned int err = glewInit();
    if(err != GLEW_OK) {
        printf("Failed to initialize GLFW: \n%s\n", glewGetErrorString(err));
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int main() {
    initialize();
    prepare();
    loop();
    glfwTerminate();
    return 0;
}
