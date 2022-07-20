#include <iostream>

#include "callbacks.h"
#include "glfw3.h"

void callback::framebuffer_size(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);
}

void callback::key_received(GLFWwindow* window, int key, 
                            int scancode, int action, int mods) {
    if(action == GLFW_PRESS) {
        std::cout << (char)key << "\n";
    }
}
