#include <iostream>
#include <string>
#include <cmath>

#include "glew.h"
#include "glfw3.h"

#include "input.h"
#include "shader.h"

const float RAD_TO_DEG = 57.29;
const int GSCR_H = 600;
const int GSCR_W = 600;

GLFWwindow* GWindow;
unsigned int vertex_array_object;
unsigned int index_array_object;

class Color_handler {
    public:
        struct {float r, g, b; } channel;

        Color_handler(float r, float g, float b) {
            channel = {r, g, b};
        }

        void change(float time) {
            channel.r = std::sin(time*RAD_TO_DEG*0.125);
            channel.g = std::sin((time*RAD_TO_DEG + 90*RAD_TO_DEG)*0.125);
            channel.b = std::sin((time*RAD_TO_DEG + 180*RAD_TO_DEG)*0.125);
        }
};

void loop() {
    // Hexagon
    //float data[] = {
        //0.0f, 0.0f,       0.525f, 0.0f,
        //0.25f, 0.5f,      -0.25f, 0.5f,
        //-0.525f, 0.0f,      -0.25f, -0.5f,
        //0.25f, -0.5f,
    //};
    
    float data[] {
        0.5f, -0.5f, 
        -0.5f, -0.5f,
        0.0f, 0.5f
    };

    glBindBuffer(GL_ARRAY_BUFFER, vertex_array_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int indices[] = {
        0, 1, 2,   0, 2, 3,
        0, 3, 4,   0, 4, 5,
        0, 5, 6,   0, 6, 1
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_array_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
    
    Color_handler color{255*RAD_TO_DEG, 255*RAD_TO_DEG, 255*RAD_TO_DEG};
    Shader_handler shader;
    input_handler input;

    unsigned int shader_program = shader.make_shader();
    glUseProgram(shader_program);

    int u_color_loc = glGetUniformLocation(shader_program, "u_color");
    int u_position_loc = glGetUniformLocation(shader_program, "u_position");

    while(not glfwWindowShouldClose(GWindow)) {
        // Receive Input
        glfwPollEvents();

        // Render
        glClearColor(31/255.0, 31/255.0, 31/255.0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        std::cout << color.channel.r << color.channel.g << color.channel.b << "\n";
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(GWindow);
        
        color.change(glfwGetTime());
        glUniform3f(u_color_loc, color.channel.r, color.channel.g, color.channel.b);
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

    unsigned int err = glewInit();
    if(err != GLEW_OK) {
        printf("Failed to initialize GLFW: \n%s\n", glewGetErrorString(err));
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glGenBuffers(1, &vertex_array_object);
    glGenBuffers(1, &index_array_object);

    loop();

    glfwTerminate();
    return 0;
}
