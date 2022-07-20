#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "glew.h"
#include "glfw3.h"

class Shader_handler {
    public:
        unsigned int compile_shader(unsigned int type, const char* source);
            /* Return a shader opject in succession, else return 0
                Parameters
                type    : Type of shader to be compiled
                source  : A GLSL script */

        unsigned int get_shader(std::string path);
            /* Grab a shader file in path and call compile_shader.
                Parameters
                path: path to the shader text
             */

        unsigned int make_shader();
            /* Return a program object in succession, else return 0 */
};

#endif
