#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "glew.h"
#include "glfw3.h"
#include "file.h"

class Shader_handler {
    private:
        enum class shaderType {
            VERTEX = 0,
            FRAGMENT = 1,
            NONE,
        };
        
        shaderType mode = shaderType::NONE;
        File_handler file{(int)shaderType::NONE};
        unsigned int program;

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

        void make_shader();
            /* Sets the program object in succession */

        unsigned int get_program();
            /* returns the program object */
};

#endif
