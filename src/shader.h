#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "glew.h"
#include "glfw3.h"
#include "file.h"

enum class shader_type {
    VERTEX = 0,
    FRAGMENT = 1,
    NONE,
};

class Shader {
    private:
        struct {
            unsigned int ID;
            File_handler file;
            shader_type type = shader_type::NONE;
        } shader_spec;
    public:
        Shader();

        void set_path(std::string path);
            /* Sets file.path field on shader_info  */

        void set_shader_type(shader_type type);
            /* Sets ID field on shader_info  */

        unsigned int compile_shader(unsigned int type, const char* source);
            /* Returns a shader object in succession, else return 0
                Parameters
                type    : Type of shader to be compiled
                source  : A GLSL script */

        void get_shader();
            /* Returns ID field on shader_info*/
        
        unsigned int get_ID();
            /* Returns the compiler shader's ID */
};

class Shader_program {
    private:
        unsigned int program;
        Shader shaders[(int)shader_type::NONE];
    public:
        Shader_program();
        
        void set_shader_source_path(char shader_t, std::string new_path);
            /* Calls set_path method of Shader class objects*/
            
        void send_floats(std::string target, float data[4], int data_count);
            /* Send uniform data to shader */

        void make_shader_program();
            /* Sets the program object in succession */

        void use_program();
            /* Calls glUseProgram */
        
        void list_uniforms();
            /* Lists all uniform variables and its location */

        ~Shader_program();
};

#endif
