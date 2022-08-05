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

const float DEG_TO_RAD = 0.01745,
            RAD_TO_DEG = 57.2958;
const int GSCR_H = 600;
const int GSCR_W = 600;

GLFWwindow* GWindow;
Render_handler Grenderer(&GWindow);
Shader_handler Gshader;
Input_handler Ginput;
File_handler Gfile(1);

unsigned int Gvertex_array_object;

void loop() {
    std::array<float, 15> data;
    std::array<float, 15> data2;
    
    unsigned int indices[] = {
        0, 1, 2,   0, 2, 3,
        0, 3, 4,   0, 4, 5,
        0, 5, 6,   0, 6, 1
    };
    
    Gfile.set_path("../data.txt");
    std::ifstream stream = Gfile.get_stream();
    if(stream.is_open()) {
        int radius, ptr = 0;
        float angle, r, g, b;
    
        while(ptr < data.size()) {
            stream >> radius >> angle >> r >> g >> b;
            data[ptr] = Point2D::locate(radius, GSCR_H, angle, 'x');
            data[ptr + 1] = Point2D::locate(radius, GSCR_H, angle, 'y');
            data[ptr + 2] = r/255; data[ptr + 3] = g/255; data[ptr + 4] = b/255;
            ptr += 5;
        }
    } else {
        perror("Something went wrong!\n");
        exit(0);
    }

    for(int i = 0; i < 15; i++) {
        if(i % 5 < 3) { data2[i] = -data[i];
        } else { data2[i] = data[i];
        }
    }
    
    unsigned int vertex_array_obj;
    glGenVertexArrays(1, &vertex_array_obj);

    std::array<unsigned int, 2> vertex_buffer_object; 
    glGenBuffers(2, vertex_buffer_object.begin());
    unsigned int index_array_object; glGenBuffers(1, &index_array_object);

    glGenVertexArrays(1, &Gvertex_array_object);
    glBindVertexArray(Gvertex_array_object);

    // TODO: Create something to make this tidy
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_array_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glBindVertexArray(vertex_array_obj);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data2), &data2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    Gfile.set_path("../data.txt");
    Gshader.make_shader();
    unsigned int shader_program = Gshader.get_program();
    glUseProgram(shader_program);
    
    float time, something;
    unsigned int time_loc = glGetUniformLocation(shader_program, "time");
    
    while(not glfwWindowShouldClose(GWindow)) {
        // Receive Input
        glfwPollEvents();

        // Render
        time = glfwGetTime();
        something = std::tan(time + 180*RAD_TO_DEG);
        glBindVertexArray(something < -0.6? vertex_array_obj: Gvertex_array_object);

        glUniform1f(time_loc, time);
        Grenderer.render();
    }
    glDeleteProgram(shader_program);
}

int main() {
    if(glfwInit() == GLFW_FALSE) {
        printf("Failed to initialize GLFW");
        return 0;
    }

    GWindow = glfwCreateWindow( GSCR_H, GSCR_W, "Title",
                                NULL, NULL);
    glfwMakeContextCurrent(GWindow);
    glfwSetFramebufferSizeCallback(GWindow, callback::framebuffer_size);

    unsigned int err = glewInit();
    if(err != GLEW_OK) {
        printf("Failed to initialize GLFW: \n%s\n", glewGetErrorString(err));
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    loop();

    glfwTerminate();
    return 0;
}
