#include "renderer.h"

Renderer::Renderer(GLFWwindow** target_window) {
    target = target_window;
}

void Renderer::render() {
    glClearColor(31/255.0, 31/255.0, 31/255.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(*target);
}
