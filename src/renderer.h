#ifndef RENDERER_H
#define RENDERER_H

#include "glew.h"
#include "glfw3.h"

class Renderer {
    private:
        GLFWwindow** target;
    public:
        Renderer(GLFWwindow** target_window);
        void render();
};
#endif
