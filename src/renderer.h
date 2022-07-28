#ifndef RENDERER_H
#define RENDERER_H

#include "glew.h"
#include "glfw3.h"

class Render_handler {
    private:
        GLFWwindow** target;
    public:
        Render_handler(GLFWwindow** target_window);
        void render();
};
#endif
