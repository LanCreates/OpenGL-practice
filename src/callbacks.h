#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "glfw3.h"

class callback {
    public:
        static void framebuffer_size(GLFWwindow* window, int w, int h);
        static void key_received(GLFWwindow* window, int key, 
                                int scancode, int action, int mods);
};

#endif
