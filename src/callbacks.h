#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <iostream>
#include "glfw3.h"

namespace callback {
    void framebuffer_size(GLFWwindow* window, int w, int h);
    void key_received(GLFWwindow* window, int key, int scancode, 
                      int action, int mods);
};

#endif
